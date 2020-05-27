//
// auto-generated by ops.py
//
__constant__ int dims_advec_cell_kernel3_ydir [8][1];
static int dims_advec_cell_kernel3_ydir_h [8][1] = {0};

//user function
__device__

inline void advec_cell_kernel3_ydir_gpu(const ACC<double> &vol_flux_y,
  const ACC<double> &pre_vol,
  const ACC<int> &yy,
  const ACC<double> &vertexdy,
  const ACC<double> &density1,
  const ACC<double> &energy1,
  ACC<double> &mass_flux_y,
  ACC<double> &ener_flux) {

  double sigmat, sigmav, sigmam, sigma3, sigma4;
  double diffuw, diffdw, limiter;
  double one_by_six = 1.0/6.0;

  int y_max=field.y_max;

  int upwind,donor,downwind,dif;





  if(vol_flux_y(0,0) > 0.0) {
    upwind   = -2;
    donor    = -1;
    downwind = 0;
    dif      = donor;
  }
  else if (yy(0,1) < y_max+2-2) {
    upwind   = 1;
    donor    = 0;
    downwind = -1;
    dif      = upwind;
  } else {
    upwind   = 0;
    donor    = 0;
    downwind = -1;
    dif      = upwind;
  }


  sigmat = fabs(vol_flux_y(0,0))/pre_vol(0,donor);
  sigma3 = (1.0 + sigmat)*(vertexdy(0,0)/vertexdy(0,dif));
  sigma4 = 2.0 - sigmat;

  sigmav = sigmat;

  diffuw = density1(0,donor) - density1(0,upwind);
  diffdw = density1(0,downwind) - density1(0,donor);

  if( (diffuw*diffdw) > 0.0)
    limiter=(1.0 - sigmav) * SIGN(1.0 , diffdw) *
    MIN( MIN(fabs(diffuw), fabs(diffdw)),
    one_by_six * (sigma3*fabs(diffuw) + sigma4 * fabs(diffdw)));
  else
    limiter=0.0;

  mass_flux_y(0,0) = (vol_flux_y(0,0)) * ( density1(0,donor) + limiter );

  sigmam = fabs(mass_flux_y(0,0))/( density1(0,donor) * pre_vol(0,donor));
  diffuw = energy1(0,donor) - energy1(0,upwind);
  diffdw = energy1(0,downwind) - energy1(0,donor);

  if( (diffuw*diffdw) > 0.0)
    limiter = (1.0 - sigmam) * SIGN(1.0,diffdw) *
    MIN( MIN(fabs(diffuw), fabs(diffdw)),
    one_by_six * (sigma3 * fabs(diffuw) + sigma4 * fabs(diffdw)));
  else
    limiter=0.0;

  ener_flux(0,0) = mass_flux_y(0,0) * ( energy1(0,donor) + limiter );
}



__global__ void ops_advec_cell_kernel3_ydir(
double* __restrict arg0,
double* __restrict arg1,
int* __restrict arg2,
double* __restrict arg3,
double* __restrict arg4,
double* __restrict arg5,
double* __restrict arg6,
double* __restrict arg7,
int size0,
int size1 ){


  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1*1 + idx_y * 1*1 * dims_advec_cell_kernel3_ydir[0][0];
  arg1 += idx_x * 1*1 + idx_y * 1*1 * dims_advec_cell_kernel3_ydir[1][0];
  arg2 += idx_x * 0*1 + idx_y * 1*1 * dims_advec_cell_kernel3_ydir[2][0];
  arg3 += idx_x * 0*1 + idx_y * 1*1 * dims_advec_cell_kernel3_ydir[3][0];
  arg4 += idx_x * 1*1 + idx_y * 1*1 * dims_advec_cell_kernel3_ydir[4][0];
  arg5 += idx_x * 1*1 + idx_y * 1*1 * dims_advec_cell_kernel3_ydir[5][0];
  arg6 += idx_x * 1*1 + idx_y * 1*1 * dims_advec_cell_kernel3_ydir[6][0];
  arg7 += idx_x * 1*1 + idx_y * 1*1 * dims_advec_cell_kernel3_ydir[7][0];

  if (idx_x < size0 && idx_y < size1) {
    const ACC<double> argp0(dims_advec_cell_kernel3_ydir[0][0], arg0);
    const ACC<double> argp1(dims_advec_cell_kernel3_ydir[1][0], arg1);
    const ACC<int> argp2(dims_advec_cell_kernel3_ydir[2][0], arg2);
    const ACC<double> argp3(dims_advec_cell_kernel3_ydir[3][0], arg3);
    const ACC<double> argp4(dims_advec_cell_kernel3_ydir[4][0], arg4);
    const ACC<double> argp5(dims_advec_cell_kernel3_ydir[5][0], arg5);
    ACC<double> argp6(dims_advec_cell_kernel3_ydir[6][0], arg6);
    ACC<double> argp7(dims_advec_cell_kernel3_ydir[7][0], arg7);
    advec_cell_kernel3_ydir_gpu(argp0, argp1, argp2, argp3,
                   argp4, argp5, argp6, argp7);
  }

}

