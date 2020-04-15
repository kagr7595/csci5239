/*
 *  OpenCL square matrix multiplier
 *
 *  The size of the matrix is width*blocks
 *
 *  Parameters:
 *  -v      Verbose - show hardware detila
 *  width   Block width (width squared <= max threads/block)
 *  blocks  Number of blocks
 */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/opencl.h>
#endif
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

/*
 *  Return elapsed wall time since last call (seconds)
 */
static double t0=0;
float Elapsed(void)
{
#ifdef _WIN32
   //  Windows version of wall time
   LARGE_INTEGER tv,freq;
   QueryPerformanceCounter((LARGE_INTEGER*)&tv);
   QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
   double t = tv.QuadPart/(double)freq.QuadPart;
#else
   //  Unix/Linux/OSX version of wall time
   struct timeval tv;
   gettimeofday(&tv,NULL);
   double t = tv.tv_sec+1e-6*tv.tv_usec;
#endif
   float s = t-t0;
   t0 = t;
   return s;
}

/*
 *  Print message to stderr and exit
 */
void Fatal(const char* format , ...)
{
   va_list args;
   va_start(args,format);
   vfprintf(stderr,format,args);
   va_end(args);
   exit(1);
}

/*
 *  Initialize array with random values
 */
void RandomInit(float x[],const unsigned int num_add)
{
   for (unsigned int i=0;i<num_add;i++)
   {
      x[i] = rand() / (float)RAND_MAX;
	  while(x[i] == 0)
         x[i] = rand() / (float)RAND_MAX;
   }
}

/*
 *  OpenCL notify callback (echo to stderr)
 */
void Notify(const char* errinfo,const void* private_info,size_t cb,void* user_data)
{
   fprintf(stderr,"%s\n",errinfo);
}

/*
 *  Initialize fastest OpenCL device
 */
cl_device_id     devid;
cl_context       context;
cl_command_queue queue;
int InitGPU(int verbose)
{
   cl_uint Nplat;
   cl_int  err;
   char name[1024];
   int  MaxGflops = -1;

   //  Get platforms
   cl_platform_id platforms[1024];
   if (clGetPlatformIDs(1024,platforms,&Nplat))
      Fatal("Cannot get number of OpenCL platforms\n");
   else if (Nplat<1)
      Fatal("No OpenCL platforms found\n");
   //  Loop over platforms
   for (unsigned int platform=0;platform<Nplat;platform++)
   {
      if (clGetPlatformInfo(platforms[platform],CL_PLATFORM_NAME,sizeof(name),name,NULL)) Fatal("Cannot get OpenCL platform name\n");
      if (verbose) printf("OpenCL Platform %d: %s\n",platform,name);

      //  Get GPU device IDs
      cl_uint Ndev;
      cl_device_id id[1024];
      if (clGetDeviceIDs(platforms[platform],CL_DEVICE_TYPE_GPU,1024,id,&Ndev))
         Fatal("Cannot get number of OpenCL devices\n");
      else if (Ndev<1)
         Fatal("No OpenCL devices found\n");

      //  Find the fastest device
      for (unsigned int dev=0;dev<Ndev;dev++)
      {
         cl_uint proc,freq;
         if (clGetDeviceInfo(id[dev],CL_DEVICE_MAX_COMPUTE_UNITS,sizeof(proc),&proc,NULL)) Fatal("Cannot get OpenCL device units\n");
         if (clGetDeviceInfo(id[dev],CL_DEVICE_MAX_CLOCK_FREQUENCY,sizeof(freq),&freq,NULL)) Fatal("Cannot get OpenCL device frequency\n");
         if (clGetDeviceInfo(id[dev],CL_DEVICE_NAME,sizeof(name),name, NULL)) Fatal("Cannot get OpenCL device name\n");
         int Gflops = proc*freq;
         if (verbose) printf("OpenCL Device %d: %s Gflops %f\n",dev,name,1e-3*Gflops);
         if(Gflops > MaxGflops)
         {
            devid = id[dev];
            MaxGflops = Gflops;
         }
      }
   }

   //  Print fastest device info
   if (clGetDeviceInfo(devid,CL_DEVICE_NAME,sizeof(name),name,NULL)) Fatal("Cannot get OpenCL device name\n");
   printf("Fastest OpenCL Device: %s\n",name);

   //  Check thread count
   size_t mwgs;
   if (clGetDeviceInfo(devid,CL_DEVICE_MAX_WORK_GROUP_SIZE,sizeof(mwgs),&mwgs,NULL)) Fatal("Cannot get OpenCL max work group size\n");

   //  Create OpenCL context for fastest device
   //context = clCreateContext(0,1,&devid,NULL,NULL,&err);
   context = clCreateContext(0,1,&devid,Notify,NULL,&err);
   if(!context || err) Fatal("Cannot create OpenCL context\n");

   //  Create OpenCL command queue for fastest device
   queue = clCreateCommandQueue(context,devid,0,&err);
   if(!queue || err) Fatal("Cannot create OpenCL command cue\n");

   return mwgs;
} 

