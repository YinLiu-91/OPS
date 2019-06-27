//
// auto-generated by ops.py
//

#define OPS_GPU

int xdim0_generate_chunk_kernel;
int xdim1_generate_chunk_kernel;
int xdim2_generate_chunk_kernel;
int xdim3_generate_chunk_kernel;
int xdim4_generate_chunk_kernel;
int xdim5_generate_chunk_kernel;
int xdim6_generate_chunk_kernel;

// user function
#pragma acc routine
inline void generate_chunk_kernel(const ptr_double vertexx,
                                  const ptr_double vertexy, ptr_double energy0,
                                  ptr_double density0, ptr_double u0,
                                  const ptr_double cellx,
                                  const ptr_double celly) {

  double radius, x_cent, y_cent;
  int is_in = 0;
  int is_in2 = 0;

  OPS_ACC(energy0, 0, 0) = states[0].energy;
  OPS_ACC(density0, 0, 0) = states[0].density;

  for (int i = 1; i < number_of_states; i++) {

    x_cent = states[i].xmin;
    y_cent = states[i].ymin;
    is_in = 0;
    is_in2 = 0;

    if (states[i].geometry == g_rect) {
      for (int i1 = -1; i1 <= 0; i1++) {
        for (int j1 = -1; j1 <= 0; j1++) {
          if (OPS_ACC(vertexx, 1 + i1, 0) >= states[i].xmin &&
              OPS_ACC(vertexx, 0 + i1, 0) < states[i].xmax) {
            if (OPS_ACC(vertexy, 0, 1 + j1) >= states[i].ymin &&
                OPS_ACC(vertexy, 0, 0 + j1) < states[i].ymax) {
              is_in = 1;
            }
          }
        }
      }
      if (OPS_ACC(vertexx, 1, 0) >= states[i].xmin &&
          OPS_ACC(vertexx, 0, 0) < states[i].xmax) {
        if (OPS_ACC(vertexy, 0, 1) >= states[i].ymin &&
            OPS_ACC(vertexy, 0, 0) < states[i].ymax) {
          is_in2 = 1;
        }
      }
      if (is_in2) {
        OPS_ACC(energy0, 0, 0) = states[i].energy;
        OPS_ACC(density0, 0, 0) = states[i].density;
      }
    } else if (states[i].geometry == g_circ) {
      for (int i1 = -1; i1 <= 0; i1++) {
        for (int j1 = -1; j1 <= 0; j1++) {
          radius = sqrt((OPS_ACC(cellx, i1, 0) - x_cent) *
                            (OPS_ACC(cellx, i1, 0) - x_cent) +
                        (OPS_ACC(celly, 0, j1) - y_cent) *
                            (OPS_ACC(celly, 0, j1) - y_cent));
          if (radius <= states[i].radius) {
            is_in = 1;
          }
        }
      }
      if (radius <= states[i].radius)
        is_in2 = 1;

      if (is_in2) {
        OPS_ACC(energy0, 0, 0) = states[i].energy;
        OPS_ACC(density0, 0, 0) = states[i].density;
      }
    } else if (states[i].geometry == g_point) {
      if (OPS_ACC(vertexx, 0, 0) == x_cent &&
          OPS_ACC(vertexy, 0, 0) == y_cent) {
        OPS_ACC(energy0, 0, 0) = states[i].energy;
        OPS_ACC(density0, 0, 0) = states[i].density;
      }
    }
  }
  OPS_ACC(u0, 0, 0) = OPS_ACC(energy0, 0, 0) * OPS_ACC(density0, 0, 0);
}

void generate_chunk_kernel_c_wrapper(double *p_a0, double *p_a1, double *p_a2,
                                     double *p_a3, double *p_a4, double *p_a5,
                                     double *p_a6, int x_size, int y_size) {
#ifdef OPS_GPU
#pragma acc parallel deviceptr(p_a0, p_a1, p_a2, p_a3, p_a4, p_a5, p_a6)
#pragma acc loop
#endif
  for (int n_y = 0; n_y < y_size; n_y++) {
#ifdef OPS_GPU
#pragma acc loop
#endif
    for (int n_x = 0; n_x < x_size; n_x++) {
      const ptr_double ptr0 = {p_a0 + n_x * 1 * 1 +
                                   n_y * xdim0_generate_chunk_kernel * 0 * 1,
                               xdim0_generate_chunk_kernel};
      const ptr_double ptr1 = {p_a1 + n_x * 0 * 1 +
                                   n_y * xdim1_generate_chunk_kernel * 1 * 1,
                               xdim1_generate_chunk_kernel};
      ptr_double ptr2 = {p_a2 + n_x * 1 * 1 +
                             n_y * xdim2_generate_chunk_kernel * 1 * 1,
                         xdim2_generate_chunk_kernel};
      ptr_double ptr3 = {p_a3 + n_x * 1 * 1 +
                             n_y * xdim3_generate_chunk_kernel * 1 * 1,
                         xdim3_generate_chunk_kernel};
      ptr_double ptr4 = {p_a4 + n_x * 1 * 1 +
                             n_y * xdim4_generate_chunk_kernel * 1 * 1,
                         xdim4_generate_chunk_kernel};
      const ptr_double ptr5 = {p_a5 + n_x * 1 * 1 +
                                   n_y * xdim5_generate_chunk_kernel * 0 * 1,
                               xdim5_generate_chunk_kernel};
      const ptr_double ptr6 = {p_a6 + n_x * 0 * 1 +
                                   n_y * xdim6_generate_chunk_kernel * 1 * 1,
                               xdim6_generate_chunk_kernel};
      generate_chunk_kernel(ptr0, ptr1, ptr2, ptr3, ptr4, ptr5, ptr6);
    }
  }
}
