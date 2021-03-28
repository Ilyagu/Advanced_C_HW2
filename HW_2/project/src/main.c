// Copyright 2021 Ilyagu Nagdimaev

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <time.h>
#include <sys/time.h>
#include "one/one_proc_utils.h"
#include "multi/multi_process_utils.h"


int main(int argc, char **argv) {
    char file_name[50] = {};
    if (argc > 1)
        strcpy(file_name, argv[1]);
    else
    if (scanf("%49s", file_name) == 0)
        return 0;

    Matrix* matrix;

    matrix = read_file(file_name);
    if (matrix == NULL)
        return 0;
    struct  timeval start;
    gettimeofday(&start, NULL);
    Diagonals* one_proc_res = calculate_matrix(matrix);

    if (one_proc_res == NULL) {
        free_matrix(matrix);
        return 0;
    }
    struct  timeval end;
    gettimeofday(&end, NULL);
    long time = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000;

    printf("Результат вычислений синхронного алгоритма:%c", '\n');
    printf("Сумма главной диагонали = %d\n", one_proc_res->main_diagonal);
    printf("Сумма побочной диагонали = %d\n", one_proc_res->side_diagonal);
    printf("Время однопроцессорной версии: %ld миллисекунд\n", time);

    gettimeofday(&start, NULL);
    Diagonals* multi_proc_res = multi_calculate_matrix(matrix);
    gettimeofday(&end, NULL);

    if (multi_proc_res == NULL) {
        free(one_proc_res);
        free_matrix(matrix);
        return 0;
    }
    time = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000;
    printf("Результат вычислений много-процессорного алгоритма:%c", '\n');
    printf("Сумма главной диагонали = %d\n", multi_proc_res->main_diagonal);
    printf("Сумма побочной диагонали = %d\n", multi_proc_res->side_diagonal);
    printf("Время многопроцессорной версии: %ld миллисекунд\n", time);


    if (multi_proc_res->main_diagonal == one_proc_res->main_diagonal &&
        multi_proc_res->side_diagonal == one_proc_res->side_diagonal)
        printf("Результаты вычислений совпадают%c", '\n');
    else
        printf("Результаты вычислений не совпадают%c", '\n');

    free(one_proc_res);
    free(multi_proc_res);
    free_matrix(matrix);
    return 0;
}
