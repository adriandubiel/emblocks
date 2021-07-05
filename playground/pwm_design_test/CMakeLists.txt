cmake_minimum_required(VERSION 3.12)
project(PWMTEST)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(pwm ./src/main.cpp)

target_include_directories(pwm PRIVATE ./src/controller)
target_include_directories(pwm PRIVATE ../../components/pwm/tl)
