//
// auto-generated by ops.py
//
#include "./MPI_inline/clover_leaf_common.h"

int xdim0_flux_calc_kernely;
int ydim0_flux_calc_kernely;
int xdim1_flux_calc_kernely;
int ydim1_flux_calc_kernely;
int xdim2_flux_calc_kernely;
int ydim2_flux_calc_kernely;
int xdim3_flux_calc_kernely;
int ydim3_flux_calc_kernely;

#define OPS_ACC0(x, y, z)                                                      \
  (n_x * 1 + n_y * xdim0_flux_calc_kernely * 1 +                               \
   n_z * xdim0_flux_calc_kernely * ydim0_flux_calc_kernely * 1 + x +           \
   xdim0_flux_calc_kernely * (y) +                                             \
   xdim0_flux_calc_kernely * ydim0_flux_calc_kernely * (z))
#define OPS_ACC1(x, y, z)                                                      \
  (n_x * 1 + n_y * xdim1_flux_calc_kernely * 1 +                               \
   n_z * xdim1_flux_calc_kernely * ydim1_flux_calc_kernely * 1 + x +           \
   xdim1_flux_calc_kernely * (y) +                                             \
   xdim1_flux_calc_kernely * ydim1_flux_calc_kernely * (z))
#define OPS_ACC2(x, y, z)                                                      \
  (n_x * 1 + n_y * xdim2_flux_calc_kernely * 1 +                               \
   n_z * xdim2_flux_calc_kernely * ydim2_flux_calc_kernely * 1 + x +           \
   xdim2_flux_calc_kernely * (y) +                                             \
   xdim2_flux_calc_kernely * ydim2_flux_calc_kernely * (z))
#define OPS_ACC3(x, y, z)                                                      \
  (n_x * 1 + n_y * xdim3_flux_calc_kernely * 1 +                               \
   n_z * xdim3_flux_calc_kernely * ydim3_flux_calc_kernely * 1 + x +           \
   xdim3_flux_calc_kernely * (y) +                                             \
   xdim3_flux_calc_kernely * ydim3_flux_calc_kernely * (z))

// user function

void flux_calc_kernely_c_wrapper(double *restrict vol_flux_y,
                                 const double *restrict yarea,
                                 const double *restrict yvel0,
                                 const double *restrict yvel1, int x_size,
                                 int y_size, int z_size) {
#pragma omp parallel for
  for (int n_z = 0; n_z < z_size; n_z++) {
    for (int n_y = 0; n_y < y_size; n_y++) {
      for (int n_x = 0; n_x < x_size; n_x++) {

        vol_flux_y[OPS_ACC0(0, 0, 0)] =
            0.125 * dt * (yarea[OPS_ACC1(0, 0, 0)]) *
            (yvel0[OPS_ACC2(0, 0, 0)] + yvel0[OPS_ACC2(1, 0, 0)] +
             yvel0[OPS_ACC2(0, 0, 1)] + yvel0[OPS_ACC2(1, 0, 1)] +
             yvel1[OPS_ACC3(0, 0, 0)] + yvel1[OPS_ACC3(1, 0, 0)] +
             yvel1[OPS_ACC3(0, 0, 1)] + yvel1[OPS_ACC3(1, 0, 1)]);
      }
    }
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
