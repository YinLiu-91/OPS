//
// auto-generated by ops.py
//

#define OPS_GPU

int xdim0_update_halo_kernel2_yvel_plus_2_b;
int xdim1_update_halo_kernel2_yvel_plus_2_b;

// user function
#pragma acc routine

inline void update_halo_kernel2_yvel_plus_2_b(ptr_double yvel0,
                                              ptr_double yvel1,
                                              const int *fields) {
  if (fields[FIELD_YVEL0] == 1)
    OPS_ACC(yvel0, 0, 0) = OPS_ACC(yvel0, -2, 0);
  if (fields[FIELD_YVEL1] == 1)
    OPS_ACC(yvel1, 0, 0) = OPS_ACC(yvel1, -2, 0);
}

void update_halo_kernel2_yvel_plus_2_b_c_wrapper(double *p_a0, double *p_a1,
                                                 int *p_a2, int x_size,
                                                 int y_size) {
#ifdef OPS_GPU
#pragma acc parallel deviceptr(p_a0, p_a1, p_a2)
#pragma acc loop
#endif
  for (int n_y = 0; n_y < y_size; n_y++) {
#ifdef OPS_GPU
#pragma acc loop
#endif
    for (int n_x = 0; n_x < x_size; n_x++) {
      ptr_double ptr0 = {p_a0 + n_x * 1 * 1 +
                             n_y * xdim0_update_halo_kernel2_yvel_plus_2_b * 1 *
                                 1,
                         xdim0_update_halo_kernel2_yvel_plus_2_b};
      ptr_double ptr1 = {p_a1 + n_x * 1 * 1 +
                             n_y * xdim1_update_halo_kernel2_yvel_plus_2_b * 1 *
                                 1,
                         xdim1_update_halo_kernel2_yvel_plus_2_b};
      update_halo_kernel2_yvel_plus_2_b(ptr0, ptr1, p_a2);
    }
  }
}
