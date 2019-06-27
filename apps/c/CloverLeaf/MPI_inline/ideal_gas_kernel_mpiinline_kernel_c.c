//
// auto-generated by ops.py
//

int xdim0_ideal_gas_kernel;
int xdim1_ideal_gas_kernel;
int xdim2_ideal_gas_kernel;
int xdim3_ideal_gas_kernel;

// user function

void ideal_gas_kernel_c_wrapper(double *restrict density_p,
                                double *restrict energy_p,
                                double *restrict pressure_p,
                                double *restrict soundspeed_p, int x_size,
                                int y_size) {
#pragma omp parallel for
  for (int n_y = 0; n_y < y_size; n_y++) {
    for (int n_x = 0; n_x < x_size; n_x++) {
      const ptr_double density = {density_p + n_x * 1 +
                                      n_y * xdim0_ideal_gas_kernel * 1,
                                  xdim0_ideal_gas_kernel};
      const ptr_double energy = {energy_p + n_x * 1 +
                                     n_y * xdim1_ideal_gas_kernel * 1,
                                 xdim1_ideal_gas_kernel};
      ptr_double pressure = {pressure_p + n_x * 1 +
                                 n_y * xdim2_ideal_gas_kernel * 1,
                             xdim2_ideal_gas_kernel};
      ptr_double soundspeed = {soundspeed_p + n_x * 1 +
                                   n_y * xdim3_ideal_gas_kernel * 1,
                               xdim3_ideal_gas_kernel};

      double sound_speed_squared, v, pressurebyenergy, pressurebyvolume;

      v = 1.0 / OPS_ACC(density, 0, 0);
      OPS_ACC(pressure, 0, 0) =
          (1.4 - 1.0) * OPS_ACC(density, 0, 0) * OPS_ACC(energy, 0, 0);
      pressurebyenergy = (1.4 - 1.0) * OPS_ACC(density, 0, 0);
      pressurebyvolume = -1 * OPS_ACC(density, 0, 0) * OPS_ACC(pressure, 0, 0);
      sound_speed_squared =
          v * v *
          (OPS_ACC(pressure, 0, 0) * pressurebyenergy - pressurebyvolume);
      OPS_ACC(soundspeed, 0, 0) = sqrt(sound_speed_squared);
    }
  }
}
