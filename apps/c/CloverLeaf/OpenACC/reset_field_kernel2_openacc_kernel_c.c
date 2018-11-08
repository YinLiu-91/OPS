//
// auto-generated by ops.py
//

#define OPS_GPU

int xdim0_reset_field_kernel2;
int xdim1_reset_field_kernel2;
int xdim2_reset_field_kernel2;
int xdim3_reset_field_kernel2;


#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3


#define OPS_ACC0(x,y) (x+xdim0_reset_field_kernel2*(y))
#define OPS_ACC1(x,y) (x+xdim1_reset_field_kernel2*(y))
#define OPS_ACC2(x,y) (x+xdim2_reset_field_kernel2*(y))
#define OPS_ACC3(x,y) (x+xdim3_reset_field_kernel2*(y))

//user function
inline 
void reset_field_kernel2( ACC<double> &xvel0, const ACC<double> &xvel1,
                        ACC<double> &yvel0, const ACC<double> &yvel1) {

  xvel0(0,0)  = xvel1(0,0) ;
  yvel0(0,0)  = yvel1(0,0) ;

}


#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3



void reset_field_kernel2_c_wrapper(
  double *p_a0,
  double *p_a1,
  double *p_a2,
  double *p_a3,
  int x_size, int y_size) {
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1,p_a2,p_a3)
  #pragma acc loop
  #endif
  for ( int n_y=0; n_y<y_size; n_y++ ){
    #ifdef OPS_GPU
    #pragma acc loop
    #endif
    for ( int n_x=0; n_x<x_size; n_x++ ){
      reset_field_kernel2(  p_a0 + n_x*1*1 + n_y*xdim0_reset_field_kernel2*1*1,
           p_a1 + n_x*1*1 + n_y*xdim1_reset_field_kernel2*1*1, p_a2 + n_x*1*1 + n_y*xdim2_reset_field_kernel2*1*1,
           p_a3 + n_x*1*1 + n_y*xdim3_reset_field_kernel2*1*1 );

    }
  }
}
