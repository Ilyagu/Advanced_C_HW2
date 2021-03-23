#include_directories("${PROJECT_SOURCE_DIR}/include")
#
#file(GLOB tests "${PROJECT_SOURCE_DIR}/test.cpp")
#
#foreach(file ${tests})
#    set(name)
#    get_filename_component(name ${file} NAME_WE)
#    add_executable("${name}_tests"
#            ${sources}
#            ${file}
#            "${PROJECT_SOURCE_DIR}/test/main.cpp")
#    target_link_libraries("${name}_tests" gtest_main)
#    add_test(NAME ${name} COMMAND "${name}_tests")
#endforeach()
#
##include_directories("${PROJECT_SOURCE_DIR}/include")
##
##file(GLOB tests "${PROJECT_SOURCE_DIR}/tests_for_valgrind.cpp")
##
##foreach(file ${tests})
##    set(name)
##    get_filename_component(name ${file} NAME_WE)
##    add_executable("${name}_tests"
##            ${sources}
##            ${file}
##            "${PROJECT_SOURCE_DIR}/test/main.cpp")
##    target_link_libraries("${name}_tests" gtest_main)
##    add_test(NAME ${name} COMMAND "${name}_tests")
##endforeach()
##file(GLOB sources
##        "${PROJECT_SOURCE_DIR}/src/*.c")
##
##add_executable(TEST
##        tests/test.cpp)
##
##target_include_directories(TEST PUBLIC ${INC_DIR})
##
##target_link_libraries(TEST ${GTEST_LIBRARIES} Threads::Threads pthread compute_matrix compute_matrix_parallel)
##
##add_executable(TEST_VALGRIND
##        tests/tests_for_valgrind.cpp)
##
##target_include_directories(TEST_VALGRIND PUBLIC ${INC_DIR})
##
##target_link_libraries(TEST_VALGRIND ${GTEST_LIBRARIES} Threads::Threads pthread compute_matrix compute_matrix_parallel)
##
##add_test(NAME TEST_ONE COMMAND tests1)
##add_test(NAME TEST_VALGRIND COMMAND tests2)