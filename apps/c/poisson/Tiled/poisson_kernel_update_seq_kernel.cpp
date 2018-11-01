//
// auto-generated by ops.py
//
<<<<<<< HEAD:apps/c/poisson/Tiled/poisson_kernel_update_seq_kernel.cpp
#define OPS_ACC0(x, y)                                                         \
  (n_x * 1 + n_y * xdim0_poisson_kernel_update * 1 + x +                       \
   xdim0_poisson_kernel_update * (y))
#define OPS_ACC1(x, y)                                                         \
  (n_x * 1 + n_y * xdim1_poisson_kernel_update * 1 + x +                       \
   xdim1_poisson_kernel_update * (y))
=======
>>>>>>> 1d8186c... Works on CPU with poisson:apps/c/poisson/MPI_OpenMP/poisson_kernel_update_cpu_kernel.cpp

//user function

// host stub function
<<<<<<< HEAD:apps/c/poisson/Tiled/poisson_kernel_update_seq_kernel.cpp
=======
#ifndef OPS_LAZY
void ops_par_loop_poisson_kernel_update(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1) {
#else
>>>>>>> 1d8186c... Works on CPU with poisson:apps/c/poisson/MPI_OpenMP/poisson_kernel_update_cpu_kernel.cpp
void ops_par_loop_poisson_kernel_update_execute(ops_kernel_descriptor *desc) {
  ops_block block = desc->block;
  int dim = desc->dim;
  int *range = desc->range;
  ops_arg arg0 = desc->args[0];
  ops_arg arg1 = desc->args[1];
<<<<<<< HEAD:apps/c/poisson/Tiled/poisson_kernel_update_seq_kernel.cpp

  // Timing
  double t1, t2, c1, c2;
=======
  #endif

  //Timing
  double __t1,__t2,__c1,__c2;

  ops_arg args[2] = { arg0, arg1};
>>>>>>> 1d8186c... Works on CPU with poisson:apps/c/poisson/MPI_OpenMP/poisson_kernel_update_cpu_kernel.cpp


<<<<<<< HEAD:apps/c/poisson/Tiled/poisson_kernel_update_seq_kernel.cpp
#ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args, 2, range, 1))
    return;
#endif

  if (OPS_diags > 1) {
    OPS_kernels[1].count++;
    ops_timers_core(&c2, &t2);
  }

  // compute locally allocated range for the sub-block
  int start[2];
  int end[2];

  for (int n = 0; n < 2; n++) {
    start[n] = range[2 * n];
    end[n] = range[2 * n + 1];
  }

#ifdef OPS_DEBUG
  ops_register_args(args, "poisson_kernel_update");
#endif
=======

  #if defined(CHECKPOINTING) && !defined(OPS_LAZY)
  if (!ops_checkpointing_before(args,2,range,1)) return;
  #endif

  if (OPS_diags > 1) {
    ops_timing_realloc(1,"poisson_kernel_update");
    OPS_kernels[1].count++;
    ops_timers_core(&__c2,&__t2);
  }

  #ifdef OPS_DEBUG
  ops_register_args(args, "poisson_kernel_update");
  #endif


  //compute locally allocated range for the sub-block
  int start[2];
  int end[2];
  #ifdef OPS_MPI
  int arg_idx[2];
  #endif
  #if defined(OPS_LAZY) || !defined(OPS_MPI)
  for ( int n=0; n<2; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }
  #else
  if (compute_ranges(args, 2,block, range, start, end, arg_idx) < 0) return;
  #endif


  //initialize global variable with the dimension of dats
  int xdim0_poisson_kernel_update = args[0].dat->size[0];
  int xdim1_poisson_kernel_update = args[1].dat->size[0];
>>>>>>> 1d8186c... Works on CPU with poisson:apps/c/poisson/MPI_OpenMP/poisson_kernel_update_cpu_kernel.cpp

  //set up initial pointers and exchange halos if necessary
  int base0 = args[0].dat->base_offset;
  double * __restrict__ u2_p = (double *)(args[0].data + base0);

  int base1 = args[1].dat->base_offset;
  double * __restrict__ u_p = (double *)(args[1].data + base1);

<<<<<<< HEAD:apps/c/poisson/Tiled/poisson_kernel_update_seq_kernel.cpp
  // initialize global variable with the dimension of dats
  int xdim0_poisson_kernel_update = args[0].dat->size[0];
  int xdim1_poisson_kernel_update = args[1].dat->size[0];

  if (OPS_diags > 1) {
    ops_timers_core(&c1, &t1);
    OPS_kernels[1].mpi_time += t1 - t2;
  }

#pragma omp parallel for
  for (int n_y = start[1]; n_y < end[1]; n_y++) {
#ifdef intel
#pragma loop_count(10000)
#pragma omp simd aligned(u2, u)
#else
#pragma simd
#endif
    for (int n_x = start[0]; n_x < end[0]; n_x++) {
=======


  #ifndef OPS_LAZY
  //Halo Exchanges
  ops_H_D_exchanges_host(args, 2);
  ops_halo_exchanges(args,2,range);
  ops_H_D_exchanges_host(args, 2);
  #endif

  if (OPS_diags > 1) {
    ops_timers_core(&__c1,&__t1);
    OPS_kernels[1].mpi_time += __t1-__t2;
  }

  #pragma omp parallel for
  for ( int n_y=start[1]; n_y<end[1]; n_y++ ){
    #ifdef __INTEL_COMPILER
    #pragma loop_count(10000)
    #pragma omp simd
    #else
    #pragma simd
    #endif
    for ( int n_x=start[0]; n_x<end[0]; n_x++ ){
      const ACC<double> u2(xdim0_poisson_kernel_update, u2_p + n_x + n_y * xdim0_poisson_kernel_update);
      ACC<double> u(xdim1_poisson_kernel_update, u_p + n_x + n_y * xdim1_poisson_kernel_update);
      
  u(0,0) = u2(0,0);
>>>>>>> 1d8186c... Works on CPU with poisson:apps/c/poisson/MPI_OpenMP/poisson_kernel_update_cpu_kernel.cpp

    }
  }
  if (OPS_diags > 1) {
<<<<<<< HEAD:apps/c/poisson/Tiled/poisson_kernel_update_seq_kernel.cpp
    ops_timers_core(&c2, &t2);
    OPS_kernels[1].time += t2 - t1;
  }

  if (OPS_diags > 1) {
    // Update kernel record
    ops_timers_core(&c1, &t1);
    OPS_kernels[1].mpi_time += t1 - t2;
=======
    ops_timers_core(&__c2,&__t2);
    OPS_kernels[1].time += __t2-__t1;
  }
  #ifndef OPS_LAZY
  ops_set_dirtybit_host(args, 2);
  ops_set_halo_dirtybit3(&args[1],range);
  #endif

  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&__c1,&__t1);
    OPS_kernels[1].mpi_time += __t1-__t2;
>>>>>>> 1d8186c... Works on CPU with poisson:apps/c/poisson/MPI_OpenMP/poisson_kernel_update_cpu_kernel.cpp
    OPS_kernels[1].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[1].transfer += ops_compute_transfer(dim, start, end, &arg1);
  }
}
#undef OPS_ACC0
#undef OPS_ACC1

<<<<<<< HEAD:apps/c/poisson/Tiled/poisson_kernel_update_seq_kernel.cpp
void ops_par_loop_poisson_kernel_update(char const *name, ops_block block,
                                        int dim, int *range, ops_arg arg0,
                                        ops_arg arg1) {
  ops_kernel_descriptor *desc =
      (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
=======

#ifdef OPS_LAZY
void ops_par_loop_poisson_kernel_update(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1) {
  ops_kernel_descriptor *desc = (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
>>>>>>> 1d8186c... Works on CPU with poisson:apps/c/poisson/MPI_OpenMP/poisson_kernel_update_cpu_kernel.cpp
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->device = 1;
  desc->index = 1;
  desc->hash = 5381;
  desc->hash = ((desc->hash << 5) + desc->hash) + 1;
  for ( int i=0; i<4; i++ ){
    desc->range[i] = range[i];
    desc->orig_range[i] = range[i];
    desc->hash = ((desc->hash << 5) + desc->hash) + range[i];
  }
  desc->nargs = 2;
  desc->args = (ops_arg*)malloc(2*sizeof(ops_arg));
  desc->args[0] = arg0;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg0.dat->index;
  desc->args[1] = arg1;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg1.dat->index;
  desc->function = ops_par_loop_poisson_kernel_update_execute;
  if (OPS_diags > 1) {
    ops_timing_realloc(1,"poisson_kernel_update");
  }
  ops_enqueue_kernel(desc);
}