/*
 * multiple operations -- host
 */
void ABh(float C[], const float A[], const float B[], unsigned int num_add, unsigned int op, unsigned int repeat_op)
{
   for (unsigned int i=0;i<num_add;i++)
   {
	  C[i] = 0;
      for (unsigned int j=0;j<repeat_op;j++)
	  {
	      if(op == 0)
	         C[i] += (float)((double)A[i] + (double)B[i]);
	      else if(op == 1)
	         C[i] += (float)((double)A[i] - (double)B[i]);
	      else if(op == 2)
	         C[i] += (float)((double)A[i] * (double)B[i]);
	      else if(op == 3)
	         C[i] += (float)((double)A[i] / (double)B[i]);
	  }
   }
}

/*
* Compute one element of A + B:A - B:A * B:A / B
*/
const char* source =
  "__kernel void ApB(__global float C[],__global const float A[],__global const float B[],__global const float repeat_op[])\n"
  "{\n"
  "   unsigned int i = get_global_id(0);\n"
  "   float value = 0;\n"
  "   for(int j = 0; j<repeat_op[0]; j++)\n"
  "      value += A[i] + B[i];\n"
  "   C[i] = value;\n"
  "}\n"
  "__kernel void AsB(__global float C[],__global const float A[],__global const float B[],__global const float repeat_op[])\n"
  "{\n"
  "   unsigned int i = get_global_id(0);\n"
  "   float value = 0;\n"
  "   for(int j = 0; j<repeat_op[0]; j++)\n"
  "      value += A[i] - B[i];\n"
  "   C[i] = value;\n"
  "}\n"
  "__kernel void AmB(__global float C[],__global const float A[],__global const float B[],__global const float repeat_op[])\n"
  "{\n"
  "   unsigned int i = get_global_id(0);\n"
  "   float value = 0;\n"
  "   for(int j = 0; j<repeat_op[0]; j++)\n"
  "      value += A[i] * B[i];\n"
  "   C[i] = value;\n"
  "}\n"
  "__kernel void AdB(__global float C[],__global const float A[],__global const float B[],__global const float repeat_op[])\n"
  "{\n"
  "   unsigned int i = get_global_id(0);\n"
  "   float value = 0;\n"
  "   for(int j = 0; j<repeat_op[0]; j++)\n"
  "      value += A[i] / B[i];\n"
  "   C[i] = value;\n"
  "}\n";

/*
 * C = A + B -- device
 */
