//
// auto-generated by ops.py
//
#define OPS_ACC0(x, y)                                                         \
  (n_x * 1 + x + (n_y * 1 + (y)) * xdim0_initialise_chunk_kernel_volume)
#define OPS_ACC1(x, y)                                                         \
  (n_x * 0 + x + (n_y * 1 + (y)) * xdim1_initialise_chunk_kernel_volume)
#define OPS_ACC2(x, y)                                                         \
  (n_x * 1 + x + (n_y * 1 + (y)) * xdim2_initialise_chunk_kernel_volume)
#define OPS_ACC3(x, y)                                                         \
  (n_x * 1 + x + (n_y * 0 + (y)) * xdim3_initialise_chunk_kernel_volume)
#define OPS_ACC4(x, y)                                                         \
  (n_x * 1 + x + (n_y * 1 + (y)) * xdim4_initialise_chunk_kernel_volume)

// user function

// host stub function
#ifndef OPS_LAZY
void ops_par_loop_initialise_chunk_kernel_volume(char const *name,
                                                 ops_block block, int dim,
                                                 int *range, ops_arg arg0,
                                                 ops_arg arg1, ops_arg arg2,
                                                 ops_arg arg3, ops_arg arg4) {
#else
void ops_par_loop_initialise_chunk_kernel_volume_execute(
    ops_kernel_descriptor *desc) {
  ops_block block = desc->block;
  int dim = desc->dim;
  int *range = desc->range;
  ops_arg arg0 = desc->args[0];
  ops_arg arg1 = desc->args[1];
  ops_arg arg2 = desc->args[2];
  ops_arg arg3 = desc->args[3];
  ops_arg arg4 = desc->args[4];
#endif

  // Timing
  double __t1, __t2, __c1, __c2;

  ops_arg args[5] = {arg0, arg1, arg2, arg3, arg4};

#if defined(CHECKPOINTING) && !defined(OPS_LAZY)
  if (!ops_checkpointing_before(args, 5, range, 6))
    return;
#endif

  if (OPS_diags > 1) {
    ops_timing_realloc(6, "initialise_chunk_kernel_volume");
    OPS_kernels[6].count++;
    ops_timers_core(&__c2, &__t2);
  }

#ifdef OPS_DEBUG
  ops_register_args(args, "initialise_chunk_kernel_volume");
#endif

  // compute locally allocated range for the sub-block
  int start[2];
  int end[2];
#ifdef OPS_MPI
  int arg_idx[2];
#endif
#if defined(OPS_LAZY) || !defined(OPS_MPI)
  for (int n = 0; n < 2; n++) {
    start[n] = range[2 * n];
    end[n] = range[2 * n + 1];
  }
#else
  if (compute_ranges(args, 5, block, range, start, end, arg_idx) < 0)
    return;
#endif

  // initialize global variable with the dimension of dats
  int xdim0_initialise_chunk_kernel_volume = args[0].dat->size[0];
  int xdim1_initialise_chunk_kernel_volume = args[1].dat->size[0];
  int xdim2_initialise_chunk_kernel_volume = args[2].dat->size[0];
  int xdim3_initialise_chunk_kernel_volume = args[3].dat->size[0];
  int xdim4_initialise_chunk_kernel_volume = args[4].dat->size[0];

  // set up initial pointers and exchange halos if necessary
  int base0 = args[0].dat->base_offset;
  double *__restrict__ volume = (double *)(args[0].data + base0);

  int base1 = args[1].dat->base_offset;
  const double *__restrict__ celldy = (double *)(args[1].data + base1);

  int base2 = args[2].dat->base_offset;
  double *__restrict__ xarea = (double *)(args[2].data + base2);

  int base3 = args[3].dat->base_offset;
  const double *__restrict__ celldx = (double *)(args[3].data + base3);

  int base4 = args[4].dat->base_offset;
  double *__restrict__ yarea = (double *)(args[4].data + base4);

#ifndef OPS_LAZY
  // Halo Exchanges
  ops_H_D_exchanges_host(args, 5);
  ops_halo_exchanges(args, 5, range);
  ops_H_D_exchanges_host(args, 5);
#endif

  if (OPS_diags > 1) {
    ops_timers_core(&__c1, &__t1);
    OPS_kernels[6].mpi_time += __t1 - __t2;
  }

#pragma omp parallel for
  for (int n_y = start[1]; n_y < end[1]; n_y++) {
#ifdef __INTEL_COMPILER
#pragma loop_count(10000)
#pragma omp simd aligned(volume, celldy, xarea, celldx, yarea)
#else
#pragma simd
#endif
    for (int n_x = start[0]; n_x < end[0]; n_x++) {

      double d_x, d_y;

      d_x = (grid.xmax - grid.xmin) / (double)grid.x_cells;
      d_y = (grid.ymax - grid.ymin) / (double)grid.y_cells;

      volume[OPS_ACC0(0, 0)] = d_x * d_y;
      xarea[OPS_ACC2(0, 0)] = celldy[OPS_ACC1(0, 0)];
      yarea[OPS_ACC4(0, 0)] = celldx[OPS_ACC3(0, 0)];
    }
  }
  if (OPS_diags > 1) {
    ops_timers_core(&__c2, &__t2);
    OPS_kernels[6].time += __t2 - __t1;
  }
#ifndef OPS_LAZY
  ops_set_dirtybit_host(args, 5);
  ops_set_halo_dirtybit3(&args[0], range);
  ops_set_halo_dirtybit3(&args[2], range);
  ops_set_halo_dirtybit3(&args[4], range);
#endif

  if (OPS_diags > 1) {
    // Update kernel record
    ops_timers_core(&__c1, &__t1);
    OPS_kernels[6].mpi_time += __t1 - __t2;
    OPS_kernels[6].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[6].transfer += ops_compute_transfer(dim, start, end, &arg1);
    OPS_kernels[6].transfer += ops_compute_transfer(dim, start, end, &arg2);
    OPS_kernels[6].transfer += ops_compute_transfer(dim, start, end, &arg3);
    OPS_kernels[6].transfer += ops_compute_transfer(dim, start, end, &arg4);
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4

#ifdef OPS_LAZY
void ops_par_loop_initialise_chunk_kernel_volume(char const *name,
                                                 ops_block block, int dim,
                                                 int *range, ops_arg arg0,
                                                 ops_arg arg1, ops_arg arg2,
                                                 ops_arg arg3, ops_arg arg4) {
  ops_kernel_descriptor *desc =
      (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->device = 1;
  desc->index = 6;
  desc->hash = 5381;
  desc->hash = ((desc->hash << 5) + desc->hash) + 6;
  for (int i = 0; i < 4; i++) {
    desc->range[i] = range[i];
    desc->orig_range[i] = range[i];
    desc->hash = ((desc->hash << 5) + desc->hash) + range[i];
  }
  desc->nargs = 5;
  desc->args = (ops_arg *)malloc(5 * sizeof(ops_arg));
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
  desc->function = ops_par_loop_initialise_chunk_kernel_volume_execute;
  if (OPS_diags > 1) {
    ops_timing_realloc(6, "initialise_chunk_kernel_volume");
  }
  ops_enqueue_kernel(desc);
}
#endif
