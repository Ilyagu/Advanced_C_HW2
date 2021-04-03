cmake_minimum_required(VERSION 3.9.2)
project(HW_2 C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_FLAGS "-g -Wall -Werror -Wextra -O3 -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "-g -Wall -O3 -fprofile-arcs -ftest-coverage")

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)



set(DIR ${CMAKE_CURRENT_SOURCE_DIR})
add_definitions(-DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

set(INC_DIR ${DIR}/project/include)

set(SRC_DIR ${DIR}/project/src)

set(TESTS_DIR ${DIR}/tests)

include_directories("${GTEST_INCLUDE_DIRS}")
include_directories(project/include)

add_library(compute_matrix STATIC
#        ${INC_DIR}/common/common_utils.h
        ${SRC_DIR}/utils.c
#        ${INC_DIR}/gen_utils.h
#        ${INC_DIR}/utils.h
        ${SRC_DIR}/one/calculate_matrix.c)

add_library(multi_compute_matrix MODULE
#        ${INC_DIR}/common/common_utils.h
        ${SRC_DIR}/utils.c
#        ${INC_DIR}/gen_utils.h
#        ${INC_DIR}/utils.h
        ${SRC_DIR}/multi/multi_calculate_matrix.c)

add_executable(TEST
        tests/test.cpp)

target_include_directories(TEST PUBLIC ${INC_DIR})

target_link_libraries(TEST ${GTEST_LIBRARIES} Threads::Threads pthread -ldl compute_matrix)

add_executable(TEST_VALGRIND
        tests/tests_for_valgrind.cpp)

target_include_directories(TEST_VALGRIND PUBLIC ${INC_DIR})

target_link_libraries(TEST_VALGRIND ${GTEST_LIBRARIES} Threads::Threads pthread -ldl compute_matrix)


enable_testing()
add_test(NAME TEST_ONE COMMAND tests1)
add_test(NAME TEST_VALGRIND COMMAND tests2)


add_executable(HW_2
        ${SRC_DIR}/main.c)

target_link_libraries(HW_2 Threads::Threads pthread -ldl compute_matrix)

target_include_directories(HW_2 PUBLIC ${INC_DIR})

add_executable(TEST_MAIN
        ${SRC_DIR}/test_main.c)

target_link_libraries(TEST_MAIN Threads::Threads pthread -ldl compute_matrix)

target_include_directories(TEST_MAIN PUBLIC ${INC_DIR})