void ABd(float Ch[],float Ah[],float Bh[],unsigned int num_add,unsigned int op,unsigned int repeat_op,unsigned int thread_num)
{
   //  Float size * num_add (num_add is number of random values to add)
   unsigned int N = num_add*sizeof(float);
   float ro[1] = {(float)repeat_op};

   // Allocate device memory and copy A&B from host to device
   cl_int  err;
   cl_mem Ad = clCreateBuffer(context,CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR,N,Ah,&err);
   if (err) Fatal("Cannot create and copy A from host to device\n");
   cl_mem Bd = clCreateBuffer(context,CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR,N,Bh,&err);
   if (err) Fatal("Cannot create and copy B from host to device\n");
   cl_mem repeat_opd = clCreateBuffer(context,CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR,1*sizeof(float),ro,&err);
   if (err) Fatal("Cannot create and copy repeat_op from host to device\n");

   //printf("After allocation of A and B\n");
   //  Allocate device memory for C on device
   cl_mem Cd = clCreateBuffer(context,CL_MEM_WRITE_ONLY,N,NULL,&err);
   if (err) Fatal("Cannot create C on device\n");
   
   //printf("After allocation of C\n");
   //  Compile kernel
   cl_program prog = clCreateProgramWithSource(context,1,&source,0,&err);
   if (err) Fatal("Cannot create program\n");
   if (clBuildProgram(prog,0,NULL,NULL,NULL,NULL))
   {
      char log[1048576];
      if (clGetProgramBuildInfo(prog,devid,CL_PROGRAM_BUILD_LOG,sizeof(log),log,NULL))
         Fatal("Cannot get build log\n");
      else
         Fatal("Cannot build program\n%s\n",log);
   }
   cl_kernel kernel = clCreateKernel(prog,"ApB",&err);
   if(op == 1)
      kernel = clCreateKernel(prog,"AsB",&err);
   else if(op == 2)
      kernel = clCreateKernel(prog,"AmB",&err);
   else if(op == 3)
      kernel = clCreateKernel(prog,"AdB",&err);
   if (err) Fatal("Cannot create kernel\n");

   //  Set parameters for kernel
   if (clSetKernelArg(kernel,0,sizeof(cl_mem),&Cd)) Fatal("Cannot set kernel parameter Cd\n");
   if (clSetKernelArg(kernel,1,sizeof(cl_mem),&Ad)) Fatal("Cannot set kernel parameter Ad\n");
   if (clSetKernelArg(kernel,2,sizeof(cl_mem),&Bd)) Fatal("Cannot set kernel parameter Bd\n");
   if (clSetKernelArg(kernel,3,sizeof(cl_mem),&repeat_opd)) Fatal("Cannot set kernel parameter repeat_opd\n");

   //printf("After setting kernel paramters\n");
   //  Run kernel
   size_t Global[1] = {num_add};
   size_t Local[1]  = {thread_num};
   //printf("After setting Global/Local values - Global[0] = %d, Local[0] = %d\n", Global[0], Local[0]);
   if (clEnqueueNDRangeKernel(queue,kernel,1,NULL,Global,Local,0,NULL,NULL)) Fatal("Cannot run kernel\n");

   //printf("After running kernel\n");
   //  Release kernel and program
   if (clReleaseKernel(kernel)) Fatal("Cannot release kernel\n");
   if (clReleaseProgram(prog)) Fatal("Cannot release program\n");

   //printf("After releasing kernel and program\n");
   // Copy C from device to host (block until done)
   if (clEnqueueReadBuffer(queue,Cd,CL_TRUE,0,N,Ch,0,NULL,NULL)) Fatal("Cannot copy C from device to host\n");

   //printf("After copying from device to host\n");
   //  Free device memory
   clReleaseMemObject(Ad);
   clReleaseMemObject(Bd);
   clReleaseMemObject(repeat_opd);
   clReleaseMemObject(Cd);
   //printf("After release mem object\n");
}

/*
 *  main
 */
