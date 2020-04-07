//
// auto-generated by ops.py
//
__constant__ int dims_ideal_gas_kernel [4][1];
static int dims_ideal_gas_kernel_h [4][1] = {0};

//user function
__device__

void ideal_gas_kernel_gpu(const ACC<double> &density,
  const ACC<double> &energy,
  ACC<double> &pressure,
  ACC<double> &soundspeed) {

  double sound_speed_squared, v, pressurebyenergy, pressurebyvolume;

  v = 1.0 / density(0,0);
  pressure(0,0) = (1.4 - 1.0) * density(0,0) * energy(0,0);
  pressurebyenergy = (1.4 - 1.0) * density(0,0);
  pressurebyvolume = -1*density(0,0) * pressure(0,0);
  sound_speed_squared = v*v*(pressure(0,0) * pressurebyenergy-pressurebyvolume);
  soundspeed(0,0) = sqrt(sound_speed_squared);
}



__global__ void ops_ideal_gas_kernel(
double* __restrict arg0,
double* __restrict arg1,
double* __restrict arg2,
double* __restrict arg3,
int size0,
int size1 ){


  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1*1 + idx_y * 1*1 * dims_ideal_gas_kernel[0][0];
  arg1 += idx_x * 1*1 + idx_y * 1*1 * dims_ideal_gas_kernel[1][0];
  arg2 += idx_x * 1*1 + idx_y * 1*1 * dims_ideal_gas_kernel[2][0];
  arg3 += idx_x * 1*1 + idx_y * 1*1 * dims_ideal_gas_kernel[3][0];

  if (idx_x < size0 && idx_y < size1) {
    const ACC<double> argp0(dims_ideal_gas_kernel[0][0], arg0);
    const ACC<double> argp1(dims_ideal_gas_kernel[1][0], arg1);
    ACC<double> argp2(dims_ideal_gas_kernel[2][0], arg2);
    ACC<double> argp3(dims_ideal_gas_kernel[3][0], arg3);
    ideal_gas_kernel_gpu(argp0, argp1, argp2, argp3);
  }

}

