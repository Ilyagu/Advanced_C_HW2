// Copyright 2021 Ilyagu Nagdimaev

#include <gtest/gtest.h>
#include <string>
#include <sys/mman.h>
#include <dlfcn.h>


extern "C" {
    #include "utils.h"
}

TEST(read_file, reading_from_file_test2) {
    Matrix* matrix = read_file(SOURCE_DIR"/tests/tes");
    if (matrix != NULL)
        free_matrix(matrix);
}

//
// Тест чтения из файлов
//

TEST(read_file, reading_from_file_test3) {
    Matrix* matrix = read_file(SOURCE_DIR"/tests/test2");
    if (matrix != NULL) {
        Diagonals* res = calculate_matrix(matrix);
        size_t size = matrix->size;
        int main = res->main_diagonal;
        int side = res->side_diagonal;
        free(res);
        EXPECT_EQ(2, size);
        EXPECT_EQ(5, main);
        EXPECT_EQ(5, side);
    }
}

//
// Тест синхронного алгоритма
//

TEST(calculate_matrix, calculate_matrix_one_proc2) {
    Matrix* matrix = read_file(SOURCE_DIR"/tests/test1");

    if (matrix != NULL) {
        Diagonals* res = calculate_matrix(matrix);
        size_t size = matrix->size;
        int main = res->main_diagonal;
        int side = res->side_diagonal;
        free(res);

        free_matrix(matrix);
        EXPECT_EQ(4, size);
        EXPECT_EQ(15, main);
        EXPECT_EQ(16, side);
    }
}


//
// Тест многопроцессорного алгоритма
//
TEST(multi_calculate_matrix, test_1_multi_calculate_matrix) {
    char file_name[] = SOURCE_DIR"/tests/5";

    Matrix *matrix = read_file(file_name);

    if (matrix == NULL) {
        return;
    }

    void *handle = dlopen("./libmulti_compute_matrix.so", RTLD_LAZY);
    if (!handle) {
        return;
    }

    int (*funcpt)();
    *reinterpret_cast<void **>(&funcpt) = dlsym(handle, "calculate_matrix");

    Diagonals* res = calculate_matrix(matrix);

    dlclose(handle);

    if (res != NULL) {
        size_t size = matrix->size;
        int main = res->main_diagonal;
        int side = res->side_diagonal;
        free(res);
        EXPECT_EQ(5, size);
        EXPECT_EQ(32, main);
        EXPECT_EQ(14, side);
    }
}


