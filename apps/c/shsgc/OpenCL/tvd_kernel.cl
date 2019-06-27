//
// auto-generated by ops.py
//

#ifdef OCL_FMA
#pragma OPENCL FP_CONTRACT ON
#else
#pragma OPENCL FP_CONTRACT OFF
#endif
#pragma OPENCL EXTENSION cl_khr_fp64 : enable

#define OPS_1D
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

void tvd_kernel(const ptrm_double tht, ptrm_double ep2, const double akap2) {
  double maxim;
  for (int m = 0; m < 3; m++) {
    if (OPS_ACCM(tht, m, 0) > OPS_ACCM(tht, m, 1))
      maxim = OPS_ACCM(tht, m, 0);
    else
      maxim = OPS_ACCM(tht, m, 1);
    OPS_ACCM(ep2, m, 0) = akap2 * maxim;
  }
}

__kernel void ops_tvd_kernel(__global const double *restrict arg0,
                             __global double *restrict arg1, const double akap2,
                             const int base0, const int base1,
                             const int size0) {

  int idx_x = get_global_id(0);

  if (idx_x < size0) {
#ifdef OPS_SOA
    const ptrm_double ptr0 = {&arg0[base0 + idx_x * 1 * 3], xdim0_tvd_kernel};
#else
    const ptrm_double ptr0 = {&arg0[base0 + idx_x * 1 * 3], 3};
#endif
#ifdef OPS_SOA
    ptrm_double ptr1 = {&arg1[base1 + idx_x * 1 * 3], xdim1_tvd_kernel};
#else
    ptrm_double ptr1 = {&arg1[base1 + idx_x * 1 * 3], 3};
#endif
    tvd_kernel(ptr0, ptr1, akap2);
  }
}
