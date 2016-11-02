//
// auto-generated by ops.py
//
__constant__ int xdim3_poisson_kernel_populate;
int xdim3_poisson_kernel_populate_h = -1;
int ydim3_poisson_kernel_populate_h = -1;
__constant__ int xdim4_poisson_kernel_populate;
int xdim4_poisson_kernel_populate_h = -1;
int ydim4_poisson_kernel_populate_h = -1;
__constant__ int xdim5_poisson_kernel_populate;
int xdim5_poisson_kernel_populate_h = -1;
int ydim5_poisson_kernel_populate_h = -1;

#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5

#define OPS_ACC3(x, y) (x + xdim3_poisson_kernel_populate * (y))
#define OPS_ACC4(x, y) (x + xdim4_poisson_kernel_populate * (y))
#define OPS_ACC5(x, y) (x + xdim5_poisson_kernel_populate * (y))

// user function
__device__

    void
    poisson_kernel_populate_gpu(const int *dispx, const int *dispy,
                                const int *idx, double *u, double *f,
                                double *ref) {
  double x = dx * (double)(idx[0] + dispx[0]);
  double y = dy * (double)(idx[1] + dispy[0]);

  u[OPS_ACC3(0, 0)] = sin(M_PI * x) * cos(2.0 * M_PI * y);
  f[OPS_ACC4(0, 0)] = -5.0 * M_PI * M_PI * sin(M_PI * x) * cos(2.0 * M_PI * y);
  ref[OPS_ACC5(0, 0)] = sin(M_PI * x) * cos(2.0 * M_PI * y);
}

#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5

__global__ void ops_poisson_kernel_populate(const int arg0, const int arg1,
                                            int arg_idx0, int arg_idx1,
                                            double *__restrict arg3,
                                            double *__restrict arg4,
                                            double *__restrict arg5, int size0,
                                            int size1) {

  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  int arg_idx[2];
  arg_idx[0] = arg_idx0 + idx_x;
  arg_idx[1] = arg_idx1 + idx_y;
  arg3 += idx_x * 1 * 1 + idx_y * 1 * 1 * xdim3_poisson_kernel_populate;
  arg4 += idx_x * 1 * 1 + idx_y * 1 * 1 * xdim4_poisson_kernel_populate;
  arg5 += idx_x * 1 * 1 + idx_y * 1 * 1 * xdim5_poisson_kernel_populate;

  if (idx_x < size0 && idx_y < size1) {
    poisson_kernel_populate_gpu(&arg0, &arg1, arg_idx, arg3, arg4, arg5);
  }
}

