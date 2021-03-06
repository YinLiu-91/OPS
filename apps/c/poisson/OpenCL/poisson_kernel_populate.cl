//
// auto-generated by ops.py
//

#ifdef OCL_FMA
#pragma OPENCL FP_CONTRACT ON
#else
#pragma OPENCL FP_CONTRACT OFF
#endif
#pragma OPENCL EXTENSION cl_khr_fp64:enable

#include "user_types.h"
#define OPS_2D
#define OPS_API 2
#define OPS_NO_GLOBALS
#include "ops_macros.h"
#include "ops_opencl_reduction.h"

#ifndef MIN
#define MIN(a,b) ((a<b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b) ((a>b) ? (a) : (b))
#endif
#ifndef SIGN
#define SIGN(a,b) ((b<0.0) ? (a*(-1)) : (a))
#endif
#define OPS_READ 0
#define OPS_WRITE 1
#define OPS_RW 2
#define OPS_INC 3
#define OPS_MIN 4
#define OPS_MAX 5

//user function

void poisson_kernel_populate(const int *dispx,
  const int *dispy,
  const int *idx,
  ptr_double u,
  ptr_double f,
  ptr_double ref, const double dx, const double dy)
{
  double x = dx * (double)(idx[0]+dispx[0]);
  double y = dy * (double)(idx[1]+dispy[0]);

  OPS_ACCS(u, 0,0) = myfun(sin(M_PI*x),cos(2.0*M_PI*y))-1.0;
  OPS_ACCS(f, 0,0) = -5.0*M_PI*M_PI*sin(M_PI*x)*cos(2.0*M_PI*y);
  OPS_ACCS(ref, 0,0) = sin(M_PI*x)*cos(2.0*M_PI*y);

}


__kernel void ops_poisson_kernel_populate(
const int arg0,
const int arg1,
__global double* restrict arg3,
__global double* restrict arg4,
__global double* restrict arg5,
const double dx,
const double dy,
const int base3,
const int base4,
const int base5,
int arg_idx0, int arg_idx1,
const int size0,
const int size1 ){


  int idx_y = get_global_id(1);
  int idx_x = get_global_id(0);

  int arg_idx[2];
  arg_idx[0] = arg_idx0+idx_x;
  arg_idx[1] = arg_idx1+idx_y;
  if (idx_x < size0 && idx_y < size1) {
    ptr_double ptr3 = { &arg3[base3 + idx_x * 1*1 + idx_y * 1*1 * xdim3_poisson_kernel_populate], xdim3_poisson_kernel_populate};
    ptr_double ptr4 = { &arg4[base4 + idx_x * 1*1 + idx_y * 1*1 * xdim4_poisson_kernel_populate], xdim4_poisson_kernel_populate};
    ptr_double ptr5 = { &arg5[base5 + idx_x * 1*1 + idx_y * 1*1 * xdim5_poisson_kernel_populate], xdim5_poisson_kernel_populate};
    poisson_kernel_populate(&arg0,
                   &arg1,
                   arg_idx,
                   ptr3,
                   ptr4,
                   ptr5,
                   dx,
                   dy);
  }

}
