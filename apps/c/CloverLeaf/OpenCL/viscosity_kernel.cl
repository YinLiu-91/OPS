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

void viscosity_kernel(const ptr_double xvel0, const ptr_double yvel0,
                      const ptr_double celldx, const ptr_double celldy,
                      const ptr_double pressure, const ptr_double density0,
                      ptr_double viscosity) {

  double ugrad, vgrad, grad2, pgradx, pgrady, pgradx2, pgrady2, grad, ygrad,
      xgrad, div, strain2, limiter, pgrad;

  ugrad = (OPS_ACCS(xvel0, 1, 0) + OPS_ACCS(xvel0, 1, 1)) -
          (OPS_ACCS(xvel0, 0, 0) + OPS_ACCS(xvel0, 0, 1));
  vgrad = (OPS_ACCS(yvel0, 0, 1) + OPS_ACCS(yvel0, 1, 1)) -
          (OPS_ACCS(yvel0, 0, 0) + OPS_ACCS(yvel0, 1, 0));

  div = (OPS_ACCS(celldx, 0, 0)) * (ugrad) + (OPS_ACCS(celldy, 0, 0)) * (vgrad);

  strain2 = 0.5 * (OPS_ACCS(xvel0, 0, 1) + OPS_ACCS(xvel0, 1, 1) -
                   OPS_ACCS(xvel0, 0, 0) - OPS_ACCS(xvel0, 1, 0)) /
                (OPS_ACCS(celldy, 0, 0)) +
            0.5 * (OPS_ACCS(yvel0, 1, 0) + OPS_ACCS(yvel0, 1, 1) -
                   OPS_ACCS(yvel0, 0, 0) - OPS_ACCS(yvel0, 0, 1)) /
                (OPS_ACCS(celldx, 0, 0));

  pgradx = (OPS_ACCS(pressure, 1, 0) - OPS_ACCS(pressure, -1, 0)) /
           (OPS_ACCS(celldx, 0, 0) + OPS_ACCS(celldx, 1, 0));
  pgrady = (OPS_ACCS(pressure, 0, 1) - OPS_ACCS(pressure, 0, -1)) /
           (OPS_ACCS(celldy, 0, 0) + OPS_ACCS(celldy, 0, 1));

  pgradx2 = pgradx * pgradx;
  pgrady2 = pgrady * pgrady;

  limiter = ((0.5 * (ugrad) / OPS_ACCS(celldx, 0, 0)) * pgradx2 +
             (0.5 * (vgrad) / OPS_ACCS(celldy, 0, 0)) * pgrady2 +
             strain2 * pgradx * pgrady) /
            MAX(pgradx2 + pgrady2, 1.0e-16);

  if ((limiter > 0.0) || (div >= 0.0)) {
    OPS_ACCS(viscosity, 0, 0) = 0.0;
  } else {
    pgradx = SIGN(MAX(1.0e-16, fabs(pgradx)), pgradx);
    pgrady = SIGN(MAX(1.0e-16, fabs(pgrady)), pgrady);
    pgrad = sqrt(pgradx * pgradx + pgrady * pgrady);
    xgrad = fabs(OPS_ACCS(celldx, 0, 0) * pgrad / pgradx);
    ygrad = fabs(OPS_ACCS(celldy, 0, 0) * pgrad / pgrady);
    grad = MIN(xgrad, ygrad);
    grad2 = grad * grad;

    OPS_ACCS(viscosity, 0, 0) =
        2.0 * (OPS_ACCS(density0, 0, 0)) * grad2 * limiter * limiter;
  }
}

__kernel void ops_viscosity_kernel(
    __global const double *restrict arg0, __global const double *restrict arg1,
    __global const double *restrict arg2, __global const double *restrict arg3,
    __global const double *restrict arg4, __global const double *restrict arg5,
    __global double *restrict arg6, const int base0, const int base1,
    const int base2, const int base3, const int base4, const int base5,
    const int base6, const int size0, const int size1) {

  int idx_y = get_global_id(1);
  int idx_x = get_global_id(0);

  if (idx_x < size0 && idx_y < size1) {
    const ptr_double ptr0 = {
        &arg0[base0 + idx_x * 1 * 1 + idx_y * 1 * 1 * xdim0_viscosity_kernel],
        xdim0_viscosity_kernel};
    const ptr_double ptr1 = {
        &arg1[base1 + idx_x * 1 * 1 + idx_y * 1 * 1 * xdim1_viscosity_kernel],
        xdim1_viscosity_kernel};
    const ptr_double ptr2 = {
        &arg2[base2 + idx_x * 1 * 1 + idx_y * 0 * 1 * xdim2_viscosity_kernel],
        xdim2_viscosity_kernel};
    const ptr_double ptr3 = {
        &arg3[base3 + idx_x * 0 * 1 + idx_y * 1 * 1 * xdim3_viscosity_kernel],
        xdim3_viscosity_kernel};
    const ptr_double ptr4 = {
        &arg4[base4 + idx_x * 1 * 1 + idx_y * 1 * 1 * xdim4_viscosity_kernel],
        xdim4_viscosity_kernel};
    const ptr_double ptr5 = {
        &arg5[base5 + idx_x * 1 * 1 + idx_y * 1 * 1 * xdim5_viscosity_kernel],
        xdim5_viscosity_kernel};
    ptr_double ptr6 = {
        &arg6[base6 + idx_x * 1 * 1 + idx_y * 1 * 1 * xdim6_viscosity_kernel],
        xdim6_viscosity_kernel};
    viscosity_kernel(ptr0, ptr1, ptr2, ptr3, ptr4, ptr5, ptr6);
  }
}
