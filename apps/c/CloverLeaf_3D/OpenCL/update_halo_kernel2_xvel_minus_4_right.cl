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

inline void
update_halo_kernel2_xvel_minus_4_right(ptr_double xvel0, ptr_double xvel1,
                                       const __global int *restrict fields) {
  if (fields[FIELD_XVEL0] == 1)
    OPS_ACCS(xvel0, 0, 0, 0) = -OPS_ACCS(xvel0, -4, 0, 0);
  if (fields[FIELD_XVEL1] == 1)
    OPS_ACCS(xvel1, 0, 0, 0) = -OPS_ACCS(xvel1, -4, 0, 0);
}

__kernel void ops_update_halo_kernel2_xvel_minus_4_right(
    __global double *restrict arg0, __global double *restrict arg1,
    __global const int *restrict arg2, const int base0, const int base1,
    const int size0, const int size1, const int size2) {

  int idx_y = get_global_id(1);
  int idx_z = get_global_id(2);
  int idx_x = get_global_id(0);

  if (idx_x < size0 && idx_y < size1 && idx_z < size2) {
    ptr_double ptr0 = {
        &arg0[base0 + idx_x * 1 * 1 +
              idx_y * 1 * 1 * xdim0_update_halo_kernel2_xvel_minus_4_right +
              idx_z * 1 * 1 * xdim0_update_halo_kernel2_xvel_minus_4_right *
                  ydim0_update_halo_kernel2_xvel_minus_4_right],
        xdim0_update_halo_kernel2_xvel_minus_4_right,
        ydim0_update_halo_kernel2_xvel_minus_4_right};
    ptr_double ptr1 = {
        &arg1[base1 + idx_x * 1 * 1 +
              idx_y * 1 * 1 * xdim1_update_halo_kernel2_xvel_minus_4_right +
              idx_z * 1 * 1 * xdim1_update_halo_kernel2_xvel_minus_4_right *
                  ydim1_update_halo_kernel2_xvel_minus_4_right],
        xdim1_update_halo_kernel2_xvel_minus_4_right,
        ydim1_update_halo_kernel2_xvel_minus_4_right};
    update_halo_kernel2_xvel_minus_4_right(ptr0, ptr1, arg2);
  }
}
