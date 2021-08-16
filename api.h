#pragma once

#include <stdio.h>
#include "Eigen/Dense"
#include "Eigen/LU"

// for DIM 17 and above : stack size issues
#define DIM 16

using namespace Eigen;
using MatType = Matrix<double, DIM, DIM>;
using VecType = Matrix<double, DIM, 1>;

void print_solution(VecType, int);

void solve_cuda(MatType*, VecType*, int);

#pragma acc routine seq
void solve_openacc(MatType*, VecType*, int);
