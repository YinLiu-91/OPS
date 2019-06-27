//
// auto-generated by ops.py
//

int xdim0_update_halo_kernel4_plus_4_a;
int ydim0_update_halo_kernel4_plus_4_a;
int xdim1_update_halo_kernel4_plus_4_a;
int ydim1_update_halo_kernel4_plus_4_a;

// user function

void update_halo_kernel4_plus_4_a_c_wrapper(double *restrict vol_flux_y_p,
                                            double *restrict mass_flux_y_p,
                                            const int *restrict fields,
                                            int x_size, int y_size,
                                            int z_size) {
#pragma omp parallel for
  for (int n_z = 0; n_z < z_size; n_z++) {
    for (int n_y = 0; n_y < y_size; n_y++) {
      for (int n_x = 0; n_x < x_size; n_x++) {
        ptr_double vol_flux_y = {vol_flux_y_p + n_x * 1 +
                                     n_y * xdim0_update_halo_kernel4_plus_4_a *
                                         1 +
                                     n_z * xdim0_update_halo_kernel4_plus_4_a *
                                         ydim0_update_halo_kernel4_plus_4_a * 1,
                                 xdim0_update_halo_kernel4_plus_4_a,
                                 ydim0_update_halo_kernel4_plus_4_a};
        ptr_double mass_flux_y = {
            mass_flux_y_p + n_x * 1 +
                n_y * xdim1_update_halo_kernel4_plus_4_a * 1 +
                n_z * xdim1_update_halo_kernel4_plus_4_a *
                    ydim1_update_halo_kernel4_plus_4_a * 1,
            xdim1_update_halo_kernel4_plus_4_a,
            ydim1_update_halo_kernel4_plus_4_a};

        if (fields[FIELD_VOL_FLUX_Y] == 1)
          OPS_ACC(vol_flux_y, 0, 0, 0) = OPS_ACC(vol_flux_y, 4, 0, 0);
        if (fields[FIELD_MASS_FLUX_Y] == 1)
          OPS_ACC(mass_flux_y, 0, 0, 0) = OPS_ACC(mass_flux_y, 4, 0, 0);
      }
    }
  }
}
