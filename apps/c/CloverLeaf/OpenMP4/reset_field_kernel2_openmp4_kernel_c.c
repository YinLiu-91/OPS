//
// auto-generated by ops.py
//
#include "./OpenMP4/clover_leaf_common.h"

#define OPS_GPU

extern int xdim0_reset_field_kernel2;
extern int xdim1_reset_field_kernel2;
extern int xdim2_reset_field_kernel2;
extern int xdim3_reset_field_kernel2;

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3

#define OPS_ACC0(x, y) (x + xdim0_reset_field_kernel2 * (y))
#define OPS_ACC1(x, y) (x + xdim1_reset_field_kernel2 * (y))
#define OPS_ACC2(x, y) (x + xdim2_reset_field_kernel2 * (y))
#define OPS_ACC3(x, y) (x + xdim3_reset_field_kernel2 * (y))

// user function

void reset_field_kernel2_c_wrapper(double *p_a0, int base0, int tot0,
                                   double *p_a1, int base1, int tot1,
                                   double *p_a2, int base2, int tot2,
                                   double *p_a3, int base3, int tot3,
                                   int x_size, int y_size) {
#ifdef OPS_GPU

#pragma omp target teams distribute parallel for num_teams(OPS_threads)        \
    thread_limit(OPS_threads_for_block) schedule(static, 1)
#endif
  for (int i = 0; i < y_size * x_size; i++) {
    int n_x = i % x_size;
    int n_y = i / x_size;
    double *xvel0 =
        p_a0 + base0 + n_x * 1 * 1 + n_y * xdim0_reset_field_kernel2 * 1 * 1;

    const double *xvel1 =
        p_a1 + base1 + n_x * 1 * 1 + n_y * xdim1_reset_field_kernel2 * 1 * 1;
    double *yvel0 =
        p_a2 + base2 + n_x * 1 * 1 + n_y * xdim2_reset_field_kernel2 * 1 * 1;

    const double *yvel1 =
        p_a3 + base3 + n_x * 1 * 1 + n_y * xdim3_reset_field_kernel2 * 1 * 1;

    xvel0[OPS_ACC0(0, 0)] = xvel1[OPS_ACC1(0, 0)];
    yvel0[OPS_ACC2(0, 0)] = yvel1[OPS_ACC3(0, 0)];
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
