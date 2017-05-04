#include <stdio.h>
#include <iostream>
#include <string>
#include <chrono>

#include "helper.hpp"

using namespace std;

/* buffer size */
#define MAT_SIZE		(256)
#define BUF_MAT_SIZE	(MAT_SIZE * MAT_SIZE)

/**
* Retrieve GPU device
*/
void gpu_find(cl_device_id &device, 
		uint platform_select, 
		uint device_select)
{
	cl_platform_id platform;
	cl_uint platform_num = 0;
	cl_platform_id* platform_list = NULL;

	cl_uint device_num = 0;
	cl_device_id* device_list = NULL;

	size_t attr_size = 0;
	cl_char* attr_data = NULL;

	/* get num of available OpenCL platforms */
	CL_ERR( clGetPlatformIDs(0, NULL, &platform_num));
	platform_list = new cl_platform_id[platform_num];
	DIE(platform_list == NULL, "alloc platform_list");

	/* get all available OpenCL platforms */
	CL_ERR( clGetPlatformIDs(platform_num, platform_list, NULL));
	cout << "Platforms found: " << platform_num << endl;

	/* list all platforms and VENDOR/VERSION properties */
	for(uint platf=0; platf<platform_num; platf++)
	{
		/* get attribute CL_PLATFORM_VENDOR */
		CL_ERR( clGetPlatformInfo(platform_list[platf],
				CL_PLATFORM_VENDOR, 0, NULL, &attr_size));
		attr_data = new cl_char[attr_size];
		DIE(attr_data == NULL, "alloc attr_data");

		/* get data CL_PLATFORM_VENDOR */
		CL_ERR( clGetPlatformInfo(platform_list[platf],
				CL_PLATFORM_VENDOR, attr_size, attr_data, NULL));
		cout << "Platform " << platf << " " << attr_data << " ";
		delete[] attr_data;

		/* get attribute size CL_PLATFORM_VERSION */
		CL_ERR( clGetPlatformInfo(platform_list[platf],
				CL_PLATFORM_VERSION, 0, NULL, &attr_size));
		attr_data = new cl_char[attr_size];
		DIE(attr_data == NULL, "alloc attr_data");

		/* get data size CL_PLATFORM_VERSION */
		CL_ERR( clGetPlatformInfo(platform_list[platf],
				CL_PLATFORM_VERSION, attr_size, attr_data, NULL));
		cout << attr_data << endl;
		delete[] attr_data;

		/* no valid platform found */
		platform = platform_list[platf];
		DIE(platform == 0, "platform selection");

		/* get num of available OpenCL devices type ALL on the selected platform */
		if(clGetDeviceIDs(platform, 
			CL_DEVICE_TYPE_ALL, 0, NULL, &device_num) == CL_DEVICE_NOT_FOUND) {
			device_num = 0;
			continue;
		}

		device_list = new cl_device_id[device_num];
		DIE(device_list == NULL, "alloc devices");

		/* get all available OpenCL devices type ALL on the selected platform */
		CL_ERR( clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL,
			  device_num, device_list, NULL));
		cout << "\tDevices found " << device_num  << endl;

		/* list all devices and TYPE/VERSION properties */
		for(uint dev=0; dev<device_num; dev++)
		{
			/* get attribute size */
			CL_ERR( clGetDeviceInfo(device_list[dev], CL_DEVICE_NAME,
				0, NULL, &attr_size));
			attr_data = new cl_char[attr_size];
			DIE(attr_data == NULL, "alloc attr_data");

			/* get attribute CL_DEVICE_NAME */
			CL_ERR( clGetDeviceInfo(device_list[dev], CL_DEVICE_NAME,
				attr_size, attr_data, NULL));
			cout << "\tDevice " << dev << " " << attr_data << " ";
			delete[] attr_data;

			/* get attribute size */
			CL_ERR( clGetDeviceInfo(device_list[dev], CL_DEVICE_VERSION,
				0, NULL, &attr_size));
			attr_data = new cl_char[attr_size];
			DIE(attr_data == NULL, "alloc attr_data");

			/* get attribute CL_DEVICE_VERSION */
			CL_ERR( clGetDeviceInfo(device_list[dev], CL_DEVICE_VERSION,
				attr_size, attr_data, NULL));
			cout << attr_data; 
			delete[] attr_data;

			/* select device based on cli arguments */
			if((platf == platform_select) && (dev == device_select)){
				device = device_list[dev];
				cout << " <--- SELECTED ";
			}

			cout << endl;
		}
	}

	delete[] platform_list;
	delete[] device_list;
}

