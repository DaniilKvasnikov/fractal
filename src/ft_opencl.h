#ifndef FT_OPENCL_H
# define FT_OPENCL_H

# include <stdio.h>
# include <stdlib.h>
# include <OpenCL/opencl.h>

# define MEM_SIZE (128)
# define MAX_SOURCE_SIZE (0x100000)

typedef struct  		s_opencl
{
	cl_int				error;
	cl_platform_id		platform;
	cl_device_id		device;
	cl_uint				platforms;
	cl_uint				devices;
	cl_context			context;
	cl_command_queue	cq;
	cl_program			prog;
	char				*source_str;
	size_t				source_size;
}               		t_opencl;

void					ft_opencl(int *buf1, float *c);

#endif
