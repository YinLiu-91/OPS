//
// auto-generated by ops.py
//

#define OPS_GPU

int xdim0_initialise_chunk_kernel_x;
int xdim1_initialise_chunk_kernel_x;
int xdim2_initialise_chunk_kernel_x;

// user function
#pragma acc routine
inline void initialise_chunk_kernel_x(ptr_double vertexx, const ptr_int xx,
                                      ptr_double vertexdx) {

  int x_min = field.x_min - 2;
  double min_x, d_x;

  d_x = (grid.xmax - grid.xmin) / (double)grid.x_cells;
  min_x = grid.xmin + d_x * field.left;

  OPS_ACC(vertexx, 0, 0) = min_x + d_x * (OPS_ACC(xx, 0, 0) - x_min);
  OPS_ACC(vertexdx, 0, 0) = (double)d_x;
}

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
      ptr_double ptr0 = {p_a0 + n_x * 1 * 1 +
                             n_y * xdim0_initialise_chunk_kernel_x * 0 * 1,
                         xdim0_initialise_chunk_kernel_x};
      const ptr_int ptr1 = {p_a1 + n_x * 1 * 1 +
                                n_y * xdim1_initialise_chunk_kernel_x * 0 * 1,
                            xdim1_initialise_chunk_kernel_x};
      ptr_double ptr2 = {p_a2 + n_x * 1 * 1 +
                             n_y * xdim2_initialise_chunk_kernel_x * 0 * 1,
                         xdim2_initialise_chunk_kernel_x};
      initialise_chunk_kernel_x(ptr0, ptr1, ptr2);
    }
  }
}
