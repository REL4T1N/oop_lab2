cmake_minimum_required(VERSION 3.14)
project(lab2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Установка Google Test через FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)
FetchContent_MakeAvailable(googletest)

# Основная программа
add_executable(lab2 main.cpp src/lab2.cpp)
target_include_directories(lab2 PRIVATE include)

# Тесты
add_executable(tests tests/main_test.cpp tests/eleven_test.cpp src/lab2.cpp)
target_include_directories(tests PRIVATE include)
target_link_libraries(tests gtest gtest_main)

# Добавление тестов в CTest
enable_testing()
add_test(NAME lab2_tests COMMAND tests)