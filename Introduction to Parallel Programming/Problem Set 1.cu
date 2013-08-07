#include "reference_calc.cpp"
#include "utils.h"
#include <stdio.h>

__global__
void rgba_to_greyscale(const uchar4* const rgbaImage,
                       unsigned char* const greyImage,
                       int numRows, int numCols)
{
    int x = blockIdx.x;
    int y = threadIdx.x;
    int idx = x * numCols + y;
    float r = rgbaImage[idx].x;
    float g = rgbaImage[idx].y;
    float b = rgbaImage[idx].z;
    float i = 0.299f * r + 0.587f * g + 0.114f * b;
    greyImage[idx] = i;
}

void your_rgba_to_greyscale(const uchar4 * const h_rgbaImage, uchar4 * const d_rgbaImage,
                            unsigned char* const d_greyImage, size_t numRows, size_t numCols)
{
    const dim3 gridSize(numRows, 1, 1);
    const dim3 blockSize(numCols, 1, 1);
    rgba_to_greyscale<<<gridSize, blockSize>>>(d_rgbaImage, d_greyImage, numRows, numCols);
    cudaDeviceSynchronize(); 
    checkCudaErrors(cudaGetLastError());
}

