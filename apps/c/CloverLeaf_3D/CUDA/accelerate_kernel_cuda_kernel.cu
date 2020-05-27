//
// auto-generated by ops.py
//
__constant__ int dims_accelerate_kernel [14][2];
static int dims_accelerate_kernel_h [14][2] = {0};

//user function
__device__

void accelerate_kernel_gpu(const ACC<double> &density0,
  const ACC<double> &volume,
  ACC<double> &stepbymass,
  const ACC<double> &xvel0,
  ACC<double> &xvel1,
  const ACC<double> &xarea,
  const ACC<double> &pressure,
  const ACC<double> &yvel0,
  ACC<double> &yvel1,
  const ACC<double> &yarea,
  const ACC<double> &viscosity,
  const ACC<double> &zvel0,
  ACC<double> &zvel1,
  const ACC<double> &zarea) {

  double nodal_mass = 0.0;
  nodal_mass =(density0(-1,-1, 0) * volume(-1,-1, 0) +
               density0( 0,-1, 0) * volume( 0,-1, 0) +
               density0( 0, 0, 0) * volume( 0, 0, 0) +
               density0(-1, 0, 0) * volume(-1, 0, 0) +
               density0(-1,-1,-1) * volume(-1,-1,-1) +
               density0( 0,-1,-1) * volume( 0,-1,-1) +
               density0( 0, 0,-1) * volume( 0, 0,-1) +
               density0(-1, 0,-1) * volume(-1, 0,-1)) * 0.125;

  stepbymass(0,0,0) = 0.25*dt / nodal_mass;

  xvel1(0,0,0) = xvel0(0,0,0) - stepbymass(0,0,0) *
            ( xarea(0,0,0)  * ( pressure(0,0,0) - pressure(-1,0,0) ) +
              xarea(0,-1,0) * ( pressure(0,-1,0) - pressure(-1,-1,0) ) +
              xarea(0,0,-1) * ( pressure(0,0,-1) - pressure(-1,0,-1) ) +
              xarea(0,-1,-1) * ( pressure(0,-1,-1) - pressure(-1,-1,-1) ) );

  yvel1(0,0,0) = yvel0(0,0,0) - stepbymass(0,0,0) *
            ( yarea(0,0,0)  * ( pressure(0,0,0) - pressure(0,-1,0) ) +
              yarea(-1,0,0) * ( pressure(-1,0,0) - pressure(-1,-1,0) ) +
              yarea(0,0,-1) * ( pressure(0,0,-1) - pressure(0,-1,-1) ) +
              yarea(-1,0,-1)* ( pressure(-1,0,-1) - pressure(-1,-1,-1) ) );

  zvel1(0,0,0) = zvel0(0,0,0) - stepbymass(0,0,0) *
            ( zarea(0,0,0)  * ( pressure(0,0,0) - pressure(0,0,-1) ) +
              zarea(0,-1,0) * ( pressure(0,-1,0) - pressure(0,-1,-1) ) +
              zarea(-1,0,0) * ( pressure(-1,0,0) - pressure(-1,0,-1) ) +
              zarea(-1,-1,0)* ( pressure(-1,-1,0) - pressure(-1,-1,-1) ) );

  xvel1(0,0,0) = xvel1(0,0,0) - stepbymass(0,0,0) *
            ( xarea(0,0,0)  * ( viscosity(0,0,0) - viscosity(-1,0,0) ) +
              xarea(0,-1,0) * ( viscosity(0,-1,0) - viscosity(-1,-1,0) ) +
              xarea(0,0,-1) * ( viscosity(0,0,-1) - viscosity(-1,0,-1) ) +
              xarea(0,-1,-1)* ( viscosity(0,-1,-1) - viscosity(-1,-1,-1) ) );

  yvel1(0,0,0) = yvel1(0,0,0) - stepbymass(0,0,0) *
            ( yarea(0,0,0)  * ( viscosity(0,0,0)  - viscosity(0,-1,0) ) +
              yarea(-1,0,0) * ( viscosity(-1,0,0) - viscosity(-1,-1,0) ) +
              yarea(0,0,-1) * ( viscosity(0,0,-1) - viscosity(0,-1,-1) ) +
              yarea(-1,0,-1)* ( viscosity(-1,0,-1)- viscosity(-1,-1,-1) ) );

  zvel1(0,0,0) = zvel1(0,0,0) - stepbymass(0,0,0) *
            ( zarea(0,0,0)  * ( viscosity(0,0,0)  - viscosity(0,0,-1) ) +
              zarea(0,-1,0) * ( viscosity(0,-1,0) - viscosity(0,-1,-1) ) +
              zarea(-1,0,0) * ( viscosity(-1,0,0) - viscosity(-1,0,-1) ) +
              zarea(-1,-1,0)* ( viscosity(-1,-1,0)- viscosity(-1,-1,-1) ) );

}



