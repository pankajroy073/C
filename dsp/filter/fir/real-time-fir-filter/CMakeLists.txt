cmake_minimum_required(VERSION 3.13)
project(fir-filter C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(fir STATIC src/fir.c)
target_include_directories(fir PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(realtime_stdin examples/realtime_stdin.c)
target_link_libraries(realtime_stdin PRIVATE fir)

enable_testing()
add_executable(test_fir tests/test_fir.c)
target_link_libraries(test_fir PRIVATE fir)
add_test(NAME fir_tests COMMAND test_fir)
