cmake_minimum_required(VERSION 2.8)

project(domain)

# grab the implementation / header files
file(GLOB DOMAIN_SRCS src/*.cpp src/*.h)

# add an executable with the source files
add_executable(domain ${DOMAIN_SRCS})

# link the shared hifi library
include(../LinkHifiShared.cmake)
link_hifi_shared_library(domain)