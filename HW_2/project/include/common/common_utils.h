// Copyright 2021 Ilyagu Nagdimaev

#ifndef ADVANCED_C_HW2_COMMON_UTILS_H
#define ADVANCED_C_HW2_COMMON_UTILS_H

#include <pthread.h>
#include <stdio.h>

#define MAX_FILE_NAME 50
#define MSECONDS 1000
#define PARENT_PID -5
#define ERROR "ERROR"

typedef struct {
    int main_diagonal;
    int side_diagonal;
} Diagonals;

typedef struct {
    size_t size;
    int** matrix;
} Matrix;


Matrix* read_file(const char* file_name);
void free_matrix(Matrix* matrix);

#endif //ADVANCED_C_HW2_COMMON_UTILS_H