// host stub function
#ifndef OPS_LAZY
void ops_par_loop_ideal_gas_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3) {
#else
void ops_par_loop_ideal_gas_kernel_execute(ops_kernel_descriptor *desc) {
  int dim = desc->dim;
  #if OPS_MPI
  ops_block block = desc->block;
  #endif
  int *range = desc->range;
  ops_arg arg0 = desc->args[0];
  ops_arg arg1 = desc->args[1];
  ops_arg arg2 = desc->args[2];
  ops_arg arg3 = desc->args[3];
  #endif

  //Timing
  double t1,t2,c1,c2;

  ops_arg args[4] = { arg0, arg1, arg2, arg3};


  #if CHECKPOINTING && !OPS_LAZY
  if (!ops_checkpointing_before(args,4,range,8)) return;
  #endif

  if (block->instance->OPS_diags > 1) {
    ops_timing_realloc(block->instance,8,"ideal_gas_kernel");
    block->instance->OPS_kernels[8].count++;
    ops_timers_core(&c1,&t1);
  }

  //compute locally allocated range for the sub-block
  int start[2];
  int end[2];
  #if OPS_MPI && !OPS_LAZY
  sub_block_list sb = OPS_sub_block_list[block->index];
  #endif //OPS_MPI

  #ifdef OPS_MPI
  int arg_idx[2];
  #endif
  #if defined(OPS_LAZY) || !defined(OPS_MPI)
  for ( int n=0; n<2; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }
  #else
  if (compute_ranges(args, 4,block, range, start, end, arg_idx) < 0) return;
  #endif

  int xdim0 = args[0].dat->size[0];
  int xdim1 = args[1].dat->size[0];
  int xdim2 = args[2].dat->size[0];
  int xdim3 = args[3].dat->size[0];

  if (xdim0 != dims_ideal_gas_kernel_h[0][0] || xdim1 != dims_ideal_gas_kernel_h[1][0] || xdim2 != dims_ideal_gas_kernel_h[2][0] || xdim3 != dims_ideal_gas_kernel_h[3][0]) {
    dims_ideal_gas_kernel_h[0][0] = xdim0;
    dims_ideal_gas_kernel_h[1][0] = xdim1;
    dims_ideal_gas_kernel_h[2][0] = xdim2;
    dims_ideal_gas_kernel_h[3][0] = xdim3;
    cutilSafeCall(block->instance->ostream(), cudaMemcpyToSymbol( dims_ideal_gas_kernel, dims_ideal_gas_kernel_h, sizeof(dims_ideal_gas_kernel)));
  }



  int x_size = MAX(0,end[0]-start[0]);
  int y_size = MAX(0,end[1]-start[1]);

  dim3 grid( (x_size-1)/block->instance->OPS_block_size_x+ 1, (y_size-1)/block->instance->OPS_block_size_y + 1, 1);
  dim3 tblock(block->instance->OPS_block_size_x,block->instance->OPS_block_size_y,block->instance->OPS_block_size_z);



  int dat0 = (block->instance->OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size);
  int dat1 = (block->instance->OPS_soa ? args[1].dat->type_size : args[1].dat->elem_size);
  int dat2 = (block->instance->OPS_soa ? args[2].dat->type_size : args[2].dat->elem_size);
  int dat3 = (block->instance->OPS_soa ? args[3].dat->type_size : args[3].dat->elem_size);

  char *p_a[4];

  //set up initial pointers
  int base0 = args[0].dat->base_offset + 
           dat0 * 1 * (start[0] * args[0].stencil->stride[0]);
  base0 = base0+ dat0 *
    args[0].dat->size[0] *
    (start[1] * args[0].stencil->stride[1]);
  p_a[0] = (char *)args[0].data_d + base0;

  int base1 = args[1].dat->base_offset + 
           dat1 * 1 * (start[0] * args[1].stencil->stride[0]);
  base1 = base1+ dat1 *
    args[1].dat->size[0] *
    (start[1] * args[1].stencil->stride[1]);
  p_a[1] = (char *)args[1].data_d + base1;

  int base2 = args[2].dat->base_offset + 
           dat2 * 1 * (start[0] * args[2].stencil->stride[0]);
  base2 = base2+ dat2 *
    args[2].dat->size[0] *
    (start[1] * args[2].stencil->stride[1]);
  p_a[2] = (char *)args[2].data_d + base2;

  int base3 = args[3].dat->base_offset + 
           dat3 * 1 * (start[0] * args[3].stencil->stride[0]);
  base3 = base3+ dat3 *
    args[3].dat->size[0] *
    (start[1] * args[3].stencil->stride[1]);
  p_a[3] = (char *)args[3].data_d + base3;


  #ifndef OPS_LAZY
  ops_H_D_exchanges_device(args, 4);
  ops_halo_exchanges(args,4,range);
  #endif

  if (block->instance->OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    block->instance->OPS_kernels[8].mpi_time += t2-t1;
  }


  //call kernel wrapper function, passing in pointers to data
  if (x_size > 0 && y_size > 0)
    ops_ideal_gas_kernel<<<grid, tblock >>> (  (double *)p_a[0], (double *)p_a[1],
         (double *)p_a[2], (double *)p_a[3],x_size, y_size);

  cutilSafeCall(block->instance->ostream(), cudaGetLastError());

  if (block->instance->OPS_diags>1) {
    cutilSafeCall(block->instance->ostream(), cudaDeviceSynchronize());
    ops_timers_core(&c1,&t1);
    block->instance->OPS_kernels[8].time += t1-t2;
  }

  #ifndef OPS_LAZY
  ops_set_dirtybit_device(args, 4);
  ops_set_halo_dirtybit3(&args[2],range);
  ops_set_halo_dirtybit3(&args[3],range);
  #endif

  if (block->instance->OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c2,&t2);
    block->instance->OPS_kernels[8].mpi_time += t2-t1;
    block->instance->OPS_kernels[8].transfer += ops_compute_transfer(dim, start, end, &arg0);
    block->instance->OPS_kernels[8].transfer += ops_compute_transfer(dim, start, end, &arg1);
    block->instance->OPS_kernels[8].transfer += ops_compute_transfer(dim, start, end, &arg2);
    block->instance->OPS_kernels[8].transfer += ops_compute_transfer(dim, start, end, &arg3);
  }
}

#ifdef OPS_LAZY
void ops_par_loop_ideal_gas_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3) {
  ops_kernel_descriptor *desc = (ops_kernel_descriptor *)calloc(1,sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->device = 1;
  desc->index = 8;
  desc->hash = 5381;
  desc->hash = ((desc->hash << 5) + desc->hash) + 8;
  for ( int i=0; i<4; i++ ){
    desc->range[i] = range[i];
    desc->orig_range[i] = range[i];
    desc->hash = ((desc->hash << 5) + desc->hash) + range[i];
  }
  desc->nargs = 4;
  desc->args = (ops_arg*)malloc(4*sizeof(ops_arg));
  desc->args[0] = arg0;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg0.dat->index;
  desc->args[1] = arg1;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg1.dat->index;
  desc->args[2] = arg2;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg2.dat->index;
  desc->args[3] = arg3;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg3.dat->index;
  desc->function = ops_par_loop_ideal_gas_kernel_execute;
  if (block->instance->OPS_diags > 1) {
    ops_timing_realloc(block->instance,8,"ideal_gas_kernel");
  }
  ops_enqueue_kernel(desc);
}
#endif
