//
// auto-generated by ops.py
//
#include "./OpenMP4/PdV_kernel_nopredict_openmp4_kernel_c.c"
#include "./OpenMP4/clover_leaf_common.h"

#define OPS_GPU

int xdim0_PdV_kernel_nopredict;
int xdim0_PdV_kernel_nopredict_h = -1;
int xdim1_PdV_kernel_nopredict;
int xdim1_PdV_kernel_nopredict_h = -1;
int xdim2_PdV_kernel_nopredict;
int xdim2_PdV_kernel_nopredict_h = -1;
int xdim3_PdV_kernel_nopredict;
int xdim3_PdV_kernel_nopredict_h = -1;
int xdim4_PdV_kernel_nopredict;
int xdim4_PdV_kernel_nopredict_h = -1;
int xdim5_PdV_kernel_nopredict;
int xdim5_PdV_kernel_nopredict_h = -1;
int xdim6_PdV_kernel_nopredict;
int xdim6_PdV_kernel_nopredict_h = -1;
int xdim7_PdV_kernel_nopredict;
int xdim7_PdV_kernel_nopredict_h = -1;
int xdim8_PdV_kernel_nopredict;
int xdim8_PdV_kernel_nopredict_h = -1;
int xdim9_PdV_kernel_nopredict;
int xdim9_PdV_kernel_nopredict_h = -1;
int xdim10_PdV_kernel_nopredict;
int xdim10_PdV_kernel_nopredict_h = -1;
int xdim11_PdV_kernel_nopredict;
int xdim11_PdV_kernel_nopredict_h = -1;
int xdim12_PdV_kernel_nopredict;
int xdim12_PdV_kernel_nopredict_h = -1;
int xdim13_PdV_kernel_nopredict;
int xdim13_PdV_kernel_nopredict_h = -1;

