// Copyright 2021 Ilyagu Nagdimaev

#ifndef HW_2_PROJECT_INCLUDE_MULTI_MULTI_PROCESS_UTILS_H_
#define HW_2_PROJECT_INCLUDE_MULTI_MULTI_PROCESS_UTILS_H_

#include <pthread.h>
#include "utils.h"

# define PARENT_PID -5

typedef struct {
    int main_diagonal;
    int side_diagonal;
    pthread_mutex_t mutex;
} Multi_Diogonals;

Diagonals* multi_calculate_matrix(Matrix* matrix);

#endif  // HW_2_PROJECT_INCLUDE_MULTI_MULTI_PROCESS_UTILS_H_