// host stub function
void ops_par_loop_poisson_kernel_populate(char const *name, ops_block block,
                                          int dim, int *range, ops_arg arg0,
                                          ops_arg arg1, ops_arg arg2,
                                          ops_arg arg3, ops_arg arg4,
                                          ops_arg arg5) {

  // Timing
  double t1, t2, c1, c2;

  ops_arg args[6] = {arg0, arg1, arg2, arg3, arg4, arg5};

#ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args, 6, range, 0))
    return;
#endif

  if (OPS_diags > 1) {
    ops_timing_realloc(0, "poisson_kernel_populate");
    OPS_kernels[0].count++;
    ops_timers_core(&c1, &t1);
  }

  // compute locally allocated range for the sub-block
  int start[2];
  int end[2];
#ifdef OPS_MPI
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (!sb->owned)
    return;
  for (int n = 0; n < 2; n++) {
    start[n] = sb->decomp_disp[n];
    end[n] = sb->decomp_disp[n] + sb->decomp_size[n];
    if (start[n] >= range[2 * n]) {
      start[n] = 0;
    } else {
      start[n] = range[2 * n] - start[n];
    }
    if (sb->id_m[n] == MPI_PROC_NULL && range[2 * n] < 0)
      start[n] = range[2 * n];
    if (end[n] >= range[2 * n + 1]) {
      end[n] = range[2 * n + 1] - sb->decomp_disp[n];
    } else {
      end[n] = sb->decomp_size[n];
    }
    if (sb->id_p[n] == MPI_PROC_NULL &&
        (range[2 * n + 1] > sb->decomp_disp[n] + sb->decomp_size[n]))
      end[n] += (range[2 * n + 1] - sb->decomp_disp[n] - sb->decomp_size[n]);
  }
#else
  for (int n = 0; n < 2; n++) {
    start[n] = range[2 * n];
    end[n] = range[2 * n + 1];
  }
#endif

  int x_size = MAX(0, end[0] - start[0]);
  int y_size = MAX(0, end[1] - start[1]);

  int arg_idx[2];
#ifdef OPS_MPI
  arg_idx[0] = sb->decomp_disp[0] + start[0];
  arg_idx[1] = sb->decomp_disp[1] + start[1];
#else
  arg_idx[0] = start[0];
  arg_idx[1] = start[1];
#endif
  int xdim3 = args[3].dat->size[0];
  int xdim4 = args[4].dat->size[0];
  int xdim5 = args[5].dat->size[0];

  if (xdim3 != xdim3_poisson_kernel_populate_h ||
      xdim4 != xdim4_poisson_kernel_populate_h ||
      xdim5 != xdim5_poisson_kernel_populate_h) {
    cudaMemcpyToSymbol(xdim3_poisson_kernel_populate, &xdim3, sizeof(int));
    xdim3_poisson_kernel_populate_h = xdim3;
    cudaMemcpyToSymbol(xdim4_poisson_kernel_populate, &xdim4, sizeof(int));
    xdim4_poisson_kernel_populate_h = xdim4;
    cudaMemcpyToSymbol(xdim5_poisson_kernel_populate, &xdim5, sizeof(int));
    xdim5_poisson_kernel_populate_h = xdim5;
  }

  dim3 grid((x_size - 1) / OPS_block_size_x + 1,
            (y_size - 1) / OPS_block_size_y + 1, 1);
  dim3 tblock(OPS_block_size_x, OPS_block_size_y, 1);

  int dat3 = args[3].dat->elem_size;
  int dat4 = args[4].dat->elem_size;
  int dat5 = args[5].dat->elem_size;

  char *p_a[6];

  // set up initial pointers
  int d_m[OPS_MAX_DIM];
#ifdef OPS_MPI
  for (int d = 0; d < dim; d++)
    d_m[d] =
        args[3].dat->d_m[d] + OPS_sub_dat_list[args[3].dat->index]->d_im[d];
#else
  for (int d = 0; d < dim; d++)
    d_m[d] = args[3].dat->d_m[d];
#endif
  int base3 = dat3 * 1 * (start[0] * args[3].stencil->stride[0] -
                          args[3].dat->base[0] - d_m[0]);
  base3 = base3 +
          dat3 * args[3].dat->size[0] * (start[1] * args[3].stencil->stride[1] -
                                         args[3].dat->base[1] - d_m[1]);
  p_a[3] = (char *)args[3].data_d + base3;

#ifdef OPS_MPI
  for (int d = 0; d < dim; d++)
    d_m[d] =
        args[4].dat->d_m[d] + OPS_sub_dat_list[args[4].dat->index]->d_im[d];
#else
  for (int d = 0; d < dim; d++)
    d_m[d] = args[4].dat->d_m[d];
#endif
  int base4 = dat4 * 1 * (start[0] * args[4].stencil->stride[0] -
                          args[4].dat->base[0] - d_m[0]);
  base4 = base4 +
          dat4 * args[4].dat->size[0] * (start[1] * args[4].stencil->stride[1] -
                                         args[4].dat->base[1] - d_m[1]);
  p_a[4] = (char *)args[4].data_d + base4;

#ifdef OPS_MPI
  for (int d = 0; d < dim; d++)
    d_m[d] =
        args[5].dat->d_m[d] + OPS_sub_dat_list[args[5].dat->index]->d_im[d];
#else
  for (int d = 0; d < dim; d++)
    d_m[d] = args[5].dat->d_m[d];
#endif
  int base5 = dat5 * 1 * (start[0] * args[5].stencil->stride[0] -
                          args[5].dat->base[0] - d_m[0]);
  base5 = base5 +
          dat5 * args[5].dat->size[0] * (start[1] * args[5].stencil->stride[1] -
                                         args[5].dat->base[1] - d_m[1]);
  p_a[5] = (char *)args[5].data_d + base5;

  ops_H_D_exchanges_device(args, 6);
  ops_halo_exchanges(args, 6, range);

  if (OPS_diags > 1) {
    ops_timers_core(&c2, &t2);
    OPS_kernels[0].mpi_time += t2 - t1;
  }

  // call kernel wrapper function, passing in pointers to data
  ops_poisson_kernel_populate<<<grid, tblock>>>(
      *(int *)arg0.data, *(int *)arg1.data, arg_idx[0], arg_idx[1],
      (double *)p_a[3], (double *)p_a[4], (double *)p_a[5], x_size, y_size);

  if (OPS_diags > 1) {
    cutilSafeCall(cudaDeviceSynchronize());
    ops_timers_core(&c1, &t1);
    OPS_kernels[0].time += t1 - t2;
  }

  ops_set_dirtybit_device(args, 6);
  ops_set_halo_dirtybit3(&args[3], range);
  ops_set_halo_dirtybit3(&args[4], range);
  ops_set_halo_dirtybit3(&args[5], range);

  if (OPS_diags > 1) {
    // Update kernel record
    ops_timers_core(&c2, &t2);
    OPS_kernels[0].mpi_time += t2 - t1;
    OPS_kernels[0].transfer += ops_compute_transfer(dim, start, end, &arg3);
    OPS_kernels[0].transfer += ops_compute_transfer(dim, start, end, &arg4);
    OPS_kernels[0].transfer += ops_compute_transfer(dim, start, end, &arg5);
  }
}
