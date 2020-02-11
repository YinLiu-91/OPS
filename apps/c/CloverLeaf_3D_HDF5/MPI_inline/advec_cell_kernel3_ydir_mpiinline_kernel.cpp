//
// auto-generated by ops.py
//

extern int xdim0_advec_cell_kernel3_ydir;
int xdim0_advec_cell_kernel3_ydir_h = -1;
extern int ydim0_advec_cell_kernel3_ydir;
int ydim0_advec_cell_kernel3_ydir_h = -1;
extern int xdim1_advec_cell_kernel3_ydir;
int xdim1_advec_cell_kernel3_ydir_h = -1;
extern int ydim1_advec_cell_kernel3_ydir;
int ydim1_advec_cell_kernel3_ydir_h = -1;
extern int xdim2_advec_cell_kernel3_ydir;
int xdim2_advec_cell_kernel3_ydir_h = -1;
extern int ydim2_advec_cell_kernel3_ydir;
int ydim2_advec_cell_kernel3_ydir_h = -1;
extern int xdim3_advec_cell_kernel3_ydir;
int xdim3_advec_cell_kernel3_ydir_h = -1;
extern int ydim3_advec_cell_kernel3_ydir;
int ydim3_advec_cell_kernel3_ydir_h = -1;
extern int xdim4_advec_cell_kernel3_ydir;
int xdim4_advec_cell_kernel3_ydir_h = -1;
extern int ydim4_advec_cell_kernel3_ydir;
int ydim4_advec_cell_kernel3_ydir_h = -1;
extern int xdim5_advec_cell_kernel3_ydir;
int xdim5_advec_cell_kernel3_ydir_h = -1;
extern int ydim5_advec_cell_kernel3_ydir;
int ydim5_advec_cell_kernel3_ydir_h = -1;
extern int xdim6_advec_cell_kernel3_ydir;
int xdim6_advec_cell_kernel3_ydir_h = -1;
extern int ydim6_advec_cell_kernel3_ydir;
int ydim6_advec_cell_kernel3_ydir_h = -1;
extern int xdim7_advec_cell_kernel3_ydir;
int xdim7_advec_cell_kernel3_ydir_h = -1;
extern int ydim7_advec_cell_kernel3_ydir;
int ydim7_advec_cell_kernel3_ydir_h = -1;

#ifdef __cplusplus
extern "C" {
#endif
void advec_cell_kernel3_ydir_c_wrapper(double *p_a0, double *p_a1, int *p_a2,
                                       double *p_a3, double *p_a4, double *p_a5,
                                       double *p_a6, double *p_a7, int x_size,
                                       int y_size, int z_size);

#ifdef __cplusplus
}
#endif

