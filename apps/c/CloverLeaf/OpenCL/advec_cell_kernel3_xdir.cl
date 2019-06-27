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

inline void
advec_cell_kernel3_xdir(const ptr_double vol_flux_x, const ptr_double pre_vol,
                        const ptr_int xx, const ptr_double vertexdx,
                        const ptr_double density1, const ptr_double energy1,
                        ptr_double mass_flux_x, ptr_double ener_flux,
                        const field_type field) {

  double sigmat, sigmav, sigmam, sigma3, sigma4;
  double diffuw, diffdw, limiter;
  double one_by_six = 1.0 / 6.0;

  int x_max = field.x_max;

  int upwind, donor, downwind, dif;

  if (OPS_ACCS(vol_flux_x, 0, 0) > 0.0) {
    upwind = -2;
    donor = -1;
    downwind = 0;
    dif = donor;
  } else if (OPS_ACCS(xx, 1, 0) < x_max + 2 - 2) {
    upwind = 1;
    donor = 0;
    downwind = -1;
    dif = upwind;
  } else {
    upwind = 0;
    donor = 0;
    downwind = -1;
    dif = upwind;
  }

  sigmat = fabs(OPS_ACCS(vol_flux_x, 0, 0)) / OPS_ACCS(pre_vol, donor, 0);
  sigma3 =
      (1.0 + sigmat) * (OPS_ACCS(vertexdx, 0, 0) / OPS_ACCS(vertexdx, dif, 0));
  sigma4 = 2.0 - sigmat;

  sigmav = sigmat;

  diffuw = OPS_ACCS(density1, donor, 0) - OPS_ACCS(density1, upwind, 0);
  diffdw = OPS_ACCS(density1, downwind, 0) - OPS_ACCS(density1, donor, 0);

  if ((diffuw * diffdw) > 0.0)
    limiter = (1.0 - sigmav) * SIGN(1.0, diffdw) *
              MIN(MIN(fabs(diffuw), fabs(diffdw)),
                  one_by_six * (sigma3 * fabs(diffuw) + sigma4 * fabs(diffdw)));
  else
    limiter = 0.0;

  OPS_ACCS(mass_flux_x, 0, 0) =
      (OPS_ACCS(vol_flux_x, 0, 0)) * (OPS_ACCS(density1, donor, 0) + limiter);

  sigmam = fabs(OPS_ACCS(mass_flux_x, 0, 0)) /
           (OPS_ACCS(density1, donor, 0) * OPS_ACCS(pre_vol, donor, 0));
  diffuw = OPS_ACCS(energy1, donor, 0) - OPS_ACCS(energy1, upwind, 0);
  diffdw = OPS_ACCS(energy1, downwind, 0) - OPS_ACCS(energy1, donor, 0);

  if ((diffuw * diffdw) > 0.0)
    limiter = (1.0 - sigmam) * SIGN(1.0, diffdw) *
              MIN(MIN(fabs(diffuw), fabs(diffdw)),
                  one_by_six * (sigma3 * fabs(diffuw) + sigma4 * fabs(diffdw)));
  else
    limiter = 0.0;

  OPS_ACCS(ener_flux, 0, 0) =
      OPS_ACCS(mass_flux_x, 0, 0) * (OPS_ACCS(energy1, donor, 0) + limiter);
}

__kernel void ops_advec_cell_kernel3_xdir(
    __global const double *restrict arg0, __global const double *restrict arg1,
    __global const int *restrict arg2, __global const double *restrict arg3,
    __global const double *restrict arg4, __global const double *restrict arg5,
    __global double *restrict arg6, __global double *restrict arg7,
    __constant const struct field_type *restrict field, const int base0,
    const int base1, const int base2, const int base3, const int base4,
    const int base5, const int base6, const int base7, const int size0,
    const int size1) {

  int idx_y = get_global_id(1);
  int idx_x = get_global_id(0);

  if (idx_x < size0 && idx_y < size1) {
    const ptr_double ptr0 = {
        &arg0[base0 + idx_x * 1 * 1 +
              idx_y * 1 * 1 * xdim0_advec_cell_kernel3_xdir],
        xdim0_advec_cell_kernel3_xdir};
    const ptr_double ptr1 = {
        &arg1[base1 + idx_x * 1 * 1 +
              idx_y * 1 * 1 * xdim1_advec_cell_kernel3_xdir],
        xdim1_advec_cell_kernel3_xdir};
    const ptr_int ptr2 = {&arg2[base2 + idx_x * 1 * 1 +
                                idx_y * 0 * 1 * xdim2_advec_cell_kernel3_xdir],
                          xdim2_advec_cell_kernel3_xdir};
    const ptr_double ptr3 = {
        &arg3[base3 + idx_x * 1 * 1 +
              idx_y * 0 * 1 * xdim3_advec_cell_kernel3_xdir],
        xdim3_advec_cell_kernel3_xdir};
    const ptr_double ptr4 = {
        &arg4[base4 + idx_x * 1 * 1 +
              idx_y * 1 * 1 * xdim4_advec_cell_kernel3_xdir],
        xdim4_advec_cell_kernel3_xdir};
    const ptr_double ptr5 = {
        &arg5[base5 + idx_x * 1 * 1 +
              idx_y * 1 * 1 * xdim5_advec_cell_kernel3_xdir],
        xdim5_advec_cell_kernel3_xdir};
    ptr_double ptr6 = {&arg6[base6 + idx_x * 1 * 1 +
                             idx_y * 1 * 1 * xdim6_advec_cell_kernel3_xdir],
                       xdim6_advec_cell_kernel3_xdir};
    ptr_double ptr7 = {&arg7[base7 + idx_x * 1 * 1 +
                             idx_y * 1 * 1 * xdim7_advec_cell_kernel3_xdir],
                       xdim7_advec_cell_kernel3_xdir};
    advec_cell_kernel3_xdir(ptr0, ptr1, ptr2, ptr3, ptr4, ptr5, ptr6, ptr7,
                            *field);
  }
}