// host stub function
#ifndef OPS_LAZY
void ops_par_loop_advec_cell_kernel3_ydir(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5, ops_arg arg6, ops_arg arg7) {
#else
void ops_par_loop_advec_cell_kernel3_ydir_execute(ops_kernel_descriptor *desc) {
  int dim = desc->dim;
  #if OPS_MPI
  ops_block block = desc->block;
  #endif
  int *range = desc->range;
  ops_arg arg0 = desc->args[0];
  ops_arg arg1 = desc->args[1];
  ops_arg arg2 = desc->args[2];
  ops_arg arg3 = desc->args[3];
  ops_arg arg4 = desc->args[4];
  ops_arg arg5 = desc->args[5];
  ops_arg arg6 = desc->args[6];
  ops_arg arg7 = desc->args[7];
  #endif

  //Timing
  double t1,t2,c1,c2;

  ops_arg args[8] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7};


  #if CHECKPOINTING && !OPS_LAZY
  if (!ops_checkpointing_before(args,8,range,67)) return;
  #endif

  if (block->instance->OPS_diags > 1) {
    ops_timing_realloc(block->instance,67,"advec_cell_kernel3_ydir");
    block->instance->OPS_kernels[67].count++;
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
  if (compute_ranges(args, 8,block, range, start, end, arg_idx) < 0) return;
  #endif

  int xdim0 = args[0].dat->size[0];
  int xdim1 = args[1].dat->size[0];
  int xdim2 = args[2].dat->size[0];
  int xdim3 = args[3].dat->size[0];
  int xdim4 = args[4].dat->size[0];
  int xdim5 = args[5].dat->size[0];
  int xdim6 = args[6].dat->size[0];
  int xdim7 = args[7].dat->size[0];

  if (xdim0 != dims_advec_cell_kernel3_ydir_h[0][0] || xdim1 != dims_advec_cell_kernel3_ydir_h[1][0] || xdim2 != dims_advec_cell_kernel3_ydir_h[2][0] || xdim3 != dims_advec_cell_kernel3_ydir_h[3][0] || xdim4 != dims_advec_cell_kernel3_ydir_h[4][0] || xdim5 != dims_advec_cell_kernel3_ydir_h[5][0] || xdim6 != dims_advec_cell_kernel3_ydir_h[6][0] || xdim7 != dims_advec_cell_kernel3_ydir_h[7][0]) {
    dims_advec_cell_kernel3_ydir_h[0][0] = xdim0;
    dims_advec_cell_kernel3_ydir_h[1][0] = xdim1;
    dims_advec_cell_kernel3_ydir_h[2][0] = xdim2;
    dims_advec_cell_kernel3_ydir_h[3][0] = xdim3;
    dims_advec_cell_kernel3_ydir_h[4][0] = xdim4;
    dims_advec_cell_kernel3_ydir_h[5][0] = xdim5;
    dims_advec_cell_kernel3_ydir_h[6][0] = xdim6;
    dims_advec_cell_kernel3_ydir_h[7][0] = xdim7;
    cutilSafeCall(block->instance->ostream(), cudaMemcpyToSymbol( dims_advec_cell_kernel3_ydir, dims_advec_cell_kernel3_ydir_h, sizeof(dims_advec_cell_kernel3_ydir)));
  }



  int x_size = MAX(0,end[0]-start[0]);
  int y_size = MAX(0,end[1]-start[1]);

  dim3 grid( (x_size-1)/block->instance->OPS_block_size_x+ 1, (y_size-1)/block->instance->OPS_block_size_y + 1, 1);
  dim3 tblock(block->instance->OPS_block_size_x,block->instance->OPS_block_size_y,block->instance->OPS_block_size_z);



  int dat0 = (block->instance->OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size);
  int dat1 = (block->instance->OPS_soa ? args[1].dat->type_size : args[1].dat->elem_size);
  int dat2 = (block->instance->OPS_soa ? args[2].dat->type_size : args[2].dat->elem_size);
  int dat3 = (block->instance->OPS_soa ? args[3].dat->type_size : args[3].dat->elem_size);
  int dat4 = (block->instance->OPS_soa ? args[4].dat->type_size : args[4].dat->elem_size);
  int dat5 = (block->instance->OPS_soa ? args[5].dat->type_size : args[5].dat->elem_size);
  int dat6 = (block->instance->OPS_soa ? args[6].dat->type_size : args[6].dat->elem_size);
  int dat7 = (block->instance->OPS_soa ? args[7].dat->type_size : args[7].dat->elem_size);

  char *p_a[8];

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

  int base4 = args[4].dat->base_offset + 
           dat4 * 1 * (start[0] * args[4].stencil->stride[0]);
  base4 = base4+ dat4 *
    args[4].dat->size[0] *
    (start[1] * args[4].stencil->stride[1]);
  p_a[4] = (char *)args[4].data_d + base4;

  int base5 = args[5].dat->base_offset + 
           dat5 * 1 * (start[0] * args[5].stencil->stride[0]);
  base5 = base5+ dat5 *
    args[5].dat->size[0] *
    (start[1] * args[5].stencil->stride[1]);
  p_a[5] = (char *)args[5].data_d + base5;

  int base6 = args[6].dat->base_offset + 
           dat6 * 1 * (start[0] * args[6].stencil->stride[0]);
  base6 = base6+ dat6 *
    args[6].dat->size[0] *
    (start[1] * args[6].stencil->stride[1]);
  p_a[6] = (char *)args[6].data_d + base6;

  int base7 = args[7].dat->base_offset + 
           dat7 * 1 * (start[0] * args[7].stencil->stride[0]);
  base7 = base7+ dat7 *
    args[7].dat->size[0] *
    (start[1] * args[7].stencil->stride[1]);
  p_a[7] = (char *)args[7].data_d + base7;


  #ifndef OPS_LAZY
  ops_H_D_exchanges_device(args, 8);
  ops_halo_exchanges(args,8,range);
  #endif

  if (block->instance->OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    block->instance->OPS_kernels[67].mpi_time += t2-t1;
  }


  //call kernel wrapper function, passing in pointers to data
  if (x_size > 0 && y_size > 0)
    ops_advec_cell_kernel3_ydir<<<grid, tblock >>> (  (double *)p_a[0], (double *)p_a[1],
         (int *)p_a[2], (double *)p_a[3],
         (double *)p_a[4], (double *)p_a[5],
         (double *)p_a[6], (double *)p_a[7],x_size, y_size);

  cutilSafeCall(block->instance->ostream(), cudaGetLastError());

  if (block->instance->OPS_diags>1) {
    cutilSafeCall(block->instance->ostream(), cudaDeviceSynchronize());
    ops_timers_core(&c1,&t1);
    block->instance->OPS_kernels[67].time += t1-t2;
  }

  #ifndef OPS_LAZY
  ops_set_dirtybit_device(args, 8);
  ops_set_halo_dirtybit3(&args[6],range);
  ops_set_halo_dirtybit3(&args[7],range);
  #endif

  if (block->instance->OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c2,&t2);
    block->instance->OPS_kernels[67].mpi_time += t2-t1;
    block->instance->OPS_kernels[67].transfer += ops_compute_transfer(dim, start, end, &arg0);
    block->instance->OPS_kernels[67].transfer += ops_compute_transfer(dim, start, end, &arg1);
    block->instance->OPS_kernels[67].transfer += ops_compute_transfer(dim, start, end, &arg2);
    block->instance->OPS_kernels[67].transfer += ops_compute_transfer(dim, start, end, &arg3);
    block->instance->OPS_kernels[67].transfer += ops_compute_transfer(dim, start, end, &arg4);
    block->instance->OPS_kernels[67].transfer += ops_compute_transfer(dim, start, end, &arg5);
    block->instance->OPS_kernels[67].transfer += ops_compute_transfer(dim, start, end, &arg6);
    block->instance->OPS_kernels[67].transfer += ops_compute_transfer(dim, start, end, &arg7);
  }
}

