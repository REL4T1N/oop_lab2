cmake_minimum_required(VERSION 3.10)
project(lab2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Добавление опций компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)
FetchContent_MakeAvailable(googletest)


add_library(lab2_lib src/lab2.cpp)
add_executable(lab2 main.cpp)

target_link_libraries(lab2 PRIVATE lab2_lib)

# Добавление тестов
enable_testing()

add_executable(lab2_tests tests/lab2_tests.cpp)
target_link_libraries(lab2_tests lab2_lib gtest_main)

# Добавление тестов в тестовый набор
add_test(NAME lab2Tests COMMAND lab2_tests)