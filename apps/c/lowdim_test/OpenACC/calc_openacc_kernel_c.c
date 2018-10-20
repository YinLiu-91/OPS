//
// auto-generated by ops.py
//

#define OPS_GPU

int xdim0_calc;
int ydim0_calc;
int xdim1_calc;
int ydim1_calc;
int xdim2_calc;
int ydim2_calc;
int xdim3_calc;
int ydim3_calc;
int xdim4_calc;
int ydim4_calc;
int xdim5_calc;
int ydim5_calc;
int xdim6_calc;
int ydim6_calc;


#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6


#define OPS_ACC0(x,y,z) (x+xdim0_calc*(y)+xdim0_calc*ydim0_calc*(z))
#define OPS_ACC1(x,y,z) (x+xdim1_calc*(y)+xdim1_calc*ydim1_calc*(z))
#define OPS_ACC2(x,y,z) (x+xdim2_calc*(y)+xdim2_calc*ydim2_calc*(z))
#define OPS_ACC3(x,y,z) (x+xdim3_calc*(y)+xdim3_calc*ydim3_calc*(z))
#define OPS_ACC4(x,y,z) (x+xdim4_calc*(y)+xdim4_calc*ydim4_calc*(z))
#define OPS_ACC5(x,y,z) (x+xdim5_calc*(y)+xdim5_calc*ydim5_calc*(z))
#define OPS_ACC6(x,y,z) (x+xdim6_calc*(y)+xdim6_calc*ydim6_calc*(z))

//user function
inline 
void calc(double *dat3D, const double *dat2D_xy,  const double *dat2D_yz, const double *dat2D_xz,
    const double *dat1D_x,  const double *dat1D_y, const double *dat1D_z)
{
  dat3D[OPS_ACC0(0,0,0)] = dat2D_xy[OPS_ACC1(0,0,0)] +
                           dat2D_yz[OPS_ACC2(0,0,0)] +
                           dat2D_xz[OPS_ACC3(0,0,0)] +
                           dat1D_x[OPS_ACC4(0,0,0)] +
                           dat1D_y[OPS_ACC5(0,0,0)] +
                           dat1D_z[OPS_ACC6(0,0,0)];
}


#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6



void calc_c_wrapper(
  double *p_a0,
  double *p_a1,
  double *p_a2,
  double *p_a3,
  double *p_a4,
  double *p_a5,
  double *p_a6,
  int x_size, int y_size, int z_size) {
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1,p_a2,p_a3,p_a4,p_a5,p_a6)
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
        calc(  p_a0 + n_x*1*1 + n_y*xdim0_calc*1*1 + n_z*xdim0_calc*ydim0_calc*1*1,
           p_a1 + n_x*1*1 + n_y*xdim1_calc*1*1 + n_z*xdim1_calc*ydim1_calc*0*1,
           p_a2 + n_x*0*1 + n_y*xdim2_calc*1*1 + n_z*xdim2_calc*ydim2_calc*1*1,
           p_a3 + n_x*1*1 + n_y*xdim3_calc*0*1 + n_z*xdim3_calc*ydim3_calc*1*1,
           p_a4 + n_x*1*1 + n_y*xdim4_calc*0*1 + n_z*xdim4_calc*ydim4_calc*0*1,
           p_a5 + n_x*0*1 + n_y*xdim5_calc*1*1 + n_z*xdim5_calc*ydim5_calc*0*1,
           p_a6 + n_x*0*1 + n_y*xdim6_calc*0*1 + n_z*xdim6_calc*ydim6_calc*1*1 );

      }
    }
  }
}
