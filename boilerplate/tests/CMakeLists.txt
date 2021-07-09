cmake_minimum_required(VERSION 3.14)
project(boilerplate)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(hello_test
    hello_test.cpp
)

target_link_libraries(hello_test
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)

