cmake_minimum_required(VERSION 3.9)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(LRUCache)

enable_testing()

# Prevent overriding the parent project's compiler/linker settings on Windows.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(install_gtest OFF)
set(install_gmock OFF)
set(build_gmock OFF)

# This project is tested using GoogleTest.
add_subdirectory("third_party/googletest")

add_executable(LRUCacheTest lru_cache_test.cc)
target_link_libraries(LRUCacheTest gtest_main)
