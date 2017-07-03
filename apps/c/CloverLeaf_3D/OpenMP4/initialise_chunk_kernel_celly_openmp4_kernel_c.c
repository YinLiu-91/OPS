//
// auto-generated by ops.py
//
#include "./OpenMP4/clover_leaf_common.h"

#define OPS_GPU

extern int xdim0_initialise_chunk_kernel_celly;
extern int ydim0_initialise_chunk_kernel_celly;
extern int xdim1_initialise_chunk_kernel_celly;
extern int ydim1_initialise_chunk_kernel_celly;
extern int xdim2_initialise_chunk_kernel_celly;
extern int ydim2_initialise_chunk_kernel_celly;

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2

#define OPS_ACC0(x, y, z)                                                      \
  (x + xdim0_initialise_chunk_kernel_celly * (y) +                             \
   xdim0_initialise_chunk_kernel_celly * ydim0_initialise_chunk_kernel_celly * \
       (z))
#define OPS_ACC1(x, y, z)                                                      \
  (x + xdim1_initialise_chunk_kernel_celly * (y) +                             \
   xdim1_initialise_chunk_kernel_celly * ydim1_initialise_chunk_kernel_celly * \
       (z))
#define OPS_ACC2(x, y, z)                                                      \
  (x + xdim2_initialise_chunk_kernel_celly * (y) +                             \
   xdim2_initialise_chunk_kernel_celly * ydim2_initialise_chunk_kernel_celly * \
       (z))

// user function

void initialise_chunk_kernel_celly_c_wrapper(double *p_a0, int base0, int tot0,
                                             double *p_a1, int base1, int tot1,
                                             double *p_a2, int base2, int tot2,
                                             int x_size, int y_size,
                                             int z_size) {
#ifdef OPS_GPU

#pragma omp target teams distribute parallel for num_teams(OPS_threads)        \
    thread_limit(OPS_threads_for_block) collapse(3) schedule(static, 1)
#endif
  for (int n_z = 0; n_z < z_size; n_z++) {
    for (int n_y = 0; n_y < y_size; n_y++) {
      for (int n_x = 0; n_x < x_size; n_x++) {
        const double *vertexy =
            p_a0 + base0 + n_x * 0 * 1 +
            n_y * xdim0_initialise_chunk_kernel_celly * 1 * 1 +
            n_z * xdim0_initialise_chunk_kernel_celly *
                ydim0_initialise_chunk_kernel_celly * 0;

        double *celly = p_a1 + base1 + n_x * 0 * 1 +
                        n_y * xdim1_initialise_chunk_kernel_celly * 1 * 1 +
                        n_z * xdim1_initialise_chunk_kernel_celly *
                            ydim1_initialise_chunk_kernel_celly * 0;

        double *celldy = p_a2 + base2 + n_x * 0 * 1 +
                         n_y * xdim2_initialise_chunk_kernel_celly * 1 * 1 +
                         n_z * xdim2_initialise_chunk_kernel_celly *
                             ydim2_initialise_chunk_kernel_celly * 0;

        double d_y = (grid.ymax - grid.ymin) / (double)grid.y_cells;
        celly[OPS_ACC1(0, 0, 0)] =
            0.5 * (vertexy[OPS_ACC0(0, 0, 0)] + vertexy[OPS_ACC0(0, 1, 0)]);
        celldy[OPS_ACC2(0, 0, 0)] = d_y;
        if (celldy[OPS_ACC2(0, 0, 0)] < 0) {
        }
      }
    }
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
