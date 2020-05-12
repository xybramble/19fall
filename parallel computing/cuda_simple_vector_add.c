// host code
int main()
{
    int *h_A, *h_B, *h_C, *d_A, *d_B, *d_C;
    int N = 4096;
    size_t size = N * sizeof(int);
    
    // allocate input vectors h_A and h_B in host memory
    h_A = (int*)malloc(size);
    h_B = (int*)malloc(size);
    h_C = (int*)malloc(size);
    
    for (int i=0; i<N; i++)
    {
        h_A[i] = i;
        h_B[i] = i;
    }
    
    // allocate vectors in device memory
    cudaMalloc((void**)&d_A, size);
    cudaMalloc((void**)&d_B, size);
    cudaMalloc((void**)&d_C, size);
    
    // copy vectors from host memory to device memory
    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);
    
    // invoke kernel
    int threadsPerBlock = 256;
    int blockPerGrid = N/threadsPerBlock;
    VecAdd<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C);
    
    // device code
    __global__ void VecAdd(int* A, int* B, int* C)
    {
        int i = blockDim.x * blockIdx.x + threadIdx.x;
        C[i] = A[i] + B[i];
    }
    
    // copy result from device memory to host memory
    // h_C contains the result in host memory
    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);
    
    // Free host memory
    free(h_A);
    free(h_B);
    free(h_C);
    
    // free device memory
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
}
