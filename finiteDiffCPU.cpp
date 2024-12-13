#include <iostream>
#include <chrono>

float f(float t){
    return t*t;
}

int main(void) {
    auto start = std::chrono::high_resolution_clock::now();
    // Declare Vairables host variables 
	int numElements = 50000; // vector size --- determine whats the max we can do on GPU
	// size_t size = numElements*sizeof(float); // total vector size

	// we want C <-- A*B so init three vectors on host
	float *h_Tp = new float[numElements];
    float *h_Tn = new float[numElements];
    float *h_dF = new float[numElements];

    float e = 0.0001;
    auto startL = std::chrono::high_resolution_clock::now();
    for (int  i = 0; i < numElements; i++)
    {
        // 0.001 -> 500
        h_Tn[i] = i/100 - e;
        h_Tp[i] = i/100 + e;     
    }

    for (int i = 0; i < numElements; i++)
    {
        h_dF[i] = (f(h_Tp[i]) - f(h_Tn[i])) / (2*e);
    }
    auto stopL = std::chrono::high_resolution_clock::now();
    auto durationL = std::chrono::duration_cast<std::chrono::microseconds>(stopL- startL);
    // delete vectors
    delete[] h_Tn;
    delete[] h_Tp;
    delete[] h_dF;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout<< "Run time for evalulating Finite difference on CPU: " << durationL.count() << " microseconds" << std::endl;
    std::cout<< "Total Run time on CPU: " << duration.count() << " microseconds" << std::endl;
}