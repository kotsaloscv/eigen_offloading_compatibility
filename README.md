# eigen_openacc_compatibility

To test:

1. `git clone -b cms/master/09d7122468fb9b9adf813cf32167ab212511c4d8 https://github.com/cms-externals/eigen-git-mirror.git eigen`
2. `mkdir build && cd build`
3. `cmake .. -DCMAKE_CXX_COMPILER=nvc++ -DCMAKE_CUDA_COMPILER=nvcc && make -j`
4. `./eigen_openacc`
