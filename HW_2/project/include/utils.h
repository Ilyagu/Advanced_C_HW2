// Copytight 2021 Ilyagu Nagdimaev

#ifndef HW_2_UTILS_H
#define HW_2_UTILS_H

#include <stdio.h>

typedef struct {
    size_t size;
    int** matrix;
} Matrix;

typedef struct {
    int main_diagonal;
    int side_diagonal;
} Diagonals;

Matrix* read_file(const char* file_name);
void free_matrix(Matrix* matrix);

#endif //HW_2_UTILS_H
