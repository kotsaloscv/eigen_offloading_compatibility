# cmake .. -DCMAKE_CXX_COMPILER=nvc++ -DCMAKE_CUDA_COMPILER=nvcc

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(eigen_openacc_comp LANGUAGES CXX CUDA)

set(CUDA_FLAGS --expt-relaxed-constexpr)
set(OPENACC_FLAGS -DEIGEN_DONT_VECTORIZE=1 -acc)

include_directories("eigen")

# WORKAROUND - enable cuda dynamic linking:
# https://gitlab.kitware.com/cmake/cmake/-/issues/17559
#
# The cudart_static gives a segmentation fault,
# therefore I used this workaround.
#
# CMake 3.17 and above (replaces the workaround)
set(CMAKE_CUDA_RUNTIME_LIBRARY Shared)
# ToDo: to remove this workaround
if ( CMAKE_CUDA_HOST_IMPLICIT_LINK_LIBRARIES )
        list( REMOVE_ITEM CMAKE_CUDA_HOST_IMPLICIT_LINK_LIBRARIES "cudart_static" )
        list( REMOVE_ITEM CMAKE_CUDA_HOST_IMPLICIT_LINK_LIBRARIES "cudadevrt" )
        list( APPEND CMAKE_CUDA_HOST_IMPLICIT_LINK_LIBRARIES "cudart" )

endif()
if ( CMAKE_CUDA_IMPLICIT_LINK_LIBRARIES )
        list( REMOVE_ITEM CMAKE_CUDA_IMPLICIT_LINK_LIBRARIES "cudart_static" )
        list( REMOVE_ITEM CMAKE_CUDA_IMPLICIT_LINK_LIBRARIES "cudadevrt" )
        list( APPEND CMAKE_CUDA_IMPLICIT_LINK_LIBRARIES "cudart" )
endif()

add_library(api OBJECT api.cu)
set_target_properties(api PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
target_compile_options(api PUBLIC $<$<COMPILE_LANGUAGE:CUDA>:${CUDA_FLAGS}>)

add_executable(eigen_openacc eigen.cpp)
target_link_libraries(eigen_openacc api)
target_compile_options(eigen_openacc PUBLIC $<$<COMPILE_LANGUAGE:CXX>:${OPENACC_FLAGS}>)
target_link_options(eigen_openacc PUBLIC $<$<COMPILE_LANGUAGE:CXX>:${OPENACC_FLAGS} -cuda>)
