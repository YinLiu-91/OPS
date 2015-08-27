//
// auto-generated by ops.py
//
__constant__ int xdim0_updateRK3_kernel;
int xdim0_updateRK3_kernel_h = -1;
int ydim0_updateRK3_kernel_h = -1;
__constant__ int xdim1_updateRK3_kernel;
int xdim1_updateRK3_kernel_h = -1;
int ydim1_updateRK3_kernel_h = -1;
__constant__ int xdim2_updateRK3_kernel;
int xdim2_updateRK3_kernel_h = -1;
int ydim2_updateRK3_kernel_h = -1;
__constant__ int xdim3_updateRK3_kernel;
int xdim3_updateRK3_kernel_h = -1;
int ydim3_updateRK3_kernel_h = -1;
__constant__ int xdim4_updateRK3_kernel;
int xdim4_updateRK3_kernel_h = -1;
int ydim4_updateRK3_kernel_h = -1;
__constant__ int xdim5_updateRK3_kernel;
int xdim5_updateRK3_kernel_h = -1;
int ydim5_updateRK3_kernel_h = -1;
__constant__ int xdim6_updateRK3_kernel;
int xdim6_updateRK3_kernel_h = -1;
int ydim6_updateRK3_kernel_h = -1;
__constant__ int xdim7_updateRK3_kernel;
int xdim7_updateRK3_kernel_h = -1;
int ydim7_updateRK3_kernel_h = -1;
__constant__ int xdim8_updateRK3_kernel;
int xdim8_updateRK3_kernel_h = -1;
int ydim8_updateRK3_kernel_h = -1;

#define OPS_ACC0(x) (x)
#define OPS_ACC1(x) (x)
#define OPS_ACC2(x) (x)
#define OPS_ACC3(x) (x)
#define OPS_ACC4(x) (x)
#define OPS_ACC5(x) (x)
#define OPS_ACC6(x) (x)
#define OPS_ACC7(x) (x)
#define OPS_ACC8(x) (x)

//user function
__device__

void updateRK3_kernel(double *rho_new, double* rhou_new, double* rhoE_new,
                      double *rho_old, double* rhou_old, double* rhoE_old,
                      const double *rho_res, const double *rhou_res, const double *rhoE_res,
                      const double* a1, const double* a2) {

			rho_new[OPS_ACC0(0)] = rho_old[OPS_ACC3(0)] + dt * a1[0] * (-rho_res[OPS_ACC6(0)]);
			rhou_new[OPS_ACC1(0)] = rhou_old[OPS_ACC4(0)] + dt * a1[0] * (-rhou_res[OPS_ACC7(0)]);
			rhoE_new[OPS_ACC2(0)] = rhoE_old[OPS_ACC5(0)] + dt * a1[0] * (-rhoE_res[OPS_ACC8(0)]);

			rho_old[OPS_ACC3(0)] = rho_old[OPS_ACC3(0)] + dt * a2[0] * (-rho_res[OPS_ACC6(0)]);
			rhou_old[OPS_ACC4(0)] = rhou_old[OPS_ACC4(0)] + dt * a2[0] * (-rhou_res[OPS_ACC7(0)]);
			rhoE_old[OPS_ACC5(0)] = rhoE_old[OPS_ACC5(0)] + dt * a2[0] * (-rhoE_res[OPS_ACC8(0)]);
}



#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6
#undef OPS_ACC7
#undef OPS_ACC8


__global__ void ops_updateRK3_kernel(
double* __restrict arg0,
double* __restrict arg1,
double* __restrict arg2,
double* __restrict arg3,
double* __restrict arg4,
double* __restrict arg5,
const double* __restrict arg6,
const double* __restrict arg7,
const double* __restrict arg8,
const double arg9,
const double arg10,
int size0 ){


  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1*1;
  arg1 += idx_x * 1*1;
  arg2 += idx_x * 1*1;
  arg3 += idx_x * 1*1;
  arg4 += idx_x * 1*1;
  arg5 += idx_x * 1*1;
  arg6 += idx_x * 1*1;
  arg7 += idx_x * 1*1;
  arg8 += idx_x * 1*1;

  if (idx_x < size0) {
    updateRK3_kernel(arg0, arg1, arg2, arg3,
                   arg4, arg5, arg6, arg7, arg8,
                   &arg9, &arg10);
  }

}

