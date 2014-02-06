#include "reference_calc.cpp"
#include "utils.h"

__global__ 
void reduceMinKernel(float *d_out, const float* d_in)
{
    extern __shared__ float sdata[];

    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    int tid = threadIdx.x;
    sdata[tid] = d_in[idx];
    __syncthreads();

    for (unsigned int s = blockDim.x >> 1; s > 0; s >>= 1)
    {
        if (tid < s)
        {
            if (sdata[tid] > sdata[tid + s])
            {
                sdata[tid] = sdata[tid + s];
            }
        }
        __syncthreads();
    }

    if (tid == 0)
    {
        d_out[blockIdx.x] = sdata[0];
    }
}

__global__ 
void reduceMaxKernel(float *d_out, const float* d_in)
{
    extern __shared__ float sdata[];

    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    int tid = threadIdx.x;
    sdata[tid] = d_in[idx];
    __syncthreads();

    for (unsigned int s = blockDim.x >> 1; s > 0; s >>= 1)
    {
        if (tid < s)
        {
            if (sdata[tid] < sdata[tid + s])
            {
                sdata[tid] = sdata[tid + s];
            }
        }
        __syncthreads();
    }

    if (tid == 0)
    {
        d_out[blockIdx.x] = sdata[0];
    }
}

void reduce(float &min_logLum,
            float &max_logLum,
            float *d_out, 
            float *d_intermediate, 
            const float *d_in, 
            int size)
{
    int threads, blocks;

    threads = 1024;
    blocks = (size - 1) / 1024 + 1;
    reduceMinKernel<<<blocks, threads, threads * sizeof(float)>>>(d_intermediate, d_in);
    threads = blocks;
    blocks = 1;
    reduceMinKernel<<<blocks, threads, threads * sizeof(float)>>>(d_out, d_intermediate);
    cudaMemcpy(&min_logLum, d_out, sizeof(float), cudaMemcpyDeviceToHost);

    threads = 1024;
    blocks = (size - 1) / 1024 + 1;
    reduceMaxKernel<<<blocks, threads, threads * sizeof(float)>>>(d_intermediate, d_in);
    threads = blocks;
    blocks = 1;
    reduceMaxKernel<<<blocks, threads, threads * sizeof(float)>>>(d_out, d_intermediate);
    max_logLum = d_out[0];
    cudaMemcpy(&max_logLum, d_out, sizeof(float), cudaMemcpyDeviceToHost);
}

__global__
void histKernel(unsigned int *d_out, 
                const float *d_in, 
                float min_logLum, 
                float lumRange, 
                const int numBins)
{
    int idx = threadIdx.x + blockDim.x * blockIdx.x;
    int bin = (d_in[idx] - min_logLum) / lumRange * numBins;
    atomicAdd(&(d_out[bin]), 1);
}

void genHist(unsigned int *d_out, 
             const float *d_in, 
             size_t size,
             float min_logLum, 
             float max_logLum, 
             const int numBins)
{
    int threads = 1024;
    int blocks = (size - 1) / 1024 + 1;
    //histKernel<<<blocks, threads>>>(d_out, d_in, min_logLum, max_logLum - min_logLum, numBins);
}

void your_histogram_and_prefixsum(const float* const d_logLuminance,
                                  unsigned int* const d_cdf,
                                  float &min_logLum,
                                  float &max_logLum,
                                  const size_t numRows,
                                  const size_t numCols,
                                  const size_t numBins)
{
  //TODO
  /*Here are the steps you need to implement
    1) find the minimum and maximum value in the input logLuminance channel
       store in min_logLum and max_logLum
    2) subtract them to find the range
    3) generate a histogram of all the values in the logLuminance channel using
       the formula: bin = (lum[i] - lumMin) / lumRange * numBins
    4) Perform an exclusive scan (prefix sum) on the histogram to get
       the cumulative distribution of luminance values (this should go in the
       incoming d_cdf pointer which already has been allocated for you)       */
    
    float *d_out;
    float *d_intermediate;
    size_t size = numRows * numCols;
    cudaMalloc((void**)&d_out, sizeof(float));
    cudaMalloc((void**)&d_intermediate, sizeof(float) * size);
    reduce(min_logLum, max_logLum, d_out, d_intermediate, d_logLuminance, size);
    cudaDeviceSynchronize(); 
    checkCudaErrors(cudaGetLastError());
    unsigned int *d_hist;
    cudaMalloc((void**)&d_hist, sizeof(unsigned int) * numBins);
    genHist(d_hist, d_logLuminance, size, min_logLum, max_logLum, numBins);
}

