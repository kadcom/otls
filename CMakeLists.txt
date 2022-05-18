cmake_minimum_required(VERSION 3.5.1)
project(binfetch)

set(SOURCES main.c tls_debug.c) 

add_executable(binfetch ${SOURCES})

if (WIN32)
  target_link_libraries(binfetch PUBLIC ws2_32)
endif (WIN32)

add_subdirectory(mbedtls-3.1.0)

target_link_libraries(binfetch
        PUBLIC mbedtls
               mbedcrypto
               mbedx509)

target_include_directories(binfetch PUBLIC "${MBEDTLS_DIR}/include")
