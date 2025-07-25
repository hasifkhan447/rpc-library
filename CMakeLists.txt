cmake_minimum_required(VERSION 3.11.0)
project(rpc)

add_library(rpc_lib STATIC src/rpc.c include/rpc.h)
# target_sources(src/rpc.c)

# target_include_directories(lib./include)
