//
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
// auto-generated by ops.py on 2014-06-17 17:28
=======
// auto-generated by ops.py on 2014-05-13 14:45
>>>>>>> 57308c8... Addign ideal_gas and flux_calc to opencl
=======
// auto-generated by ops.py on 2014-05-13 15:00
>>>>>>> 45be066... addign advec_mom to OpenCL
=======
// auto-generated by ops.py on 2014-05-13 15:30
>>>>>>> 2dd8a20... testing OpenCL with currently converted kernels
=======
// auto-generated by ops.py on 2014-05-14 16:53
>>>>>>> fcc5de7... Attempting to upload global constants, but these need to be uploaded every time
=======
// auto-generated by ops.py on 2014-05-15 16:54
>>>>>>> 2eff219... Added advec_cell kernel to OpenCL with ability to pass constants to device
=======
// auto-generated by ops.py on 2014-05-15 16:56
>>>>>>> 7f143a4... working OpenCL with all non-reduction kernels and without Update halo
=======
// auto-generated by ops.py on 2014-05-15 17:08
>>>>>>> ceca208... Attempting to setup update halo kernel to OpenCL .. need to fix reductions
=======
// auto-generated by ops.py on 2014-05-28 15:13
>>>>>>> 033d7a0... Attempting to add calc_dt global reductions to OpenCL
=======
// auto-generated by ops.py on 2014-06-02 12:10
>>>>>>> ad432fc... Code generating global reductions
=======
// auto-generated by ops.py on 2014-06-02 12:26
>>>>>>> aee5038... Codegen working for reductions except for the __global key word issue in user kernel
=======
// auto-generated by ops.py on 2014-06-02 14:07
>>>>>>> 24690b8... Fixed user kernel parsing for __global
=======
// auto-generated by ops.py on 2014-06-02 16:13
>>>>>>> 496889f... Adding update halo kernel to Opencl - performance had gotten worse
=======
// auto-generated by ops.py on 2014-06-03 12:34
>>>>>>> ea30500... Setting up compilation that works for both CPUs and NVIDIA GPUs
=======
// auto-generated by ops.py on 2014-06-03 13:36
>>>>>>> 16b8dff... Fixing parse error in user kernel argument parsing
=======
// auto-generated by ops.py on 2014-06-03 14:49
>>>>>>> 4eb6712... Code generating initialize_chunk and generate .. but structs not working
=======
// auto-generated by ops.py on 2014-06-05 11:30
>>>>>>> a794738... Reverting to working version of OpenCL
=======
// auto-generated by ops.py on 2014-06-05 12:48
>>>>>>> 6ba9c42... OpenCL broken after rebase
=======
// auto-generated by ops.py on 2014-06-05 13:01
>>>>>>> a7f01b0... Still attempting to debug
=======
// auto-generated by ops.py on 2014-06-05 13:43
>>>>>>> 56d4657... Testing all other backends
=======
// auto-generated by ops.py on 2014-06-05 14:01
>>>>>>> 9f06c0a... Fixed bug after rebase
=======
// auto-generated by ops.py on 2014-06-05 14:25
>>>>>>> a3c575e... OpenCL code gen working after rebase
=======
// auto-generated by ops.py on 2014-06-05 17:28
>>>>>>> 18d43ab... Converting field summary to OpenCL
=======
// auto-generated by ops.py on 2014-06-09 10:49
>>>>>>> cf21327... Fixing error in generate.cpp
=======
// auto-generated by ops.py on 2014-06-09 10:54
>>>>>>> 7d9e635... fixed code generator for array of structs constants
=======
// auto-generated by ops.py on 2014-06-09 11:20
>>>>>>> 6c066de... Working OpenCL version with initialize_chunk
=======
// auto-generated by ops.py on 2014-06-09 14:31
>>>>>>> 5f1884f... decl_const_char2 implemented in the master header
=======
// auto-generated by ops.py on 2014-06-09 15:04
>>>>>>> df0baa6... Code generating all kernles exceps the ones outside hydro
=======
// auto-generated by ops.py on 2014-06-10 16:44
>>>>>>> ab55dc9... Experimenting with OpenCL performance
=======
// auto-generated by ops.py on 2014-06-11 17:51
>>>>>>> 3bcf778... Removing some unwanted function calls
=======
// auto-generated by ops.py on 2014-06-12 17:20
>>>>>>> 8e871f5... Optimizing OpenCL - 1
=======
// auto-generated by ops.py on 2014-06-13 15:00
>>>>>>> 7792f7b... removed cuda syncs based on ops_diags .. but need to make this application agnostic
=======
// auto-generated by ops.py on 2014-06-16 10:17
>>>>>>> 7c594e3... Removing device syncs to increase performance
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


#include  "ops_lib_cpp.h"

//
// ops_par_loop declarations
//

void ops_par_loop_reset_field_kernel1(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_reset_field_kernel2(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );



#include "data.h"
#include "definitions.h"

//#include "reset_field_kernel.h"

void reset_field()
{
  error_condition = 0;

  int x_cells = grid.x_cells;
  int y_cells = grid.y_cells;
  int x_min = field.x_min;
  int x_max = field.x_max;
  int y_min = field.y_min;
  int y_max = field.y_max;

  int rangexy_inner[] = {x_min,x_max,y_min,y_max};

  ops_par_loop_reset_field_kernel1("reset_field_kernel1", clover_grid, 2, rangexy_inner,
               ops_arg_dat(density0, S2D_00, "double", OPS_WRITE),
               ops_arg_dat(density1, S2D_00, "double", OPS_READ),
               ops_arg_dat(energy0, S2D_00, "double", OPS_WRITE),
               ops_arg_dat(energy1, S2D_00, "double", OPS_READ));

  int rangexy_inner_plus1xy[] = {x_min,x_max+1,y_min,y_max+1};

  ops_par_loop_reset_field_kernel2("reset_field_kernel2", clover_grid, 2, rangexy_inner_plus1xy,
               ops_arg_dat(xvel0, S2D_00, "double", OPS_WRITE),
               ops_arg_dat(xvel1, S2D_00, "double", OPS_READ),
               ops_arg_dat(yvel0, S2D_00, "double", OPS_WRITE),
               ops_arg_dat(yvel1, S2D_00, "double", OPS_READ));

}
