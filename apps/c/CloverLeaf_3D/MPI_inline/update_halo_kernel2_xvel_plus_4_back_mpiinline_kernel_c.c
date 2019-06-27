//
// auto-generated by ops.py
//

int xdim0_update_halo_kernel2_xvel_plus_4_back;
int ydim0_update_halo_kernel2_xvel_plus_4_back;
int xdim1_update_halo_kernel2_xvel_plus_4_back;
int ydim1_update_halo_kernel2_xvel_plus_4_back;

// user function

void update_halo_kernel2_xvel_plus_4_back_c_wrapper(double *restrict xvel0_p,
                                                    double *restrict xvel1_p,
                                                    const int *restrict fields,
                                                    int x_size, int y_size,
                                                    int z_size) {
#pragma omp parallel for
  for (int n_z = 0; n_z < z_size; n_z++) {
    for (int n_y = 0; n_y < y_size; n_y++) {
      for (int n_x = 0; n_x < x_size; n_x++) {
        ptr_double xvel0 = {
            xvel0_p + n_x * 1 +
                n_y * xdim0_update_halo_kernel2_xvel_plus_4_back * 1 +
                n_z * xdim0_update_halo_kernel2_xvel_plus_4_back *
                    ydim0_update_halo_kernel2_xvel_plus_4_back * 1,
            xdim0_update_halo_kernel2_xvel_plus_4_back,
            ydim0_update_halo_kernel2_xvel_plus_4_back};
        ptr_double xvel1 = {
            xvel1_p + n_x * 1 +
                n_y * xdim1_update_halo_kernel2_xvel_plus_4_back * 1 +
                n_z * xdim1_update_halo_kernel2_xvel_plus_4_back *
                    ydim1_update_halo_kernel2_xvel_plus_4_back * 1,
            xdim1_update_halo_kernel2_xvel_plus_4_back,
            ydim1_update_halo_kernel2_xvel_plus_4_back};

        if (fields[FIELD_XVEL0] == 1)
          OPS_ACC(xvel0, 0, 0, 0) = OPS_ACC(xvel0, 0, 0, 4);
        if (fields[FIELD_XVEL1] == 1)
          OPS_ACC(xvel1, 0, 0, 0) = OPS_ACC(xvel1, 0, 0, 4);
      }
    }
  }
}