void ops_par_loop_PdV_kernel_nopredict(char const *name, ops_block block,
                                       int dim, int *range, ops_arg arg0,
                                       ops_arg arg1, ops_arg arg2, ops_arg arg3,
                                       ops_arg arg4, ops_arg arg5, ops_arg arg6,
                                       ops_arg arg7, ops_arg arg8, ops_arg arg9,
                                       ops_arg arg10, ops_arg arg11,
                                       ops_arg arg12, ops_arg arg13) {

  // Timing
  double t1, t2, c1, c2;
  ops_arg args[14] = {arg0, arg1, arg2, arg3,  arg4,  arg5,  arg6,
                      arg7, arg8, arg9, arg10, arg11, arg12, arg13};

#ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args, 14, range, 5))
    return;
#endif

  if (OPS_diags > 1) {
    ops_timing_realloc(5, "PdV_kernel_nopredict");
    OPS_kernels[5].count++;
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
  xdim7 = args[7].dat->size[0];
  xdim8 = args[8].dat->size[0];
  xdim9 = args[9].dat->size[0];
  xdim10 = args[10].dat->size[0];
  xdim11 = args[11].dat->size[0];
  xdim12 = args[12].dat->size[0];
  xdim13 = args[13].dat->size[0];
  if (xdim0 != xdim0_PdV_kernel_nopredict_h ||
      xdim1 != xdim1_PdV_kernel_nopredict_h ||
      xdim2 != xdim2_PdV_kernel_nopredict_h ||
      xdim3 != xdim3_PdV_kernel_nopredict_h ||
      xdim4 != xdim4_PdV_kernel_nopredict_h ||
      xdim5 != xdim5_PdV_kernel_nopredict_h ||
      xdim6 != xdim6_PdV_kernel_nopredict_h ||
      xdim7 != xdim7_PdV_kernel_nopredict_h ||
      xdim8 != xdim8_PdV_kernel_nopredict_h ||
      xdim9 != xdim9_PdV_kernel_nopredict_h ||
      xdim10 != xdim10_PdV_kernel_nopredict_h ||
      xdim11 != xdim11_PdV_kernel_nopredict_h ||
      xdim12 != xdim12_PdV_kernel_nopredict_h ||
      xdim13 != xdim13_PdV_kernel_nopredict_h) {
    xdim0_PdV_kernel_nopredict = xdim0;
    xdim0_PdV_kernel_nopredict_h = xdim0;
    xdim1_PdV_kernel_nopredict = xdim1;
    xdim1_PdV_kernel_nopredict_h = xdim1;
    xdim2_PdV_kernel_nopredict = xdim2;
    xdim2_PdV_kernel_nopredict_h = xdim2;
    xdim3_PdV_kernel_nopredict = xdim3;
    xdim3_PdV_kernel_nopredict_h = xdim3;
    xdim4_PdV_kernel_nopredict = xdim4;
    xdim4_PdV_kernel_nopredict_h = xdim4;
    xdim5_PdV_kernel_nopredict = xdim5;
    xdim5_PdV_kernel_nopredict_h = xdim5;
    xdim6_PdV_kernel_nopredict = xdim6;
    xdim6_PdV_kernel_nopredict_h = xdim6;
    xdim7_PdV_kernel_nopredict = xdim7;
    xdim7_PdV_kernel_nopredict_h = xdim7;
    xdim8_PdV_kernel_nopredict = xdim8;
    xdim8_PdV_kernel_nopredict_h = xdim8;
    xdim9_PdV_kernel_nopredict = xdim9;
    xdim9_PdV_kernel_nopredict_h = xdim9;
    xdim10_PdV_kernel_nopredict = xdim10;
    xdim10_PdV_kernel_nopredict_h = xdim10;
    xdim11_PdV_kernel_nopredict = xdim11;
    xdim11_PdV_kernel_nopredict_h = xdim11;
    xdim12_PdV_kernel_nopredict = xdim12;
    xdim12_PdV_kernel_nopredict_h = xdim12;
    xdim13_PdV_kernel_nopredict = xdim13;
    xdim13_PdV_kernel_nopredict_h = xdim13;
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
  int tot7 = 1;
  for (int i = 0; i < args[7].dat->block->dims; i++)
    tot7 = tot7 * args[7].dat->size[i];
  int tot8 = 1;
  for (int i = 0; i < args[8].dat->block->dims; i++)
    tot8 = tot8 * args[8].dat->size[i];
  int tot9 = 1;
  for (int i = 0; i < args[9].dat->block->dims; i++)
    tot9 = tot9 * args[9].dat->size[i];
  int tot10 = 1;
  for (int i = 0; i < args[10].dat->block->dims; i++)
    tot10 = tot10 * args[10].dat->size[i];
  int tot11 = 1;
  for (int i = 0; i < args[11].dat->block->dims; i++)
    tot11 = tot11 * args[11].dat->size[i];
  int tot12 = 1;
  for (int i = 0; i < args[12].dat->block->dims; i++)
    tot12 = tot12 * args[12].dat->size[i];
  int tot13 = 1;
  for (int i = 0; i < args[13].dat->block->dims; i++)
    tot13 = tot13 * args[13].dat->size[i];

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

  int base7 = args[7].dat->base_offset +
              args[7].dat->elem_size * start[0] * args[7].stencil->stride[0];
  base7 = base7 +
          args[7].dat->elem_size * args[7].dat->size[0] * start[1] *
              args[7].stencil->stride[1];
#ifdef OPS_GPU
  double *p_a7 = (double *)((char *)args[7].data);
#else
  double *p_a7 = (double *)((char *)args[7].data + base7);
#endif

  int base8 = args[8].dat->base_offset +
              args[8].dat->elem_size * start[0] * args[8].stencil->stride[0];
  base8 = base8 +
          args[8].dat->elem_size * args[8].dat->size[0] * start[1] *
              args[8].stencil->stride[1];
#ifdef OPS_GPU
  double *p_a8 = (double *)((char *)args[8].data);
#else
  double *p_a8 = (double *)((char *)args[8].data + base8);
#endif

  int base9 = args[9].dat->base_offset +
              args[9].dat->elem_size * start[0] * args[9].stencil->stride[0];
  base9 = base9 +
          args[9].dat->elem_size * args[9].dat->size[0] * start[1] *
              args[9].stencil->stride[1];
#ifdef OPS_GPU
  double *p_a9 = (double *)((char *)args[9].data);
#else
  double *p_a9 = (double *)((char *)args[9].data + base9);
#endif

  int base10 = args[10].dat->base_offset +
               args[10].dat->elem_size * start[0] * args[10].stencil->stride[0];
  base10 = base10 +
           args[10].dat->elem_size * args[10].dat->size[0] * start[1] *
               args[10].stencil->stride[1];
#ifdef OPS_GPU
  double *p_a10 = (double *)((char *)args[10].data);
#else
  double *p_a10 = (double *)((char *)args[10].data + base10);
#endif

  int base11 = args[11].dat->base_offset +
               args[11].dat->elem_size * start[0] * args[11].stencil->stride[0];
  base11 = base11 +
           args[11].dat->elem_size * args[11].dat->size[0] * start[1] *
               args[11].stencil->stride[1];
#ifdef OPS_GPU
  double *p_a11 = (double *)((char *)args[11].data);
#else
  double *p_a11 = (double *)((char *)args[11].data + base11);
#endif

  int base12 = args[12].dat->base_offset +
               args[12].dat->elem_size * start[0] * args[12].stencil->stride[0];
  base12 = base12 +
           args[12].dat->elem_size * args[12].dat->size[0] * start[1] *
               args[12].stencil->stride[1];
#ifdef OPS_GPU
  double *p_a12 = (double *)((char *)args[12].data);
#else
  double *p_a12 = (double *)((char *)args[12].data + base12);
#endif

  int base13 = args[13].dat->base_offset +
               args[13].dat->elem_size * start[0] * args[13].stencil->stride[0];
  base13 = base13 +
           args[13].dat->elem_size * args[13].dat->size[0] * start[1] *
               args[13].stencil->stride[1];
#ifdef OPS_GPU
  double *p_a13 = (double *)((char *)args[13].data);
#else
  double *p_a13 = (double *)((char *)args[13].data + base13);
#endif

#ifdef OPS_GPU
  for (int n = 0; n < 14; n++)
    if (args[n].argtype == OPS_ARG_DAT && args[n].dat->dirty_hd == 1) {
      int size = 1;
      for (int i = 0; i < args[n].dat->block->dims; i++)
        size += size * args[n].dat->size[i];
#pragma omp target update to(args[n].dat->data[0 : size])
      args[n].dat->dirty_hd = 0;
    }
// ops_H_D_exchanges_device(args, 14);
#else
  for (int n = 0; n < 14; n++)
    if (args[n].argtype == OPS_ARG_DAT && args[n].dat->dirty_hd == 2) {
      int size = 1;
      for (int i = 0; i < args[n].dat->block->dims; i++)
        size += size * args[n].dat->size[i];
#pragma omp target update from(args[n].dat->data[0 : size])
      args[n].dat->dirty_hd = 0;
    }
// ops_H_D_exchanges_host(args, 14);
#endif
  ops_halo_exchanges(args, 14, range);

#ifdef OPS_GPU
// ops_H_D_exchanges_device(args, 14);
#else
// ops_H_D_exchanges_host(args, 14);
#endif
  if (OPS_diags > 1) {
    ops_timers_core(&c2, &t2);
    OPS_kernels[5].mpi_time += t2 - t1;
  }

  PdV_kernel_nopredict_c_wrapper(p_a0, base0 / args[0].dat->elem_size, tot0,
                                 p_a1, base1 / args[1].dat->elem_size, tot1,
                                 p_a2, base2 / args[2].dat->elem_size, tot2,
                                 p_a3, base3 / args[3].dat->elem_size, tot3,
                                 p_a4, base4 / args[4].dat->elem_size, tot4,
                                 p_a5, base5 / args[5].dat->elem_size, tot5,
                                 p_a6, base6 / args[6].dat->elem_size, tot6,
                                 p_a7, base7 / args[7].dat->elem_size, tot7,
                                 p_a8, base8 / args[8].dat->elem_size, tot8,
                                 p_a9, base9 / args[9].dat->elem_size, tot9,
                                 p_a10, base10 / args[10].dat->elem_size, tot10,
                                 p_a11, base11 / args[11].dat->elem_size, tot11,
                                 p_a12, base12 / args[12].dat->elem_size, tot12,
                                 p_a13, base13 / args[13].dat->elem_size, tot13,
                                 x_size, y_size);

  if (OPS_diags > 1) {
    ops_timers_core(&c1, &t1);
    OPS_kernels[5].time += t1 - t2;
  }
#ifdef OPS_GPU
  // for (int n = 0; n < 14; n++) {
  // if ((args[n].argtype == OPS_ARG_DAT) &&
  //(args[n].acc == OPS_INC || args[n].acc == OPS_WRITE ||
  // args[n].acc == OPS_RW)) {
  // args[n].dat->dirty_hd = 2;
  //}
  //}
  ops_set_dirtybit_device(args, 14);
#else
  // for (int n = 0; n < 14; n++) {
  // if ((args[n].argtype == OPS_ARG_DAT) &&
  //(args[n].acc == OPS_INC || args[n].acc == OPS_WRITE ||
  // args[n].acc == OPS_RW)) {
  // args[n].dat->dirty_hd = 1;
  //}
  //}
  ops_set_dirtybit_host(args, 14);
#endif
  ops_set_halo_dirtybit3(&args[6], range);
  ops_set_halo_dirtybit3(&args[10], range);
  ops_set_halo_dirtybit3(&args[13], range);

  if (OPS_diags > 1) {
    // Update kernel record
    ops_timers_core(&c2, &t2);
    OPS_kernels[5].mpi_time += t2 - t1;
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg1);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg2);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg3);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg4);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg5);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg6);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg7);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg8);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg9);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg10);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg11);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg12);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg13);
  }
}
