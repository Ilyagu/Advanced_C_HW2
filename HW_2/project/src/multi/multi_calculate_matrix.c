// Copyright 2021 Ilyagu Nagdimaev

#include "utils.h"

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <pthread.h>
#include <sys/wait.h>


int create_forks(const int num_forks, int *pids) {
    for (int i = 0; i != num_forks; ++i) {
        static int pid = 0;
        if ((pid = fork()) == -1)
            return -1;
        if (pid == 0) {
            return i;
        }
        pids[i] = pid;
    }
    return PARENT_PID;
}

Multi_Diogonals *create_shared_memory() {
    size_t page_size = getpagesize();

    Multi_Diogonals *shared_res = mmap(NULL, page_size, PROT_READ | PROT_WRITE,
                                                     MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (!shared_res) {
        return NULL;
    }
    shared_res->main_diagonal = 0;
    shared_res->side_diagonal = 0;
    return shared_res;
}

int calculate_multi_proc(Matrix* matrix, Multi_Diogonals* res, int number, int amount) {
    int matrix_size = matrix->size;
    int line_for_proc = (matrix_size / amount);

    int rest = (number + 1) * line_for_proc;
    if (number + 1 == amount) {
        rest = matrix->size;
    }

    for (int i = number * line_for_proc; i != rest; ++i) {
        for (int j = 0; j != matrix_size; ++j) {
            if (i == j) {
                pthread_mutex_lock(&res->mutex);
                res->main_diagonal += matrix->matrix[i][j];
                pthread_mutex_unlock(&res->mutex);
            }
            if (matrix_size == i + j + 1) {
                pthread_mutex_lock(&res->mutex);
                res->side_diagonal += matrix->matrix[i][j];
                pthread_mutex_unlock(&res->mutex);
            }
        }
    }
    exit(0);
}

int select_proc_num(size_t matrix_size) {
    if (matrix_size < 100)
        return 1;
    if (matrix_size < 1000)
        return 2;
    if (matrix_size < 5000)
        return 3;
    if (matrix_size < 10000)
        return 4;
    if (matrix_size < 20000)
        return 5;
    if (matrix_size < 100000)
        return 6;
    return 9;
}

Diagonals* calculate_matrix(Matrix* matrix) {
    if (matrix == NULL)
        return NULL;
    int num_forks = select_proc_num(matrix->size);
    int *pids = malloc(sizeof(int) * num_forks);
    for (int i = 0; i != num_forks; ++i)
        pids[i] = 0;

    Multi_Diogonals* res;

    if ((res = create_shared_memory()) == NULL) {
        free(pids);
        return NULL;
    }

    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&res->mutex, &attr);

    int process_number;
    if ((process_number = create_forks(num_forks, pids)) == -1) {
        munmap(res, getpagesize());
        free(pids);
        return NULL;
    }

    if (process_number != PARENT_PID)
        calculate_multi_proc(matrix, res, process_number, num_forks);

    for (int i = 0; i < num_forks; i++) {
        while (waitpid(pids[i], NULL, 0) > 0) {}
    }

    Diagonals* res_to_return;
    if ((res_to_return = malloc(sizeof(Diagonals))) == NULL) {
        munmap(res, getpagesize());
        free(pids);
        return NULL;
    }
    res_to_return->main_diagonal = res->main_diagonal;
    res_to_return->side_diagonal = res->side_diagonal;
    munmap(res, getpagesize());

    free(pids);
    return res_to_return;
}

