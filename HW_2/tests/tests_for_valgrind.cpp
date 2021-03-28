// Copyright 2021 Ilyagu Nagdimaev

#include <gtest/gtest.h>
#include <string>
#include <sys/mman.h>


extern "C" {
    #include "one/one_proc_utils.h"
    #include "multi/multi_process_utils.h"
}

// Сравнение результатов синхронного и многопроцессорного алгоритма
// При разных матрицах и разном количестве процессов

TEST(multi_calculate_matrix, compare_algs_matrix_size_10) {
    char file_name[] = SOURCE_DIR"/tests/size_10";

    Matrix *matrix = read_file(file_name);

    if (matrix == NULL) {
        return;
    }
    size_t size = matrix->size;
    Diagonals* res = multi_calculate_matrix(matrix);

    if (res != NULL) {
        int main = res->main_diagonal;
        int side = res->side_diagonal;
        free(res);


        Diagonals* res2 = calculate_matrix(matrix);
        free_matrix(matrix);
        int main2 = res2->main_diagonal;
        int side2 = res2->side_diagonal;
        free(res2);

        EXPECT_EQ(10, size);
        EXPECT_EQ(main2, main);
        EXPECT_EQ(side2, side);
    } else {
        free_matrix(matrix);
    }
}

TEST(multi_calculate_matrix, compare_algs_matrix_size_20) {
    char file_name[] = SOURCE_DIR"/tests/size_20";

    Matrix *matrix = read_file(file_name);

    if (matrix == NULL) {
        return;
    }
    size_t size = matrix->size;
    Diagonals* res = multi_calculate_matrix(matrix);

    if (res != NULL) {
        int main = res->main_diagonal;
        int side = res->side_diagonal;
        free(res);


        Diagonals* res2 = calculate_matrix(matrix);
        free_matrix(matrix);
        int main2 = res2->main_diagonal;
        int side2 = res2->side_diagonal;
        free(res2);

        EXPECT_EQ(20, size);
        EXPECT_EQ(main2, main);
        EXPECT_EQ(side2, side);
    } else {
        free_matrix(matrix);
    }
}

TEST(multi_calculate_matrix, compare_algs_matrix_size_30) {
    char file_name[] = SOURCE_DIR"/tests/size_30";

    Matrix *matrix = read_file(file_name);

    if (matrix == NULL) {
        return;
    }
    size_t size = matrix->size;
    Diagonals* res = multi_calculate_matrix(matrix);

    if (res != NULL) {
        int main = res->main_diagonal;
        int side = res->side_diagonal;
        free(res);


        Diagonals* res2 = calculate_matrix(matrix);
        free_matrix(matrix);
        int main2 = res2->main_diagonal;
        int side2 = res2->side_diagonal;
        free(res2);

        EXPECT_EQ(30, size);
        EXPECT_EQ(main2, main);
        EXPECT_EQ(side2, side);
    } else {
        free_matrix(matrix);
    }
}

TEST(multi_calculate_matrix, compare_algs_matrix_size_40) {
    char file_name[] = SOURCE_DIR"/tests/size_40";

    Matrix *matrix = read_file(file_name);

    if (matrix == NULL) {
        return;
    }
    size_t size = matrix->size;
    Diagonals* res = multi_calculate_matrix(matrix);

    if (res != NULL) {
        int main = res->main_diagonal;
        int side = res->side_diagonal;
        free(res);


        Diagonals* res2 = calculate_matrix(matrix);
        free_matrix(matrix);
        int main2 = res2->main_diagonal;
        int side2 = res2->side_diagonal;
        free(res2);

        EXPECT_EQ(40, size);
        EXPECT_EQ(main2, main);
        EXPECT_EQ(side2, side);
    } else {
        free_matrix(matrix);
    }
}

