//
// auto-generated by ops.py
//

#define OPS_GPU

int xdim0_initialise_chunk_kernel_x;
int xdim1_initialise_chunk_kernel_x;
int xdim2_initialise_chunk_kernel_x;

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2

#define OPS_ACC0(x, y) (x + xdim0_initialise_chunk_kernel_x * (y))
#define OPS_ACC1(x, y) (x + xdim1_initialise_chunk_kernel_x * (y))
#define OPS_ACC2(x, y) (x + xdim2_initialise_chunk_kernel_x * (y))

// user function
inline void initialise_chunk_kernel_x(double *vertexx, const int *xx,
                                      double *vertexdx) {

  int x_min = field.x_min - 2;
  double min_x, d_x;

  d_x = (grid.xmax - grid.xmin) / (double)grid.x_cells;
  min_x = grid.xmin + d_x * field.left;

  vertexx[OPS_ACC0(0, 0)] = min_x + d_x * (xx[OPS_ACC1(0, 0)] - x_min);
  vertexdx[OPS_ACC2(0, 0)] = (double)d_x;
}

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2

void initialise_chunk_kernel_x_c_wrapper(double *p_a0, int *p_a1, double *p_a2,
                                         int x_size, int y_size) {
#ifdef OPS_GPU
#pragma acc parallel deviceptr(p_a0, p_a1, p_a2)
#pragma acc loop
#endif
  for (int n_y = 0; n_y < y_size; n_y++) {
#ifdef OPS_GPU
#pragma acc loop
#endif
    for (int n_x = 0; n_x < x_size; n_x++) {
      initialise_chunk_kernel_x(
          p_a0 + n_x * 1 * 1 + n_y * xdim0_initialise_chunk_kernel_x * 0 * 1,
          p_a1 + n_x * 1 * 1 + n_y * xdim1_initialise_chunk_kernel_x * 0 * 1,
          p_a2 + n_x * 1 * 1 + n_y * xdim2_initialise_chunk_kernel_x * 0 * 1);
    }
  }
}
