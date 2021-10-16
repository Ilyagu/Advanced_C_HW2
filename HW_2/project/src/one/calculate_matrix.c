// Copyright 2021 Ilyagu Nagdimaev

#include "utils.h"
#include <stdlib.h>

diagonals* calculate_matrix(matrix_type* matrix) {
    if (matrix == NULL)
        return NULL;

    diagonals* res;

    if ((res = malloc(sizeof(diagonals))) == NULL)
        return NULL;
    int n = matrix->size;

    res->main_diagonal = 0;
    res->side_diagonal = 0;

    for (int i = 0; i != n; ++i) {
        for (int j = 0; j != n; ++j) {
            if (i == j)
                res->main_diagonal += matrix->matrix[i][j];
            if (n == i + j + 1)
                res->side_diagonal += matrix->matrix[i][j];
        }
    }

    return res;
}

