
#include <iostream>
#include <cuda_runtime.h>


// called only from device 
__device__ void costFunction(float* F, float* T, int i, int numElements){

	if (i < numElements)
	{
		F[i] = T[i] * T[i];
	}
	
}

// Trying finite difference, called from host
__global__ void finiteDiff(float* Fp, float* Tp, float* Fn, float* Tn, float* dF, float e, int numElements){
	int i = blockDim.x * blockIdx.x + threadIdx.x;

	costFunction(Fn,Tn,i,numElements);
	costFunction(Fp,Tp,i,numElements);
	if (i < numElements)
	{
		dF[i] = (Fp[i] - Fn[i]) / (2*e); // think the 0.0f exists to cast to float
	}
	
}




int main (void) {
    
    // Declare Vairables host variables start with h, device vars with d
	int numElements = 50000; // vector size --- determine whats the max we can do on GPU
	size_t size = numElements*sizeof(float); // total vector size

	// we want C <-- A*B so init three vectors on host
	float *h_Fp = (float*) malloc(size);
	float *h_Fn = (float*) malloc(size);
	float *h_Tp = (float*) malloc(size);
    float *h_Tn = (float*) malloc(size);
    float *h_dF = (float*) malloc(size);

	if (h_Fp == NULL || h_Fn == NULL || h_Tp == NULL || h_Tn == NULL)
	{
		std::cout<< "Failed to allocate on host device" << std::endl;
		exit(EXIT_FAILURE);
	}

    // initialize Tp and Tn
    float e = 0.0001;
    for (int  i = 0; i < numElements; i++)
    {
        // 0.001 -> 500
        h_Tn[i] = i/100 - e;
        h_Tp[i] = i/100 + e;     
    }
    
    // DEVICE -- GPU

	cudaError_t err = cudaSuccess; // errror code 

	// init vectors on device
	float *d_Fp = NULL; // NULL pointer
	err = cudaMalloc((void **)&d_Fp, size);
	if (err != cudaSuccess)
	{
		std::cout << "Failed to allocate device vector d_Fp, Error code: " << cudaGetErrorString(err) << std::endl;
		exit(EXIT_FAILURE);
	}

    float *d_Fn = NULL; // NULL pointer
	err = cudaMalloc((void **)&d_Fn, size);
	if (err != cudaSuccess)
	{
		std::cout << "Failed to allocate device vector d_Fn, Error code: " << cudaGetErrorString(err) << std::endl;
		exit(EXIT_FAILURE);
	}

    float *d_Tp = NULL; // NULL pointer
	err = cudaMalloc((void **)&d_Tp, size);
	if (err != cudaSuccess)
	{
		std::cout << "Failed to allocate device vector d_Tp, Error code: " << cudaGetErrorString(err) << std::endl;
		exit(EXIT_FAILURE);
	}

    float *d_Tn = NULL; // NULL pointer
	err = cudaMalloc((void **)&d_Tn, size);
	if (err != cudaSuccess)
	{
		std::cout << "Failed to allocate device vector d_Tn, Error code: " << cudaGetErrorString(err) << std::endl;
		exit(EXIT_FAILURE);
	}

    float *d_dF = NULL; // NULL pointer
	err = cudaMalloc((void **)&d_dF, size);
	if (err != cudaSuccess)
	{
		std::cout << "Failed to allocate device vector d_dF, Error code: " << cudaGetErrorString(err) << std::endl;
		exit(EXIT_FAILURE);
	}

    // COPY DATA FROM HOST TO DEVICE using cudaMemcpy(destination_add, source_add, size, direction)
	std::cout << "Begin to copy memory from host to device." << std::endl;

    err = cudaMemcpy(d_Tp, h_Tp, size, cudaMemcpyHostToDevice);
	if (err != cudaSuccess)
	{
		std::cout << "Failed to copy host vector Tp to device, Error code: " << cudaGetErrorString(err) << std::endl;
		exit(EXIT_FAILURE);
	}

    err = cudaMemcpy(d_Tn, h_Tn, size, cudaMemcpyHostToDevice);
	if (err != cudaSuccess)
	{
		std::cout << "Failed to copy host vector Tp to device, Error code: " << cudaGetErrorString(err) << std::endl;
		exit(EXIT_FAILURE);
	}

    // FINITE DIFF ON KERNEL
	int threadsPerBlock = 256; // threads per block is limited to 1024
	int blocksPerGrid = (numElements + threadsPerBlock - 1) / threadsPerBlock; // dont understand this tbh
	std::cout<<"CUDA kernel lauched with " << blocksPerGrid << " blocks of " << threadsPerBlock << " threads" << std::endl;

    finiteDiff<<<blocksPerGrid,threadsPerBlock>>>(d_Fp,d_Tp,d_Fn,d_Tn, d_dF, e, numElements);
    err = cudaGetLastError();
    if (err != cudaSuccess)
	{
		std::cout << "Failed to lauch vecAdd kernel, Error code: " << cudaGetErrorString(err) << std::endl;
		exit(EXIT_FAILURE);
	}

    // COPY DATA BACK TO HOST FROM DEVICE 
	std::cout << "Begin to copy memory from device to host." << std::endl;
	err = cudaMemcpy(h_dF, d_dF, size, cudaMemcpyDeviceToHost);
	if (err != cudaSuccess)
	{
		std::cout << "Failed to copy device vector dF to host, Error code: " << cudaGetErrorString(err) << std::endl;
		exit(EXIT_FAILURE);
	}

    // for (int i = 0; i < 200; i++)
	// {
	// 	if (fabs(2*(h_Tn[i] + e) - h_dF[i]) > 1e-2)
	// 	{		
	// 		std::cout<<"Result verification failed at element " << i << " tol:: " << fabs(2*(h_Tn[i] + e) - h_dF[i]) << std::endl;
	// 		exit(EXIT_FAILURE);
	// 	}
	// }

    // free vectors on device
	err = cudaFree(d_Fp);
	if (err != cudaSuccess)
	{
		std::cout << "Failed to free device vector d_Fp, Error code: " << cudaGetErrorString(err) << std::endl;
		exit(EXIT_FAILURE);
	}
    err = cudaFree(d_Fn);
	if (err != cudaSuccess)
	{
		std::cout << "Failed to free device vector d_Fn, Error code: " << cudaGetErrorString(err) << std::endl;
		exit(EXIT_FAILURE);
	}
    err = cudaFree(d_Tp);
	if (err != cudaSuccess)
	{
		std::cout << "Failed to free device vector d_Tp, Error code: " << cudaGetErrorString(err) << std::endl;
		exit(EXIT_FAILURE);
	}
    err = cudaFree(d_Tn);
	if (err != cudaSuccess)
	{
		std::cout << "Failed to free device vector d_Tn, Error code: " << cudaGetErrorString(err) << std::endl;
		exit(EXIT_FAILURE);
	}
    err = cudaFree(d_dF);
	if (err != cudaSuccess)
	{
		std::cout << "Failed to free device vector d_dF, Error code: " << cudaGetErrorString(err) << std::endl;
		exit(EXIT_FAILURE);
	}




    // free memory
    free(h_Fp);
    free(h_Fn);
    free(h_Tp);
    free(h_Tn);
    free(h_dF);

    std::cout << "Done!" << std::endl;
    return 0;
}