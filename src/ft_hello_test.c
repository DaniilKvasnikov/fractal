/* Simple Hello World for OpenCL, written in C.
 * For real code, check for errors. The error code is stored in all calls here,
 * but no checking is done, which is certainly bad. It'll likely simply crash
 * right after a failing call.
 *
 * On GNU/Linux with nVidia OpenCL, program builds with -lOpenCL.
 * Not sure about other platforms.
 */

#include <stdio.h>
#include <string.h>

#include "ft_opencl.h"

void	ft_get_fun_code(t_opencl *obj_opencl)
{
	FILE	*fp;
	char	*fileName;

	fileName = "./src/rot13.cl";
	fp = fopen(fileName, "r");
	if (!fp)
		exit(1);
	obj_opencl->source_str = (char*)malloc(MAX_SOURCE_SIZE);
	obj_opencl->source_size = fread(obj_opencl->source_str, 1, MAX_SOURCE_SIZE, fp);
	fclose(fp);
}

void ft_opencl(int *buf1, float *c) {
	t_opencl	obj_opencl;
	size_t		worksize=MEM_SIZE;
	size_t		srcsize;
	const char	*src;
	const char	**srcptr;
	size_t		size;
	cl_mem		mem1;
	cl_mem		mem2;
	cl_program	prog;
	cl_kernel	k_rot13;

	size = 1024 * 1024;
	ft_get_fun_code(&obj_opencl);
	obj_opencl.error=clGetPlatformIDs(1, &obj_opencl.platform, &obj_opencl.platforms);
	obj_opencl.error=clGetDeviceIDs(obj_opencl.platform, CL_DEVICE_TYPE_ALL, 1, &obj_opencl.device, &obj_opencl.devices);
	cl_context_properties properties[]={
		CL_CONTEXT_PLATFORM, (cl_context_properties)obj_opencl.platform, 0};
	obj_opencl.context=clCreateContext(properties, 1, &obj_opencl.device, NULL, NULL, &obj_opencl.error);
	obj_opencl.cq = clCreateCommandQueue(obj_opencl.context, obj_opencl.device, 0, &obj_opencl.error);
	src=obj_opencl.source_str;
	srcsize=obj_opencl.source_size;
	srcptr=&src;
	prog=clCreateProgramWithSource(obj_opencl.context,
		1, srcptr, &srcsize, &obj_opencl.error);
	obj_opencl.error=clBuildProgram(prog, 0, NULL, "", NULL, NULL);
	mem1=clCreateBuffer(obj_opencl.context, CL_MEM_READ_WRITE, size * sizeof(int), NULL, &obj_opencl.error);
	mem2=clCreateBuffer(obj_opencl.context, CL_MEM_READ_WRITE, 2 * sizeof(float), NULL, &obj_opencl.error);
	k_rot13=clCreateKernel(prog, "rot13", &obj_opencl.error);
	clSetKernelArg(k_rot13, 0, sizeof(mem1), &mem1);
	clSetKernelArg(k_rot13, 1, sizeof(mem2), &mem2);
	obj_opencl.error=clEnqueueWriteBuffer(obj_opencl.cq, mem1, CL_FALSE, 0, size * sizeof(int), buf1, 0, NULL, NULL);
	obj_opencl.error=clEnqueueWriteBuffer(obj_opencl.cq, mem2, CL_FALSE, 0, 2 * sizeof(float), c, 0, NULL, NULL);
	obj_opencl.error=clEnqueueNDRangeKernel(obj_opencl.cq, k_rot13, 1, NULL, &worksize, &worksize, 0, NULL, NULL);
	obj_opencl.error=clEnqueueReadBuffer(obj_opencl.cq, mem1, CL_FALSE, 0, size * sizeof(int), buf1, 0, NULL, NULL);
	obj_opencl.error=clFinish(obj_opencl.cq);
}