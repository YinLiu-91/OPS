//
// auto-generated by ops.py
//
#define OPS_ACC0(x,y) (n_x*1+n_y*xdim0_advec_mom_kernel_post_pre_advec_x*1+x+xdim0_advec_mom_kernel_post_pre_advec_x*(y))
#define OPS_ACC1(x,y) (n_x*1+n_y*xdim1_advec_mom_kernel_post_pre_advec_x*1+x+xdim1_advec_mom_kernel_post_pre_advec_x*(y))
#define OPS_ACC2(x,y) (n_x*1+n_y*xdim2_advec_mom_kernel_post_pre_advec_x*1+x+xdim2_advec_mom_kernel_post_pre_advec_x*(y))
#define OPS_ACC3(x,y) (n_x*1+n_y*xdim3_advec_mom_kernel_post_pre_advec_x*1+x+xdim3_advec_mom_kernel_post_pre_advec_x*(y))
#define OPS_ACC4(x,y) (n_x*1+n_y*xdim4_advec_mom_kernel_post_pre_advec_x*1+x+xdim4_advec_mom_kernel_post_pre_advec_x*(y))


//user function

// host stub function
void ops_par_loop_advec_mom_kernel_post_pre_advec_x_execute(ops_kernel_descriptor *desc) {
  int dim = desc->dim;
  int *range = desc->range;
  ops_arg arg0 = desc->args[0];
  ops_arg arg1 = desc->args[1];
  ops_arg arg2 = desc->args[2];
  ops_arg arg3 = desc->args[3];
  ops_arg arg4 = desc->args[4];

  //Timing
  double t1,t2,c1,c2;

  ops_arg args[5] = { arg0, arg1, arg2, arg3, arg4};



  #ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args,5,range,20)) return;
  #endif

  if (OPS_diags > 1) {
    ops_timing_realloc(20,"advec_mom_kernel_post_pre_advec_x");
    OPS_kernels[20].count++;
    ops_timers_core(&c2,&t2);
  }

  //compute locally allocated range for the sub-block
  int start[2];
  int end[2];

  for ( int n=0; n<2; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }

  #ifdef OPS_DEBUG
  ops_register_args(args, "advec_mom_kernel_post_pre_advec_x");
  #endif



  //set up initial pointers and exchange halos if necessary
  int base0 = args[0].dat->base_offset;
  double * __restrict__ node_mass_post = (double *)(args[0].data + base0);

  int base1 = args[1].dat->base_offset;
  const double * __restrict__ post_vol = (double *)(args[1].data + base1);

  int base2 = args[2].dat->base_offset;
  const double * __restrict__ density1 = (double *)(args[2].data + base2);

  int base3 = args[3].dat->base_offset;
  double * __restrict__ node_mass_pre = (double *)(args[3].data + base3);

  int base4 = args[4].dat->base_offset;
  const double * __restrict__ node_flux = (double *)(args[4].data + base4);


  //initialize global variable with the dimension of dats
  int xdim0_advec_mom_kernel_post_pre_advec_x = args[0].dat->size[0];
  int xdim1_advec_mom_kernel_post_pre_advec_x = args[1].dat->size[0];
  int xdim2_advec_mom_kernel_post_pre_advec_x = args[2].dat->size[0];
  int xdim3_advec_mom_kernel_post_pre_advec_x = args[3].dat->size[0];
  int xdim4_advec_mom_kernel_post_pre_advec_x = args[4].dat->size[0];

  //Halo Exchanges
  ops_H_D_exchanges_host(args, 5);
  ops_halo_exchanges(args,5,range);
  ops_H_D_exchanges_host(args, 5);

  if (OPS_diags > 1) {
    ops_timers_core(&c1,&t1);
    OPS_kernels[20].mpi_time += t1-t2;
  }

  #pragma omp parallel for
  for ( int n_y=start[1]; n_y<end[1]; n_y++ ){
    #pragma simd
    for ( int n_x=start[0]; n_x<end[0]; n_x++ ){
      



  node_mass_post[OPS_ACC0(0,0)] = 0.25 * ( density1[OPS_ACC2(0,-1)] * post_vol[OPS_ACC1(0,-1)] +
                              density1[OPS_ACC2(0,0)]   * post_vol[OPS_ACC1(0,0)]   +
                              density1[OPS_ACC2(-1,-1)] * post_vol[OPS_ACC1(-1,-1)] +
                              density1[OPS_ACC2(-1,0)]  * post_vol[OPS_ACC1(-1,0)]  );

  node_mass_pre[OPS_ACC3(0,0)] = node_mass_post[OPS_ACC0(0,0)] - node_flux[OPS_ACC4(-1,0)] + node_flux[OPS_ACC4(0,0)];


    }
  }
  if (OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    OPS_kernels[20].time += t2-t1;
  }
  ops_set_dirtybit_host(args, 5);
  ops_set_halo_dirtybit3(&args[0],range);
  ops_set_halo_dirtybit3(&args[3],range);

  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c1,&t1);
    OPS_kernels[20].mpi_time += t1-t2;
    OPS_kernels[20].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[20].transfer += ops_compute_transfer(dim, start, end, &arg1);
    OPS_kernels[20].transfer += ops_compute_transfer(dim, start, end, &arg2);
    OPS_kernels[20].transfer += ops_compute_transfer(dim, start, end, &arg3);
    OPS_kernels[20].transfer += ops_compute_transfer(dim, start, end, &arg4);
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4


void ops_par_loop_advec_mom_kernel_post_pre_advec_x(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4) {
  ops_kernel_descriptor *desc = (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->index = 20;
  #ifdef OPS_MPI
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (!sb->owned) return;
  for ( int n=0; n<2; n++ ){
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
  for ( int i=0; i<4; i++ ){
    desc->range[i] = range[i];
  }
  #endif //OPS_MPI
  desc->nargs = 5;
  desc->args = (ops_arg*)malloc(5*sizeof(ops_arg));
  desc->args[0] = arg0;
  desc->args[1] = arg1;
  desc->args[2] = arg2;
  desc->args[3] = arg3;
  desc->args[4] = arg4;
  desc->function = ops_par_loop_advec_mom_kernel_post_pre_advec_x_execute;
  ops_enqueue_kernel(desc);
  }
