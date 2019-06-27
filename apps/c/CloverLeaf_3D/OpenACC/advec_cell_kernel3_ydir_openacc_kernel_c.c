//
// auto-generated by ops.py
//

#define OPS_GPU

int xdim0_advec_cell_kernel3_ydir;
int ydim0_advec_cell_kernel3_ydir;
int xdim1_advec_cell_kernel3_ydir;
int ydim1_advec_cell_kernel3_ydir;
int xdim2_advec_cell_kernel3_ydir;
int ydim2_advec_cell_kernel3_ydir;
int xdim3_advec_cell_kernel3_ydir;
int ydim3_advec_cell_kernel3_ydir;
int xdim4_advec_cell_kernel3_ydir;
int ydim4_advec_cell_kernel3_ydir;
int xdim5_advec_cell_kernel3_ydir;
int ydim5_advec_cell_kernel3_ydir;
int xdim6_advec_cell_kernel3_ydir;
int ydim6_advec_cell_kernel3_ydir;
int xdim7_advec_cell_kernel3_ydir;
int ydim7_advec_cell_kernel3_ydir;

// user function
#pragma acc routine

inline void
advec_cell_kernel3_ydir(const ptr_double vol_flux_y, const ptr_double pre_vol,
                        const ptr_int yy, const ptr_double vertexdy,
                        const ptr_double density1, const ptr_double energy1,
                        ptr_double mass_flux_y, ptr_double ener_flux) {

  double sigmat, sigmav, sigmam, sigma3, sigma4;
  double diffuw, diffdw, limiter;
  double one_by_six = 1.0 / 6.0;

  int y_max = field.y_max;

  int upwind, donor, downwind, dif;

  if (OPS_ACC(vol_flux_y, 0, 0, 0) > 0.0) {
    upwind = -2;
    donor = -1;
    downwind = 0;
    dif = donor;
  } else if (OPS_ACC(yy, 0, 1, 0) < y_max + 2 - 2) {
    upwind = 1;
    donor = 0;
    downwind = -1;
    dif = upwind;
  } else {
    upwind = 0;
    donor = 0;
    downwind = -1;
    dif = upwind;
  }

  sigmat = fabs(OPS_ACC(vol_flux_y, 0, 0, 0)) / OPS_ACC(pre_vol, 0, donor, 0);
  sigma3 = (1.0 + sigmat) *
           (OPS_ACC(vertexdy, 0, 0, 0) / OPS_ACC(vertexdy, 0, dif, 0));
  sigma4 = 2.0 - sigmat;

  sigmav = sigmat;

  diffuw = OPS_ACC(density1, 0, donor, 0) - OPS_ACC(density1, 0, upwind, 0);
  diffdw = OPS_ACC(density1, 0, downwind, 0) - OPS_ACC(density1, 0, donor, 0);

  if ((diffuw * diffdw) > 0.0)
    limiter = (1.0 - sigmav) * SIGN(1.0, diffdw) *
              MIN(MIN(fabs(diffuw), fabs(diffdw)),
                  one_by_six * (sigma3 * fabs(diffuw) + sigma4 * fabs(diffdw)));
  else
    limiter = 0.0;

  OPS_ACC(mass_flux_y, 0, 0, 0) = (OPS_ACC(vol_flux_y, 0, 0, 0)) *
                                  (OPS_ACC(density1, 0, donor, 0) + limiter);

  sigmam = fabs(OPS_ACC(mass_flux_y, 0, 0, 0)) /
           (OPS_ACC(density1, 0, donor, 0) * OPS_ACC(pre_vol, 0, donor, 0));
  diffuw = OPS_ACC(energy1, 0, donor, 0) - OPS_ACC(energy1, 0, upwind, 0);
  diffdw = OPS_ACC(energy1, 0, downwind, 0) - OPS_ACC(energy1, 0, donor, 0);

  if ((diffuw * diffdw) > 0.0)
    limiter = (1.0 - sigmam) * SIGN(1.0, diffdw) *
              MIN(MIN(fabs(diffuw), fabs(diffdw)),
                  one_by_six * (sigma3 * fabs(diffuw) + sigma4 * fabs(diffdw)));
  else
    limiter = 0.0;

  OPS_ACC(ener_flux, 0, 0, 0) =
      OPS_ACC(mass_flux_y, 0, 0, 0) * (OPS_ACC(energy1, 0, donor, 0) + limiter);
}

