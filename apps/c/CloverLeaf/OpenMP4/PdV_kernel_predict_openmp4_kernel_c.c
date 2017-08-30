//
// auto-generated by ops.py
//
#include "./OpenMP4/clover_leaf_common.h"
#include <omp.h>
#define OPS_GPU

extern int xdim0_PdV_kernel_predict;
extern int xdim1_PdV_kernel_predict;
extern int xdim2_PdV_kernel_predict;
extern int xdim3_PdV_kernel_predict;
extern int xdim4_PdV_kernel_predict;
extern int xdim5_PdV_kernel_predict;
extern int xdim6_PdV_kernel_predict;
extern int xdim7_PdV_kernel_predict;
extern int xdim8_PdV_kernel_predict;
extern int xdim9_PdV_kernel_predict;
extern int xdim10_PdV_kernel_predict;
extern int xdim11_PdV_kernel_predict;

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6
#undef OPS_ACC7
#undef OPS_ACC8
#undef OPS_ACC9
#undef OPS_ACC10
#undef OPS_ACC11

#define OPS_ACC0(x, y)                                                         \
  (n_x * 1 * 1 + n_y * xdim0_PdV_kernel_predict * 1 * 1 + x +                  \
   xdim0_PdV_kernel_predict * (y))
#define OPS_ACC1(x, y)                                                         \
  (n_x * 1 * 1 + n_y * xdim1_PdV_kernel_predict * 1 * 1 + x +                  \
   xdim1_PdV_kernel_predict * (y))
#define OPS_ACC2(x, y)                                                         \
  (n_x * 1 * 1 + n_y * xdim2_PdV_kernel_predict * 1 * 1 + x +                  \
   xdim2_PdV_kernel_predict * (y))
#define OPS_ACC3(x, y)                                                         \
  (n_x * 1 * 1 + n_y * xdim3_PdV_kernel_predict * 1 * 1 + x +                  \
   xdim3_PdV_kernel_predict * (y))
#define OPS_ACC4(x, y)                                                         \
  (n_x * 1 * 1 + n_y * xdim4_PdV_kernel_predict * 1 * 1 + x +                  \
   xdim4_PdV_kernel_predict * (y))
#define OPS_ACC5(x, y)                                                         \
  (n_x * 1 * 1 + n_y * xdim5_PdV_kernel_predict * 1 * 1 + x +                  \
   xdim5_PdV_kernel_predict * (y))
#define OPS_ACC6(x, y)                                                         \
  (n_x * 1 * 1 + n_y * xdim6_PdV_kernel_predict * 1 * 1 + x +                  \
   xdim6_PdV_kernel_predict * (y))
#define OPS_ACC7(x, y)                                                         \
  (n_x * 1 * 1 + n_y * xdim7_PdV_kernel_predict * 1 * 1 + x +                  \
   xdim7_PdV_kernel_predict * (y))
#define OPS_ACC8(x, y)                                                         \
  (n_x * 1 * 1 + n_y * xdim8_PdV_kernel_predict * 1 * 1 + x +                  \
   xdim8_PdV_kernel_predict * (y))
#define OPS_ACC9(x, y)                                                         \
  (n_x * 1 * 1 + n_y * xdim9_PdV_kernel_predict * 1 * 1 + x +                  \
   xdim9_PdV_kernel_predict * (y))
#define OPS_ACC10(x, y)                                                        \
  (n_x * 1 * 1 + n_y * xdim10_PdV_kernel_predict * 1 * 1 + x +                 \
   xdim10_PdV_kernel_predict * (y))
#define OPS_ACC11(x, y)                                                        \
  (n_x * 1 * 1 + n_y * xdim11_PdV_kernel_predict * 1 * 1 + x +                 \
   xdim11_PdV_kernel_predict * (y))

// user function

void PdV_kernel_predict_c_wrapper(double *p_a0, double *p_a1, double *p_a2,
                                  double *p_a3, double *p_a4, double *p_a5,
                                  double *p_a6, double *p_a7, double *p_a8,
                                  double *p_a9, double *p_a10, double *p_a11,
                                  int x_size, int y_size) {
#ifdef OPS_GPU

#pragma omp target teams distribute parallel for schedule(static, 1)
#endif
  for (int i = 0; i < y_size * x_size; i++) {
    int n_x = i % x_size;
    int n_y = i / x_size;
    const double *xarea = p_a0;

    const double *xvel0 = p_a1;
    const double *yarea = p_a2;

    const double *yvel0 = p_a3;
    double *volume_change = p_a4;

    const double *volume = p_a5;
    const double *pressure = p_a6;

    const double *density0 = p_a7;
    double *density1 = p_a8;

    const double *viscosity = p_a9;
    const double *energy0 = p_a10;

    double *energy1 = p_a11;

    double recip_volume, energy_change;
    double right_flux, left_flux, top_flux, bottom_flux, total_flux;

    left_flux = (xarea[OPS_ACC0(0, 0)] *
                 (xvel0[OPS_ACC1(0, 0)] + xvel0[OPS_ACC1(0, 1)] +
                  xvel0[OPS_ACC1(0, 0)] + xvel0[OPS_ACC1(0, 1)])) *
                0.25 * dt * 0.5;
    right_flux = (xarea[OPS_ACC0(1, 0)] *
                  (xvel0[OPS_ACC1(1, 0)] + xvel0[OPS_ACC1(1, 1)] +
                   xvel0[OPS_ACC1(1, 0)] + xvel0[OPS_ACC1(1, 1)])) *
                 0.25 * dt * 0.5;

    bottom_flux = (yarea[OPS_ACC2(0, 0)] *
                   (yvel0[OPS_ACC3(0, 0)] + yvel0[OPS_ACC3(1, 0)] +
                    yvel0[OPS_ACC3(0, 0)] + yvel0[OPS_ACC3(1, 0)])) *
                  0.25 * dt * 0.5;
    top_flux = (yarea[OPS_ACC2(0, 1)] *
                (yvel0[OPS_ACC3(0, 1)] + yvel0[OPS_ACC3(1, 1)] +
                 yvel0[OPS_ACC3(0, 1)] + yvel0[OPS_ACC3(1, 1)])) *
               0.25 * dt * 0.5;

    total_flux = right_flux - left_flux + top_flux - bottom_flux;

    volume_change[OPS_ACC4(0, 0)] =
        (volume[OPS_ACC5(0, 0)]) / (volume[OPS_ACC5(0, 0)] + total_flux);

    recip_volume = 1.0 / volume[OPS_ACC5(0, 0)];

    energy_change = (pressure[OPS_ACC6(0, 0)] / density0[OPS_ACC7(0, 0)] +
                     viscosity[OPS_ACC9(0, 0)] / density0[OPS_ACC7(0, 0)]) *
                    total_flux * recip_volume;
    energy1[OPS_ACC11(0, 0)] = energy0[OPS_ACC10(0, 0)] - energy_change;
    density1[OPS_ACC8(0, 0)] =
        density0[OPS_ACC7(0, 0)] * volume_change[OPS_ACC4(0, 0)];
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6
#undef OPS_ACC7
#undef OPS_ACC8
#undef OPS_ACC9
#undef OPS_ACC10
#undef OPS_ACC11
