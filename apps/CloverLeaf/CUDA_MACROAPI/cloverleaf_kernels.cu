//
// auto-generated by op2.py on 2013-10-25 15:16
//

//header
#include "ops_lib_cpp.h"
#include "ops_cuda_rt_support.h"
#include "ops_cuda_reduction.h"


__constant__ int xdim0_device;
__constant__ int xdim1_device;
__constant__ int xdim2_device;
__constant__ int xdim3_device;
__constant__ int xdim4_device;
__constant__ int xdim5_device;
__constant__ int xdim6_device;
__constant__ int xdim7_device;
__constant__ int xdim8_device;
__constant__ int xdim9_device;
__constant__ int xdim10_device;
__constant__ int xdim11_device;
__constant__ int xdim12_device;
__constant__ int xdim13_device;

__constant__ double dt;
__constant__ double x_max;
__constant__ double y_max;

__constant__ double g_small;
__constant__ double dtc_safe;
__constant__ double g_big;
__constant__ double dtu_safe;
__constant__ double dtv_safe;
__constant__ double dtdiv_safe;

__constant__ int FIELD_DEVICE_DENSITY0   = 0;
__constant__ int FIELD_DEVICE_DENSITY1   = 1;
__constant__ int FIELD_DEVICE_ENERGY0    = 2;
__constant__ int FIELD_DEVICE_ENERGY1    = 3;
__constant__ int FIELD_DEVICE_PRESSURE   = 4;
__constant__ int FIELD_DEVICE_VISCOSITY  = 5;
__constant__ int FIELD_DEVICE_SOUNDSPEED = 6;
__constant__ int FIELD_DEVICE_XVEL0      = 7;
__constant__ int FIELD_DEVICE_XVEL1      = 8;
__constant__ int FIELD_DEVICE_YVEL0      = 9;
__constant__ int FIELD_DEVICE_YVEL1      =10;
__constant__ int FIELD_DEVICE_VOL_FLUX_X =11;
__constant__ int FIELD_DEVICE_VOL_FLUX_Y =12;
__constant__ int FIELD_DEVICE_MASS_FLUX_X=13;
__constant__ int FIELD_DEVICE_MASS_FLUX_Y=14;

#define NUM_FIELDS 15

__device__ int* fields_device;// = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};



void ops_decl_const_char(int dim, char const *type,
            int size, char *dat, char const *name) {
  if (!strcmp(name,"dt")) {
    cutilSafeCall(cudaMemcpyToSymbol(dt, dat, dim*size));
  } else if (!strcmp(name,"x_max")) {
    cutilSafeCall(cudaMemcpyToSymbol(x_max, dat, dim*size));
  } else if (!strcmp(name,"y_max")) {
    cutilSafeCall(cudaMemcpyToSymbol(y_max, dat, dim*size));
  } else if (!strcmp(name,"g_small")) {
    cutilSafeCall(cudaMemcpyToSymbol(g_small, dat, dim*size));
  } else if (!strcmp(name,"dtc_safe")) {
    cutilSafeCall(cudaMemcpyToSymbol(dtc_safe, dat, dim*size));
  } else if (!strcmp(name,"g_big")) {
    cutilSafeCall(cudaMemcpyToSymbol(g_big, dat, dim*size));
  } else if (!strcmp(name,"dtu_safe")) {
    cutilSafeCall(cudaMemcpyToSymbol(dtu_safe, dat, dim*size));
  } else if (!strcmp(name,"dtv_safe")) {
    cutilSafeCall(cudaMemcpyToSymbol(dtv_safe, dat, dim*size));
  } else if (!strcmp(name,"dtdiv_safe")) {
    cutilSafeCall(cudaMemcpyToSymbol(dtdiv_safe, dat, dim*size));
  } else {
    printf("error: unknown const name\n"); exit(1);
  }
}


#define OPS_ACC_MACROS
#define OPS_ACC0(x,y) (x+xdim0_device*(y))
#define OPS_ACC1(x,y) (x+xdim1_device*(y))
#define OPS_ACC2(x,y) (x+xdim2_device*(y))
#define OPS_ACC3(x,y) (x+xdim3_device*(y))
#define OPS_ACC4(x,y) (x+xdim4_device*(y))
#define OPS_ACC5(x,y) (x+xdim5_device*(y))
#define OPS_ACC6(x,y) (x+xdim6_device*(y))
#define OPS_ACC7(x,y) (x+xdim7_device*(y))
#define OPS_ACC8(x,y) (x+xdim8_device*(y))
#define OPS_ACC9(x,y) (x+xdim9_device*(y))
#define OPS_ACC10(x,y) (x+xdim10_device*(y))
#define OPS_ACC11(x,y) (x+xdim11_device*(y))
#define OPS_ACC12(x,y) (x+xdim12_device*(y))
#define OPS_ACC13(x,y) (x+xdim13_device*(y))


//user kernel files

#include "accelerate_kernel_stepbymass_cuda_kernel.cu"
#include "accelerate_kernelx1_cuda_kernel.cu"
#include "accelerate_kernely1_cuda_kernel.cu"
#include "accelerate_kernelx2_cuda_kernel.cu"
#include "accelerate_kernely2_cuda_kernel.cu"
#include "viscosity_kernel_cuda_kernel.cu"

#include "PdV_kernel_predict_cuda_kernel.cu"
#include "PdV_kernel_nopredict_cuda_kernel.cu"
#include "revert_kernel_cuda_kernel.cu"
#include "reset_field_kernel1_cuda_kernel.cu"
#include "reset_field_kernel2_cuda_kernel.cu"

