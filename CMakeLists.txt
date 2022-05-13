cmake_minimum_required(VERSION 3.20.0)
project(binfetch)

set (SOURCES main.c) 

add_executable(binfetch ${SOURCES})

if (WIN32)
  target_link_libraries(binfetch ws2_32)
endif (WIN32)

# add_subdirectory(mbedtls-3.1.0)
