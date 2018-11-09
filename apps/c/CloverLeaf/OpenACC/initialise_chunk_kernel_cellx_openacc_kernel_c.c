//
// auto-generated by ops.py
//

#define OPS_GPU

int xdim0_initialise_chunk_kernel_cellx;
int xdim1_initialise_chunk_kernel_cellx;
int xdim2_initialise_chunk_kernel_cellx;

//user function
inline 
void initialise_chunk_kernel_cellx(const ptr_double vertexx, ptr_double cellx, ptr_double celldx) {

  double d_x;
  d_x = (grid.xmax - grid.xmin)/(double)grid.x_cells;

  OPS_ACC(cellx, 0,0)  = 0.5*( OPS_ACC(vertexx, 0,0) + OPS_ACC(vertexx, 1,0) );
  OPS_ACC(celldx, 0,0)  = d_x;

}


void initialise_chunk_kernel_cellx_c_wrapper(
  double *p_a0,
  double *p_a1,
  double *p_a2,
  int x_size, int y_size) {
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1,p_a2)
  #pragma acc loop
  #endif
  for ( int n_y=0; n_y<y_size; n_y++ ){
    #ifdef OPS_GPU
    #pragma acc loop
    #endif
    for ( int n_x=0; n_x<x_size; n_x++ ){
      const ptr_double ptr0 = {  p_a0 + n_x*1*1 + n_y*xdim0_initialise_chunk_kernel_cellx*0*1, xdim0_initialise_chunk_kernel_cellx};
      ptr_double ptr1 = {  p_a1 + n_x*1*1 + n_y*xdim1_initialise_chunk_kernel_cellx*0*1, xdim1_initialise_chunk_kernel_cellx};
      ptr_double ptr2 = {  p_a2 + n_x*1*1 + n_y*xdim2_initialise_chunk_kernel_cellx*0*1, xdim2_initialise_chunk_kernel_cellx};
      initialise_chunk_kernel_cellx( ptr0,
          ptr1,ptr2 );

    }
  }
}