__global__ void ops_accelerate_kernel(
double* __restrict arg0,
double* __restrict arg1,
double* __restrict arg2,
double* __restrict arg3,
double* __restrict arg4,
double* __restrict arg5,
double* __restrict arg6,
double* __restrict arg7,
double* __restrict arg8,
double* __restrict arg9,
double* __restrict arg10,
double* __restrict arg11,
double* __restrict arg12,
double* __restrict arg13,
int size0,
int size1,
int size2 ){


  int idx_z = blockDim.z * blockIdx.z + threadIdx.z;
  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1*1 + idx_y * 1*1 * dims_accelerate_kernel[0][0] + idx_z * 1*1 * dims_accelerate_kernel[0][0] * dims_accelerate_kernel[0][1];
  arg1 += idx_x * 1*1 + idx_y * 1*1 * dims_accelerate_kernel[1][0] + idx_z * 1*1 * dims_accelerate_kernel[1][0] * dims_accelerate_kernel[1][1];
  arg2 += idx_x * 1*1 + idx_y * 1*1 * dims_accelerate_kernel[2][0] + idx_z * 1*1 * dims_accelerate_kernel[2][0] * dims_accelerate_kernel[2][1];
  arg3 += idx_x * 1*1 + idx_y * 1*1 * dims_accelerate_kernel[3][0] + idx_z * 1*1 * dims_accelerate_kernel[3][0] * dims_accelerate_kernel[3][1];
  arg4 += idx_x * 1*1 + idx_y * 1*1 * dims_accelerate_kernel[4][0] + idx_z * 1*1 * dims_accelerate_kernel[4][0] * dims_accelerate_kernel[4][1];
  arg5 += idx_x * 1*1 + idx_y * 1*1 * dims_accelerate_kernel[5][0] + idx_z * 1*1 * dims_accelerate_kernel[5][0] * dims_accelerate_kernel[5][1];
  arg6 += idx_x * 1*1 + idx_y * 1*1 * dims_accelerate_kernel[6][0] + idx_z * 1*1 * dims_accelerate_kernel[6][0] * dims_accelerate_kernel[6][1];
  arg7 += idx_x * 1*1 + idx_y * 1*1 * dims_accelerate_kernel[7][0] + idx_z * 1*1 * dims_accelerate_kernel[7][0] * dims_accelerate_kernel[7][1];
  arg8 += idx_x * 1*1 + idx_y * 1*1 * dims_accelerate_kernel[8][0] + idx_z * 1*1 * dims_accelerate_kernel[8][0] * dims_accelerate_kernel[8][1];
  arg9 += idx_x * 1*1 + idx_y * 1*1 * dims_accelerate_kernel[9][0] + idx_z * 1*1 * dims_accelerate_kernel[9][0] * dims_accelerate_kernel[9][1];
  arg10 += idx_x * 1*1 + idx_y * 1*1 * dims_accelerate_kernel[10][0] + idx_z * 1*1 * dims_accelerate_kernel[10][0] * dims_accelerate_kernel[10][1];
  arg11 += idx_x * 1*1 + idx_y * 1*1 * dims_accelerate_kernel[11][0] + idx_z * 1*1 * dims_accelerate_kernel[11][0] * dims_accelerate_kernel[11][1];
  arg12 += idx_x * 1*1 + idx_y * 1*1 * dims_accelerate_kernel[12][0] + idx_z * 1*1 * dims_accelerate_kernel[12][0] * dims_accelerate_kernel[12][1];
  arg13 += idx_x * 1*1 + idx_y * 1*1 * dims_accelerate_kernel[13][0] + idx_z * 1*1 * dims_accelerate_kernel[13][0] * dims_accelerate_kernel[13][1];

  if (idx_x < size0 && idx_y < size1 && idx_z < size2) {
    const ACC<double> argp0(dims_accelerate_kernel[0][0], dims_accelerate_kernel[0][1], arg0);
    const ACC<double> argp1(dims_accelerate_kernel[1][0], dims_accelerate_kernel[1][1], arg1);
    ACC<double> argp2(dims_accelerate_kernel[2][0], dims_accelerate_kernel[2][1], arg2);
    const ACC<double> argp3(dims_accelerate_kernel[3][0], dims_accelerate_kernel[3][1], arg3);
    ACC<double> argp4(dims_accelerate_kernel[4][0], dims_accelerate_kernel[4][1], arg4);
    const ACC<double> argp5(dims_accelerate_kernel[5][0], dims_accelerate_kernel[5][1], arg5);
    const ACC<double> argp6(dims_accelerate_kernel[6][0], dims_accelerate_kernel[6][1], arg6);
    const ACC<double> argp7(dims_accelerate_kernel[7][0], dims_accelerate_kernel[7][1], arg7);
    ACC<double> argp8(dims_accelerate_kernel[8][0], dims_accelerate_kernel[8][1], arg8);
    const ACC<double> argp9(dims_accelerate_kernel[9][0], dims_accelerate_kernel[9][1], arg9);
    const ACC<double> argp10(dims_accelerate_kernel[10][0], dims_accelerate_kernel[10][1], arg10);
    const ACC<double> argp11(dims_accelerate_kernel[11][0], dims_accelerate_kernel[11][1], arg11);
    ACC<double> argp12(dims_accelerate_kernel[12][0], dims_accelerate_kernel[12][1], arg12);
    const ACC<double> argp13(dims_accelerate_kernel[13][0], dims_accelerate_kernel[13][1], arg13);
    accelerate_kernel_gpu(argp0, argp1, argp2, argp3,
                   argp4, argp5, argp6, argp7, argp8,
                   argp9, argp10, argp11, argp12, argp13);
  }

}

