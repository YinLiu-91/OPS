//
// auto-generated by ops.py
//

int xdim0_update_halo_kernel4_plus_4_b;
int xdim1_update_halo_kernel4_plus_4_b;


#define OPS_ACC0(x,y) (n_x*1 + x + (n_y*1+(y))*xdim0_update_halo_kernel4_plus_4_b)
#define OPS_ACC1(x,y) (n_x*1 + x + (n_y*1+(y))*xdim1_update_halo_kernel4_plus_4_b)
//user function



void update_halo_kernel4_plus_4_b_c_wrapper(
  double * restrict vol_flux_y,
  double * restrict mass_flux_y,
  const int * restrict fields,
  int x_size, int y_size) {
  #pragma omp parallel for
  for ( int n_y=0; n_y<y_size; n_y++ ){
    for ( int n_x=0; n_x<x_size; n_x++ ){
      
  if(fields[FIELD_VOL_FLUX_Y] == 1) vol_flux_y(0,0) = vol_flux_y(-4,0);
  if(fields[FIELD_MASS_FLUX_Y] == 1) mass_flux_y(0,0) = mass_flux_y(-4,0);

    }
  }
}
#undef OPS_ACC0
#undef OPS_ACC1