/**
 * Profile kernel execution using the selected device
 */
void gpu_profile_kernel(cl_device_id device)
{
	cl_int ret;
	
	cl_context context;
	cl_command_queue cmdQueue;
	cl_program program;
	cl_kernel kernel;
	
	string kernel_src;
	int matSize = MAT_SIZE;
	int bufMatSize = BUF_MAT_SIZE;
	
	float checkResult;
	double timeDiff = 0;
	
	/* create a context for the device */
	context = clCreateContext(0, 1, &device, NULL, NULL, &ret);
	CL_ERR( ret );
	
	/* create a command queue for the device in the context */
	// TODO ex2: add profiling options to the queue
	cmdQueue = clCreateCommandQueue(context, device, CL_QUEUE_PROFILING_ENABLE, &ret);
	CL_ERR( ret );
	
	/* allocate 1 buffer of BUF_128 float elements on the CPU (HOST) */
	cl_float *matA = new cl_float[bufMatSize];
	cl_float *matB = new cl_float[bufMatSize];
	cl_float *matC = new cl_float[bufMatSize];
	
	/* assert HOST (CPU/RAM) allocation */
	DIE ( matA == NULL, "alloc failed" );
	DIE ( matB == NULL, "alloc failed" );
	DIE ( matC == NULL, "alloc failed" );
	
	/* fill data such that matA * matB = (12.f 12.f ... ) */
	for(int i = 0; i < bufMatSize; i++) {
		matA[i] = 3.f / (float) matSize;
		matB[i] = 4.f;
	}
	
	/* matC = matA * matB = (12.f 12.f ... ) */
	checkResult = 12.f;
	
	/* allocate buffer on the DEVICE (GPU/VRAM) */
	cl_mem bufMatA = clCreateBuffer(context, 
		CL_MEM_READ_ONLY, sizeof(cl_float) * bufMatSize, NULL, &ret);
	CL_ERR( ret );
	cl_mem bufMatB = clCreateBuffer(context, 
		CL_MEM_READ_ONLY, sizeof(cl_float) * bufMatSize, NULL, &ret);
	CL_ERR( ret );
	cl_mem bufMatC = clCreateBuffer(context, 
		CL_MEM_READ_WRITE, sizeof(cl_float) * bufMatSize, NULL, &ret);
	CL_ERR( ret );
	
	/* TODO ex1 - copy the buffers to VRAM */
	clEnqueueWriteBuffer(cmdQueue, bufMatA, CL_TRUE, 0, sizeof(float) * bufMatSize, matA, 0, NULL, NULL);
	clEnqueueWriteBuffer(cmdQueue, bufMatB, CL_TRUE, 0, sizeof(float) * bufMatSize, matB, 0, NULL, NULL);
	clEnqueueWriteBuffer(cmdQueue, bufMatC, CL_TRUE, 0, sizeof(float) * bufMatSize, matC, 0, NULL, NULL);

	/* retrieve kernel source */
	read_kernel("skl_device.cl", kernel_src);
	const char* kernel_c_str = kernel_src.c_str();
	
	/* create kernel program from source */
	program = clCreateProgramWithSource(context, 1, &kernel_c_str, NULL, &ret);
	CL_ERR( ret );
	
	/* compile the program for the given set of devices */
	/* TODO ex4 - add compiler flags for fast math */
	//ret = clBuildProgram(program, 1, &device, "", NULL, NULL);
	ret = clBuildProgram(program, 1, &device, "-cl-fast-relaxed-math", NULL, NULL);
	CL_COMPILE_ERR( ret, program, device );
	
	/* create kernel associated to compiled source kernel */
	kernel = clCreateKernel(program, "mat_mul", &ret);
	CL_ERR( ret );
	
	/* set OpenCL kernel argument */
	CL_ERR( clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&bufMatA) );
	CL_ERR( clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&bufMatB) );
	CL_ERR( clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&bufMatC) );
	CL_ERR( clSetKernelArg(kernel, 3, sizeof(cl_uint), (void *)&matSize) );
	
	/* TIME - start */
	auto start = std::chrono::system_clock::now();
	
	// TODO ex2 - add event notification when function finishes
	/* profile execution of OpenCL kernel */
	cl_event event;
	size_t globalSize[2] = {matSize, matSize};
	ret = clEnqueueNDRangeKernel(cmdQueue, 
		kernel, 2, NULL, globalSize, 0, 0, NULL, &event);
	CL_ERR( ret );
	
	// TODO ex2 - add event wait on event using clWaitForEvents
	clWaitForEvents(1, &event);
	/* TIME - end */
	auto end = std::chrono::system_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	std::cout << "Kernel exec time (chrono, ms): " << elapsed.count() / 1000.f  << '\n';
	std::cout << "Gflops: " << (double) bufMatSize * matSize * 2 / elapsed.count() << endl;
	
	/* TODO ex1 - copy matC back to RAM */
	clEnqueueReadBuffer(cmdQueue, bufMatC, CL_TRUE, 0, sizeof(float) * bufMatSize, matC, 0, NULL, NULL);
	/* TODO ex3 - profile transfer using events */
	clEnqueueReadBuffer(cmdQueue, bufMatC, CL_TRUE, 0, sizeof(float) * bufMatSize, matC, 0, NULL, &event);
	/* print some values from CPU buffers (after GPU compute) */
	for(int i = 0; i < bufMatSize; i ++) {
		DIE( matC[i] != checkResult, "matC check failed" );
	}
	cout << "Check GPU result OK." << endl;
	
	/* wait for all enqueued operations to finish */
	CL_ERR( clFinish(cmdQueue) );
	
	// TODO ex1 - compute the event time start end difference
	// use clGetEventProfilingInfo and CL_PROFILING_COMMAND_START/STOP
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(start), &start, NULL);
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(end), &end, NULL);
	timeDiff = (end - start).count();

	cout << "Kernel exec time (opencl, ms):" << timeDiff / 1000.f << endl;
	
	/* free all resources related to GPU */
	CL_ERR( clReleaseMemObject(bufMatA) );
	CL_ERR( clReleaseMemObject(bufMatB) );
	CL_ERR( clReleaseMemObject(bufMatC) );
	CL_ERR( clReleaseCommandQueue(cmdQueue) );
	CL_ERR( clReleaseContext(context) );
	
	/* free all resources on CPU */
	delete[] matA;
	delete[] matB;
	delete[] matC;
}

/**
* MAIN function (CPU/HOST)
*/
int main(int argc, char** argv)
{
	cl_device_id device;
	int platform_select = 0;
	int device_select = 0;

	if(argc == 3){
		platform_select = atoi(argv[1]);
		device_select = atoi(argv[2]);
	} else {
		cout << "./bin <platform> <device>" << endl << endl;
   	}

	/* list selected platform and devices */
	cout << "SELECT(platform = " << platform_select 
		<< ", device = " << device_select << ")" << endl;

	/* search and select platform/devices in OpenCL */
	gpu_find(device, platform_select, device_select);

	/* perform kernel profile using selected device (GPU NVIDIA TESLA) */
	gpu_profile_kernel(device);

	return 0;
}
