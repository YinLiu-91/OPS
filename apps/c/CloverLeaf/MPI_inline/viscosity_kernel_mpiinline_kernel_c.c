//
// auto-generated by ops.py
//

int xdim0_viscosity_kernel;
int xdim1_viscosity_kernel;
int xdim2_viscosity_kernel;
int xdim3_viscosity_kernel;
int xdim4_viscosity_kernel;
int xdim5_viscosity_kernel;
int xdim6_viscosity_kernel;

// user function

void viscosity_kernel_c_wrapper(
    double *restrict xvel0_p, double *restrict yvel0_p,
    double *restrict celldx_p, double *restrict celldy_p,
    double *restrict pressure_p, double *restrict density0_p,
    double *restrict viscosity_p, int x_size, int y_size) {
#pragma omp parallel for
  for (int n_y = 0; n_y < y_size; n_y++) {
    for (int n_x = 0; n_x < x_size; n_x++) {
      const ptr_double xvel0 = {xvel0_p + n_x * 1 +
                                    n_y * xdim0_viscosity_kernel * 1,
                                xdim0_viscosity_kernel};
      const ptr_double yvel0 = {yvel0_p + n_x * 1 +
                                    n_y * xdim1_viscosity_kernel * 1,
                                xdim1_viscosity_kernel};
      const ptr_double celldx = {celldx_p + n_x * 1 +
                                     n_y * xdim2_viscosity_kernel * 0,
                                 xdim2_viscosity_kernel};
      const ptr_double celldy = {celldy_p + n_x * 0 +
                                     n_y * xdim3_viscosity_kernel * 1,
                                 xdim3_viscosity_kernel};
      const ptr_double pressure = {pressure_p + n_x * 1 +
                                       n_y * xdim4_viscosity_kernel * 1,
                                   xdim4_viscosity_kernel};
      const ptr_double density0 = {density0_p + n_x * 1 +
                                       n_y * xdim5_viscosity_kernel * 1,
                                   xdim5_viscosity_kernel};
      ptr_double viscosity = {viscosity_p + n_x * 1 +
                                  n_y * xdim6_viscosity_kernel * 1,
                              xdim6_viscosity_kernel};

      double ugrad, vgrad, grad2, pgradx, pgrady, pgradx2, pgrady2, grad, ygrad,
          xgrad, div, strain2, limiter, pgrad;

      ugrad = (OPS_ACC(xvel0, 1, 0) + OPS_ACC(xvel0, 1, 1)) -
              (OPS_ACC(xvel0, 0, 0) + OPS_ACC(xvel0, 0, 1));
      vgrad = (OPS_ACC(yvel0, 0, 1) + OPS_ACC(yvel0, 1, 1)) -
              (OPS_ACC(yvel0, 0, 0) + OPS_ACC(yvel0, 1, 0));

      div =
          (OPS_ACC(celldx, 0, 0)) * (ugrad) + (OPS_ACC(celldy, 0, 0)) * (vgrad);

      strain2 = 0.5 * (OPS_ACC(xvel0, 0, 1) + OPS_ACC(xvel0, 1, 1) -
                       OPS_ACC(xvel0, 0, 0) - OPS_ACC(xvel0, 1, 0)) /
                    (OPS_ACC(celldy, 0, 0)) +
                0.5 * (OPS_ACC(yvel0, 1, 0) + OPS_ACC(yvel0, 1, 1) -
                       OPS_ACC(yvel0, 0, 0) - OPS_ACC(yvel0, 0, 1)) /
                    (OPS_ACC(celldx, 0, 0));

      pgradx = (OPS_ACC(pressure, 1, 0) - OPS_ACC(pressure, -1, 0)) /
               (OPS_ACC(celldx, 0, 0) + OPS_ACC(celldx, 1, 0));
      pgrady = (OPS_ACC(pressure, 0, 1) - OPS_ACC(pressure, 0, -1)) /
               (OPS_ACC(celldy, 0, 0) + OPS_ACC(celldy, 0, 1));

      pgradx2 = pgradx * pgradx;
      pgrady2 = pgrady * pgrady;

      limiter = ((0.5 * (ugrad) / OPS_ACC(celldx, 0, 0)) * pgradx2 +
                 (0.5 * (vgrad) / OPS_ACC(celldy, 0, 0)) * pgrady2 +
                 strain2 * pgradx * pgrady) /
                MAX(pgradx2 + pgrady2, 1.0e-16);

      if ((limiter > 0.0) || (div >= 0.0)) {
        OPS_ACC(viscosity, 0, 0) = 0.0;
      } else {
        pgradx = SIGN(MAX(1.0e-16, fabs(pgradx)), pgradx);
        pgrady = SIGN(MAX(1.0e-16, fabs(pgrady)), pgrady);
        pgrad = sqrt(pgradx * pgradx + pgrady * pgrady);
        xgrad = fabs(OPS_ACC(celldx, 0, 0) * pgrad / pgradx);
        ygrad = fabs(OPS_ACC(celldy, 0, 0) * pgrad / pgrady);
        grad = MIN(xgrad, ygrad);
        grad2 = grad * grad;

        OPS_ACC(viscosity, 0, 0) =
            2.0 * (OPS_ACC(density0, 0, 0)) * grad2 * limiter * limiter;
      }
    }
  }
}
