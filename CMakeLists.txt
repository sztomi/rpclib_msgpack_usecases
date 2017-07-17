project(rpclib_msgpack_usecases)
cmake_minimum_required(VERSION 3.6)

add_executable(test_msgpack src/main.cpp)
target_include_directories(test_msgpack PRIVATE include)
