//
// auto-generated by ops.py
//

#define OPS_GPU

int xdim0_update_halo_kernel1_t2;
int xdim1_update_halo_kernel1_t2;
int xdim2_update_halo_kernel1_t2;
int xdim3_update_halo_kernel1_t2;
int xdim4_update_halo_kernel1_t2;
int xdim5_update_halo_kernel1_t2;

// user function
#pragma acc routine

inline void update_halo_kernel1_t2(ptr_double density0, ptr_double energy0,
                                   ptr_double energy1, ptr_double u,
                                   ptr_double p, ptr_double sd,
                                   const int *fields) {
  if (fields[FIELD_DENSITY] == 1)
    OPS_ACC(density0, 0, 0) = OPS_ACC(density0, 0, -3);
  if (fields[FIELD_ENERGY0] == 1)
    OPS_ACC(energy0, 0, 0) = OPS_ACC(energy0, 0, -3);
  if (fields[FIELD_ENERGY1] == 1)
    OPS_ACC(energy1, 0, 0) = OPS_ACC(energy1, 0, -3);
  if (fields[FIELD_U] == 1)
    OPS_ACC(u, 0, 0) = OPS_ACC(u, 0, -3);
  if (fields[FIELD_P] == 1)
    OPS_ACC(p, 0, 0) = OPS_ACC(p, 0, -3);
  if (fields[FIELD_SD] == 1)
    OPS_ACC(sd, 0, 0) = OPS_ACC(sd, 0, -3);
}

void update_halo_kernel1_t2_c_wrapper(double *p_a0, double *p_a1, double *p_a2,
                                      double *p_a3, double *p_a4, double *p_a5,
                                      int *p_a6, int x_size, int y_size) {
#ifdef OPS_GPU
#pragma acc parallel deviceptr(p_a0, p_a1, p_a2, p_a3, p_a4, p_a5, p_a6)
#pragma acc loop
#endif
  for (int n_y = 0; n_y < y_size; n_y++) {
#ifdef OPS_GPU
#pragma acc loop
#endif
    for (int n_x = 0; n_x < x_size; n_x++) {
      ptr_double ptr0 = {p_a0 + n_x * 1 * 1 +
                             n_y * xdim0_update_halo_kernel1_t2 * 1 * 1,
                         xdim0_update_halo_kernel1_t2};
      ptr_double ptr1 = {p_a1 + n_x * 1 * 1 +
                             n_y * xdim1_update_halo_kernel1_t2 * 1 * 1,
                         xdim1_update_halo_kernel1_t2};
      ptr_double ptr2 = {p_a2 + n_x * 1 * 1 +
                             n_y * xdim2_update_halo_kernel1_t2 * 1 * 1,
                         xdim2_update_halo_kernel1_t2};
      ptr_double ptr3 = {p_a3 + n_x * 1 * 1 +
                             n_y * xdim3_update_halo_kernel1_t2 * 1 * 1,
                         xdim3_update_halo_kernel1_t2};
      ptr_double ptr4 = {p_a4 + n_x * 1 * 1 +
                             n_y * xdim4_update_halo_kernel1_t2 * 1 * 1,
                         xdim4_update_halo_kernel1_t2};
      ptr_double ptr5 = {p_a5 + n_x * 1 * 1 +
                             n_y * xdim5_update_halo_kernel1_t2 * 1 * 1,
                         xdim5_update_halo_kernel1_t2};
      update_halo_kernel1_t2(ptr0, ptr1, ptr2, ptr3, ptr4, ptr5, p_a6);
    }
  }
}
