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

diagonals *create_shared_memory(const int num_forks) {
    size_t page_size = getpagesize();

    diagonals *shared_res = mmap(NULL, page_size, PROT_READ | PROT_WRITE,
                                                     MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (!shared_res) {
        return NULL;
    }
    for (int i  = 0; i < num_forks; i++) {
        shared_res[i].main_diagonal = 0;
        shared_res[i].side_diagonal = 0;
    }
    return shared_res;
}

int calculate_multi_proc(matrix_type* matrix, diagonals* arr_res, int number, int amount) {
    int matrix_size = matrix->size;
    int line_for_proc = (matrix_size / amount);

    int rest = (number + 1) * line_for_proc;
    if (number + 1 == amount) {
        rest = matrix->size;
    }

    for (int i = number * line_for_proc; i != rest; ++i) {
        for (int j = 0; j != matrix_size; ++j) {
            if (i == j) {
                 arr_res[number].main_diagonal += matrix->matrix[i][j];
            }
            if (matrix_size == i + j + 1) {
                arr_res[number].side_diagonal += matrix->matrix[i][j];
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
    return 7;
}

diagonals* calculate_matrix(matrix_type* matrix) {
    if (matrix == NULL)
        return NULL;
//    int num_forks = select_proc_num(matrix->size);
    int num_forks = sysconf(_SC_NPROCESSORS_ONLN);
    int *pids = malloc(sizeof(int) * num_forks);
    for (int i = 0; i != num_forks; ++i)
        pids[i] = 0;

    diagonals* res = NULL;
    diagonals* arr_res;

    if ((arr_res = create_shared_memory(num_forks)) == NULL) {
        free(pids);
        return NULL;
    }

    int process_number;
    if ((process_number = create_forks(num_forks, pids)) == -1) {
        munmap(arr_res, getpagesize());
        free(pids);
        return NULL;
    }

    if (process_number != PARENT_PID)
        calculate_multi_proc(matrix, arr_res, process_number, num_forks);

    for (int i = 0; i < num_forks; i++) {
        while (waitpid(pids[i], NULL, 0) > 0) {}
    }

    for (int i = 0; i < num_forks; i++) {
        res->main_diagonal+=arr_res[i].main_diagonal;
        res->side_diagonal+=arr_res[i].side_diagonal;
    }

    munmap(arr_res, getpagesize());

    free(arr_res);
    free(pids);
    return res;
}

