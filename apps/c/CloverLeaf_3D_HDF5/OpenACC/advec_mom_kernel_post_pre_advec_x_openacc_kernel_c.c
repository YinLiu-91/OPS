//
// auto-generated by ops.py
//
#include "./OpenACC/clover_leaf_common.h"

//#define OPS_GPU

int xdim0_advec_mom_kernel_post_pre_advec_x;
int ydim0_advec_mom_kernel_post_pre_advec_x;
int xdim1_advec_mom_kernel_post_pre_advec_x;
int ydim1_advec_mom_kernel_post_pre_advec_x;
int xdim2_advec_mom_kernel_post_pre_advec_x;
int ydim2_advec_mom_kernel_post_pre_advec_x;
int xdim3_advec_mom_kernel_post_pre_advec_x;
int ydim3_advec_mom_kernel_post_pre_advec_x;
int xdim4_advec_mom_kernel_post_pre_advec_x;
int ydim4_advec_mom_kernel_post_pre_advec_x;

#define OPS_ACC0(x,y,z) (x+xdim0_advec_mom_kernel_post_pre_advec_x*(y)+xdim0_advec_mom_kernel_post_pre_advec_x*ydim0_advec_mom_kernel_post_pre_advec_x*(z))
#define OPS_ACC1(x,y,z) (x+xdim1_advec_mom_kernel_post_pre_advec_x*(y)+xdim1_advec_mom_kernel_post_pre_advec_x*ydim1_advec_mom_kernel_post_pre_advec_x*(z))
#define OPS_ACC2(x,y,z) (x+xdim2_advec_mom_kernel_post_pre_advec_x*(y)+xdim2_advec_mom_kernel_post_pre_advec_x*ydim2_advec_mom_kernel_post_pre_advec_x*(z))
#define OPS_ACC3(x,y,z) (x+xdim3_advec_mom_kernel_post_pre_advec_x*(y)+xdim3_advec_mom_kernel_post_pre_advec_x*ydim3_advec_mom_kernel_post_pre_advec_x*(z))
#define OPS_ACC4(x,y,z) (x+xdim4_advec_mom_kernel_post_pre_advec_x*(y)+xdim4_advec_mom_kernel_post_pre_advec_x*ydim4_advec_mom_kernel_post_pre_advec_x*(z))

//user function

inline void advec_mom_kernel_post_pre_advec_x( double *node_mass_post, const double *post_vol,
                                  const double *density1, double *node_mass_pre, const double *node_flux) {

  node_mass_post[OPS_ACC0(0,0,0)] = 0.125 * ( density1[OPS_ACC2(0,-1,0)] * post_vol[OPS_ACC1(0,-1,0)] +
                                              density1[OPS_ACC2(0,0,0)]   * post_vol[OPS_ACC1(0,0,0)]   +
                                              density1[OPS_ACC2(-1,-1,0)] * post_vol[OPS_ACC1(-1,-1,0)] +
                                              density1[OPS_ACC2(-1,0,0)]  * post_vol[OPS_ACC1(-1,0,0)] +
                                              density1[OPS_ACC2(0,-1,-1)] * post_vol[OPS_ACC1(0,-1,-1)] +
                                              density1[OPS_ACC2(0,0,-1)]   * post_vol[OPS_ACC1(0,0,-1)]   +
                                              density1[OPS_ACC2(-1,-1,-1)] * post_vol[OPS_ACC1(-1,-1,-1)] +
                                              density1[OPS_ACC2(-1,0,-1)]  * post_vol[OPS_ACC1(-1,0,-1)]  );

  node_mass_pre[OPS_ACC3(0,0,0)] = node_mass_post[OPS_ACC0(0,0,0)] - node_flux[OPS_ACC4(-1,0,0)] + node_flux[OPS_ACC4(0,0,0)];

}


#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4



void advec_mom_kernel_post_pre_advec_x_c_wrapper(
  double *p_a0,
  double *p_a1,
  double *p_a2,
  double *p_a3,
  double *p_a4,
  int x_size, int y_size, int z_size) {
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1,p_a2,p_a3,p_a4)
  #pragma acc loop
  #endif
  for ( int n_z=0; n_z<z_size; n_z++ ){
    #ifdef OPS_GPU
    #pragma acc loop
    #endif
    for ( int n_y=0; n_y<y_size; n_y++ ){
      #ifdef OPS_GPU
      #pragma acc loop
      #endif
      for ( int n_x=0; n_x<x_size; n_x++ ){
        advec_mom_kernel_post_pre_advec_x(  p_a0 + n_x*1*1 + n_y*xdim0_advec_mom_kernel_post_pre_advec_x*1*1 + n_z*xdim0_advec_mom_kernel_post_pre_advec_x*ydim0_advec_mom_kernel_post_pre_advec_x*1,
           p_a1 + n_x*1*1 + n_y*xdim1_advec_mom_kernel_post_pre_advec_x*1*1 + n_z*xdim1_advec_mom_kernel_post_pre_advec_x*ydim1_advec_mom_kernel_post_pre_advec_x*1,
           p_a2 + n_x*1*1 + n_y*xdim2_advec_mom_kernel_post_pre_advec_x*1*1 + n_z*xdim2_advec_mom_kernel_post_pre_advec_x*ydim2_advec_mom_kernel_post_pre_advec_x*1,
           p_a3 + n_x*1*1 + n_y*xdim3_advec_mom_kernel_post_pre_advec_x*1*1 + n_z*xdim3_advec_mom_kernel_post_pre_advec_x*ydim3_advec_mom_kernel_post_pre_advec_x*1,
           p_a4 + n_x*1*1 + n_y*xdim4_advec_mom_kernel_post_pre_advec_x*1*1 + n_z*xdim4_advec_mom_kernel_post_pre_advec_x*ydim4_advec_mom_kernel_post_pre_advec_x*1 );

      }
    }
  }
}