#include "advec_mom_kernel_x1_cuda_kernel.cu"
#include "advec_mom_kernel_y1_cuda_kernel.cu"
#include "advec_mom_kernel_x2_cuda_kernel.cu"
#include "advec_mom_kernel_y2_cuda_kernel.cu"
#include "advec_mom_kernel_mass_flux_x_cuda_kernel.cu"
#include "advec_mom_kernel_post_advec_x_cuda_kernel.cu"
#include "advec_mom_kernel_pre_advec_x_cuda_kernel.cu"
#include "advec_mom_kernel1_x_cuda_kernel.cu"
#include "advec_mom_kernel2_x_cuda_kernel.cu"
#include "advec_mom_kernel_mass_flux_y_cuda_kernel.cu"
#include "advec_mom_kernel_post_advec_y_cuda_kernel.cu"
#include "advec_mom_kernel_pre_advec_y_cuda_kernel.cu"
#include "advec_mom_kernel1_y_cuda_kernel.cu"
#include "advec_mom_kernel2_y_cuda_kernel.cu"

#include "advec_cell_kernel1_xdir_cuda_kernel.cu"
#include "advec_cell_kernel2_xdir_cuda_kernel.cu"
#include "advec_cell_kernel3_xdir_cuda_kernel.cu"
#include "advec_cell_kernel4_xdir_cuda_kernel.cu"
#include "advec_cell_kernel1_ydir_cuda_kernel.cu"
#include "advec_cell_kernel2_ydir_cuda_kernel.cu"
#include "advec_cell_kernel3_ydir_cuda_kernel.cu"
#include "advec_cell_kernel4_ydir_cuda_kernel.cu"

#include "ideal_gas_kernel_cuda_kernel.cu"
#include "flux_calc_kernelx_cuda_kernel.cu"
#include "flux_calc_kernely_cuda_kernel.cu"

#include "field_summary_kernel_cuda_kernel.cu"

#include "update_halo_kernel1_b2_cuda_kernel.cu"
#include "update_halo_kernel1_b1_cuda_kernel.cu"
#include "update_halo_kernel1_t2_cuda_kernel.cu"
#include "update_halo_kernel1_t1_cuda_kernel.cu"
#include "update_halo_kernel1_l2_cuda_kernel.cu"
#include "update_halo_kernel1_l1_cuda_kernel.cu"
#include "update_halo_kernel1_r2_cuda_kernel.cu"
#include "update_halo_kernel1_r1_cuda_kernel.cu"
#include "update_halo_kernel2_xvel_plus_4_a_cuda_kernel.cu"
#include "update_halo_kernel2_xvel_plus_2_a_cuda_kernel.cu"
#include "update_halo_kernel2_xvel_plus_4_b_cuda_kernel.cu"
#include "update_halo_kernel2_xvel_plus_2_b_cuda_kernel.cu"
#include "update_halo_kernel2_xvel_minus_4_a_cuda_kernel.cu"
#include "update_halo_kernel2_xvel_minus_2_a_cuda_kernel.cu"
#include "update_halo_kernel2_xvel_minus_4_b_cuda_kernel.cu"
#include "update_halo_kernel2_xvel_minus_2_b_cuda_kernel.cu"
#include "update_halo_kernel2_yvel_minus_4_a_cuda_kernel.cu"
#include "update_halo_kernel2_yvel_minus_2_a_cuda_kernel.cu"
#include "update_halo_kernel2_yvel_minus_4_b_cuda_kernel.cu"
#include "update_halo_kernel2_yvel_minus_2_b_cuda_kernel.cu"
#include "update_halo_kernel2_yvel_plus_4_a_cuda_kernel.cu"
#include "update_halo_kernel2_yvel_plus_2_a_cuda_kernel.cu"
#include "update_halo_kernel2_yvel_plus_4_b_cuda_kernel.cu"
#include "update_halo_kernel2_yvel_plus_2_b_cuda_kernel.cu"
#include "update_halo_kernel3_plus_4_a_cuda_kernel.cu"
#include "update_halo_kernel3_plus_2_a_cuda_kernel.cu"
#include "update_halo_kernel3_plus_4_b_cuda_kernel.cu"
#include "update_halo_kernel3_plus_2_b_cuda_kernel.cu"
#include "update_halo_kernel3_minus_4_a_cuda_kernel.cu"
#include "update_halo_kernel3_minus_2_a_cuda_kernel.cu"
#include "update_halo_kernel3_minus_4_b_cuda_kernel.cu"
#include "update_halo_kernel3_minus_2_b_cuda_kernel.cu"
#include "update_halo_kernel4_minus_4_a_cuda_kernel.cu"
#include "update_halo_kernel4_minus_2_a_cuda_kernel.cu"
#include "update_halo_kernel4_minus_4_b_cuda_kernel.cu"
#include "update_halo_kernel4_minus_2_b_cuda_kernel.cu"
#include "update_halo_kernel4_plus_4_a_cuda_kernel.cu"
#include "update_halo_kernel4_plus_2_a_cuda_kernel.cu"
#include "update_halo_kernel4_plus_4_b_cuda_kernel.cu"
#include "update_halo_kernel4_plus_2_b_cuda_kernel.cu"

#include "calc_dt_kernel_cuda_kernel.cu"
#include "calc_dt_kernel_min_cuda_kernel.cu"
#include "calc_dt_kernel_get_cuda_kernel.cu"
#include "calc_dt_kernel_print_cuda_kernel.cu"

/*#include "initialise_chunk_kernel_x_cuda_kernel.cu"
#include "initialise_chunk_kernel_y_cuda_kernel.cu"
#include "initialise_chunk_kernel_cellx_cuda_kernel.cu"
#include "initialise_chunk_kernel_celly_cuda_kernel.cu"
#include "initialise_chunk_kernel_volume_cuda_kernel.cu"*/
