//
// auto-generated by ops.py
//
#include "./OpenMP4/clover_leaf_common.h"

#define OPS_GPU

extern int xdim0_update_halo_kernel2_zvel_minus_2_front;
extern int ydim0_update_halo_kernel2_zvel_minus_2_front;
extern int xdim1_update_halo_kernel2_zvel_minus_2_front;
extern int ydim1_update_halo_kernel2_zvel_minus_2_front;

#undef OPS_ACC0
#undef OPS_ACC1

#define OPS_ACC0(x, y, z)                                                      \
  (x + xdim0_update_halo_kernel2_zvel_minus_2_front * (y) +                    \
   xdim0_update_halo_kernel2_zvel_minus_2_front *                              \
       ydim0_update_halo_kernel2_zvel_minus_2_front * (z))
#define OPS_ACC1(x, y, z)                                                      \
  (x + xdim1_update_halo_kernel2_zvel_minus_2_front * (y) +                    \
   xdim1_update_halo_kernel2_zvel_minus_2_front *                              \
       ydim1_update_halo_kernel2_zvel_minus_2_front * (z))

// user function

void update_halo_kernel2_zvel_minus_2_front_c_wrapper(
    double *p_a0, int base0, int tot0, double *p_a1, int base1, int tot1,
    int *p_a2, int tot2, int x_size, int y_size, int z_size) {
#ifdef OPS_GPU

#pragma omp target teams distribute parallel for num_teams(OPS_threads)        \
    thread_limit(OPS_threads_for_block) collapse(3) schedule(static, 1)
#endif
  for (int n_z = 0; n_z < z_size; n_z++) {
    for (int n_y = 0; n_y < y_size; n_y++) {
      for (int n_x = 0; n_x < x_size; n_x++) {
        double *zvel0 =
            p_a0 + base0 + n_x * 1 * 1 +
            n_y * xdim0_update_halo_kernel2_zvel_minus_2_front * 1 * 1 +
            n_z * xdim0_update_halo_kernel2_zvel_minus_2_front *
                ydim0_update_halo_kernel2_zvel_minus_2_front * 1;

        double *zvel1 =
            p_a1 + base1 + n_x * 1 * 1 +
            n_y * xdim1_update_halo_kernel2_zvel_minus_2_front * 1 * 1 +
            n_z * xdim1_update_halo_kernel2_zvel_minus_2_front *
                ydim1_update_halo_kernel2_zvel_minus_2_front * 1;

        const int *fields = p_a2;

        if (fields[FIELD_ZVEL0] == 1)
          zvel0[OPS_ACC0(0, 0, 0)] = -zvel0[OPS_ACC0(0, 0, -2)];
        if (fields[FIELD_ZVEL1] == 1)
          zvel1[OPS_ACC1(0, 0, 0)] = -zvel1[OPS_ACC1(0, 0, -2)];
      }
    }
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
