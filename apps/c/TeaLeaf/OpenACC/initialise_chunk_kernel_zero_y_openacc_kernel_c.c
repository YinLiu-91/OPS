//
// auto-generated by ops.py
//

#define OPS_GPU

int xdim0_initialise_chunk_kernel_zero_y;

// user function
#pragma acc routine
inline void initialise_chunk_kernel_zero_y(ptr_double var) {
  OPS_ACC(var, 0, 0) = 0.0;
}

void initialise_chunk_kernel_zero_y_c_wrapper(double *p_a0, int x_size,
                                              int y_size) {
#ifdef OPS_GPU
#pragma acc parallel deviceptr(p_a0)
#pragma acc loop
#endif
  for (int n_y = 0; n_y < y_size; n_y++) {
#ifdef OPS_GPU
#pragma acc loop
#endif
    for (int n_x = 0; n_x < x_size; n_x++) {
      ptr_double ptr0 = {p_a0 + n_x * 0 * 1 +
                             n_y * xdim0_initialise_chunk_kernel_zero_y * 1 * 1,
                         xdim0_initialise_chunk_kernel_zero_y};
      initialise_chunk_kernel_zero_y(ptr0);
    }
  }
}