// host stub function
#ifndef OPS_LAZY
void ops_par_loop_accelerate_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5, ops_arg arg6, ops_arg arg7, ops_arg arg8,
 ops_arg arg9, ops_arg arg10, ops_arg arg11, ops_arg arg12, ops_arg arg13) {
#else
void ops_par_loop_accelerate_kernel_execute(ops_kernel_descriptor *desc) {
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
  ops_arg arg8 = desc->args[8];
  ops_arg arg9 = desc->args[9];
  ops_arg arg10 = desc->args[10];
  ops_arg arg11 = desc->args[11];
  ops_arg arg12 = desc->args[12];
  ops_arg arg13 = desc->args[13];
  #endif

  //Timing
  double t1,t2,c1,c2;

  ops_arg args[14] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13};


  #if CHECKPOINTING && !OPS_LAZY
  if (!ops_checkpointing_before(args,14,range,105)) return;
  #endif

  if (block->instance->OPS_diags > 1) {
    ops_timing_realloc(block->instance,105,"accelerate_kernel");
    block->instance->OPS_kernels[105].count++;
    ops_timers_core(&c1,&t1);
  }

  //compute locally allocated range for the sub-block
  int start[3];
  int end[3];
  #if OPS_MPI && !OPS_LAZY
  sub_block_list sb = OPS_sub_block_list[block->index];
  #endif //OPS_MPI

  #ifdef OPS_MPI
  int arg_idx[3];
  #endif
  #if defined(OPS_LAZY) || !defined(OPS_MPI)
  for ( int n=0; n<3; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }
  #else
  if (compute_ranges(args, 14,block, range, start, end, arg_idx) < 0) return;
  #endif

  int xdim0 = args[0].dat->size[0];
  int ydim0 = args[0].dat->size[1];
  int xdim1 = args[1].dat->size[0];
  int ydim1 = args[1].dat->size[1];
  int xdim2 = args[2].dat->size[0];
  int ydim2 = args[2].dat->size[1];
  int xdim3 = args[3].dat->size[0];
  int ydim3 = args[3].dat->size[1];
  int xdim4 = args[4].dat->size[0];
  int ydim4 = args[4].dat->size[1];
  int xdim5 = args[5].dat->size[0];
  int ydim5 = args[5].dat->size[1];
  int xdim6 = args[6].dat->size[0];
  int ydim6 = args[6].dat->size[1];
  int xdim7 = args[7].dat->size[0];
  int ydim7 = args[7].dat->size[1];
  int xdim8 = args[8].dat->size[0];
  int ydim8 = args[8].dat->size[1];
  int xdim9 = args[9].dat->size[0];
  int ydim9 = args[9].dat->size[1];
  int xdim10 = args[10].dat->size[0];
  int ydim10 = args[10].dat->size[1];
  int xdim11 = args[11].dat->size[0];
  int ydim11 = args[11].dat->size[1];
  int xdim12 = args[12].dat->size[0];
  int ydim12 = args[12].dat->size[1];
  int xdim13 = args[13].dat->size[0];
  int ydim13 = args[13].dat->size[1];

  if (xdim0 != dims_accelerate_kernel_h[0][0] || ydim0 != dims_accelerate_kernel_h[0][1] || xdim1 != dims_accelerate_kernel_h[1][0] || ydim1 != dims_accelerate_kernel_h[1][1] || xdim2 != dims_accelerate_kernel_h[2][0] || ydim2 != dims_accelerate_kernel_h[2][1] || xdim3 != dims_accelerate_kernel_h[3][0] || ydim3 != dims_accelerate_kernel_h[3][1] || xdim4 != dims_accelerate_kernel_h[4][0] || ydim4 != dims_accelerate_kernel_h[4][1] || xdim5 != dims_accelerate_kernel_h[5][0] || ydim5 != dims_accelerate_kernel_h[5][1] || xdim6 != dims_accelerate_kernel_h[6][0] || ydim6 != dims_accelerate_kernel_h[6][1] || xdim7 != dims_accelerate_kernel_h[7][0] || ydim7 != dims_accelerate_kernel_h[7][1] || xdim8 != dims_accelerate_kernel_h[8][0] || ydim8 != dims_accelerate_kernel_h[8][1] || xdim9 != dims_accelerate_kernel_h[9][0] || ydim9 != dims_accelerate_kernel_h[9][1] || xdim10 != dims_accelerate_kernel_h[10][0] || ydim10 != dims_accelerate_kernel_h[10][1] || xdim11 != dims_accelerate_kernel_h[11][0] || ydim11 != dims_accelerate_kernel_h[11][1] || xdim12 != dims_accelerate_kernel_h[12][0] || ydim12 != dims_accelerate_kernel_h[12][1] || xdim13 != dims_accelerate_kernel_h[13][0] || ydim13 != dims_accelerate_kernel_h[13][1]) {
    dims_accelerate_kernel_h[0][0] = xdim0;
    dims_accelerate_kernel_h[0][1] = ydim0;
    dims_accelerate_kernel_h[1][0] = xdim1;
    dims_accelerate_kernel_h[1][1] = ydim1;
    dims_accelerate_kernel_h[2][0] = xdim2;
    dims_accelerate_kernel_h[2][1] = ydim2;
    dims_accelerate_kernel_h[3][0] = xdim3;
    dims_accelerate_kernel_h[3][1] = ydim3;
    dims_accelerate_kernel_h[4][0] = xdim4;
    dims_accelerate_kernel_h[4][1] = ydim4;
    dims_accelerate_kernel_h[5][0] = xdim5;
    dims_accelerate_kernel_h[5][1] = ydim5;
    dims_accelerate_kernel_h[6][0] = xdim6;
    dims_accelerate_kernel_h[6][1] = ydim6;
    dims_accelerate_kernel_h[7][0] = xdim7;
    dims_accelerate_kernel_h[7][1] = ydim7;
    dims_accelerate_kernel_h[8][0] = xdim8;
    dims_accelerate_kernel_h[8][1] = ydim8;
    dims_accelerate_kernel_h[9][0] = xdim9;
    dims_accelerate_kernel_h[9][1] = ydim9;
    dims_accelerate_kernel_h[10][0] = xdim10;
    dims_accelerate_kernel_h[10][1] = ydim10;
    dims_accelerate_kernel_h[11][0] = xdim11;
    dims_accelerate_kernel_h[11][1] = ydim11;
    dims_accelerate_kernel_h[12][0] = xdim12;
    dims_accelerate_kernel_h[12][1] = ydim12;
    dims_accelerate_kernel_h[13][0] = xdim13;
    dims_accelerate_kernel_h[13][1] = ydim13;
    cutilSafeCall(block->instance->ostream(), cudaMemcpyToSymbol( dims_accelerate_kernel, dims_accelerate_kernel_h, sizeof(dims_accelerate_kernel)));
  }



  int x_size = MAX(0,end[0]-start[0]);
  int y_size = MAX(0,end[1]-start[1]);
  int z_size = MAX(0,end[2]-start[2]);

  dim3 grid( (x_size-1)/block->instance->OPS_block_size_x+ 1, (y_size-1)/block->instance->OPS_block_size_y + 1, (z_size-1)/block->instance->OPS_block_size_z +1);
  dim3 tblock(block->instance->OPS_block_size_x,block->instance->OPS_block_size_y,block->instance->OPS_block_size_z);



  int dat0 = (block->instance->OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size);
  int dat1 = (block->instance->OPS_soa ? args[1].dat->type_size : args[1].dat->elem_size);
  int dat2 = (block->instance->OPS_soa ? args[2].dat->type_size : args[2].dat->elem_size);
  int dat3 = (block->instance->OPS_soa ? args[3].dat->type_size : args[3].dat->elem_size);
  int dat4 = (block->instance->OPS_soa ? args[4].dat->type_size : args[4].dat->elem_size);
  int dat5 = (block->instance->OPS_soa ? args[5].dat->type_size : args[5].dat->elem_size);
  int dat6 = (block->instance->OPS_soa ? args[6].dat->type_size : args[6].dat->elem_size);
  int dat7 = (block->instance->OPS_soa ? args[7].dat->type_size : args[7].dat->elem_size);
  int dat8 = (block->instance->OPS_soa ? args[8].dat->type_size : args[8].dat->elem_size);
  int dat9 = (block->instance->OPS_soa ? args[9].dat->type_size : args[9].dat->elem_size);
  int dat10 = (block->instance->OPS_soa ? args[10].dat->type_size : args[10].dat->elem_size);
  int dat11 = (block->instance->OPS_soa ? args[11].dat->type_size : args[11].dat->elem_size);
  int dat12 = (block->instance->OPS_soa ? args[12].dat->type_size : args[12].dat->elem_size);
  int dat13 = (block->instance->OPS_soa ? args[13].dat->type_size : args[13].dat->elem_size);

  char *p_a[14];

  //set up initial pointers
  int base0 = args[0].dat->base_offset + 
           dat0 * 1 * (start[0] * args[0].stencil->stride[0]);
  base0 = base0+ dat0 *
    args[0].dat->size[0] *
    (start[1] * args[0].stencil->stride[1]);
  base0 = base0+ dat0 *
    args[0].dat->size[0] *
    args[0].dat->size[1] *
    (start[2] * args[0].stencil->stride[2]);
  p_a[0] = (char *)args[0].data_d + base0;

  int base1 = args[1].dat->base_offset + 
           dat1 * 1 * (start[0] * args[1].stencil->stride[0]);
  base1 = base1+ dat1 *
    args[1].dat->size[0] *
    (start[1] * args[1].stencil->stride[1]);
  base1 = base1+ dat1 *
    args[1].dat->size[0] *
    args[1].dat->size[1] *
    (start[2] * args[1].stencil->stride[2]);
  p_a[1] = (char *)args[1].data_d + base1;

  int base2 = args[2].dat->base_offset + 
           dat2 * 1 * (start[0] * args[2].stencil->stride[0]);
  base2 = base2+ dat2 *
    args[2].dat->size[0] *
    (start[1] * args[2].stencil->stride[1]);
  base2 = base2+ dat2 *
    args[2].dat->size[0] *
    args[2].dat->size[1] *
    (start[2] * args[2].stencil->stride[2]);
  p_a[2] = (char *)args[2].data_d + base2;

  int base3 = args[3].dat->base_offset + 
           dat3 * 1 * (start[0] * args[3].stencil->stride[0]);
  base3 = base3+ dat3 *
    args[3].dat->size[0] *
    (start[1] * args[3].stencil->stride[1]);
  base3 = base3+ dat3 *
    args[3].dat->size[0] *
    args[3].dat->size[1] *
    (start[2] * args[3].stencil->stride[2]);
  p_a[3] = (char *)args[3].data_d + base3;

  int base4 = args[4].dat->base_offset + 
           dat4 * 1 * (start[0] * args[4].stencil->stride[0]);
  base4 = base4+ dat4 *
    args[4].dat->size[0] *
    (start[1] * args[4].stencil->stride[1]);
  base4 = base4+ dat4 *
    args[4].dat->size[0] *
    args[4].dat->size[1] *
    (start[2] * args[4].stencil->stride[2]);
  p_a[4] = (char *)args[4].data_d + base4;

  int base5 = args[5].dat->base_offset + 
           dat5 * 1 * (start[0] * args[5].stencil->stride[0]);
  base5 = base5+ dat5 *
    args[5].dat->size[0] *
    (start[1] * args[5].stencil->stride[1]);
  base5 = base5+ dat5 *
    args[5].dat->size[0] *
    args[5].dat->size[1] *
    (start[2] * args[5].stencil->stride[2]);
  p_a[5] = (char *)args[5].data_d + base5;

  int base6 = args[6].dat->base_offset + 
           dat6 * 1 * (start[0] * args[6].stencil->stride[0]);
  base6 = base6+ dat6 *
    args[6].dat->size[0] *
    (start[1] * args[6].stencil->stride[1]);
  base6 = base6+ dat6 *
    args[6].dat->size[0] *
    args[6].dat->size[1] *
    (start[2] * args[6].stencil->stride[2]);
  p_a[6] = (char *)args[6].data_d + base6;

  int base7 = args[7].dat->base_offset + 
           dat7 * 1 * (start[0] * args[7].stencil->stride[0]);
  base7 = base7+ dat7 *
    args[7].dat->size[0] *
    (start[1] * args[7].stencil->stride[1]);
  base7 = base7+ dat7 *
    args[7].dat->size[0] *
    args[7].dat->size[1] *
    (start[2] * args[7].stencil->stride[2]);
  p_a[7] = (char *)args[7].data_d + base7;

  int base8 = args[8].dat->base_offset + 
           dat8 * 1 * (start[0] * args[8].stencil->stride[0]);
  base8 = base8+ dat8 *
    args[8].dat->size[0] *
    (start[1] * args[8].stencil->stride[1]);
  base8 = base8+ dat8 *
    args[8].dat->size[0] *
    args[8].dat->size[1] *
    (start[2] * args[8].stencil->stride[2]);
  p_a[8] = (char *)args[8].data_d + base8;

  int base9 = args[9].dat->base_offset + 
           dat9 * 1 * (start[0] * args[9].stencil->stride[0]);
  base9 = base9+ dat9 *
    args[9].dat->size[0] *
    (start[1] * args[9].stencil->stride[1]);
  base9 = base9+ dat9 *
    args[9].dat->size[0] *
    args[9].dat->size[1] *
    (start[2] * args[9].stencil->stride[2]);
  p_a[9] = (char *)args[9].data_d + base9;

  int base10 = args[10].dat->base_offset + 
           dat10 * 1 * (start[0] * args[10].stencil->stride[0]);
  base10 = base10+ dat10 *
    args[10].dat->size[0] *
    (start[1] * args[10].stencil->stride[1]);
  base10 = base10+ dat10 *
    args[10].dat->size[0] *
    args[10].dat->size[1] *
    (start[2] * args[10].stencil->stride[2]);
  p_a[10] = (char *)args[10].data_d + base10;

  int base11 = args[11].dat->base_offset + 
           dat11 * 1 * (start[0] * args[11].stencil->stride[0]);
  base11 = base11+ dat11 *
    args[11].dat->size[0] *
    (start[1] * args[11].stencil->stride[1]);
  base11 = base11+ dat11 *
    args[11].dat->size[0] *
    args[11].dat->size[1] *
    (start[2] * args[11].stencil->stride[2]);
  p_a[11] = (char *)args[11].data_d + base11;

  int base12 = args[12].dat->base_offset + 
           dat12 * 1 * (start[0] * args[12].stencil->stride[0]);
  base12 = base12+ dat12 *
    args[12].dat->size[0] *
    (start[1] * args[12].stencil->stride[1]);
  base12 = base12+ dat12 *
    args[12].dat->size[0] *
    args[12].dat->size[1] *
    (start[2] * args[12].stencil->stride[2]);
  p_a[12] = (char *)args[12].data_d + base12;

  int base13 = args[13].dat->base_offset + 
           dat13 * 1 * (start[0] * args[13].stencil->stride[0]);
  base13 = base13+ dat13 *
    args[13].dat->size[0] *
    (start[1] * args[13].stencil->stride[1]);
  base13 = base13+ dat13 *
    args[13].dat->size[0] *
    args[13].dat->size[1] *
    (start[2] * args[13].stencil->stride[2]);
  p_a[13] = (char *)args[13].data_d + base13;


  #ifndef OPS_LAZY
  ops_H_D_exchanges_device(args, 14);
  ops_halo_exchanges(args,14,range);
  #endif

  if (block->instance->OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    block->instance->OPS_kernels[105].mpi_time += t2-t1;
  }


  //call kernel wrapper function, passing in pointers to data
  if (x_size > 0 && y_size > 0 && z_size > 0)
    ops_accelerate_kernel<<<grid, tblock >>> (  (double *)p_a[0], (double *)p_a[1],
         (double *)p_a[2], (double *)p_a[3],
         (double *)p_a[4], (double *)p_a[5],
         (double *)p_a[6], (double *)p_a[7],
         (double *)p_a[8], (double *)p_a[9],
         (double *)p_a[10], (double *)p_a[11],
         (double *)p_a[12], (double *)p_a[13],x_size, y_size, z_size);

  cutilSafeCall(block->instance->ostream(), cudaGetLastError());

  if (block->instance->OPS_diags>1) {
    cutilSafeCall(block->instance->ostream(), cudaDeviceSynchronize());
    ops_timers_core(&c1,&t1);
    block->instance->OPS_kernels[105].time += t1-t2;
  }

  #ifndef OPS_LAZY
  ops_set_dirtybit_device(args, 14);
  ops_set_halo_dirtybit3(&args[2],range);
  ops_set_halo_dirtybit3(&args[4],range);
  ops_set_halo_dirtybit3(&args[8],range);
  ops_set_halo_dirtybit3(&args[12],range);
  #endif

  if (block->instance->OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c2,&t2);
    block->instance->OPS_kernels[105].mpi_time += t2-t1;
    block->instance->OPS_kernels[105].transfer += ops_compute_transfer(dim, start, end, &arg0);
    block->instance->OPS_kernels[105].transfer += ops_compute_transfer(dim, start, end, &arg1);
    block->instance->OPS_kernels[105].transfer += ops_compute_transfer(dim, start, end, &arg2);
    block->instance->OPS_kernels[105].transfer += ops_compute_transfer(dim, start, end, &arg3);
    block->instance->OPS_kernels[105].transfer += ops_compute_transfer(dim, start, end, &arg4);
    block->instance->OPS_kernels[105].transfer += ops_compute_transfer(dim, start, end, &arg5);
    block->instance->OPS_kernels[105].transfer += ops_compute_transfer(dim, start, end, &arg6);
    block->instance->OPS_kernels[105].transfer += ops_compute_transfer(dim, start, end, &arg7);
    block->instance->OPS_kernels[105].transfer += ops_compute_transfer(dim, start, end, &arg8);
    block->instance->OPS_kernels[105].transfer += ops_compute_transfer(dim, start, end, &arg9);
    block->instance->OPS_kernels[105].transfer += ops_compute_transfer(dim, start, end, &arg10);
    block->instance->OPS_kernels[105].transfer += ops_compute_transfer(dim, start, end, &arg11);
    block->instance->OPS_kernels[105].transfer += ops_compute_transfer(dim, start, end, &arg12);
    block->instance->OPS_kernels[105].transfer += ops_compute_transfer(dim, start, end, &arg13);
  }
}

