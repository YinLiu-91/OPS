//
// auto-generated by ops.py on 2013-11-25 15:46
//

__constant__ int xdim0_flux_calc_kernelx;
__constant__ int xdim1_flux_calc_kernelx;
__constant__ int xdim2_flux_calc_kernelx;
__constant__ int xdim3_flux_calc_kernelx;

#define OPS_ACC0(x,y) (x+xdim0_flux_calc_kernelx*(y))
#define OPS_ACC1(x,y) (x+xdim1_flux_calc_kernelx*(y))
#define OPS_ACC2(x,y) (x+xdim2_flux_calc_kernelx*(y))
#define OPS_ACC3(x,y) (x+xdim3_flux_calc_kernelx*(y))

//user function
__device__

inline void flux_calc_kernelx( double *vol_flux_x, const double *xarea,
                        const double *xvel0, const double *xvel1) {

  vol_flux_x[OPS_ACC0(0,0)] = 0.25 * dt * (xarea[OPS_ACC1(0,0)]) *
  ( (xvel0[OPS_ACC2(0,0)]) + (xvel0[OPS_ACC2(0,1)]) + (xvel1[OPS_ACC3(0,0)]) + (xvel1[OPS_ACC3(0,1)]) );

}



#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3


__global__ void ops_flux_calc_kernelx(
double* __restrict arg0,
const double* __restrict arg1,
const double* __restrict arg2,
const double* __restrict arg3,
int size0,
int size1 ){


  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1 + idx_y * 1 * xdim0_flux_calc_kernelx;
  arg1 += idx_x * 1 + idx_y * 1 * xdim1_flux_calc_kernelx;
  arg2 += idx_x * 1 + idx_y * 1 * xdim2_flux_calc_kernelx;
  arg3 += idx_x * 1 + idx_y * 1 * xdim3_flux_calc_kernelx;

  if (idx_x < size0 && idx_y < size1) {
    flux_calc_kernelx(arg0, arg1, arg2, arg3);
  }

}

// host stub function
void ops_par_loop_flux_calc_kernelx(char const *name, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3) {

  ops_arg args[4] = { arg0, arg1, arg2, arg3};


  int x_size = range[1]-range[0];
  int y_size = range[3]-range[2];

  int xdim0 = args[0].dat->block_size[0];
  int xdim1 = args[1].dat->block_size[0];
  int xdim2 = args[2].dat->block_size[0];
  int xdim3 = args[3].dat->block_size[0];


  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(78,"flux_calc_kernelx");
  ops_timers_core(&c1,&t1);

  if (OPS_kernels[78].count == 0) {
    cudaMemcpyToSymbol( xdim0_flux_calc_kernelx, &xdim0, sizeof(int) );
    cudaMemcpyToSymbol( xdim1_flux_calc_kernelx, &xdim1, sizeof(int) );
    cudaMemcpyToSymbol( xdim2_flux_calc_kernelx, &xdim2, sizeof(int) );
    cudaMemcpyToSymbol( xdim3_flux_calc_kernelx, &xdim3, sizeof(int) );
  }



  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, (y_size-1)/OPS_block_size_y + 1, 1);
  dim3 block(OPS_block_size_x,OPS_block_size_y,1);




  char *p_a[4];


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

  p_a[3] = &args[3].data_d[
  + args[3].dat->size * args[3].dat->block_size[0] * ( range[2] * 1 - args[3].dat->offset[1] )
  + args[3].dat->size * ( range[0] * 1 - args[3].dat->offset[0] ) ];


  ops_halo_exchanges_cuda(args, 4);


  //call kernel wrapper function, passing in pointers to data
  ops_flux_calc_kernelx<<<grid, block >>> (  (double *)p_a[0], (double *)p_a[1],
           (double *)p_a[2], (double *)p_a[3],x_size, y_size);

  if (OPS_diags>1) cudaDeviceSynchronize();
  ops_set_dirtybit_cuda(args, 4);

  //Update kernel record
  ops_timers_core(&c2,&t2);
  OPS_kernels[78].count++;
  OPS_kernels[78].time += t2-t1;
  OPS_kernels[78].transfer += ops_compute_transfer(dim, range, &arg0);
  OPS_kernels[78].transfer += ops_compute_transfer(dim, range, &arg1);
  OPS_kernels[78].transfer += ops_compute_transfer(dim, range, &arg2);
  OPS_kernels[78].transfer += ops_compute_transfer(dim, range, &arg3);
}