void advec_cell_kernel3_ydir_c_wrapper(double *p_a0, double *p_a1, int *p_a2,
                                       double *p_a3, double *p_a4, double *p_a5,
                                       double *p_a6, double *p_a7, int x_size,
                                       int y_size, int z_size) {
#ifdef OPS_GPU
#pragma acc parallel deviceptr(p_a0, p_a1, p_a2, p_a3, p_a4, p_a5, p_a6, p_a7)
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
        const ptr_double ptr0 = {
            p_a0 + n_x * 1 * 1 + n_y * xdim0_advec_cell_kernel3_ydir * 1 * 1 +
                n_z * xdim0_advec_cell_kernel3_ydir *
                    ydim0_advec_cell_kernel3_ydir * 1 * 1,
            xdim0_advec_cell_kernel3_ydir, ydim0_advec_cell_kernel3_ydir};
        const ptr_double ptr1 = {
            p_a1 + n_x * 1 * 1 + n_y * xdim1_advec_cell_kernel3_ydir * 1 * 1 +
                n_z * xdim1_advec_cell_kernel3_ydir *
                    ydim1_advec_cell_kernel3_ydir * 1 * 1,
            xdim1_advec_cell_kernel3_ydir, ydim1_advec_cell_kernel3_ydir};
        const ptr_int ptr2 = {
            p_a2 + n_x * 0 * 1 + n_y * xdim2_advec_cell_kernel3_ydir * 1 * 1 +
                n_z * xdim2_advec_cell_kernel3_ydir *
                    ydim2_advec_cell_kernel3_ydir * 0 * 1,
            xdim2_advec_cell_kernel3_ydir, ydim2_advec_cell_kernel3_ydir};
        const ptr_double ptr3 = {
            p_a3 + n_x * 0 * 1 + n_y * xdim3_advec_cell_kernel3_ydir * 1 * 1 +
                n_z * xdim3_advec_cell_kernel3_ydir *
                    ydim3_advec_cell_kernel3_ydir * 0 * 1,
            xdim3_advec_cell_kernel3_ydir, ydim3_advec_cell_kernel3_ydir};
        const ptr_double ptr4 = {
            p_a4 + n_x * 1 * 1 + n_y * xdim4_advec_cell_kernel3_ydir * 1 * 1 +
                n_z * xdim4_advec_cell_kernel3_ydir *
                    ydim4_advec_cell_kernel3_ydir * 1 * 1,
            xdim4_advec_cell_kernel3_ydir, ydim4_advec_cell_kernel3_ydir};
        const ptr_double ptr5 = {
            p_a5 + n_x * 1 * 1 + n_y * xdim5_advec_cell_kernel3_ydir * 1 * 1 +
                n_z * xdim5_advec_cell_kernel3_ydir *
                    ydim5_advec_cell_kernel3_ydir * 1 * 1,
            xdim5_advec_cell_kernel3_ydir, ydim5_advec_cell_kernel3_ydir};
        ptr_double ptr6 = {
            p_a6 + n_x * 1 * 1 + n_y * xdim6_advec_cell_kernel3_ydir * 1 * 1 +
                n_z * xdim6_advec_cell_kernel3_ydir *
                    ydim6_advec_cell_kernel3_ydir * 1 * 1,
            xdim6_advec_cell_kernel3_ydir, ydim6_advec_cell_kernel3_ydir};
        ptr_double ptr7 = {
            p_a7 + n_x * 1 * 1 + n_y * xdim7_advec_cell_kernel3_ydir * 1 * 1 +
                n_z * xdim7_advec_cell_kernel3_ydir *
                    ydim7_advec_cell_kernel3_ydir * 1 * 1,
            xdim7_advec_cell_kernel3_ydir, ydim7_advec_cell_kernel3_ydir};
        advec_cell_kernel3_ydir(ptr0, ptr1, ptr2, ptr3, ptr4, ptr5, ptr6, ptr7);
      }
    }
  }
}
