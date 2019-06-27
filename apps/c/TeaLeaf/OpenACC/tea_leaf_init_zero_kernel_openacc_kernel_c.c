//
// auto-generated by ops.py
//

#define OPS_GPU

int xdim0_tea_leaf_init_zero_kernel;

// user function
#pragma acc routine
inline void tea_leaf_init_zero_kernel(ptr_double p) { OPS_ACC(p, 0, 0) = 0.0; }

void tea_leaf_init_zero_kernel_c_wrapper(double *p_a0, int x_size, int y_size) {
#ifdef OPS_GPU
#pragma acc parallel deviceptr(p_a0)
#pragma acc loop
#endif
  for (int n_y = 0; n_y < y_size; n_y++) {
#ifdef OPS_GPU
#pragma acc loop
#endif
    for (int n_x = 0; n_x < x_size; n_x++) {
      ptr_double ptr0 = {p_a0 + n_x * 1 * 1 +
                             n_y * xdim0_tea_leaf_init_zero_kernel * 1 * 1,
                         xdim0_tea_leaf_init_zero_kernel};
      tea_leaf_init_zero_kernel(ptr0);
    }
  }
}
