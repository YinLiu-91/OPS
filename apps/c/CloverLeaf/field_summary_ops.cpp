//
// auto-generated by ops.py
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPS_2D
#include "ops_lib_core.h"

//
// ops_par_loop declarations
//

void ops_par_loop_field_summary_kernel(char const *, ops_block, int, int *,
                                       ops_arg, ops_arg, ops_arg, ops_arg,
                                       ops_arg, ops_arg, ops_arg, ops_arg,
                                       ops_arg, ops_arg, ops_arg);

#include "data.h"
#include "definitions.h"

//#include "field_summary_kernel.h"

void ideal_gas(int predict);

void field_summary() {
  double qa_diff;

  int x_min = field.x_min;
  int x_max = field.x_max;
  int y_min = field.y_min;
  int y_max = field.y_max;

  int rangexy_inner[] = {x_min, x_max, y_min, y_max};

  ideal_gas(FALSE);

  double vol = 0.0, mass = 0.0, ie = 0.0, ke = 0.0, press = 0.0;

  ops_par_loop_field_summary_kernel(
      "field_summary_kernel", clover_grid, 2, rangexy_inner,
      ops_arg_dat(volume, 1, S2D_00, "double", OPS_READ),
      ops_arg_dat(density0, 1, S2D_00, "double", OPS_READ),
      ops_arg_dat(energy0, 1, S2D_00, "double", OPS_READ),
      ops_arg_dat(pressure, 1, S2D_00, "double", OPS_READ),
      ops_arg_dat(xvel0, 1, S2D_00_P10_0P1_P1P1, "double", OPS_READ),
      ops_arg_dat(yvel0, 1, S2D_00_P10_0P1_P1P1, "double", OPS_READ),
      ops_arg_reduce(red_vol, 1, "double", OPS_INC),
      ops_arg_reduce(red_mass, 1, "double", OPS_INC),
      ops_arg_reduce(red_ie, 1, "double", OPS_INC),
      ops_arg_reduce(red_ke, 1, "double", OPS_INC),
      ops_arg_reduce(red_press, 1, "double", OPS_INC));

  ops_reduction_result(red_vol, &vol);
  ops_reduction_result(red_mass, &mass);
  ops_reduction_result(red_ie, &ie);
  ops_reduction_result(red_ke, &ke);
  ops_reduction_result(red_press, &press);

  ops_fprintf(g_out, "\n");
  ops_fprintf(g_out, "\n Time %lf\n", clover_time);
  ops_fprintf(g_out,
              "              %-10s  %-10s  %-10s  %-10s  %-15s  %-15s  %-s\n",
              " Volume", " Mass", " Density", " Pressure", " Internal Energy",
              "Kinetic Energy", "Total Energy");
  ops_fprintf(g_out, " step:   %3d   %-10.3E  %-10.3E  %-10.3E  %-10.3E  "
                     "%-15.3E  %-15.3E  %-.3E",
              step, vol, mass, mass / vol, press / vol, ie, ke, ie + ke);

  if (complete == TRUE && test_problem) {
    qa_diff = DBL_MAX;
    if (test_problem == 1)
      qa_diff = fabs((100.0 * (ke / 1.82280367310258)) - 100.0);
    if (test_problem == 2)
      qa_diff = fabs((100.0 * (ke / 1.19316898756307)) - 100.0);
    if (test_problem == 3)
      qa_diff = fabs((100.0 * (ke / 2.58984003503994)) - 100.0);
    if (test_problem == 4)
      qa_diff = fabs((100.0 * (ke / 0.307475452287895)) - 100.0);
    if (test_problem == 5)
      qa_diff = fabs((100.0 * (ke / 4.85350315783719)) - 100.0);

    ops_printf(
        "\n\nTest problem %d is within %3.15E %% of the expected solution\n",
        test_problem, qa_diff);
    ops_fprintf(
        g_out,
        "\n\nTest problem %d is within %3.15E %% of the expected solution\n",
        test_problem, qa_diff);

    if (qa_diff < 0.001) {
      ops_printf("This test is considered PASSED\n");
      ops_fprintf(g_out, "This test is considered PASSED\n");
    } else {
      ops_printf("This test is considered FAILED\n");
      ops_fprintf(g_out, "This test is considered FAILED\n");
    }
  }
}
