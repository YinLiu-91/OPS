//
// auto-generated by ops.py
//

#ifdef OCL_FMA
#pragma OPENCL FP_CONTRACT ON
#else
#pragma OPENCL FP_CONTRACT OFF
#endif
#pragma OPENCL EXTENSION cl_khr_fp64 : enable

#define OPS_3D
#define OPS_API 2
#define OPS_NO_GLOBALS
#include "ops_macros.h"
#include "ops_opencl_reduction.h"

#ifndef MIN
#define MIN(a, b) ((a < b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b) ((a > b) ? (a) : (b))
#endif
#ifndef SIGN
#define SIGN(a, b) ((b < 0.0) ? (a * (-1)) : (a))
#endif
#define OPS_READ 0
#define OPS_WRITE 1
#define OPS_RW 2
#define OPS_INC 3
#define OPS_MIN 4
#define OPS_MAX 5
#define ZERO_double 0.0;
#define INFINITY_double INFINITY;
#define ZERO_float 0.0f;
#define INFINITY_float INFINITY;
#define ZERO_int 0;
#define INFINITY_int INFINITY;
#define ZERO_uint 0;
#define INFINITY_uint INFINITY;
#define ZERO_ll 0;
#define INFINITY_ll INFINITY;
#define ZERO_ull 0;
#define INFINITY_ull INFINITY;
#define ZERO_bool 0;

// user function

void multidim_kernel(ptrm_double val, int *idx) {
  OPS_ACCM(val, 0, 0, 0, 0) = (double)(idx[0]);
  OPS_ACCM(val, 1, 0, 0, 0) = (double)(idx[1]);
  OPS_ACCM(val, 2, 0, 0, 0) = (double)(idx[2]);
}

__kernel void ops_multidim_kernel(__global double *restrict arg0,
                                  const int base0, int arg_idx0, int arg_idx1,
                                  int arg_idx2, const int size0,
                                  const int size1, const int size2) {

  int idx_y = get_global_id(1);
  int idx_z = get_global_id(2);
  int idx_x = get_global_id(0);

  int arg_idx[3];
  arg_idx[0] = arg_idx0 + idx_x;
  arg_idx[1] = arg_idx1 + idx_y;
  arg_idx[2] = arg_idx2 + idx_z;
  if (idx_x < size0 && idx_y < size1 && idx_z < size2) {
#ifdef OPS_SOA
    ptrm_double ptr0 = {
        &arg0[base0 + idx_x * 1 + idx_y * 1 * xdim0_multidim_kernel +
              idx_z * 1 * xdim0_multidim_kernel * ydim0_multidim_kernel],
        xdim0_multidim_kernel, ydim0_multidim_kernel, zdim0_multidim_kernel};
#else
    ptrm_double ptr0 = {
        &arg0[base0 + idx_x * 1 + idx_y * 1 * xdim0_multidim_kernel +
              idx_z * 1 * xdim0_multidim_kernel * ydim0_multidim_kernel],
        xdim0_multidim_kernel, ydim0_multidim_kernel, 3};
#endif
    multidim_kernel(ptr0, arg_idx);
  }
}
