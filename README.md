# eigen_openacc_compatibility

To test:

1. `git clone --branch v3.5-alpha.1 https://github.com/BlueBrain/eigen.git`
2. `mkdir build && cd build`
3. `cmake .. -DCMAKE_CXX_COMPILER=nvc++ -DCMAKE_CUDA_COMPILER=nvcc && make -j`
4. `./eigen_openacc`
