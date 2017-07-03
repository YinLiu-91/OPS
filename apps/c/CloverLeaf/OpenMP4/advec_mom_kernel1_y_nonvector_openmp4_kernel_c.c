//
// auto-generated by ops.py
//
#include "./OpenMP4/clover_leaf_common.h"

#define OPS_GPU

extern int xdim0_advec_mom_kernel1_y_nonvector;
extern int xdim1_advec_mom_kernel1_y_nonvector;
extern int xdim2_advec_mom_kernel1_y_nonvector;
extern int xdim3_advec_mom_kernel1_y_nonvector;
extern int xdim4_advec_mom_kernel1_y_nonvector;

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4

#define OPS_ACC0(x, y) (x + xdim0_advec_mom_kernel1_y_nonvector * (y))
#define OPS_ACC1(x, y) (x + xdim1_advec_mom_kernel1_y_nonvector * (y))
#define OPS_ACC2(x, y) (x + xdim2_advec_mom_kernel1_y_nonvector * (y))
#define OPS_ACC3(x, y) (x + xdim3_advec_mom_kernel1_y_nonvector * (y))
#define OPS_ACC4(x, y) (x + xdim4_advec_mom_kernel1_y_nonvector * (y))

// user function

void advec_mom_kernel1_y_nonvector_c_wrapper(double *p_a0, int base0, int tot0,
                                             double *p_a1, int base1, int tot1,
                                             double *p_a2, int base2, int tot2,
                                             double *p_a3, int base3, int tot3,
                                             double *p_a4, int base4, int tot4,
                                             int x_size, int y_size) {
#ifdef OPS_GPU

#pragma omp target teams distribute parallel for num_teams(OPS_threads)        \
    thread_limit(OPS_threads_for_block) schedule(static, 1)
#endif
  for (int i = 0; i < y_size * x_size; i++) {
    int n_x = i % x_size;
    int n_y = i / x_size;
    const double *node_flux = p_a0 + base0 + n_x * 1 * 1 +
                              n_y * xdim0_advec_mom_kernel1_y_nonvector * 1 * 1;

    const double *node_mass_pre =
        p_a1 + base1 + n_x * 1 * 1 +
        n_y * xdim1_advec_mom_kernel1_y_nonvector * 1 * 1;
    double *mom_flux = p_a2 + base2 + n_x * 1 * 1 +
                       n_y * xdim2_advec_mom_kernel1_y_nonvector * 1 * 1;

    const double *celldy = p_a3 + base3 + n_x * 0 * 1 +
                           n_y * xdim3_advec_mom_kernel1_y_nonvector * 1 * 1;
    const double *vel1 = p_a4 + base4 + n_x * 1 * 1 +
                         n_y * xdim4_advec_mom_kernel1_y_nonvector * 1 * 1;

    double sigma, wind, width;
    double vdiffuw, vdiffdw, auw, adw, limiter;
    int upwind, donor, downwind, dif;
    double advec_vel_temp;

    if ((node_flux[OPS_ACC0(0, 0)]) < 0.0) {
      upwind = 2;
      donor = 1;
      downwind = 0;
      dif = donor;
    } else {
      upwind = -1;
      donor = 0;
      downwind = 1;
      dif = upwind;
    }

    sigma = fabs(node_flux[OPS_ACC0(0, 0)]) / node_mass_pre[OPS_ACC1(0, donor)];
    width = celldy[OPS_ACC3(0, 0)];
    vdiffuw = vel1[OPS_ACC4(0, donor)] - vel1[OPS_ACC4(0, upwind)];
    vdiffdw = vel1[OPS_ACC4(0, downwind)] - vel1[OPS_ACC4(0, donor)];
    limiter = 0.0;
    if (vdiffuw * vdiffdw > 0.0) {
      auw = fabs(vdiffuw);
      adw = fabs(vdiffdw);
      wind = 1.0;
      if (vdiffdw <= 0.0)
        wind = -1.0;
      limiter =
          wind * MIN(width * ((2.0 - sigma) * adw / width +
                              (1.0 + sigma) * auw / celldy[OPS_ACC3(0, dif)]) /
                         6.0,
                     MIN(auw, adw));
    }
    advec_vel_temp = vel1[OPS_ACC4(0, donor)] + (1.0 - sigma) * limiter;
    mom_flux[OPS_ACC2(0, 0)] = advec_vel_temp * node_flux[OPS_ACC0(0, 0)];
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