int main(int argc, char* argv[])
{
   //  Process options
   int opt;
   int verbose=0;
   while ((opt=getopt(argc,argv,"v"))!=-1)
   {
      if (opt=='v')
         verbose++;
      else
         Fatal("Usage: [-v] <block width> <number of blocks>\n");
   }
   argc -= optind;
   argv += optind;
 
   //  Get width and number of blocks
   if (argc!=2) Fatal("Usage: [-v] <number of values to add> <number of times to repeat calculation>\n");
   int num_add = atoi(argv[0]);
   if (num_add<1) Fatal("num_add out of range %d\n",num_add);
   int repeat_num = atoi(argv[1]);
   if (repeat_num<1 || repeat_num>20) Fatal("repeat_num out of range %d, expect between 1 and 20\n",repeat_num);
   //  Total width is block times number of blocks
   int N = num_add*sizeof(float);

   //  Initialize GPU
   int Mw = InitGPU(verbose);
   int thread_num = 4000;
   while(Mw < thread_num)
	   thread_num /= 2;
   //if (Mw*2<num_add) Fatal("Thread count %d exceeds max work group size of %d\n",num_add,Mw);
   printf("num_add=%d, repeat_num=%d, max work group=%d\n",num_add, repeat_num,Mw);

   if (num_add%thread_num != 0) Fatal("num_add must be multiple of %d.  num_add = %d\n",thread_num, num_add);

   // Allocate host matrices A/B/C/R
   float* Ah = (float*)malloc(N);
   float* Bh = (float*)malloc(N);
   float* Ch = (float*)malloc(N);
   float* Rh = (float*)malloc(N);
   if (!Ah || !Bh || !Ch || !Rh) Fatal("Cannot allocate host memory\n");

   //printf("Before randominit\n");
   // Initialize A & B
   srand(9999);
   RandomInit(Ah,num_add);
   RandomInit(Bh,num_add);
   //printf("After randominit\n");
   float Th = 0;
   float Td = 0;
   double r2=0;
   double aTh = Th;
   double aTd = Td;
   double ar2 = r2;

   for(int repeat_op = 1;repeat_op<61;repeat_op=repeat_op+15)
   {
	 for(int op = 0; op < 4; op++)
	 {
		for(int repeat = 0; repeat < repeat_num; repeat++)
		{	   
		   //  Compute R = AB on host
		   Elapsed();
		   ABh(Rh,Ah,Bh,num_add,op,repeat_op);
		   Th = Elapsed();
		   //printf("After host\n");

		   //  Compute C = AB on device
		   Elapsed();
		   ABd(Ch,Ah,Bh,num_add,op,repeat_op,(unsigned int)thread_num);
		   Td = Elapsed();
		   //printf("After device\n");

		   //  Compute difference between R and C
		   r2=0;
		   for (int i=0;i<num_add;i++)
		   {
			  r2 += fabs(Ch[i]-Rh[i]);
			  if(0 && (i == num_add-1))
			     printf("Ah[i] = %f, Bh[i] = %f, Ch[i] = %f, Rh[i] = %f\n",Ah[i],Bh[i],Ch[i],Rh[i]);		  
		   }
		   r2 /= num_add;
		   
		   aTh += Th;
		   aTd += Td;
		   ar2 += r2;
		   
		   if(0 && (repeat == 0 || repeat == repeat_num -1))
		   {
			  //  Print results
			  if(op == 0)
				 printf("Add results\n");
			  else if(op == 1)
				 printf("Subtract results\n");
			  else if(op == 2)
				 printf("Multiply results\n");
			  else if(op == 3)
				 printf("Divide results\n");
			  else if(op == 3)
				 printf("Mixed results\n");
			  printf("Host   Time = %6.3f s\n",Th);
			  printf("Device Time = %6.3f s\n",Td);
			  printf("Speedup = %.1f\n",Th/Td);
			  printf("Difference = %.2e\n\n",r2);
		   }
		}

		if(op == 0)
		   printf("Add results\n");
		else if(op == 1)
		   printf("Subtract results\n");
		else if(op == 2)
		   printf("Multiply results\n");
		else if(op == 3)
		   printf("Divide results\n");
	    //  Print results
		printf("Repeat operation within task = %d\n",repeat_op);
	    printf("Avg Host   Time = %6.3f s\n",aTh/repeat_num);
	    printf("Avg Device Time = %6.3f s\n",aTd/repeat_num);
	    printf("Avg Speedup = %.1f\n",aTh/aTd);
	    printf("Avg Difference = %.2e\n\n\n",ar2/repeat_num);
	 }
   }
	
   //  Free host memory
   free(Ah);
   free(Bh);
   free(Ch);
   free(Rh);

   //  Done
   return 0;
}
