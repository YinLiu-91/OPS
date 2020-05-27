//
// auto-generated by ops.py
//

//user function

// host stub function
#ifndef OPS_LAZY
void ops_par_loop_advec_mom_kernel1_z_nonvector(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4) {
#else
void ops_par_loop_advec_mom_kernel1_z_nonvector_execute(ops_kernel_descriptor *desc) {
  ops_block block = desc->block;
  int dim = desc->dim;
  int *range = desc->range;
  ops_arg arg0 = desc->args[0];
  ops_arg arg1 = desc->args[1];
  ops_arg arg2 = desc->args[2];
  ops_arg arg3 = desc->args[3];
  ops_arg arg4 = desc->args[4];
  #endif

  //Timing
  double __t1,__t2,__c1,__c2;

  ops_arg args[5] = { arg0, arg1, arg2, arg3, arg4};



  #if defined(CHECKPOINTING) && !defined(OPS_LAZY)
  if (!ops_checkpointing_before(args,5,range,137)) return;
  #endif

  if (block->instance->OPS_diags > 1) {
    ops_timing_realloc(block->instance,137,"advec_mom_kernel1_z_nonvector");
    block->instance->OPS_kernels[137].count++;
    ops_timers_core(&__c2,&__t2);
  }

  #ifdef OPS_DEBUG
  ops_register_args(block->instance, args, "advec_mom_kernel1_z_nonvector");
  #endif


  //compute locally allocated range for the sub-block
  int start[3];
  int end[3];
  #if defined(OPS_MPI) && !defined(OPS_LAZY)
  int arg_idx[3];
  #endif
  #if defined(OPS_LAZY) || !defined(OPS_MPI)
  for ( int n=0; n<3; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }
  #else
  if (compute_ranges(args, 5,block, range, start, end, arg_idx) < 0) return;
  #endif


  //initialize global variable with the dimension of dats
  int xdim0_advec_mom_kernel1_z_nonvector = args[0].dat->size[0];
  int ydim0_advec_mom_kernel1_z_nonvector = args[0].dat->size[1];
  int xdim1_advec_mom_kernel1_z_nonvector = args[1].dat->size[0];
  int ydim1_advec_mom_kernel1_z_nonvector = args[1].dat->size[1];
  int xdim2_advec_mom_kernel1_z_nonvector = args[2].dat->size[0];
  int ydim2_advec_mom_kernel1_z_nonvector = args[2].dat->size[1];
  int xdim3_advec_mom_kernel1_z_nonvector = args[3].dat->size[0];
  int ydim3_advec_mom_kernel1_z_nonvector = args[3].dat->size[1];
  int xdim4_advec_mom_kernel1_z_nonvector = args[4].dat->size[0];
  int ydim4_advec_mom_kernel1_z_nonvector = args[4].dat->size[1];

  //set up initial pointers and exchange halos if necessary
  int base0 = args[0].dat->base_offset;
  double * __restrict__ node_flux_p = (double *)(args[0].data + base0);

  int base1 = args[1].dat->base_offset;
  double * __restrict__ node_mass_pre_p = (double *)(args[1].data + base1);

  int base2 = args[2].dat->base_offset;
  double * __restrict__ mom_flux_p = (double *)(args[2].data + base2);

  int base3 = args[3].dat->base_offset;
  double * __restrict__ celldz_p = (double *)(args[3].data + base3);

  int base4 = args[4].dat->base_offset;
  double * __restrict__ vel1_p = (double *)(args[4].data + base4);



  #ifndef OPS_LAZY
  //Halo Exchanges
  ops_H_D_exchanges_host(args, 5);
  ops_halo_exchanges(args,5,range);
  ops_H_D_exchanges_host(args, 5);
  #endif

  if (block->instance->OPS_diags > 1) {
    ops_timers_core(&__c1,&__t1);
    block->instance->OPS_kernels[137].mpi_time += __t1-__t2;
  }

  #pragma omp parallel for collapse(2)
  for ( int n_z=start[2]; n_z<end[2]; n_z++ ){
    for ( int n_y=start[1]; n_y<end[1]; n_y++ ){
      #ifdef __INTEL_COMPILER
      #pragma loop_count(10000)
      #pragma omp simd
      #elif defined(__clang__)
      #pragma clang loop vectorize(assume_safety)
      #elif defined(__GNUC__)
      #pragma GCC ivdep
      #else
      #pragma simd
      #endif
      for ( int n_x=start[0]; n_x<end[0]; n_x++ ){
        const ACC<double> node_flux(xdim0_advec_mom_kernel1_z_nonvector, ydim0_advec_mom_kernel1_z_nonvector, node_flux_p + n_x*1 + n_y * xdim0_advec_mom_kernel1_z_nonvector*1 + n_z * xdim0_advec_mom_kernel1_z_nonvector * ydim0_advec_mom_kernel1_z_nonvector*1);
        const ACC<double> node_mass_pre(xdim1_advec_mom_kernel1_z_nonvector, ydim1_advec_mom_kernel1_z_nonvector, node_mass_pre_p + n_x*1 + n_y * xdim1_advec_mom_kernel1_z_nonvector*1 + n_z * xdim1_advec_mom_kernel1_z_nonvector * ydim1_advec_mom_kernel1_z_nonvector*1);
        ACC<double> mom_flux(xdim2_advec_mom_kernel1_z_nonvector, ydim2_advec_mom_kernel1_z_nonvector, mom_flux_p + n_x*1 + n_y * xdim2_advec_mom_kernel1_z_nonvector*1 + n_z * xdim2_advec_mom_kernel1_z_nonvector * ydim2_advec_mom_kernel1_z_nonvector*1);
        const ACC<double> celldz(xdim3_advec_mom_kernel1_z_nonvector, ydim3_advec_mom_kernel1_z_nonvector, celldz_p + n_x*0 + n_y * xdim3_advec_mom_kernel1_z_nonvector*0 + n_z * xdim3_advec_mom_kernel1_z_nonvector * ydim3_advec_mom_kernel1_z_nonvector*1);
        const ACC<double> vel1(xdim4_advec_mom_kernel1_z_nonvector, ydim4_advec_mom_kernel1_z_nonvector, vel1_p + n_x*1 + n_y * xdim4_advec_mom_kernel1_z_nonvector*1 + n_z * xdim4_advec_mom_kernel1_z_nonvector * ydim4_advec_mom_kernel1_z_nonvector*1);
        

  double sigma, wind, width;
  double vdiffuw, vdiffdw, auw, adw, limiter;
  int upwind, donor, downwind, dif;
  double advec_vel_temp;

  if( (node_flux(0,0,0)) < 0.0) {
    upwind = 2;
    donor = 1;
    downwind = 0;
    dif = donor;
  } else {
    upwind = -1;
    donor = 0;
    downwind = 1;
    dif = upwind;
  }

  sigma = fabs(node_flux(0,0,0))/node_mass_pre(0,0,donor);
  width = celldz(0,0,0);
  vdiffuw = vel1(0,0,donor) - vel1(0,0,upwind);
  vdiffdw = vel1(0,0,downwind) - vel1(0,0,donor);
  limiter = 0.0;
  if(vdiffuw*vdiffdw > 0.0) {
    auw = fabs(vdiffuw);
    adw = fabs(vdiffdw);
    wind = 1.0;
    if(vdiffdw <= 0.0) wind = -1.0;
    limiter=wind*MIN(width*((2.0-sigma)*adw/width+(1.0+sigma)*auw/celldz(0,0,dif))/6.0,MIN(auw,adw));
  }
  advec_vel_temp= vel1(0,0,donor) + (1.0 - sigma) * limiter;
  mom_flux(0,0,0) = advec_vel_temp * node_flux(0,0,0);

      }
    }
  }
  if (block->instance->OPS_diags > 1) {
    ops_timers_core(&__c2,&__t2);
    block->instance->OPS_kernels[137].time += __t2-__t1;
  }
  #ifndef OPS_LAZY
  ops_set_dirtybit_host(args, 5);
  ops_set_halo_dirtybit3(&args[2],range);
  #endif

  if (block->instance->OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&__c1,&__t1);
    block->instance->OPS_kernels[137].mpi_time += __t1-__t2;
    block->instance->OPS_kernels[137].transfer += ops_compute_transfer(dim, start, end, &arg0);
    block->instance->OPS_kernels[137].transfer += ops_compute_transfer(dim, start, end, &arg1);
    block->instance->OPS_kernels[137].transfer += ops_compute_transfer(dim, start, end, &arg2);
    block->instance->OPS_kernels[137].transfer += ops_compute_transfer(dim, start, end, &arg3);
    block->instance->OPS_kernels[137].transfer += ops_compute_transfer(dim, start, end, &arg4);
  }
}


#ifdef OPS_LAZY
void ops_par_loop_advec_mom_kernel1_z_nonvector(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4) {
  ops_kernel_descriptor *desc = (ops_kernel_descriptor *)calloc(1,sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->device = 0;
  desc->index = 137;
  desc->hash = 5381;
  desc->hash = ((desc->hash << 5) + desc->hash) + 137;
  for ( int i=0; i<6; i++ ){
    desc->range[i] = range[i];
    desc->orig_range[i] = range[i];
    desc->hash = ((desc->hash << 5) + desc->hash) + range[i];
  }
  desc->nargs = 5;
  desc->args = (ops_arg *)ops_malloc(5 * sizeof(ops_arg));
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
  desc->function = ops_par_loop_advec_mom_kernel1_z_nonvector_execute;
  if (block->instance->OPS_diags > 1) {
    ops_timing_realloc(block->instance,137,"advec_mom_kernel1_z_nonvector");
  }
  ops_enqueue_kernel(desc);
}
#endif
