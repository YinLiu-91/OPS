//
// auto-generated by ops.py on 2013-11-18 12:47
//

__constant__ int xdim0_advec_mom_kernel_post_advec_y;
__constant__ int xdim1_advec_mom_kernel_post_advec_y;
__constant__ int xdim2_advec_mom_kernel_post_advec_y;

#define OPS_ACC0(x,y) (x+xdim0_advec_mom_kernel_post_advec_y*(y))
#define OPS_ACC1(x,y) (x+xdim1_advec_mom_kernel_post_advec_y*(y))
#define OPS_ACC2(x,y) (x+xdim2_advec_mom_kernel_post_advec_y*(y))

//user function
__device__

inline void advec_mom_kernel_post_advec_y( double *node_mass_post, const double *post_vol,
                                  const double *density1) {

  //post_vol accessed with: {0,0, -1,0, 0,-1, -1,-1}
  //density1 accessed with: {0,0, -1,0, 0,-1, -1,-1}

  node_mass_post[OPS_ACC0(0,0)] = 0.25 * ( density1[OPS_ACC2(0,-1)] * post_vol[OPS_ACC0(0,-1)] +
                              density1[OPS_ACC2(0,0)]   * post_vol[OPS_ACC1(0,0)]   +
                              density1[OPS_ACC2(-1,-1)] * post_vol[OPS_ACC1(-1,-1)] +
                              density1[OPS_ACC2(-1,0)]  * post_vol[OPS_ACC1(-1,0)]  );

}

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2


__global__ void ops_advec_mom_kernel_post_advec_y(
double* __restrict arg0,
const double* __restrict arg1,
const double* __restrict arg2,
int size0,
int size1 ){


  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1 + idx_y * 1 * xdim0_advec_mom_kernel_post_advec_y;
  arg1 += idx_x * 1 + idx_y * 1 * xdim1_advec_mom_kernel_post_advec_y;
  arg2 += idx_x * 1 + idx_y * 1 * xdim2_advec_mom_kernel_post_advec_y;

  if (idx_x < size0 && idx_y < size1) {
    advec_mom_kernel_post_advec_y(arg0, arg1, arg2);
  }

}

// host stub function
void ops_par_loop_advec_mom_kernel_post_advec_y(char const *name, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2) {

  ops_arg args[3] = { arg0, arg1, arg2};


  int x_size = range[1]-range[0];
  int y_size = range[3]-range[2];

  int xdim0 = args[0].dat->block_size[0];
  int xdim1 = args[1].dat->block_size[0];
  int xdim2 = args[2].dat->block_size[0];

  ops_timing_realloc(23);
  if (OPS_kernels[23].count == 0) {
    cudaMemcpyToSymbol( xdim0_advec_mom_kernel_post_advec_y, &xdim0, sizeof(int) );
    cudaMemcpyToSymbol( xdim1_advec_mom_kernel_post_advec_y, &xdim1, sizeof(int) );
    cudaMemcpyToSymbol( xdim2_advec_mom_kernel_post_advec_y, &xdim2, sizeof(int) );
  }



  int block_size = 16;
  dim3 grid( (x_size-1)/block_size+ 1, (y_size-1)/block_size + 1, 1);
  dim3 block(block_size,block_size,1);




  char *p_a[3];


  //set up initial pointers
  p_a[0] = &args[0].data_d[
  + args[0].dat->size * args[0].dat->block_size[0] * ( range[2] * 1 - args[0].dat->offset[1] )
  + args[0].dat->size * ( range[0] * 1 - args[0].dat->offset[0] ) ];

  p_a[1] = &args[1].data_d[
  + args[1].dat->size * args[1].dat->block_size[0] * ( range[2] * 1 - args[1].dat->offset[1] )
  + args[1].dat->size * ( range[0] * 1 - args[1].dat->offset[0] ) ];

  p_a[2] = &args[2].data_d[
  + args[2].dat->size * args[2].dat->block_size[0] * ( range[2] * 1 - args[2].dat->offset[1] )
  + args[2].dat->size * ( range[0] * 1 - args[2].dat->offset[0] ) ];


  ops_halo_exchanges_cuda(args, 3);


  //call kernel wrapper function, passing in pointers to data
  ops_advec_mom_kernel_post_advec_y<<<grid, block >>> (  (double *)p_a[0], (double *)p_a[1],
           (double *)p_a[2],x_size, y_size);

  cudaDeviceSynchronize();
  ops_set_dirtybit_cuda(args, 3);
}