#ifdef OPS_LAZY
void ops_par_loop_accelerate_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3, ops_arg arg4, ops_arg arg5, ops_arg arg6, ops_arg arg7, ops_arg arg8, ops_arg arg9, ops_arg arg10, ops_arg arg11, ops_arg arg12, ops_arg arg13) {
  ops_kernel_descriptor *desc = (ops_kernel_descriptor *)calloc(1,sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->device = 1;
  desc->index = 105;
  desc->hash = 5381;
  desc->hash = ((desc->hash << 5) + desc->hash) + 105;
  for ( int i=0; i<6; i++ ){
    desc->range[i] = range[i];
    desc->orig_range[i] = range[i];
    desc->hash = ((desc->hash << 5) + desc->hash) + range[i];
  }
  desc->nargs = 14;
  desc->args = (ops_arg*)ops_malloc(14*sizeof(ops_arg));
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
  desc->args[8] = arg8;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg8.dat->index;
  desc->args[9] = arg9;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg9.dat->index;
  desc->args[10] = arg10;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg10.dat->index;
  desc->args[11] = arg11;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg11.dat->index;
  desc->args[12] = arg12;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg12.dat->index;
  desc->args[13] = arg13;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg13.dat->index;
  desc->function = ops_par_loop_accelerate_kernel_execute;
  if (block->instance->OPS_diags > 1) {
    ops_timing_realloc(block->instance,105,"accelerate_kernel");
  }
  ops_enqueue_kernel(desc);
}
#endif
