//
// auto-generated by ops.py
//

#ifdef OCL_FMA
#pragma OPENCL FP_CONTRACT ON
#else
#pragma OPENCL FP_CONTRACT OFF
#endif
#pragma OPENCL EXTENSION cl_khr_fp64 : enable

#include "user_types.h"
#define OPS_2D
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

void revert_kernel(const ptr_double density0, ptr_double density1,
                   const ptr_double energy0, ptr_double energy1) {

  OPS_ACCS(density1, 0, 0) = OPS_ACCS(density0, 0, 0);
  OPS_ACCS(energy1, 0, 0) = OPS_ACCS(energy0, 0, 0);
}

__kernel void ops_revert_kernel(__global const double *restrict arg0,
                                __global double *restrict arg1,
                                __global const double *restrict arg2,
                                __global double *restrict arg3, const int base0,
                                const int base1, const int base2,
                                const int base3, const int size0,
                                const int size1) {

  int idx_y = get_global_id(1);
  int idx_x = get_global_id(0);

  if (idx_x < size0 && idx_y < size1) {
    const ptr_double ptr0 = {
        &arg0[base0 + idx_x * 1 * 1 + idx_y * 1 * 1 * xdim0_revert_kernel],
        xdim0_revert_kernel};
    ptr_double ptr1 = {
        &arg1[base1 + idx_x * 1 * 1 + idx_y * 1 * 1 * xdim1_revert_kernel],
        xdim1_revert_kernel};
    const ptr_double ptr2 = {
        &arg2[base2 + idx_x * 1 * 1 + idx_y * 1 * 1 * xdim2_revert_kernel],
        xdim2_revert_kernel};
    ptr_double ptr3 = {
        &arg3[base3 + idx_x * 1 * 1 + idx_y * 1 * 1 * xdim3_revert_kernel],
        xdim3_revert_kernel};
    revert_kernel(ptr0, ptr1, ptr2, ptr3);
  }
}
