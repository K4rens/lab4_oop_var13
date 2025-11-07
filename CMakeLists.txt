cmake_minimum_required(VERSION 3.10)
project(laba4_oop)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(main 
    main.cpp
)

target_include_directories(main PRIVATE include)

add_executable(tests
    tests/test_main.cpp
)

target_include_directories(tests PRIVATE include)
target_link_libraries(tests gtest_main gmock)

include(GoogleTest)
gtest_discover_tests(tests)
