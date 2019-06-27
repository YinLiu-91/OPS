//
// auto-generated by ops.py
//

int xdim0_initialise_chunk_kernel_celly;
int ydim0_initialise_chunk_kernel_celly;
int xdim1_initialise_chunk_kernel_celly;
int ydim1_initialise_chunk_kernel_celly;
int xdim2_initialise_chunk_kernel_celly;
int ydim2_initialise_chunk_kernel_celly;

// user function

void initialise_chunk_kernel_celly_c_wrapper(double *restrict vertexy_p,
                                             double *restrict celly_p,
                                             double *restrict celldy_p,
                                             int x_size, int y_size,
                                             int z_size) {
#pragma omp parallel for
  for (int n_z = 0; n_z < z_size; n_z++) {
    for (int n_y = 0; n_y < y_size; n_y++) {
      for (int n_x = 0; n_x < x_size; n_x++) {
        const ptr_double vertexy = {
            vertexy_p + n_x * 0 +
                n_y * xdim0_initialise_chunk_kernel_celly * 1 +
                n_z * xdim0_initialise_chunk_kernel_celly *
                    ydim0_initialise_chunk_kernel_celly * 0,
            xdim0_initialise_chunk_kernel_celly,
            ydim0_initialise_chunk_kernel_celly};
        ptr_double celly = {celly_p + n_x * 0 +
                                n_y * xdim1_initialise_chunk_kernel_celly * 1 +
                                n_z * xdim1_initialise_chunk_kernel_celly *
                                    ydim1_initialise_chunk_kernel_celly * 0,
                            xdim1_initialise_chunk_kernel_celly,
                            ydim1_initialise_chunk_kernel_celly};
        ptr_double celldy = {celldy_p + n_x * 0 +
                                 n_y * xdim2_initialise_chunk_kernel_celly * 1 +
                                 n_z * xdim2_initialise_chunk_kernel_celly *
                                     ydim2_initialise_chunk_kernel_celly * 0,
                             xdim2_initialise_chunk_kernel_celly,
                             ydim2_initialise_chunk_kernel_celly};

        double d_y = (grid.ymax - grid.ymin) / (double)grid.y_cells;
        OPS_ACC(celly, 0, 0, 0) =
            0.5 * (OPS_ACC(vertexy, 0, 0, 0) + OPS_ACC(vertexy, 0, 1, 0));
        OPS_ACC(celldy, 0, 0, 0) = d_y;
        if (OPS_ACC(celldy, 0, 0, 0) < 0) {
        }
      }
    }
  }
}
