#include "api.h"
#include <random>

int main() 
{
    std::random_device rd; // seeding
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> nums(-10, 10);

    MatType *A = (MatType*)malloc(sizeof(MatType));
    VecType *b = (VecType*)malloc(sizeof(VecType));

    do
    {
        // initialization
        for(int r = 0; r < DIM; r++) {
            for(int c = 0; c < DIM; c++) {
                (*A)(r,c) = nums(mt);
            }
            (*b)(r) = nums(mt);
        }
    } while (!A->fullPivLu().isInvertible()); // Checking Invertibility

    VecType x = A->partialPivLu().solve(*b);
    printf("\n");
    printf("[Host]");
    print_solution(x,DIM);

    #pragma acc data copyin(A,b)
    {
        #pragma acc kernels present(A,b)
        {
            solve_openacc(A, b, DIM);
        }

        #pragma acc host_data use_device(A,b)
        {
            solve_cuda(A, b, DIM);
        }
    }

    return 0;
}