TEST(multi_calculate_matrix, compare_algs_matrix_size_50) {
    char file_name[] = SOURCE_DIR"/tests/size_50";

    Matrix *matrix = read_file(file_name);

    if (matrix == NULL) {
        return;
    }
    size_t size = matrix->size;
    Diagonals* res = multi_calculate_matrix(matrix);

    if (res != NULL) {
        int main = res->main_diagonal;
        int side = res->side_diagonal;
        free(res);

        Diagonals* res2 = calculate_matrix(matrix);
        free_matrix(matrix);
        int main2 = res2->main_diagonal;
        int side2 = res2->side_diagonal;
        free(res2);

        EXPECT_EQ(50, size);
        EXPECT_EQ(main2, main);
        EXPECT_EQ(side2, side);
    } else {
        free_matrix(matrix);
    }
}

TEST(multi_calculate_matrix, compare_algs_matrix_size_60) {
    char file_name[] = SOURCE_DIR"/tests/size_60";

    Matrix *matrix = read_file(file_name);

    if (matrix == NULL) {
        return;
    }
    size_t size = matrix->size;
    Diagonals* res = multi_calculate_matrix(matrix);

    if (res != NULL) {
        int main = res->main_diagonal;
        int side = res->side_diagonal;
        free(res);


        Diagonals* res2 = calculate_matrix(matrix);
        free_matrix(matrix);
        int main2 = res2->main_diagonal;
        int side2 = res2->side_diagonal;
        free(res2);

        EXPECT_EQ(60, size);
        EXPECT_EQ(main2, main);
        EXPECT_EQ(side2, side);
    } else {
        free_matrix(matrix);
    }
}

TEST(multi_calculate_matrix, compare_algs_matrix_size_100) {
    char file_name[] = SOURCE_DIR"/tests/size_100";

    Matrix *matrix = read_file(file_name);

    if (matrix == NULL) {
        return;
    }
    size_t size = matrix->size;
    Diagonals* res = multi_calculate_matrix(matrix);

        if (res != NULL) {
        int main = res->main_diagonal;
        int side = res->side_diagonal;
        free(res);


        Diagonals* res2 = calculate_matrix(matrix);
        free_matrix(matrix);
        int main2 = res2->main_diagonal;
        int side2 = res2->side_diagonal;
        free(res2);

        EXPECT_EQ(100, size);
        EXPECT_EQ(main2, main);
        EXPECT_EQ(side2, side);
    } else {
            free_matrix(matrix);
        }
}

TEST(multi_calculate_matrix, compare_algs_matrix_size_200) {
    char file_name[] = SOURCE_DIR"/tests/size_200";

    Matrix *matrix = read_file(file_name);

    if (matrix == NULL) {
        return;
    }
    size_t size = matrix->size;
    Diagonals* res = multi_calculate_matrix(matrix);

    if (res != NULL) {
        int main = res->main_diagonal;
        int side = res->side_diagonal;
        free(res);


        Diagonals* res2 = calculate_matrix(matrix);
        free_matrix(matrix);
        int main2 = res2->main_diagonal;
        int side2 = res2->side_diagonal;
        free(res2);

        EXPECT_EQ(200, size);
        EXPECT_EQ(main2, main);
        EXPECT_EQ(side2, side);
    } else {
        free_matrix(matrix);
    }
}

TEST(multi_calculate_matrix, compare_algs_matrix_size_500) {
    char file_name[] = SOURCE_DIR"/tests/size_500";

    Matrix *matrix = read_file(file_name);

    if (matrix == NULL) {
        return;
    }
    size_t size = matrix->size;
    Diagonals* res = multi_calculate_matrix(matrix);

    if (res != NULL) {
        int main = res->main_diagonal;
        int side = res->side_diagonal;
        free(res);

        Diagonals* res2 = calculate_matrix(matrix);
        free_matrix(matrix);
        int main2 = res2->main_diagonal;
        int side2 = res2->side_diagonal;
        free(res2);
        EXPECT_EQ(500, size);
        EXPECT_EQ(main2, main);
        EXPECT_EQ(side2, side);
    } else {
        free_matrix(matrix);
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