// host stub function
void ops_par_loop_advec_cell_kernel3_ydir(char const *name, ops_block block,
                                          int dim, int *range, ops_arg arg0,
                                          ops_arg arg1, ops_arg arg2,
                                          ops_arg arg3, ops_arg arg4,
                                          ops_arg arg5, ops_arg arg6,
                                          ops_arg arg7) {

  ops_arg args[8] = {arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7};

#ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args, 8, range, 114))
    return;
#endif

  if (block->instance->OPS_diags > 1) {
    ops_timing_realloc(block->instance, 114, "advec_cell_kernel3_ydir");
    block->instance->OPS_kernels[114].count++;
  }

  // compute localy allocated range for the sub-block
  int start[3];
  int end[3];
  int arg_idx[3];

#ifdef OPS_MPI
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (compute_ranges(args, 8, block, range, start, end, arg_idx) < 0)
    return;
#else
  for (int n = 0; n < 3; n++) {
    start[n] = range[2 * n];
    end[n] = range[2 * n + 1];
    arg_idx[n] = start[n];
  }
#endif

  int x_size = MAX(0, end[0] - start[0]);
  int y_size = MAX(0, end[1] - start[1]);
  int z_size = MAX(0, end[2] - start[2]);

  int xdim0 = args[0].dat->size[0];
  int ydim0 = args[0].dat->size[1];
  int xdim1 = args[1].dat->size[0];
  int ydim1 = args[1].dat->size[1];
  int xdim2 = args[2].dat->size[0];
  int ydim2 = args[2].dat->size[1];
  int xdim3 = args[3].dat->size[0];
  int ydim3 = args[3].dat->size[1];
  int xdim4 = args[4].dat->size[0];
  int ydim4 = args[4].dat->size[1];
  int xdim5 = args[5].dat->size[0];
  int ydim5 = args[5].dat->size[1];
  int xdim6 = args[6].dat->size[0];
  int ydim6 = args[6].dat->size[1];
  int xdim7 = args[7].dat->size[0];
  int ydim7 = args[7].dat->size[1];

  // Timing
  double t1, t2, c1, c2;
  if (block->instance->OPS_diags > 1) {
    ops_timers_core(&c2, &t2);
  }

  if (xdim0 != xdim0_advec_cell_kernel3_ydir_h ||
      ydim0 != ydim0_advec_cell_kernel3_ydir_h ||
      xdim1 != xdim1_advec_cell_kernel3_ydir_h ||
      ydim1 != ydim1_advec_cell_kernel3_ydir_h ||
      xdim2 != xdim2_advec_cell_kernel3_ydir_h ||
      ydim2 != ydim2_advec_cell_kernel3_ydir_h ||
      xdim3 != xdim3_advec_cell_kernel3_ydir_h ||
      ydim3 != ydim3_advec_cell_kernel3_ydir_h ||
      xdim4 != xdim4_advec_cell_kernel3_ydir_h ||
      ydim4 != ydim4_advec_cell_kernel3_ydir_h ||
      xdim5 != xdim5_advec_cell_kernel3_ydir_h ||
      ydim5 != ydim5_advec_cell_kernel3_ydir_h ||
      xdim6 != xdim6_advec_cell_kernel3_ydir_h ||
      ydim6 != ydim6_advec_cell_kernel3_ydir_h ||
      xdim7 != xdim7_advec_cell_kernel3_ydir_h ||
      ydim7 != ydim7_advec_cell_kernel3_ydir_h) {
    xdim0_advec_cell_kernel3_ydir = xdim0;
    xdim0_advec_cell_kernel3_ydir_h = xdim0;
    ydim0_advec_cell_kernel3_ydir = ydim0;
    ydim0_advec_cell_kernel3_ydir_h = ydim0;
    xdim1_advec_cell_kernel3_ydir = xdim1;
    xdim1_advec_cell_kernel3_ydir_h = xdim1;
    ydim1_advec_cell_kernel3_ydir = ydim1;
    ydim1_advec_cell_kernel3_ydir_h = ydim1;
    xdim2_advec_cell_kernel3_ydir = xdim2;
    xdim2_advec_cell_kernel3_ydir_h = xdim2;
    ydim2_advec_cell_kernel3_ydir = ydim2;
    ydim2_advec_cell_kernel3_ydir_h = ydim2;
    xdim3_advec_cell_kernel3_ydir = xdim3;
    xdim3_advec_cell_kernel3_ydir_h = xdim3;
    ydim3_advec_cell_kernel3_ydir = ydim3;
    ydim3_advec_cell_kernel3_ydir_h = ydim3;
    xdim4_advec_cell_kernel3_ydir = xdim4;
    xdim4_advec_cell_kernel3_ydir_h = xdim4;
    ydim4_advec_cell_kernel3_ydir = ydim4;
    ydim4_advec_cell_kernel3_ydir_h = ydim4;
    xdim5_advec_cell_kernel3_ydir = xdim5;
    xdim5_advec_cell_kernel3_ydir_h = xdim5;
    ydim5_advec_cell_kernel3_ydir = ydim5;
    ydim5_advec_cell_kernel3_ydir_h = ydim5;
    xdim6_advec_cell_kernel3_ydir = xdim6;
    xdim6_advec_cell_kernel3_ydir_h = xdim6;
    ydim6_advec_cell_kernel3_ydir = ydim6;
    ydim6_advec_cell_kernel3_ydir_h = ydim6;
    xdim7_advec_cell_kernel3_ydir = xdim7;
    xdim7_advec_cell_kernel3_ydir_h = xdim7;
    ydim7_advec_cell_kernel3_ydir = ydim7;
    ydim7_advec_cell_kernel3_ydir_h = ydim7;
  }

  int dat0 = (block->instance->OPS_soa ? args[0].dat->type_size
                                       : args[0].dat->elem_size);
  int dat1 = (block->instance->OPS_soa ? args[1].dat->type_size
                                       : args[1].dat->elem_size);
  int dat2 = (block->instance->OPS_soa ? args[2].dat->type_size
                                       : args[2].dat->elem_size);
  int dat3 = (block->instance->OPS_soa ? args[3].dat->type_size
                                       : args[3].dat->elem_size);
  int dat4 = (block->instance->OPS_soa ? args[4].dat->type_size
                                       : args[4].dat->elem_size);
  int dat5 = (block->instance->OPS_soa ? args[5].dat->type_size
                                       : args[5].dat->elem_size);
  int dat6 = (block->instance->OPS_soa ? args[6].dat->type_size
                                       : args[6].dat->elem_size);
  int dat7 = (block->instance->OPS_soa ? args[7].dat->type_size
                                       : args[7].dat->elem_size);

  // set up initial pointers and exchange halos if necessary
  int base0 = args[0].dat->base_offset +
              (block->instance->OPS_soa ? args[0].dat->type_size
                                        : args[0].dat->elem_size) *
                  start[0] * args[0].stencil->stride[0];
  base0 = base0 +
          (block->instance->OPS_soa ? args[0].dat->type_size
                                    : args[0].dat->elem_size) *
              args[0].dat->size[0] * start[1] * args[0].stencil->stride[1];
  base0 = base0 +
          (block->instance->OPS_soa ? args[0].dat->type_size
                                    : args[0].dat->elem_size) *
              args[0].dat->size[0] * args[0].dat->size[1] * start[2] *
              args[0].stencil->stride[2];
  double *p_a0 = (double *)(args[0].data + base0);

  int base1 = args[1].dat->base_offset +
              (block->instance->OPS_soa ? args[1].dat->type_size
                                        : args[1].dat->elem_size) *
                  start[0] * args[1].stencil->stride[0];
  base1 = base1 +
          (block->instance->OPS_soa ? args[1].dat->type_size
                                    : args[1].dat->elem_size) *
              args[1].dat->size[0] * start[1] * args[1].stencil->stride[1];
  base1 = base1 +
          (block->instance->OPS_soa ? args[1].dat->type_size
                                    : args[1].dat->elem_size) *
              args[1].dat->size[0] * args[1].dat->size[1] * start[2] *
              args[1].stencil->stride[2];
  double *p_a1 = (double *)(args[1].data + base1);

  int base2 = args[2].dat->base_offset +
              (block->instance->OPS_soa ? args[2].dat->type_size
                                        : args[2].dat->elem_size) *
                  start[0] * args[2].stencil->stride[0];
  base2 = base2 +
          (block->instance->OPS_soa ? args[2].dat->type_size
                                    : args[2].dat->elem_size) *
              args[2].dat->size[0] * start[1] * args[2].stencil->stride[1];
  base2 = base2 +
          (block->instance->OPS_soa ? args[2].dat->type_size
                                    : args[2].dat->elem_size) *
              args[2].dat->size[0] * args[2].dat->size[1] * start[2] *
              args[2].stencil->stride[2];
  int *p_a2 = (int *)(args[2].data + base2);

  int base3 = args[3].dat->base_offset +
              (block->instance->OPS_soa ? args[3].dat->type_size
                                        : args[3].dat->elem_size) *
                  start[0] * args[3].stencil->stride[0];
  base3 = base3 +
          (block->instance->OPS_soa ? args[3].dat->type_size
                                    : args[3].dat->elem_size) *
              args[3].dat->size[0] * start[1] * args[3].stencil->stride[1];
  base3 = base3 +
          (block->instance->OPS_soa ? args[3].dat->type_size
                                    : args[3].dat->elem_size) *
              args[3].dat->size[0] * args[3].dat->size[1] * start[2] *
              args[3].stencil->stride[2];
  double *p_a3 = (double *)(args[3].data + base3);

  int base4 = args[4].dat->base_offset +
              (block->instance->OPS_soa ? args[4].dat->type_size
                                        : args[4].dat->elem_size) *
                  start[0] * args[4].stencil->stride[0];
  base4 = base4 +
          (block->instance->OPS_soa ? args[4].dat->type_size
                                    : args[4].dat->elem_size) *
              args[4].dat->size[0] * start[1] * args[4].stencil->stride[1];
  base4 = base4 +
          (block->instance->OPS_soa ? args[4].dat->type_size
                                    : args[4].dat->elem_size) *
              args[4].dat->size[0] * args[4].dat->size[1] * start[2] *
              args[4].stencil->stride[2];
  double *p_a4 = (double *)(args[4].data + base4);

  int base5 = args[5].dat->base_offset +
              (block->instance->OPS_soa ? args[5].dat->type_size
                                        : args[5].dat->elem_size) *
                  start[0] * args[5].stencil->stride[0];
  base5 = base5 +
          (block->instance->OPS_soa ? args[5].dat->type_size
                                    : args[5].dat->elem_size) *
              args[5].dat->size[0] * start[1] * args[5].stencil->stride[1];
  base5 = base5 +
          (block->instance->OPS_soa ? args[5].dat->type_size
                                    : args[5].dat->elem_size) *
              args[5].dat->size[0] * args[5].dat->size[1] * start[2] *
              args[5].stencil->stride[2];
  double *p_a5 = (double *)(args[5].data + base5);

  int base6 = args[6].dat->base_offset +
              (block->instance->OPS_soa ? args[6].dat->type_size
                                        : args[6].dat->elem_size) *
                  start[0] * args[6].stencil->stride[0];
  base6 = base6 +
          (block->instance->OPS_soa ? args[6].dat->type_size
                                    : args[6].dat->elem_size) *
              args[6].dat->size[0] * start[1] * args[6].stencil->stride[1];
  base6 = base6 +
          (block->instance->OPS_soa ? args[6].dat->type_size
                                    : args[6].dat->elem_size) *
              args[6].dat->size[0] * args[6].dat->size[1] * start[2] *
              args[6].stencil->stride[2];
  double *p_a6 = (double *)(args[6].data + base6);

  int base7 = args[7].dat->base_offset +
              (block->instance->OPS_soa ? args[7].dat->type_size
                                        : args[7].dat->elem_size) *
                  start[0] * args[7].stencil->stride[0];
  base7 = base7 +
          (block->instance->OPS_soa ? args[7].dat->type_size
                                    : args[7].dat->elem_size) *
              args[7].dat->size[0] * start[1] * args[7].stencil->stride[1];
  base7 = base7 +
          (block->instance->OPS_soa ? args[7].dat->type_size
                                    : args[7].dat->elem_size) *
              args[7].dat->size[0] * args[7].dat->size[1] * start[2] *
              args[7].stencil->stride[2];
  double *p_a7 = (double *)(args[7].data + base7);

  ops_H_D_exchanges_host(args, 8);
  ops_halo_exchanges(args, 8, range);

  if (block->instance->OPS_diags > 1) {
    ops_timers_core(&c1, &t1);
    block->instance->OPS_kernels[114].mpi_time += t1 - t2;
  }

  advec_cell_kernel3_ydir_c_wrapper(p_a0, p_a1, p_a2, p_a3, p_a4, p_a5, p_a6,
                                    p_a7, x_size, y_size, z_size);

  if (block->instance->OPS_diags > 1) {
    ops_timers_core(&c2, &t2);
    block->instance->OPS_kernels[114].time += t2 - t1;
  }
  ops_set_dirtybit_host(args, 8);
  ops_set_halo_dirtybit3(&args[6], range);
  ops_set_halo_dirtybit3(&args[7], range);

  // Update kernel record
  if (block->instance->OPS_diags > 1) {
    block->instance->OPS_kernels[114].transfer +=
        ops_compute_transfer(dim, start, end, &arg0);
    block->instance->OPS_kernels[114].transfer +=
        ops_compute_transfer(dim, start, end, &arg1);
    block->instance->OPS_kernels[114].transfer +=
        ops_compute_transfer(dim, start, end, &arg2);
    block->instance->OPS_kernels[114].transfer +=
        ops_compute_transfer(dim, start, end, &arg3);
    block->instance->OPS_kernels[114].transfer +=
        ops_compute_transfer(dim, start, end, &arg4);
    block->instance->OPS_kernels[114].transfer +=
        ops_compute_transfer(dim, start, end, &arg5);
    block->instance->OPS_kernels[114].transfer +=
        ops_compute_transfer(dim, start, end, &arg6);
    block->instance->OPS_kernels[114].transfer +=
        ops_compute_transfer(dim, start, end, &arg7);
  }
}