#ifdef OPS_LAZY
void ops_par_loop_advec_cell_kernel3_ydir(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3, ops_arg arg4, ops_arg arg5, ops_arg arg6, ops_arg arg7) {
  ops_kernel_descriptor *desc = (ops_kernel_descriptor *)calloc(1,sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->device = 1;
  desc->index = 67;
  desc->hash = 5381;
  desc->hash = ((desc->hash << 5) + desc->hash) + 67;
  for ( int i=0; i<4; i++ ){
    desc->range[i] = range[i];
    desc->orig_range[i] = range[i];
    desc->hash = ((desc->hash << 5) + desc->hash) + range[i];
  }
  desc->nargs = 8;
  desc->args = (ops_arg*)ops_malloc(8*sizeof(ops_arg));
  desc->args[0] = arg0;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg0.dat->index;
  desc->args[1] = arg1;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg1.dat->index;
  desc->args[2] = arg2;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg2.dat->index;
  desc->args[3] = arg3;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg3.dat->index;
  desc->args[4] = arg4;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg4.dat->index;
  desc->args[5] = arg5;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg5.dat->index;
  desc->args[6] = arg6;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg6.dat->index;
  desc->args[7] = arg7;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg7.dat->index;
  desc->function = ops_par_loop_advec_cell_kernel3_ydir_execute;
  if (block->instance->OPS_diags > 1) {
    ops_timing_realloc(block->instance,67,"advec_cell_kernel3_ydir");
  }
  ops_enqueue_kernel(desc);
}
#endif
