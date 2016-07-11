//
// auto-generated by ops.py
//
#define OPS_ACC3(x,y) (n_x*1+n_y*xdim3_poisson_kernel_populate*1+x+xdim3_poisson_kernel_populate*(y))
#define OPS_ACC4(x,y) (n_x*1+n_y*xdim4_poisson_kernel_populate*1+x+xdim4_poisson_kernel_populate*(y))
#define OPS_ACC5(x,y) (n_x*1+n_y*xdim5_poisson_kernel_populate*1+x+xdim5_poisson_kernel_populate*(y))


//user function

// host stub function
void ops_par_loop_poisson_kernel_populate_execute(ops_kernel_descriptor *desc) {
  ops_block block = desc->block;
  int dim = desc->dim;
  int *range = desc->range;
  ops_arg arg0 = desc->args[0];
  ops_arg arg1 = desc->args[1];
  ops_arg arg2 = desc->args[2];
  ops_arg arg3 = desc->args[3];
  ops_arg arg4 = desc->args[4];
  ops_arg arg5 = desc->args[5];

  //Timing
  double t1,t2,c1,c2;

  ops_arg args[6] = { arg0, arg1, arg2, arg3, arg4, arg5};



  #ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args,6,range,0)) return;
  #endif

  //compute locally allocated range for the sub-block
  int start[2];
  int end[2];

  for ( int n=0; n<2; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }

  #ifdef OPS_DEBUG
  ops_register_args(args, "poisson_kernel_populate");
  #endif


  int arg_idx[2];
  #ifdef OPS_MPI
  sub_block_list sb = OPS_sub_block_list[block->index];
  arg_idx[0] = sb->decomp_disp[0];
  arg_idx[1] = sb->decomp_disp[1];
  #else //OPS_MPI
  arg_idx[0] = 0;
  arg_idx[1] = 0;
  #endif //OPS_MPI

  //set up initial pointers and exchange halos if necessary
  const int * __restrict__ dispx = (int *)args[0].data;


  const int * __restrict__ dispy = (int *)args[1].data;



  int base3 = args[3].dat->base_offset;
  double * __restrict__ u = (double *)(args[3].data + base3);

  int base4 = args[4].dat->base_offset;
  double * __restrict__ f = (double *)(args[4].data + base4);

  int base5 = args[5].dat->base_offset;
  double * __restrict__ ref = (double *)(args[5].data + base5);


  //initialize global variable with the dimension of dats
  int xdim3_poisson_kernel_populate = args[3].dat->size[0];
  int xdim4_poisson_kernel_populate = args[4].dat->size[0];
  int xdim5_poisson_kernel_populate = args[5].dat->size[0];

  #pragma omp parallel for
  for ( int n_y=start[1]; n_y<end[1]; n_y++ ){
    #pragma omp simd
    for ( int n_x=start[0]; n_x<end[0]; n_x++ ){
      int idx[] = {arg_idx[0]+n_x, arg_idx[1]+n_y};
      
  double x = dx * (double)(idx[0]+dispx[0]);
  double y = dy * (double)(idx[1]+dispy[0]);

  u[OPS_ACC3(0,0)] = sin(M_PI*x)*cos(2.0*M_PI*y);
  f[OPS_ACC4(0,0)] = -5.0*M_PI*M_PI*sin(M_PI*x)*cos(2.0*M_PI*y);
  ref[OPS_ACC5(0,0)] = sin(M_PI*x)*cos(2.0*M_PI*y);


    }
  }
}
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5


void ops_par_loop_poisson_kernel_populate(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5) {
  ops_kernel_descriptor *desc = (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->index = 0;
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
  desc->nargs = 6;
  desc->args = (ops_arg*)malloc(6*sizeof(ops_arg));
  desc->args[0] = arg0;
  char *tmp = (char*)malloc(1*sizeof(int));
  memcpy(tmp, arg0.data,1*sizeof(int));
  desc->args[0].data = tmp;
  desc->args[1] = arg1;
  tmp = (char*)malloc(1*sizeof(int));
  memcpy(tmp, arg1.data,1*sizeof(int));
  desc->args[1].data = tmp;
  desc->args[2] = arg2;
  desc->args[3] = arg3;
  desc->args[4] = arg4;
  desc->args[5] = arg5;
  desc->function = ops_par_loop_poisson_kernel_populate_execute;
  ops_enqueue_kernel(desc);
  }