// host stub function
void ops_par_loop_updateRK3_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5, ops_arg arg6, ops_arg arg7, ops_arg arg8,
 ops_arg arg9, ops_arg arg10) {

  //Timing
  double t1,t2,c1,c2;

  ops_arg args[11] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10};


  #ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args,11,range,6)) return;
  #endif

  if (OPS_diags > 1) {
    ops_timing_realloc(6,"updateRK3_kernel");
    OPS_kernels[6].count++;
    ops_timers_core(&c1,&t1);
  }

  //compute locally allocated range for the sub-block
  int start[1];
  int end[1];
  #ifdef OPS_MPI
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (!sb->owned) return;
  for ( int n=0; n<1; n++ ){
    start[n] = sb->decomp_disp[n];end[n] = sb->decomp_disp[n]+sb->decomp_size[n];
    if (start[n] >= range[2*n]) {
      start[n] = 0;
    }
    else {
      start[n] = range[2*n] - start[n];
    }
    if (sb->id_m[n]==MPI_PROC_NULL && range[2*n] < 0) start[n] = range[2*n];
    if (end[n] >= range[2*n+1]) {
      end[n] = range[2*n+1] - sb->decomp_disp[n];
    }
    else {
      end[n] = sb->decomp_size[n];
    }
    if (sb->id_p[n]==MPI_PROC_NULL && (range[2*n+1] > sb->decomp_disp[n]+sb->decomp_size[n]))
      end[n] += (range[2*n+1]-sb->decomp_disp[n]-sb->decomp_size[n]);
  }
  #else //OPS_MPI
  for ( int n=0; n<1; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }
  #endif //OPS_MPI

  int x_size = MAX(0,end[0]-start[0]);

  int xdim0 = args[0].dat->size[0];
  int xdim1 = args[1].dat->size[0];
  int xdim2 = args[2].dat->size[0];
  int xdim3 = args[3].dat->size[0];
  int xdim4 = args[4].dat->size[0];
  int xdim5 = args[5].dat->size[0];
  int xdim6 = args[6].dat->size[0];
  int xdim7 = args[7].dat->size[0];
  int xdim8 = args[8].dat->size[0];

  if (xdim0 != xdim0_updateRK3_kernel_h || xdim1 != xdim1_updateRK3_kernel_h || xdim2 != xdim2_updateRK3_kernel_h || xdim3 != xdim3_updateRK3_kernel_h || xdim4 != xdim4_updateRK3_kernel_h || xdim5 != xdim5_updateRK3_kernel_h || xdim6 != xdim6_updateRK3_kernel_h || xdim7 != xdim7_updateRK3_kernel_h || xdim8 != xdim8_updateRK3_kernel_h) {
    cudaMemcpyToSymbol( xdim0_updateRK3_kernel, &xdim0, sizeof(int) );
    xdim0_updateRK3_kernel_h = xdim0;
    cudaMemcpyToSymbol( xdim1_updateRK3_kernel, &xdim1, sizeof(int) );
    xdim1_updateRK3_kernel_h = xdim1;
    cudaMemcpyToSymbol( xdim2_updateRK3_kernel, &xdim2, sizeof(int) );
    xdim2_updateRK3_kernel_h = xdim2;
    cudaMemcpyToSymbol( xdim3_updateRK3_kernel, &xdim3, sizeof(int) );
    xdim3_updateRK3_kernel_h = xdim3;
    cudaMemcpyToSymbol( xdim4_updateRK3_kernel, &xdim4, sizeof(int) );
    xdim4_updateRK3_kernel_h = xdim4;
    cudaMemcpyToSymbol( xdim5_updateRK3_kernel, &xdim5, sizeof(int) );
    xdim5_updateRK3_kernel_h = xdim5;
    cudaMemcpyToSymbol( xdim6_updateRK3_kernel, &xdim6, sizeof(int) );
    xdim6_updateRK3_kernel_h = xdim6;
    cudaMemcpyToSymbol( xdim7_updateRK3_kernel, &xdim7, sizeof(int) );
    xdim7_updateRK3_kernel_h = xdim7;
    cudaMemcpyToSymbol( xdim8_updateRK3_kernel, &xdim8, sizeof(int) );
    xdim8_updateRK3_kernel_h = xdim8;
  }



  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, 1, 1);
  dim3 tblock(OPS_block_size_x,1,1);



  int dat0 = args[0].dat->elem_size;
  int dat1 = args[1].dat->elem_size;
  int dat2 = args[2].dat->elem_size;
  int dat3 = args[3].dat->elem_size;
  int dat4 = args[4].dat->elem_size;
  int dat5 = args[5].dat->elem_size;
  int dat6 = args[6].dat->elem_size;
  int dat7 = args[7].dat->elem_size;
  int dat8 = args[8].dat->elem_size;

  char *p_a[11];

  //set up initial pointers
  int d_m[OPS_MAX_DIM];
  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[0].dat->d_m[d] + OPS_sub_dat_list[args[0].dat->index]->d_im[d];
  #else //OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[0].dat->d_m[d];
  #endif //OPS_MPI
  int base0 = dat0 * 1 *
  (start[0] * args[0].stencil->stride[0] - args[0].dat->base[0] - d_m[0]);
  p_a[0] = (char *)args[0].data_d + base0;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[1].dat->d_m[d] + OPS_sub_dat_list[args[1].dat->index]->d_im[d];
  #else //OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[1].dat->d_m[d];
  #endif //OPS_MPI
  int base1 = dat1 * 1 *
  (start[0] * args[1].stencil->stride[0] - args[1].dat->base[0] - d_m[0]);
  p_a[1] = (char *)args[1].data_d + base1;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[2].dat->d_m[d] + OPS_sub_dat_list[args[2].dat->index]->d_im[d];
  #else //OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[2].dat->d_m[d];
  #endif //OPS_MPI
  int base2 = dat2 * 1 *
  (start[0] * args[2].stencil->stride[0] - args[2].dat->base[0] - d_m[0]);
  p_a[2] = (char *)args[2].data_d + base2;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[3].dat->d_m[d] + OPS_sub_dat_list[args[3].dat->index]->d_im[d];
  #else //OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[3].dat->d_m[d];
  #endif //OPS_MPI
  int base3 = dat3 * 1 *
  (start[0] * args[3].stencil->stride[0] - args[3].dat->base[0] - d_m[0]);
  p_a[3] = (char *)args[3].data_d + base3;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[4].dat->d_m[d] + OPS_sub_dat_list[args[4].dat->index]->d_im[d];
  #else //OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[4].dat->d_m[d];
  #endif //OPS_MPI
  int base4 = dat4 * 1 *
  (start[0] * args[4].stencil->stride[0] - args[4].dat->base[0] - d_m[0]);
  p_a[4] = (char *)args[4].data_d + base4;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[5].dat->d_m[d] + OPS_sub_dat_list[args[5].dat->index]->d_im[d];
  #else //OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[5].dat->d_m[d];
  #endif //OPS_MPI
  int base5 = dat5 * 1 *
  (start[0] * args[5].stencil->stride[0] - args[5].dat->base[0] - d_m[0]);
  p_a[5] = (char *)args[5].data_d + base5;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[6].dat->d_m[d] + OPS_sub_dat_list[args[6].dat->index]->d_im[d];
  #else //OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[6].dat->d_m[d];
  #endif //OPS_MPI
  int base6 = dat6 * 1 *
  (start[0] * args[6].stencil->stride[0] - args[6].dat->base[0] - d_m[0]);
  p_a[6] = (char *)args[6].data_d + base6;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[7].dat->d_m[d] + OPS_sub_dat_list[args[7].dat->index]->d_im[d];
  #else //OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[7].dat->d_m[d];
  #endif //OPS_MPI
  int base7 = dat7 * 1 *
  (start[0] * args[7].stencil->stride[0] - args[7].dat->base[0] - d_m[0]);
  p_a[7] = (char *)args[7].data_d + base7;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[8].dat->d_m[d] + OPS_sub_dat_list[args[8].dat->index]->d_im[d];
  #else //OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[8].dat->d_m[d];
  #endif //OPS_MPI
  int base8 = dat8 * 1 *
  (start[0] * args[8].stencil->stride[0] - args[8].dat->base[0] - d_m[0]);
  p_a[8] = (char *)args[8].data_d + base8;


  ops_H_D_exchanges_device(args, 11);
  ops_halo_exchanges(args,11,range);

  if (OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    OPS_kernels[6].mpi_time += t2-t1;
  }


  //call kernel wrapper function, passing in pointers to data
  ops_updateRK3_kernel<<<grid, tblock >>> (  (double *)p_a[0], (double *)p_a[1],
           (double *)p_a[2], (double *)p_a[3],
           (double *)p_a[4], (double *)p_a[5],
           (double *)p_a[6], (double *)p_a[7],
           (double *)p_a[8], *(double *)arg9.data,
           *(double *)arg10.data,x_size);

  if (OPS_diags>1) {
    cutilSafeCall(cudaDeviceSynchronize());
    ops_timers_core(&c1,&t1);
    OPS_kernels[6].time += t1-t2;
  }

  ops_set_dirtybit_device(args, 11);
  ops_set_halo_dirtybit3(&args[0],range);
  ops_set_halo_dirtybit3(&args[1],range);
  ops_set_halo_dirtybit3(&args[2],range);
  ops_set_halo_dirtybit3(&args[3],range);
  ops_set_halo_dirtybit3(&args[4],range);
  ops_set_halo_dirtybit3(&args[5],range);

  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c2,&t2);
    OPS_kernels[6].mpi_time += t2-t1;
    OPS_kernels[6].transfer += ops_compute_transfer(dim, range, &arg0);
    OPS_kernels[6].transfer += ops_compute_transfer(dim, range, &arg1);
    OPS_kernels[6].transfer += ops_compute_transfer(dim, range, &arg2);
    OPS_kernels[6].transfer += ops_compute_transfer(dim, range, &arg3);
    OPS_kernels[6].transfer += ops_compute_transfer(dim, range, &arg4);
    OPS_kernels[6].transfer += ops_compute_transfer(dim, range, &arg5);
    OPS_kernels[6].transfer += ops_compute_transfer(dim, range, &arg6);
    OPS_kernels[6].transfer += ops_compute_transfer(dim, range, &arg7);
    OPS_kernels[6].transfer += ops_compute_transfer(dim, range, &arg8);
  }
}
