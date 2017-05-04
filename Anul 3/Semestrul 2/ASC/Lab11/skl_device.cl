/* Matrix multiply kernel */
__kernel void
mat_mul(__global float* matA,
        __global float* matB,
        __global float* matC,
        int size)
{
	/* TODO ex1 - matrix multiplication C = A * B */
	int x = get_global_id(0);
	int y = get_global_id(1);
	
	/* 
	float value = 0;
	for (int i = 0; i < size; i++)
	{
		float A = matA[y * size + i];
		float B = matB[i * size + x];
		value += A * B;
	}

	matC[y * size + x] = value;*/

	/* TODO ex5 - matrix multiplication C = A * B, using vector data types and local memory */
	
	float4 A,B,C;
	C.s0 = 0;
	C.s1 = 0;
	C.s2 = 0;
	C.s3 = 0;
	for (int i = 0; i < size; i+= 4)
	{
		A.s0 = matA[y * size + i + 0];
		A.s1 = matA[y * size + i + 1];
		A.s2 = matA[y * size + i + 2];
		A.s3 = matA[y * size + i + 3];

		B.s0 = matB[(i + 0) * size + x];
		B.s1 = matB[(i + 1) * size + x];
		B.s2 = matB[(i + 2) * size + x];
		B.s3 = matB[(i + 3) * size + x];

		C += B * A;
	}
	matC[y * size + x] = C.s0 + C.s1 + C.s2 + C.s3;
}
