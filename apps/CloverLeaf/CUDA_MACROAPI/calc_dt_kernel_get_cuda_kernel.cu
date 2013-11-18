//
// auto-generated by ops.py on 2013-11-18 11:21
//

//user function
#include "calc_dt_kernel.h"

__global__ void ops_calc_dt_kernel_get(
const double* __restrict arg0,
const double* __restrict arg1,
double* __restrict arg2,
double* __restrict arg3,
int size0,
int size1 ){

  double arg2_l[1];
  double arg3_l[1];
  for (int d=0; d<1; d++) arg2_l[d] = ZERO_double;
  for (int d=0; d<1; d++) arg3_l[d] = ZERO_double;

  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1 + idx_y * 0 * xdim0_device;
  arg1 += idx_x * 0 + idx_y * 1 * xdim1_device;

  if (idx_x < size0 && idx_y < size1) {
    calc_dt_kernel_get(arg0, arg1, arg2_l, arg3_l);
  }
  for (int d=0; d<1; d++)
    ops_reduction<OPS_INC>(&arg2[d+blockIdx.x + blockIdx.y*gridDim.x],arg2_l[d]);
  for (int d=0; d<1; d++)
    ops_reduction<OPS_INC>(&arg3[d+blockIdx.x + blockIdx.y*gridDim.x],arg3_l[d]);

}

// host stub function
void ops_par_loop_calc_dt_kernel_get(char const *name, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3) {

  ops_arg args[4] = { arg0, arg1, arg2, arg3};


  int x_size = range[1]-range[0];
  int y_size = range[3]-range[2];

  int xdim0 = args[0].dat->block_size[0];
  int xdim1 = args[1].dat->block_size[0];

  cudaMemcpyToSymbol( xdim0_device, &xdim0, sizeof(int) );
  cudaMemcpyToSymbol( xdim1_device, &xdim1, sizeof(int) );


  double *arg2h = (double *)arg2.data;
  double *arg3h = (double *)arg3.data;

  int block_size = 16;
  dim3 grid( (x_size-1)/block_size+ 1, (y_size-1)/block_size + 1, 1);
  dim3 block(block_size,block_size,1);

  int nblocks = ((x_size-1)/block_size+ 1)*((y_size-1)/block_size + 1);
  int maxblocks = nblocks;
  int reduct_bytes = 0;
  int reduct_size = 0;

  reduct_bytes += ROUND_UP(maxblocks*1*sizeof(double));
  reduct_size = MAX(reduct_size,sizeof(double)*1);
  reduct_bytes += ROUND_UP(maxblocks*1*sizeof(double));
  reduct_size = MAX(reduct_size,sizeof(double)*1);

  reallocReductArrays(reduct_bytes);
  reduct_bytes = 0;

  arg2.data = OPS_reduct_h + reduct_bytes;
  arg2.data_d = OPS_reduct_d + reduct_bytes;
  for (int b=0; b<maxblocks; b++)
  for (int d=0; d<1; d++) ((double *)arg2.data)[d+b*1] = ZERO_double;
  reduct_bytes += ROUND_UP(maxblocks*1*sizeof(double));

  arg3.data = OPS_reduct_h + reduct_bytes;
  arg3.data_d = OPS_reduct_d + reduct_bytes;
  for (int b=0; b<maxblocks; b++)
  for (int d=0; d<1; d++) ((double *)arg3.data)[d+b*1] = ZERO_double;
  reduct_bytes += ROUND_UP(maxblocks*1*sizeof(double));


  mvReductArraysToDevice(reduct_bytes);

  char *p_a[4];


  //set up initial pointers
  p_a[0] = &args[0].data_d[
  + args[0].dat->size * args[0].dat->block_size[0] * ( range[2] * 0 - args[0].dat->offset[1] )
  + args[0].dat->size * ( range[0] * 1 - args[0].dat->offset[0] ) ];

  p_a[1] = &args[1].data_d[
  + args[1].dat->size * args[1].dat->block_size[0] * ( range[2] * 1 - args[1].dat->offset[1] )
  + args[1].dat->size * ( range[0] * 0 - args[1].dat->offset[0] ) ];


  ops_halo_exchanges_cuda(args, 4);

  int nshared = 0;
  int nthread = block_size*block_size;

  nshared = MAX(nshared,sizeof(double)*1);
  nshared = MAX(nshared,sizeof(double)*1);

  nshared = MAX(nshared*nthread,reduct_size*nthread);

  //call kernel wrapper function, passing in pointers to data
  ops_calc_dt_kernel_get<<<grid, block, nshared >>> (  (double *)p_a[0], (double *)p_a[1],
           (double *)arg2.data_d,  (double *)arg3.data_d, x_size, y_size);

  mvReductArraysToHost(reduct_bytes);
  for ( int b=0; b<maxblocks; b++ ){
    for ( int d=0; d<1; d++ ){
      arg2h[d] = arg2h[d] + ((double *)arg2.data)[d+b*1];
    }
  }
  arg2.data = (char *)arg2h;

  for ( int b=0; b<maxblocks; b++ ){
    for ( int d=0; d<1; d++ ){
      arg3h[d] = arg3h[d] + ((double *)arg3.data)[d+b*1];
    }
  }
  arg3.data = (char *)arg3h;

  cudaDeviceSynchronize();
  ops_set_dirtybit_cuda(args, 4);
}
