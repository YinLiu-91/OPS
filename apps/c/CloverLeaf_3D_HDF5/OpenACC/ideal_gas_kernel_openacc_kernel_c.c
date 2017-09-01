//
// auto-generated by ops.py
//
#include "./OpenACC/clover_leaf_common.h"

#define OPS_GPU

int xdim0_ideal_gas_kernel;
int ydim0_ideal_gas_kernel;
int xdim1_ideal_gas_kernel;
int ydim1_ideal_gas_kernel;
int xdim2_ideal_gas_kernel;
int ydim2_ideal_gas_kernel;
int xdim3_ideal_gas_kernel;
int ydim3_ideal_gas_kernel;

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3

#define OPS_ACC0(x, y, z)                                                      \
  (x + xdim0_ideal_gas_kernel * (y) +                                          \
   xdim0_ideal_gas_kernel * ydim0_ideal_gas_kernel * (z))
#define OPS_ACC1(x, y, z)                                                      \
  (x + xdim1_ideal_gas_kernel * (y) +                                          \
   xdim1_ideal_gas_kernel * ydim1_ideal_gas_kernel * (z))
#define OPS_ACC2(x, y, z)                                                      \
  (x + xdim2_ideal_gas_kernel * (y) +                                          \
   xdim2_ideal_gas_kernel * ydim2_ideal_gas_kernel * (z))
#define OPS_ACC3(x, y, z)                                                      \
  (x + xdim3_ideal_gas_kernel * (y) +                                          \
   xdim3_ideal_gas_kernel * ydim3_ideal_gas_kernel * (z))

// user function
inline void ideal_gas_kernel(const double *density, const double *energy,
                             double *pressure, double *soundspeed) {

  double sound_speed_squared, v, pressurebyenergy, pressurebyvolume;

  v = 1.0 / density[OPS_ACC0(0, 0, 0)];
  pressure[OPS_ACC2(0, 0, 0)] =
      (1.4 - 1.0) * density[OPS_ACC0(0, 0, 0)] * energy[OPS_ACC1(0, 0, 0)];

  pressurebyenergy = (1.4 - 1.0) * density[OPS_ACC0(0, 0, 0)];
  pressurebyvolume =
      -1.0 * density[OPS_ACC0(0, 0, 0)] * pressure[OPS_ACC2(0, 0, 0)];
  sound_speed_squared =
      v * v *
      (pressure[OPS_ACC2(0, 0, 0)] * pressurebyenergy - pressurebyvolume);
  soundspeed[OPS_ACC3(0, 0, 0)] = sqrt(sound_speed_squared);
}

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3

void ideal_gas_kernel_c_wrapper(double *p_a0, double *p_a1, double *p_a2,
                                double *p_a3, int x_size, int y_size,
                                int z_size) {
#ifdef OPS_GPU
#pragma acc parallel deviceptr(p_a0, p_a1, p_a2, p_a3)
#pragma acc loop
#endif
  for (int n_z = 0; n_z < z_size; n_z++) {
#ifdef OPS_GPU
#pragma acc loop
#endif
    for (int n_y = 0; n_y < y_size; n_y++) {
#ifdef OPS_GPU
#pragma acc loop
#endif
      for (int n_x = 0; n_x < x_size; n_x++) {
        ideal_gas_kernel(
            p_a0 + n_x * 1 * 1 + n_y * xdim0_ideal_gas_kernel * 1 * 1 +
                n_z * xdim0_ideal_gas_kernel * ydim0_ideal_gas_kernel * 1 * 1,
            p_a1 + n_x * 1 * 1 + n_y * xdim1_ideal_gas_kernel * 1 * 1 +
                n_z * xdim1_ideal_gas_kernel * ydim1_ideal_gas_kernel * 1 * 1,
            p_a2 + n_x * 1 * 1 + n_y * xdim2_ideal_gas_kernel * 1 * 1 +
                n_z * xdim2_ideal_gas_kernel * ydim2_ideal_gas_kernel * 1 * 1,
            p_a3 + n_x * 1 * 1 + n_y * xdim3_ideal_gas_kernel * 1 * 1 +
                n_z * xdim3_ideal_gas_kernel * ydim3_ideal_gas_kernel * 1 * 1);
      }
    }
  }
}
