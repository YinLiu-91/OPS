//
// auto-generated by ops.py on 2014-05-13 14:40
//


#ifndef MIN
#define MIN(a,b) ((a<b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b) ((a>b) ? (a) : (b))
#endif
#ifndef SIGN
#define SIGN(a,b) ((b<0.0) ? (a*(-1)) : (a))
#endif

#pragma OPENCL EXTENSION cl_khr_fp64:enable

#define OPS_ACC0(x,y) (x+xdim0_reset_field_kernel2*(y))
#define OPS_ACC1(x,y) (x+xdim1_reset_field_kernel2*(y))
#define OPS_ACC2(x,y) (x+xdim2_reset_field_kernel2*(y))
#define OPS_ACC3(x,y) (x+xdim3_reset_field_kernel2*(y))


//user function

void reset_field_kernel2( __global double *xvel0,  __global double *xvel1,
                        __global double *yvel0,  __global double *yvel1,
  int xdim0_reset_field_kernel2,
  int xdim1_reset_field_kernel2,
  int xdim2_reset_field_kernel2,
  int xdim3_reset_field_kernel2)
  {

  xvel0[OPS_ACC0(0,0)]  = xvel1[OPS_ACC1(0,0)] ;
  yvel0[OPS_ACC2(0,0)]  = yvel1[OPS_ACC3(0,0)] ;

}



 #undef OPS_ACC0
 #undef OPS_ACC1
 #undef OPS_ACC2
 #undef OPS_ACC3


 __kernel void ops_reset_field_kernel2(
 __global double* arg0,
 __global double* arg1,
 __global double* arg2,
 __global double* arg3,
 int xdim0_reset_field_kernel2,
 int xdim1_reset_field_kernel2,
 int xdim2_reset_field_kernel2,
 int xdim3_reset_field_kernel2,
 const int base0,
 const int base1,
 const int base2,
 const int base3,
 int size0,
 int size1 ){


   int idx_y = get_global_id(1);
   int idx_x = get_global_id(0);

   if (idx_x < size0 && idx_y < size1) {
     reset_field_kernel2(&arg0[base0 + idx_x * 1 + idx_y * 1 * xdim0_reset_field_kernel2],
                        &arg1[base1 + idx_x * 1 + idx_y * 1 * xdim1_reset_field_kernel2],
                        &arg2[base2 + idx_x * 1 + idx_y * 1 * xdim2_reset_field_kernel2],
                        &arg3[base3 + idx_x * 1 + idx_y * 1 * xdim3_reset_field_kernel2],
                        
                        xdim0_reset_field_kernel2,
                        xdim1_reset_field_kernel2,
                        xdim2_reset_field_kernel2,
                        xdim3_reset_field_kernel2);
   }

 }