TEST(multi_calculate_matrix, test_4_multi_calculate_matrix) {
    char file_name[] = SOURCE_DIR"/tests/7";

    Matrix *matrix = read_file(file_name);

    if (matrix == NULL) {
        return;
    }
    size_t size = matrix->size;

    void *handle = dlopen("./libmulti_compute_matrix.so", RTLD_LAZY);
    if (!handle) {
        return;
    }

    int (*funcpt)();
    *reinterpret_cast<void **>(&funcpt) = dlsym(handle, "calculate_matrix");

    Diagonals* res = calculate_matrix(matrix);

    dlclose(handle);

        if (res != NULL) {
        int main = res->main_diagonal;
        int side = res->side_diagonal;
        free(res);

        EXPECT_EQ(7, size);
        EXPECT_EQ(24, main);
        EXPECT_EQ(42, side);
    }
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

    void *handle = dlopen("./libmulti_compute_matrix.so", RTLD_LAZY);
    if (!handle) {
        return;
    }

    int (*funcpt)();
    *reinterpret_cast<void **>(&funcpt) = dlsym(handle, "calculate_matrix");

    Diagonals* res = calculate_matrix(matrix);

    dlclose(handle);
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

TEST(multi_calculate_matrix, compare_algs_matrix_size_100) {
    char file_name[] = SOURCE_DIR"/tests/size_100";

    Matrix *matrix = read_file(file_name);

    if (matrix == NULL) {
        return;
    }
    size_t size = matrix->size;

    void *handle = dlopen("./libmulti_compute_matrix.so", RTLD_LAZY);
    if (!handle) {
    return;
    }

    int (*funcpt)();
    *reinterpret_cast<void **>(&funcpt) = dlsym(handle, "calculate_matrix");

    Diagonals* res = calculate_matrix(matrix);

    dlclose(handle);

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

    void *handle = dlopen("./libmulti_compute_matrix.so", RTLD_LAZY);
    if (!handle) {
        return;
    }

    int (*funcpt)();
    *reinterpret_cast<void **>(&funcpt) = dlsym(handle, "calculate_matrix");

    Diagonals* res = calculate_matrix(matrix);

    dlclose(handle);

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

    void *handle = dlopen("./libmulti_compute_matrix.so", RTLD_LAZY);
    if (!handle) {
        return;
    }

    int (*funcpt)();
    *reinterpret_cast<void **>(&funcpt) = dlsym(handle, "calculate_matrix");

    Diagonals* res = calculate_matrix(matrix);

    dlclose(handle);

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

TEST(multi_calculate_matrix, compare_algs_matrix_size_600) {
    char file_name[] = SOURCE_DIR"/tests/size_600";

    Matrix *matrix = read_file(file_name);

    if (matrix == NULL) {
        return;
    }
    size_t size = matrix->size;

    void *handle = dlopen("./libmulti_compute_matrix.so", RTLD_LAZY);
    if (!handle) {
        return;
    }

    int (*funcpt)();
    *reinterpret_cast<void **>(&funcpt) = dlsym(handle, "calculate_matrix");

    Diagonals* res = calculate_matrix(matrix);

    dlclose(handle);

    if (res != NULL) {
        int main = res->main_diagonal;
        int side = res->side_diagonal;
        free(res);


        Diagonals* res2 = calculate_matrix(matrix);
        free_matrix(matrix);
        int main2 = res2->main_diagonal;
        int side2 = res2->side_diagonal;
        free(res2);

        EXPECT_EQ(600, size);
        EXPECT_EQ(main2, main);
        EXPECT_EQ(side2, side);
    } else {
        free_matrix(matrix);
    }
}

TEST(multi_calculate_matrix, compare_algs_matrix_size_1000) {
    char file_name[] = SOURCE_DIR"/tests/size_1000";

    Matrix *matrix = read_file(file_name);

    if (matrix == NULL) {
        return;
    }
    size_t size = matrix->size;

    void *handle = dlopen("./libmulti_compute_matrix.so", RTLD_LAZY);
    if (!handle) {
        return;
    }

    int (*funcpt)();
    *reinterpret_cast<void **>(&funcpt) = dlsym(handle, "calculate_matrix");

    Diagonals* res = calculate_matrix(matrix);

    dlclose(handle);

    if (res != NULL) {
        int main = res->main_diagonal;
        int side = res->side_diagonal;
        free(res);


        Diagonals* res2 = calculate_matrix(matrix);
        free_matrix(matrix);
        int main2 = res2->main_diagonal;
        int side2 = res2->side_diagonal;
        free(res2);

        EXPECT_EQ(1000, size);
        EXPECT_EQ(main2, main);
        EXPECT_EQ(side2, side);
    } else {
        free_matrix(matrix);
    }
}

TEST(multi_calculate_matrix, compare_algs_matrix_size_2000) {
    char file_name[] = SOURCE_DIR"/tests/size_2000";

    Matrix *matrix = read_file(file_name);

    if (matrix == NULL) {
        return;
    }
    size_t size = matrix->size;

    void *handle = dlopen("./libmulti_compute_matrix.so", RTLD_LAZY);
    if (!handle) {
        return;
    }

    int (*funcpt)();
    *reinterpret_cast<void **>(&funcpt) = dlsym(handle, "calculate_matrix");

    Diagonals* res = calculate_matrix(matrix);

    dlclose(handle);
    if (res != NULL) {
        int main = res->main_diagonal;
        int side = res->side_diagonal;
        free(res);


        Diagonals* res2 = calculate_matrix(matrix);
        free_matrix(matrix);
        int main2 = res2->main_diagonal;
        int side2 = res2->side_diagonal;
        free(res2);

        EXPECT_EQ(2000, size);
        EXPECT_EQ(main2, main);
        EXPECT_EQ(side2, side);
    } else {
        free_matrix(matrix);
    }
}

TEST(multi_calculate_matrix, compare_algs_matrix_size_5000) {
    char file_name[] = SOURCE_DIR"/tests/size_5000";

    Matrix *matrix = read_file(file_name);

    if (matrix == NULL) {
        return;
    }
    size_t size = matrix->size;

    void *handle = dlopen("./libmulti_compute_matrix.so", RTLD_LAZY);
    if (!handle) {
        return;
    }

    int (*funcpt)();
    *reinterpret_cast<void **>(&funcpt) = dlsym(handle, "calculate_matrix");

    Diagonals* res = calculate_matrix(matrix);

    dlclose(handle);

    if (res != NULL) {
        int main = res->main_diagonal;
        int side = res->side_diagonal;
        free(res);


        Diagonals* res2 = calculate_matrix(matrix);
        free_matrix(matrix);
        int main2 = res2->main_diagonal;
        int side2 = res2->side_diagonal;
        free(res2);

        EXPECT_EQ(5000, size);
        EXPECT_EQ(main2, main);
        EXPECT_EQ(side2, side);
    } else {
        free_matrix(matrix);
    }
}

TEST(multi_calculate_matrix, compare_algs_matrix_size_10000) {
    char file_name[] = SOURCE_DIR"/tests/size_10000";

    Matrix *matrix = read_file(file_name);

    if (matrix == NULL) {
        return;
    }
    size_t size = matrix->size;

    void *handle = dlopen("./libmulti_compute_matrix.so", RTLD_LAZY);
    if (!handle) {
        return;
    }

    int (*funcpt)();
    *reinterpret_cast<void **>(&funcpt) = dlsym(handle, "calculate_matrix");

    Diagonals* res = calculate_matrix(matrix);

    dlclose(handle);

    if (res != NULL) {
        int main = res->main_diagonal;
        int side = res->side_diagonal;
        free(res);

    Diagonals* res2 = calculate_matrix(matrix);
        free_matrix(matrix);
        int main2 = res2->main_diagonal;
        int side2 = res2->side_diagonal;
        free(res2);

        EXPECT_EQ(10000, size);
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
