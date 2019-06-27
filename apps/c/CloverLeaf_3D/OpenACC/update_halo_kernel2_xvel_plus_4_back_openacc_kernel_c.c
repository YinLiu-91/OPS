//
// auto-generated by ops.py
//

#define OPS_GPU

int xdim0_update_halo_kernel2_xvel_plus_4_back;
int ydim0_update_halo_kernel2_xvel_plus_4_back;
int xdim1_update_halo_kernel2_xvel_plus_4_back;
int ydim1_update_halo_kernel2_xvel_plus_4_back;

// user function
#pragma acc routine

inline void update_halo_kernel2_xvel_plus_4_back(ptr_double xvel0,
                                                 ptr_double xvel1,
                                                 const int *fields) {
  if (fields[FIELD_XVEL0] == 1)
    OPS_ACC(xvel0, 0, 0, 0) = OPS_ACC(xvel0, 0, 0, 4);
  if (fields[FIELD_XVEL1] == 1)
    OPS_ACC(xvel1, 0, 0, 0) = OPS_ACC(xvel1, 0, 0, 4);
}

void update_halo_kernel2_xvel_plus_4_back_c_wrapper(double *p_a0, double *p_a1,
                                                    int *p_a2, int x_size,
                                                    int y_size, int z_size) {
#ifdef OPS_GPU
#pragma acc parallel deviceptr(p_a0, p_a1, p_a2)
#pragma acc loop
#endif
  for (int n_z = 0; n_z < z_size; n_z++) {
#ifdef OPS_GPU
#pragma acc loop
#endif
    for (int n_y = 0; n_y < y_size; n_y++) {
#ifdef OPS_GPU
#pragma acc loop
#endif
      for (int n_x = 0; n_x < x_size; n_x++) {
        ptr_double ptr0 = {
            p_a0 + n_x * 1 * 1 +
                n_y * xdim0_update_halo_kernel2_xvel_plus_4_back * 1 * 1 +
                n_z * xdim0_update_halo_kernel2_xvel_plus_4_back *
                    ydim0_update_halo_kernel2_xvel_plus_4_back * 1 * 1,
            xdim0_update_halo_kernel2_xvel_plus_4_back,
            ydim0_update_halo_kernel2_xvel_plus_4_back};
        ptr_double ptr1 = {
            p_a1 + n_x * 1 * 1 +
                n_y * xdim1_update_halo_kernel2_xvel_plus_4_back * 1 * 1 +
                n_z * xdim1_update_halo_kernel2_xvel_plus_4_back *
                    ydim1_update_halo_kernel2_xvel_plus_4_back * 1 * 1,
            xdim1_update_halo_kernel2_xvel_plus_4_back,
            ydim1_update_halo_kernel2_xvel_plus_4_back};
        update_halo_kernel2_xvel_plus_4_back(ptr0, ptr1, p_a2);
      }
    }
  }
}
