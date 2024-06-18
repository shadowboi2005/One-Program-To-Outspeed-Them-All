#include "kernel.hpp" // note: unbalanced round brackets () are not allowed and string literals can't be arbitrarily long, so periodically interrupt with )+R(

string opencl_c_container() { return R( // ########################## begin of OpenCL C code ####################################################################



kernel void add_kernel(global float* A, global float* B, global float* C) { // equivalent to "for(uint n=0u; n<N; n++) {", but executed in parallel
	const uint n = get_global_id(0);
	C[n] = A[n]+B[n];
}

kernel void mul_kernel(global float* A, global float* B, global float* C) {
	// TASK 1 CODE BEGINS HERE
	const uint n = get_global_id(0);
	C[n] = A[n]*B[n];
	return;
	// TASK 1 CODE ENDS HERE
}

kernel void matMul (__global float* A, __global float *B, __global float *C, int aCol, int cRow, int cCol) {
	// TASK 2 CODE BEGINS HERE
	// HINT : IMPLEMENT DOT PRODUCT HERE
	const uint n= get_global_id(0);
	uint N = 1024;
	const uint i = n/N;
	const uint k = n%N;
	int sum = 0;
	for(int j=0;j < N;j++){
		sum += A[i*N+j]*B[j*N+k];
		//C[n] += A[i*N+j]*B[j*N+k];
	}
	C[n] = sum;
	return;
	// TASK 2 CODE ENDS HERE
}


);} // ############################################################### end of OpenCL C code #####################################################################
