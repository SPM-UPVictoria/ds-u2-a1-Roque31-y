cmake_minimum_required(VERSION 3.10)
project(TransformacionesDiscretas LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Directorio de headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Ejecutable
add_executable(transformaciones src/main.cpp)

# Directorio de salida
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
