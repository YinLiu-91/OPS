//
// auto-generated by ops.py
//
#include "./OpenMP4/clover_leaf_common.h"
#include "./OpenMP4/update_halo_kernel1_r2_openmp4_kernel_c.c"

#define OPS_GPU

int xdim0_update_halo_kernel1_r2;
int xdim0_update_halo_kernel1_r2_h = -1;
int xdim1_update_halo_kernel1_r2;
int xdim1_update_halo_kernel1_r2_h = -1;
int xdim2_update_halo_kernel1_r2;
int xdim2_update_halo_kernel1_r2_h = -1;
int xdim3_update_halo_kernel1_r2;
int xdim3_update_halo_kernel1_r2_h = -1;
int xdim4_update_halo_kernel1_r2;
int xdim4_update_halo_kernel1_r2_h = -1;
int xdim5_update_halo_kernel1_r2;
int xdim5_update_halo_kernel1_r2_h = -1;
int xdim6_update_halo_kernel1_r2;
int xdim6_update_halo_kernel1_r2_h = -1;

void ops_par_loop_update_halo_kernel1_r2(char const *name, ops_block block,
                                         int dim, int *range, ops_arg arg0,
                                         ops_arg arg1, ops_arg arg2,
                                         ops_arg arg3, ops_arg arg4,
                                         ops_arg arg5, ops_arg arg6,
                                         ops_arg arg7) {

  // Timing
  double t1, t2, c1, c2;
  ops_arg args[8] = {arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7};

#ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args, 8, range, 49))
    return;
#endif

  if (OPS_diags > 1) {
    ops_timing_realloc(49, "update_halo_kernel1_r2");
    OPS_kernels[49].count++;
    ops_timers_core(&c1, &t1);
  }

  // compute localy allocated range for the sub-block

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

  xdim0 = args[0].dat->size[0];
  xdim1 = args[1].dat->size[0];
  xdim2 = args[2].dat->size[0];
  xdim3 = args[3].dat->size[0];
  xdim4 = args[4].dat->size[0];
  xdim5 = args[5].dat->size[0];
  xdim6 = args[6].dat->size[0];
  if (xdim0 != xdim0_update_halo_kernel1_r2_h ||
      xdim1 != xdim1_update_halo_kernel1_r2_h ||
      xdim2 != xdim2_update_halo_kernel1_r2_h ||
      xdim3 != xdim3_update_halo_kernel1_r2_h ||
      xdim4 != xdim4_update_halo_kernel1_r2_h ||
      xdim5 != xdim5_update_halo_kernel1_r2_h ||
      xdim6 != xdim6_update_halo_kernel1_r2_h) {
    xdim0_update_halo_kernel1_r2 = xdim0;
    xdim0_update_halo_kernel1_r2_h = xdim0;
    xdim1_update_halo_kernel1_r2 = xdim1;
    xdim1_update_halo_kernel1_r2_h = xdim1;
    xdim2_update_halo_kernel1_r2 = xdim2;
    xdim2_update_halo_kernel1_r2_h = xdim2;
    xdim3_update_halo_kernel1_r2 = xdim3;
    xdim3_update_halo_kernel1_r2_h = xdim3;
    xdim4_update_halo_kernel1_r2 = xdim4;
    xdim4_update_halo_kernel1_r2_h = xdim4;
    xdim5_update_halo_kernel1_r2 = xdim5;
    xdim5_update_halo_kernel1_r2_h = xdim5;
    xdim6_update_halo_kernel1_r2 = xdim6;
    xdim6_update_halo_kernel1_r2_h = xdim6;
  }

  int tot0 = 1;
  for (int i = 0; i < args[0].dat->block->dims; i++)
    tot0 = tot0 * args[0].dat->size[i];
  int tot1 = 1;
  for (int i = 0; i < args[1].dat->block->dims; i++)
    tot1 = tot1 * args[1].dat->size[i];
  int tot2 = 1;
  for (int i = 0; i < args[2].dat->block->dims; i++)
    tot2 = tot2 * args[2].dat->size[i];
  int tot3 = 1;
  for (int i = 0; i < args[3].dat->block->dims; i++)
    tot3 = tot3 * args[3].dat->size[i];
  int tot4 = 1;
  for (int i = 0; i < args[4].dat->block->dims; i++)
    tot4 = tot4 * args[4].dat->size[i];
  int tot5 = 1;
  for (int i = 0; i < args[5].dat->block->dims; i++)
    tot5 = tot5 * args[5].dat->size[i];
  int tot6 = 1;
  for (int i = 0; i < args[6].dat->block->dims; i++)
    tot6 = tot6 * args[6].dat->size[i];
  int *arg7h = (int *)arg7.data;
// Upload large globals
#ifdef OPS_GPU
  int consts_bytes = 0;
  consts_bytes += ROUND_UP(NUM_FIELDS * sizeof(int));
  int OPS_consts_bytes = 4 * consts_bytes;
  if (OPS_consts_h == NULL) {
    OPS_consts_h = (char *)malloc(OPS_consts_bytes);
    memset(OPS_consts_h, 0, OPS_consts_bytes);
  }
  consts_bytes = 0;
  args[7].data = OPS_consts_h + consts_bytes;
  args[7].data_d = OPS_consts_d + consts_bytes;
  for (int d = 0; d < NUM_FIELDS; d++)
    ((int *)args[7].data)[d] = arg7h[d];
  consts_bytes += ROUND_UP(NUM_FIELDS * sizeof(int));
  mvConstArraysToDevice(consts_bytes);
#endif // OPS_GPU

  // set up initial pointers
  int base0 = args[0].dat->base_offset +
              args[0].dat->elem_size * start[0] * args[0].stencil->stride[0];
  base0 = base0 +
          args[0].dat->elem_size * args[0].dat->size[0] * start[1] *
              args[0].stencil->stride[1];
#ifdef OPS_GPU
  double *p_a0 = (double *)((char *)args[0].data);
#else
  double *p_a0 = (double *)((char *)args[0].data + base0);
#endif

  int base1 = args[1].dat->base_offset +
              args[1].dat->elem_size * start[0] * args[1].stencil->stride[0];
  base1 = base1 +
          args[1].dat->elem_size * args[1].dat->size[0] * start[1] *
              args[1].stencil->stride[1];
#ifdef OPS_GPU
  double *p_a1 = (double *)((char *)args[1].data);
#else
  double *p_a1 = (double *)((char *)args[1].data + base1);
#endif

  int base2 = args[2].dat->base_offset +
              args[2].dat->elem_size * start[0] * args[2].stencil->stride[0];
  base2 = base2 +
          args[2].dat->elem_size * args[2].dat->size[0] * start[1] *
              args[2].stencil->stride[1];
#ifdef OPS_GPU
  double *p_a2 = (double *)((char *)args[2].data);
#else
  double *p_a2 = (double *)((char *)args[2].data + base2);
#endif

  int base3 = args[3].dat->base_offset +
              args[3].dat->elem_size * start[0] * args[3].stencil->stride[0];
  base3 = base3 +
          args[3].dat->elem_size * args[3].dat->size[0] * start[1] *
              args[3].stencil->stride[1];
#ifdef OPS_GPU
  double *p_a3 = (double *)((char *)args[3].data);
#else
  double *p_a3 = (double *)((char *)args[3].data + base3);
#endif

  int base4 = args[4].dat->base_offset +
              args[4].dat->elem_size * start[0] * args[4].stencil->stride[0];
  base4 = base4 +
          args[4].dat->elem_size * args[4].dat->size[0] * start[1] *
              args[4].stencil->stride[1];
#ifdef OPS_GPU
  double *p_a4 = (double *)((char *)args[4].data);
#else
  double *p_a4 = (double *)((char *)args[4].data + base4);
#endif

  int base5 = args[5].dat->base_offset +
              args[5].dat->elem_size * start[0] * args[5].stencil->stride[0];
  base5 = base5 +
          args[5].dat->elem_size * args[5].dat->size[0] * start[1] *
              args[5].stencil->stride[1];
#ifdef OPS_GPU
  double *p_a5 = (double *)((char *)args[5].data);
#else
  double *p_a5 = (double *)((char *)args[5].data + base5);
#endif

  int base6 = args[6].dat->base_offset +
              args[6].dat->elem_size * start[0] * args[6].stencil->stride[0];
  base6 = base6 +
          args[6].dat->elem_size * args[6].dat->size[0] * start[1] *
              args[6].stencil->stride[1];
#ifdef OPS_GPU
  double *p_a6 = (double *)((char *)args[6].data);
#else
  double *p_a6 = (double *)((char *)args[6].data + base6);
#endif

#ifdef OPS_GPU
  int *p_a7 = (int *)args[7].data;
#else
  int *p_a7 = arg7h;
#endif

#ifdef OPS_GPU
  for (int n = 0; n < 8; n++)
    if (args[n].argtype == OPS_ARG_DAT && args[n].dat->dirty_hd == 1) {
      int size = 1;
      for (int i = 0; i < args[n].dat->block->dims; i++)
        size += size * args[n].dat->size[i];
#pragma omp target update to(args[n].dat->data[0 : size])
      args[n].dat->dirty_hd = 0;
    }
// ops_H_D_exchanges_device(args, 8);
#else
  for (int n = 0; n < 8; n++)
    if (args[n].argtype == OPS_ARG_DAT && args[n].dat->dirty_hd == 2) {
      int size = 1;
      for (int i = 0; i < args[n].dat->block->dims; i++)
        size += size * args[n].dat->size[i];
#pragma omp target update from(args[n].dat->data[0 : size])
      args[n].dat->dirty_hd = 0;
    }
// ops_H_D_exchanges_host(args, 8);
#endif
  ops_halo_exchanges(args, 8, range);

#ifdef OPS_GPU
// ops_H_D_exchanges_device(args, 8);
#else
// ops_H_D_exchanges_host(args, 8);
#endif
  if (OPS_diags > 1) {
    ops_timers_core(&c2, &t2);
    OPS_kernels[49].mpi_time += t2 - t1;
  }

  update_halo_kernel1_r2_c_wrapper(p_a0, base0 / args[0].dat->elem_size, tot0,
                                   p_a1, base1 / args[1].dat->elem_size, tot1,
                                   p_a2, base2 / args[2].dat->elem_size, tot2,
                                   p_a3, base3 / args[3].dat->elem_size, tot3,
                                   p_a4, base4 / args[4].dat->elem_size, tot4,
                                   p_a5, base5 / args[5].dat->elem_size, tot5,
                                   p_a6, base6 / args[6].dat->elem_size, tot6,
                                   p_a7, NUM_FIELDS, x_size, y_size);

  if (OPS_diags > 1) {
    ops_timers_core(&c1, &t1);
    OPS_kernels[49].time += t1 - t2;
  }
#ifdef OPS_GPU
  // for (int n = 0; n < 8; n++) {
  // if ((args[n].argtype == OPS_ARG_DAT) &&
  //(args[n].acc == OPS_INC || args[n].acc == OPS_WRITE ||
  // args[n].acc == OPS_RW)) {
  // args[n].dat->dirty_hd = 2;
  //}
  //}
  ops_set_dirtybit_device(args, 8);
#else
  // for (int n = 0; n < 8; n++) {
  // if ((args[n].argtype == OPS_ARG_DAT) &&
  //(args[n].acc == OPS_INC || args[n].acc == OPS_WRITE ||
  // args[n].acc == OPS_RW)) {
  // args[n].dat->dirty_hd = 1;
  //}
  //}
  ops_set_dirtybit_host(args, 8);
#endif
  ops_set_halo_dirtybit3(&args[0], range);
  ops_set_halo_dirtybit3(&args[1], range);
  ops_set_halo_dirtybit3(&args[2], range);
  ops_set_halo_dirtybit3(&args[3], range);
  ops_set_halo_dirtybit3(&args[4], range);
  ops_set_halo_dirtybit3(&args[5], range);
  ops_set_halo_dirtybit3(&args[6], range);

  if (OPS_diags > 1) {
    // Update kernel record
    ops_timers_core(&c2, &t2);
    OPS_kernels[49].mpi_time += t2 - t1;
    OPS_kernels[49].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[49].transfer += ops_compute_transfer(dim, start, end, &arg1);
    OPS_kernels[49].transfer += ops_compute_transfer(dim, start, end, &arg2);
    OPS_kernels[49].transfer += ops_compute_transfer(dim, start, end, &arg3);
    OPS_kernels[49].transfer += ops_compute_transfer(dim, start, end, &arg4);
    OPS_kernels[49].transfer += ops_compute_transfer(dim, start, end, &arg5);
    OPS_kernels[49].transfer += ops_compute_transfer(dim, start, end, &arg6);
  }
}
