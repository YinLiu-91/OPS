//
// auto-generated by ops.py
//

int xdim0_reset_field_kernel1;
int xdim1_reset_field_kernel1;
int xdim2_reset_field_kernel1;
int xdim3_reset_field_kernel1;

// user function

void reset_field_kernel1_c_wrapper(double *restrict density0_p,
                                   double *restrict density1_p,
                                   double *restrict energy0_p,
                                   double *restrict energy1_p, int x_size,
                                   int y_size) {
#pragma omp parallel for
  for (int n_y = 0; n_y < y_size; n_y++) {
    for (int n_x = 0; n_x < x_size; n_x++) {
      ptr_double density0 = {density0_p + n_x * 1 +
                                 n_y * xdim0_reset_field_kernel1 * 1,
                             xdim0_reset_field_kernel1};
      const ptr_double density1 = {density1_p + n_x * 1 +
                                       n_y * xdim1_reset_field_kernel1 * 1,
                                   xdim1_reset_field_kernel1};
      ptr_double energy0 = {energy0_p + n_x * 1 +
                                n_y * xdim2_reset_field_kernel1 * 1,
                            xdim2_reset_field_kernel1};
      const ptr_double energy1 = {energy1_p + n_x * 1 +
                                      n_y * xdim3_reset_field_kernel1 * 1,
                                  xdim3_reset_field_kernel1};

      OPS_ACC(density0, 0, 0) = OPS_ACC(density1, 0, 0);
      OPS_ACC(energy0, 0, 0) = OPS_ACC(energy1, 0, 0);
    }
  }
}
