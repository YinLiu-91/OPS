//
// auto-generated by ops.py
//

int xdim0_update_halo_kernel3_plus_2_b;
int xdim1_update_halo_kernel3_plus_2_b;

// user function

void update_halo_kernel3_plus_2_b_c_wrapper(double *restrict vol_flux_x_p,
                                            double *restrict mass_flux_x_p,
                                            const int *restrict fields,
                                            int x_size, int y_size) {
#pragma omp parallel for
  for (int n_y = 0; n_y < y_size; n_y++) {
    for (int n_x = 0; n_x < x_size; n_x++) {
      ptr_double vol_flux_x = {vol_flux_x_p + n_x * 1 +
                                   n_y * xdim0_update_halo_kernel3_plus_2_b * 1,
                               xdim0_update_halo_kernel3_plus_2_b};
      ptr_double mass_flux_x = {mass_flux_x_p + n_x * 1 +
                                    n_y * xdim1_update_halo_kernel3_plus_2_b *
                                        1,
                                xdim1_update_halo_kernel3_plus_2_b};

      if (fields[FIELD_VOL_FLUX_X] == 1)
        OPS_ACC(vol_flux_x, 0, 0) = OPS_ACC(vol_flux_x, 0, -2);
      if (fields[FIELD_MASS_FLUX_X] == 1)
        OPS_ACC(mass_flux_x, 0, 0) = OPS_ACC(mass_flux_x, 0, -2);
    }
  }
}
