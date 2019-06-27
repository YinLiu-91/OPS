//
// auto-generated by ops.py
//

int xdim0_tea_leaf_common_residual_kernel;
int xdim1_tea_leaf_common_residual_kernel;
int xdim2_tea_leaf_common_residual_kernel;
int xdim3_tea_leaf_common_residual_kernel;
int xdim4_tea_leaf_common_residual_kernel;

// user function

void tea_leaf_common_residual_kernel_c_wrapper(
    double *restrict r_p, double *restrict Kx_p, double *restrict Ky_p,
    double *restrict u_p, double *restrict u0_p, const double *restrict rx,
    const double *restrict ry, int x_size, int y_size) {
#pragma omp parallel for
  for (int n_y = 0; n_y < y_size; n_y++) {
    for (int n_x = 0; n_x < x_size; n_x++) {
      ptr_double r = {r_p + n_x * 1 +
                          n_y * xdim0_tea_leaf_common_residual_kernel * 1,
                      xdim0_tea_leaf_common_residual_kernel};
      const ptr_double Kx = {
          Kx_p + n_x * 1 + n_y * xdim1_tea_leaf_common_residual_kernel * 1,
          xdim1_tea_leaf_common_residual_kernel};
      const ptr_double Ky = {
          Ky_p + n_x * 1 + n_y * xdim2_tea_leaf_common_residual_kernel * 1,
          xdim2_tea_leaf_common_residual_kernel};
      const ptr_double u = {u_p + n_x * 1 +
                                n_y * xdim3_tea_leaf_common_residual_kernel * 1,
                            xdim3_tea_leaf_common_residual_kernel};
      const ptr_double u0 = {
          u0_p + n_x * 1 + n_y * xdim4_tea_leaf_common_residual_kernel * 1,
          xdim4_tea_leaf_common_residual_kernel};

      double smvp = 0.0;
      smvp = (1.0 + (*ry) * (OPS_ACC(Ky, 0, 1) + OPS_ACC(Ky, 0, 0)) +
              (*rx) * (OPS_ACC(Kx, 1, 0) + OPS_ACC(Kx, 0, 0))) *
                 OPS_ACC(u, 0, 0) -
             (*ry) * (OPS_ACC(Ky, 0, 1) * OPS_ACC(u, 0, 1) +
                      OPS_ACC(Ky, 0, 0) * OPS_ACC(u, 0, -1)) -
             (*rx) * (OPS_ACC(Kx, 1, 0) * OPS_ACC(u, 1, 0) +
                      OPS_ACC(Kx, 0, 0) * OPS_ACC(u, -1, 0));
      OPS_ACC(r, 0, 0) = OPS_ACC(u0, 0, 0) - smvp;
    }
  }
}
