//
// auto-generated by ops.py
//
#define OPS_ACC0(x,y,z) (n_x*1+n_y*xdim0_advec_mom_kernel_mass_flux_y*1+n_z*xdim0_advec_mom_kernel_mass_flux_y*ydim0_advec_mom_kernel_mass_flux_y*1+x+xdim0_advec_mom_kernel_mass_flux_y*(y)+xdim0_advec_mom_kernel_mass_flux_y*ydim0_advec_mom_kernel_mass_flux_y*(z))
#define OPS_ACC1(x,y,z) (n_x*1+n_y*xdim1_advec_mom_kernel_mass_flux_y*1+n_z*xdim1_advec_mom_kernel_mass_flux_y*ydim1_advec_mom_kernel_mass_flux_y*1+x+xdim1_advec_mom_kernel_mass_flux_y*(y)+xdim1_advec_mom_kernel_mass_flux_y*ydim1_advec_mom_kernel_mass_flux_y*(z))


//user function

// host stub function
void ops_par_loop_advec_mom_kernel_mass_flux_y_execute(ops_kernel_descriptor *desc) {
  int dim = desc->dim;
  int *range = desc->range;
  ops_arg arg0 = desc->args[0];
  ops_arg arg1 = desc->args[1];

  //Timing
  double t1,t2,c1,c2;

  ops_arg args[2] = { arg0, arg1};



  #ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args,2,range,29)) return;
  #endif

  if (OPS_diags > 1) {
    ops_timing_realloc(29,"advec_mom_kernel_mass_flux_y");
    OPS_kernels[29].count++;
    ops_timers_core(&c2,&t2);
  }

  //compute locally allocated range for the sub-block
  int start[3];
  int end[3];

  for ( int n=0; n<3; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }

  #ifdef OPS_DEBUG
  ops_register_args(args, "advec_mom_kernel_mass_flux_y");
  #endif



  //set up initial pointers and exchange halos if necessary
  int base0 = args[0].dat->base_offset;
  double * __restrict__ node_flux = (double *)(args[0].data + base0);

  int base1 = args[1].dat->base_offset;
  const double * __restrict__ mass_flux_y = (double *)(args[1].data + base1);


  //initialize global variable with the dimension of dats
  int xdim0_advec_mom_kernel_mass_flux_y = args[0].dat->size[0];
  int ydim0_advec_mom_kernel_mass_flux_y = args[0].dat->size[1];
  int xdim1_advec_mom_kernel_mass_flux_y = args[1].dat->size[0];
  int ydim1_advec_mom_kernel_mass_flux_y = args[1].dat->size[1];

  //Halo Exchanges
  ops_H_D_exchanges_host(args, 2);
  ops_halo_exchanges(args,2,range);
  ops_H_D_exchanges_host(args, 2);

  if (OPS_diags > 1) {
    ops_timers_core(&c1,&t1);
    OPS_kernels[29].mpi_time += t1-t2;
  }

  #pragma omp parallel for collapse(2)
  for ( int n_z=start[2]; n_z<end[2]; n_z++ ){
    for ( int n_y=start[1]; n_y<end[1]; n_y++ ){
      #pragma simd
      for ( int n_x=start[0]; n_x<end[0]; n_x++ ){
        


  node_flux[OPS_ACC0(0,0,0)] = 0.125 * ( mass_flux_y[OPS_ACC1(-1,0,0)] + mass_flux_y[OPS_ACC1(0,0,0)] +
                                         mass_flux_y[OPS_ACC1(-1,1,0)] + mass_flux_y[OPS_ACC1(0,1,0)] +
                                         mass_flux_y[OPS_ACC1(-1,0,-1)] + mass_flux_y[OPS_ACC1(0,0,-1)] +
                                         mass_flux_y[OPS_ACC1(-1,1,-1)] + mass_flux_y[OPS_ACC1(0,1,-1)] );

      }
    }
  }
  if (OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    OPS_kernels[29].time += t2-t1;
  }
  ops_set_dirtybit_host(args, 2);
  ops_set_halo_dirtybit3(&args[0],range);

  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c1,&t1);
    OPS_kernels[29].mpi_time += t1-t2;
    OPS_kernels[29].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[29].transfer += ops_compute_transfer(dim, start, end, &arg1);
  }
}
#undef OPS_ACC0
#undef OPS_ACC1


void ops_par_loop_advec_mom_kernel_mass_flux_y(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1) {
  ops_kernel_descriptor *desc = (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->index = 29;
  #ifdef OPS_MPI
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (!sb->owned) return;
  for ( int n=0; n<3; n++ ){
    desc->range[2*n] = sb->decomp_disp[n];desc->range[2*n+1] = sb->decomp_disp[n]+sb->decomp_size[n];
    if (desc->range[2*n] >= range[2*n]) {
      desc->range[2*n] = 0;
    }
    else {
      desc->range[2*n] = range[2*n] - desc->range[2*n];
    }
    if (sb->id_m[n]==MPI_PROC_NULL && range[2*n] < 0) desc->range[2*n] = range[2*n];
    if (desc->range[2*n+1] >= range[2*n+1]) {
      desc->range[2*n+1] = range[2*n+1] - sb->decomp_disp[n];
    }
    else {
      desc->range[2*n+1] = sb->decomp_size[n];
    }
    if (sb->id_p[n]==MPI_PROC_NULL && (range[2*n+1] > sb->decomp_disp[n]+sb->decomp_size[n]))
      desc->range[2*n+1] += (range[2*n+1]-sb->decomp_disp[n]-sb->decomp_size[n]);
  }
  #else //OPS_MPI
  for ( int i=0; i<6; i++ ){
    desc->range[i] = range[i];
  }
  #endif //OPS_MPI
  desc->nargs = 2;
  desc->args = (ops_arg*)malloc(2*sizeof(ops_arg));
  desc->args[0] = arg0;
  desc->args[1] = arg1;
  desc->function = ops_par_loop_advec_mom_kernel_mass_flux_y_execute;
  ops_enqueue_kernel(desc);
  }
