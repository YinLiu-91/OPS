//
// auto-generated by ops.py
//

int xdim0_revert_kernel;
int xdim1_revert_kernel;
int xdim2_revert_kernel;
int xdim3_revert_kernel;


//user function



void revert_kernel_c_wrapper(
  double * restrict density0_p,
  double * restrict density1_p,
  double * restrict energy0_p,
  double * restrict energy1_p,
  int x_size, int y_size) {
  #pragma omp parallel for
  for ( int n_y=0; n_y<y_size; n_y++ ){
    for ( int n_x=0; n_x<x_size; n_x++ ){
      const ptr_double density0 = { density0_p + n_x*1 + n_y * xdim0_revert_kernel*1, xdim0_revert_kernel};
      ptr_double density1 = { density1_p + n_x*1 + n_y * xdim1_revert_kernel*1, xdim1_revert_kernel};
      const ptr_double energy0 = { energy0_p + n_x*1 + n_y * xdim2_revert_kernel*1, xdim2_revert_kernel};
      ptr_double energy1 = { energy1_p + n_x*1 + n_y * xdim3_revert_kernel*1, xdim3_revert_kernel};
      

  OPS_ACC(density1, 0,0) = OPS_ACC(density0, 0,0);
  OPS_ACC(energy1, 0,0) = OPS_ACC(energy0, 0,0);

    }
  }
}
