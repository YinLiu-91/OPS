/* Crown Copyright 2012 AWE.

  This file is part of CloverLeaf.

  CloverLeaf is free software: you can redistribute it and/or modify it under
  the terms of the GNU General Public License as published by the
  Free Software Foundation, either version 3 of the License, or (at your option)
  any later version.

  CloverLeaf is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
  details.

  You should have received a copy of the GNU General Public License along with
  CloverLeaf. If not, see http://www.gnu.org/licenses/. */

/** @brief CloverLeaf top level program: Invokes the main cycle
  * @author Wayne Gaudin
  * @details CloverLeaf in a proxy-app that solves the compressible Euler
  *  Equations using an explicit finite volume method on a Cartesian grid.
  *  The grid is staggered with internal energy, density and pressure at cell
  *  centres and velocities on cell vertices.

  *  A second order predictor-corrector method is used to advance the solution
  *  in time during the Lagrangian phase. A second order advective remap is then
  *  carried out to return the mesh to an orthogonal state.
  *
  *  NOTE: that the proxy-app uses uniformly spaced mesh. The actual method will
  *  work on a mesh with varying spacing to keep it relevant to it's parent code.
  *  For this reason, optimisations should only be carried out on the software
  *  that do not change the underlying numerical method. For example, the
  *  volume, though constant for all cells, should remain array and not be
  *  converted to a scalar.
  *
  *  This version is based on C/C++ and uses the OPS prototype highlevel domain
  *  specific API for developing Structured mesh applications
  */

// standard headers
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// OPS header file
#include "ops_seq.h"

// Cloverleaf constants
#include "data.h"

// Cloverleaf definitions
#include "definitions.h"

//Cloverleaf kernels
#include "test_kernel.h"
#include "initialise_chunk_kernel.h"
#include "generate_chunk_kernel.h"
#include "ideal_gas_kernel.h"
#include  "update_halo_kernel.h"
#include "field_summary_kernel.h"


// Cloverleaf functions
void read_input();
void initialise();



/******************************************************************************
* Initialize Global constants and variables
/******************************************************************************/
float   g_version = 1.0;
int     g_ibig = 640000;
double  g_small = 1.0e-16;
double  g_big  = 1.0e+21;
int     g_name_len_max = 255 ,
        g_xdir = 1,
        g_ydir = 2;

int     number_of_states;

        //These two need to be kept consistent with update_halo
int     CHUNK_LEFT    = 1,
        CHUNK_RIGHT   = 2,
        CHUNK_BOTTOM  = 3,
        CHUNK_TOP     = 4,
        EXTERNAL_FACE = -1;

int     FIELD_DENSITY0   = 0,
        FIELD_DENSITY1   = 1,
        FIELD_ENERGY0    = 2,
        FIELD_ENERGY1    = 3,
        FIELD_PRESSURE   = 4,
        FIELD_VISCOSITY  = 5,
        FIELD_SOUNDSPEED = 6,
        FIELD_XVEL0      = 7,
        FIELD_XVEL1      = 8,
        FIELD_YVEL0      = 9,
        FIELD_YVEL1      =10,
        FIELD_VOL_FLUX_X =11,
        FIELD_VOL_FLUX_Y =12,
        FIELD_MASS_FLUX_X=13,
        FIELD_MASS_FLUX_Y=14,
        NUM_FIELDS       =15;

FILE    *g_out, *g_in;  //Files for input and output

int     g_rect=1,
        g_circ=2,
        g_point=3;

state_type * states; //global variable holding state info

grid_type grid; //global variable holding global grid info

field_type field; //global variable holding info of fields

int step = 0;
int advect_x; //logical
int error_condition;
int test_problem;
int complete; //logical

int fields[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

/******************************************************************************
* Main program
/******************************************************************************/
int main(int argc, char **argv)
{

  /**--------------------Set up Cloverleaf default problem-------------------**/
  //need to fill these in through I/O
  grid = (grid_type ) xmalloc(sizeof(grid_type_core));
  grid->x_cells = 10;
  grid->y_cells = 2;

  grid->xmin = 0;
  grid->ymin = 0;
  grid->xmax = grid->x_cells;
  grid->ymax = grid->y_cells;

  field = (field_type ) xmalloc(sizeof(field_type_core));
  field->x_min = 0;
  field->y_min = 0;
  field->x_max = grid->x_cells;
  field->y_max = grid->y_cells;
  field->left = 0;
  field->bottom = 0;

  number_of_states = 2;
  states =  (state_type *) xmalloc(sizeof(state_type) * number_of_states);

  //state 1
  states[0] = (state_type ) xmalloc(sizeof(state_type_core));
  states[0]->density = 0.2;
  states[0]->energy = 1.0;
  states[0]->xvel = 0.0;
  states[0]->yvel = 0.0;

  //state 2
  states[1] = (state_type ) xmalloc(sizeof(state_type_core));
  states[1]->density=1.0;
  states[1]->energy=2.5;
  states[1]->xvel = 0.0;
  states[1]->yvel = 0.0;
  states[1]->geometry=g_rect;
  states[1]->xmin=0.0;
  states[1]->xmax=5.0;
  states[1]->ymin=0.0;
  states[1]->ymax=2.0;

  float dx= (grid->xmax-grid->xmin)/(float)(grid->x_cells);
  float dy= (grid->ymax-grid->ymin)/(float)(grid->y_cells);

  for(int i = 0; i < number_of_states; i++)
  {
    states[i]->xmin = states[i]->xmin + (dx/100.00);
    states[i]->ymin = states[i]->ymin + (dy/100.00);
    states[i]->xmax = states[i]->xmax - (dx/100.00);
    states[i]->ymax = states[i]->ymax - (dy/100.00);
  }

  NUM_FIELDS = 15;

  /**-------------------OPS Initialisation and Declarations------------------**/

  // OPS initialisation
  ops_init(argc,argv,5);
  ops_printf("Clover version %f\n", g_version);

  //declare blocks
  int x_cells = grid->x_cells;
  int y_cells = grid->y_cells;
  int x_min = field->x_min;
  int x_max = field->x_max;
  int y_min = field->y_min;
  int y_max = field->y_max;
  int dims[2] = {x_cells, y_cells};  //cloverleaf 2D block dimensions
  ops_block clover_grid = ops_decl_block(2, dims, "grid");

  //declare edges of block
  dims[0] = x_cells; dims[1] = 1;
  ops_block clover_xedge = ops_decl_block(2, dims, "xedge");
  dims[0] = 1; dims[1] = y_cells;
  ops_block clover_yedge = ops_decl_block(2, dims, "yedge");

  //declare data on blocks
  int offset[2] = {-2,-2};
  int size[2] = {(x_max+2)-(x_min-2), (y_max+2)-(y_min-2)};
  double* temp = NULL;

  ops_dat density0    = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "density0");
  ops_dat density1    = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "density1");
  ops_dat energy0     = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "energy0");
  ops_dat energy1     = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "energy1");
  ops_dat pressure    = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "pressure");
  ops_dat viscosity   = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "viscosity");
  ops_dat soundspeed  = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "soundspeed");
  ops_dat volume      = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "volume");

  size[0] = (x_max+3)-(x_min-2); size[1] = (y_max+3)-(y_min-2);
  ops_dat xvel0    = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "xvel0");
  ops_dat xvel1    = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "xvel1");
  ops_dat yvel0    = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "yvel0");
  ops_dat yvel1    = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "yvel1");

  size[0] = (x_max+3)-(x_min-2); size[1] = (y_max+2)-(y_min-2);
  ops_dat vol_flux_x  = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "vol_flux_x");
  ops_dat mass_flux_x = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "mass_flux_x");
  ops_dat xarea       = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "xarea");


  size[0] = (x_max+2)-(x_min-2); size[1] = (y_max+3)-(y_min-2);
  ops_dat vol_flux_y  = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "vol_flux_y");
  ops_dat mass_flux_y = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "mass_flux_y");
  ops_dat yarea       = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "yarea");

  size[0] = (x_max+3)-(x_min-2); size[1] = (y_max+3)-(y_min-2);
  ops_dat work_array1    = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "work_array1");
  ops_dat work_array2    = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "work_array2");
  ops_dat work_array3    = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "work_array3");
  ops_dat work_array4    = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "work_array4");
  ops_dat work_array5    = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "work_array5");
  ops_dat work_array6    = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "work_array6");
  ops_dat work_array7    = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "work_array7");

  int size2[2] = {(x_max+2)-(x_min-2),1};
  int size3[2] = {1, (y_max+2)-(y_min-2)};
  int size4[2] = {(x_max+3)-(x_min-2),1};
  int size5[2] = {1,(y_max+3)-(y_min-2)};
  int offsetx[2] = {-2,0};
  int offsety[2] = {0,-2};
  ops_dat cellx    = ops_decl_dat(clover_xedge, 1, size2, offsetx, temp, "double", "cellx");
  ops_dat celly    = ops_decl_dat(clover_yedge, 1, size3, offsety, temp, "double", "celly");
  ops_dat vertexx  = ops_decl_dat(clover_xedge, 1, size4, offsetx, temp, "double", "vertexx");
  ops_dat vertexy  = ops_decl_dat(clover_yedge, 1, size5, offsety, temp, "double", "vertexy");
  ops_dat celldx   = ops_decl_dat(clover_xedge, 1, size2, offsetx, temp, "double", "celldx");
  ops_dat celldy   = ops_decl_dat(clover_yedge, 1, size3, offsety, temp, "double", "celldy");
  ops_dat vertexdx = ops_decl_dat(clover_xedge, 1, size4, offsetx, temp, "double", "vertexdx");
  ops_dat vertexdy = ops_decl_dat(clover_yedge, 1, size5, offsety, temp, "double", "vertexdy");


  //contains x indicies from 0 to xmax+3 -- needed for initialization
  int* xindex = (int *)xmalloc(sizeof(int)*size4[0]);
  for(int i=x_min-2; i<x_max+3; i++) xindex[i-offsetx[0]] = i - x_min;
  ops_dat xx  = ops_decl_dat(clover_xedge, 1, size4, offsetx, xindex, "int", "xx");

  //contains y indicies from 0 to ymax+3 -- needed for initialization
  int* yindex = (int *)xmalloc(sizeof(int)*size5[1]);
  for(int i=y_min-2; i<y_max+3; i++) yindex[i-offsety[1]] = i - y_min;
  ops_dat yy  = ops_decl_dat(clover_yedge, 1, size5, offsety, yindex, "int", "yy");

  ops_diagnostic_output();


  /**---------------------------initialize chunk-----------------------------**/

  int self[] = {0,0};
  ops_stencil sten1 = ops_decl_stencil( 2, 1, self, "self");

  int rangex[] = {x_min-2, x_max+3, 0, 1};
  ops_par_loop(initialise_chunk_kernel_x, "initialise_chunk_kernel_x", 2, rangex,
               ops_arg_dat(vertexx, sten1, OPS_WRITE),
               ops_arg_dat(xx, sten1, OPS_READ),
               ops_arg_dat(vertexdx, sten1, OPS_WRITE));

  int rangey[] = {0, 1, y_min-2, y_max+3};
  ops_par_loop(initialise_chunk_kernel_y, "initialise_chunk_kernel_y", 2, rangey,
               ops_arg_dat(vertexy, sten1, OPS_WRITE),
               ops_arg_dat(yy, sten1, OPS_READ),
               ops_arg_dat(vertexdy, sten1, OPS_WRITE));


  int self_plus1[] = {0,0, 1,0};
  ops_stencil sten3 = ops_decl_stencil( 2, 2, self_plus1, "self_plus1");
  rangex[0] = x_min-2; rangex[1] = x_max+2; rangex[2] = 0; rangex[3] = 1;
  ops_par_loop(initialise_chunk_kernel_cellx, "initialise_chunk_kernel_cellx", 2, rangex,
               ops_arg_dat(vertexx, sten3, OPS_READ),
               ops_arg_dat(cellx, sten1, OPS_WRITE),
               ops_arg_dat(celldx, sten1, OPS_WRITE));

  self_plus1[0] = 0;self_plus1[1] = 0; self_plus1[2] = 0; self_plus1[2] = 1;
  ops_stencil sten4 = ops_decl_stencil( 2, 2, self_plus1, "self_plus1");
  rangey[0] = 0; rangey[1] = 1; rangey[2] = y_min-2; rangey[3] = y_max+2;
  ops_par_loop(initialise_chunk_kernel_celly, "initialise_chunk_kernel_celly", 2, rangey,
               ops_arg_dat(vertexy, sten4, OPS_READ),
               ops_arg_dat(celly, sten1, OPS_WRITE),
               ops_arg_dat(celldy, sten1, OPS_WRITE));

  int rangexy[] = {x_min-2,x_max+2,y_min-2,y_max+2};
  int self2d[]  = {0,0};
  int stridey[] = {0,1};
  int stridex[] = {1,0};
  ops_stencil sten2D = ops_decl_stencil( 2, 1, self2d, "self2d");
  ops_stencil sten2D_1Dstridey = ops_decl_strided_stencil( 2, 1, self2d, stridey, "self2d");
  ops_stencil sten2D_1Dstridex = ops_decl_strided_stencil( 2, 1, self2d, stridex, "self2d");

  ops_par_loop(initialise_volume_xarea_yarea, "initialise_volume_xarea_yarea", 2, rangexy,
    ops_arg_dat(volume, sten2D, OPS_WRITE),
    ops_arg_dat(celldy, sten2D_1Dstridey, OPS_READ),
    ops_arg_dat(xarea, sten2D, OPS_WRITE),
    ops_arg_dat(celldx, sten2D_1Dstridex, OPS_READ),
    ops_arg_dat(yarea, sten2D, OPS_WRITE));

  /**---------------------------generate chunk-----------------------------**/

  int self_plus1x[] = {0,0, 1,0};
  int self_plus1y[] = {0,0, 0,1};

  int strideplus1x[] = {1,0};
  int strideplus1y[] = {0,1};
  ops_stencil sten1x = ops_decl_strided_stencil( 2, 2, self_plus1x, stridex, "self_plus1x");
  ops_stencil sten1y = ops_decl_strided_stencil( 2, 2, self_plus1y, stridey, "self_plus1y");

  int four_point[]  = {0,0, 1,0, 0,1, 1,1};
  ops_stencil sten2D_4point = ops_decl_stencil( 2, 4, four_point, "sten2D_4point");
  ops_par_loop(generate_kernel, "generate_kernel", 2, rangexy,
    ops_arg_dat(vertexx, sten1x, OPS_READ),
    ops_arg_dat(vertexy, sten1y, OPS_READ),
    ops_arg_dat(energy0, sten2D, OPS_WRITE),
    ops_arg_dat(density0, sten2D, OPS_WRITE),
    ops_arg_dat(xvel0, sten2D_4point, OPS_WRITE),
    ops_arg_dat(yvel0, sten2D_4point, OPS_WRITE),
    ops_arg_dat(cellx, sten1x, OPS_READ),
    ops_arg_dat(celly, sten1y, OPS_READ));


  //ops_print_dat_to_txtfile_core(density0, "cloverdats.dat");
  //ops_print_dat_to_txtfile_core(energy0, "cloverdats.dat");

  /**------------------------------ideal_gas---------------------------------**/

  advect_x = TRUE;
  int predict = FALSE;
  int rangexy_inner[] = {x_min,x_max,y_min,y_max}; // inner range without border

  if(!predict) {
    ops_par_loop(ideal_gas_kernel, "ideal_gas_kernel", 2, rangexy_inner,
      ops_arg_dat(density0, sten2D, OPS_READ),
      ops_arg_dat(energy0, sten2D, OPS_READ),
      ops_arg_dat(pressure, sten2D, OPS_RW),
      ops_arg_dat(soundspeed, sten2D, OPS_WRITE));
  }
  else {
    ops_par_loop(ideal_gas_kernel, "ideal_gas_kernel", 2, rangexy_inner,
      ops_arg_dat(density1, sten2D, OPS_READ),
      ops_arg_dat(energy1, sten2D, OPS_READ),
      ops_arg_dat(pressure, sten2D, OPS_RW),
      ops_arg_dat(soundspeed, sten2D, OPS_WRITE));
  }


  /**-----------------------------update_halo--------------------------------**/
  // a bit complicated .. is there a better way to do this?? ..

  //Prime all halo data for the first step
  fields[FIELD_DENSITY0]  = 1;
  fields[FIELD_ENERGY0]   = 1;
  fields[FIELD_PRESSURE]  = 1;
  fields[FIELD_VISCOSITY] = 1;
  fields[FIELD_DENSITY1]  = 1;
  fields[FIELD_ENERGY1]   = 1;
  fields[FIELD_XVEL0]     = 1;
  fields[FIELD_YVEL0]     = 1;
  fields[FIELD_XVEL1]     = 1;
  fields[FIELD_YVEL1]     = 1;

  int rangexy_bottom1[] = {x_min-2,x_max+2,y_min-2,y_min-1};
  int self_bottom1[] = {0,0, 0,2};
  ops_stencil sten2D_bottom1 = ops_decl_stencil( 2, 2, self_bottom1, "sten2D_bottom1");

  int rangexy_bottom2[] = {x_min-2,x_max+2,y_min-1,y_min};
  int self_bottom2[] = {0,0, 0,1};
  ops_stencil sten2D_bottom2 = ops_decl_stencil( 2, 2, self_bottom2, "sten2D_bottom2");

  ops_par_loop(update_halo_kernel, "update_halo_kernel", 2, rangexy_bottom2,
      ops_arg_dat(density0, sten2D_bottom2, OPS_RW),
      ops_arg_dat(density1, sten2D_bottom2, OPS_RW),
      ops_arg_dat(energy0, sten2D_bottom2, OPS_RW),
      ops_arg_dat(energy1, sten2D_bottom2, OPS_RW),
      ops_arg_dat(pressure, sten2D_bottom2, OPS_RW),
      ops_arg_dat(viscosity, sten2D_bottom2, OPS_RW),
      ops_arg_dat(soundspeed, sten2D_bottom2, OPS_RW));

  ops_par_loop(update_halo_kernel, "update_halo_kernel", 2, rangexy_bottom1,
      ops_arg_dat(density0, sten2D_bottom1, OPS_RW),
      ops_arg_dat(density1, sten2D_bottom1, OPS_RW),
      ops_arg_dat(energy0, sten2D_bottom1, OPS_RW),
      ops_arg_dat(energy1, sten2D_bottom1, OPS_RW),
      ops_arg_dat(pressure, sten2D_bottom1, OPS_RW),
      ops_arg_dat(viscosity, sten2D_bottom1, OPS_RW),
      ops_arg_dat(soundspeed, sten2D_bottom1, OPS_RW));

  int rangexy_top1[] = {x_min-2,x_max+2,y_max+1,y_max+2};
  int self_top1[] = {0,0, 0,-2};
  ops_stencil sten2D_top1 = ops_decl_stencil( 2, 2, self_top1, "sten2D_top1");

  int rangexy_top2[] = {x_min-2,x_max+2,y_max,y_max+1};
  int self_top2[] = {0,0, 0,-1};
  ops_stencil sten2D_top2 = ops_decl_stencil( 2, 2, self_top2, "sten2D_top2");

  ops_par_loop(update_halo_kernel, "update_halo_kernel", 2, rangexy_top2,
      ops_arg_dat(density0, sten2D_top2, OPS_RW),
      ops_arg_dat(density1, sten2D_top2, OPS_RW),
      ops_arg_dat(energy0, sten2D_top2, OPS_RW),
      ops_arg_dat(energy1, sten2D_top2, OPS_RW),
      ops_arg_dat(pressure, sten2D_top2, OPS_RW),
      ops_arg_dat(viscosity, sten2D_top2, OPS_RW),
      ops_arg_dat(soundspeed, sten2D_top2, OPS_RW));

  ops_par_loop(update_halo_kernel, "update_halo_kernel", 2, rangexy_top1,
      ops_arg_dat(density0, sten2D_top1, OPS_RW),
      ops_arg_dat(density1, sten2D_top1, OPS_RW),
      ops_arg_dat(energy0, sten2D_top1, OPS_RW),
      ops_arg_dat(energy1, sten2D_top1, OPS_RW),
      ops_arg_dat(pressure, sten2D_top1, OPS_RW),
      ops_arg_dat(viscosity, sten2D_top1, OPS_RW),
      ops_arg_dat(soundspeed, sten2D_top1, OPS_RW));

  int rangexy_left1[] = {x_min-2,x_min-1,y_min-2,y_max+2};
  int self_left1[] = {0,0, 2,0};
  ops_stencil sten2D_left1 = ops_decl_stencil( 2, 2, self_left1, "sten2D_left1");

  int rangexy_left2[] = {x_min-1,x_min,y_min-2,y_max+2};
  int self_left2[] = {0,0, 1,0};
  ops_stencil sten2D_left2 = ops_decl_stencil( 2, 2, self_left2, "sten2D_left2");

  ops_par_loop(update_halo_kernel, "update_halo_kernel", 2, rangexy_left2,
      ops_arg_dat(density0, sten2D_left2, OPS_RW),
      ops_arg_dat(density1, sten2D_left2, OPS_RW),
      ops_arg_dat(energy0, sten2D_left2, OPS_RW),
      ops_arg_dat(energy1, sten2D_left2, OPS_RW),
      ops_arg_dat(pressure, sten2D_left2, OPS_RW),
      ops_arg_dat(viscosity, sten2D_left2, OPS_RW),
      ops_arg_dat(soundspeed, sten2D_left2, OPS_RW));

  ops_par_loop(update_halo_kernel, "update_halo_kernel", 2, rangexy_left1,
      ops_arg_dat(density0, sten2D_left1, OPS_RW),
      ops_arg_dat(density1, sten2D_left1, OPS_RW),
      ops_arg_dat(energy0, sten2D_left1, OPS_RW),
      ops_arg_dat(energy1, sten2D_left1, OPS_RW),
      ops_arg_dat(pressure, sten2D_left1, OPS_RW),
      ops_arg_dat(viscosity, sten2D_left1, OPS_RW),
      ops_arg_dat(soundspeed, sten2D_left1, OPS_RW));

  int rangexy_right1[] = {x_max+1,x_max+2,y_min-2,y_max+2};
  int self_right1[] = {0,0, -2,0};
  ops_stencil sten2D_right1 = ops_decl_stencil( 2, 2, self_right1, "sten2D_right1");

  int rangexy_right2[] = {x_max,x_max+1,y_min-2,y_max+2};
  int self_right2[] = {0,0, -1,0};
  ops_stencil sten2D_right2 = ops_decl_stencil( 2, 2, self_right2, "sten2D_right2");

  ops_par_loop(update_halo_kernel, "update_halo_kernel", 2, rangexy_right2,
      ops_arg_dat(density0, sten2D_right2, OPS_RW),
      ops_arg_dat(density1, sten2D_right2, OPS_RW),
      ops_arg_dat(energy0, sten2D_right2, OPS_RW),
      ops_arg_dat(energy1, sten2D_right2, OPS_RW),
      ops_arg_dat(pressure, sten2D_right2, OPS_RW),
      ops_arg_dat(viscosity, sten2D_right2, OPS_RW),
      ops_arg_dat(soundspeed, sten2D_right2, OPS_RW));

  ops_par_loop(update_halo_kernel, "update_halo_kernel", 2, rangexy_right1,
      ops_arg_dat(density0, sten2D_right1, OPS_RW),
      ops_arg_dat(density1, sten2D_right1, OPS_RW),
      ops_arg_dat(energy0, sten2D_right1, OPS_RW),
      ops_arg_dat(energy1, sten2D_right1, OPS_RW),
      ops_arg_dat(pressure, sten2D_right1, OPS_RW),
      ops_arg_dat(viscosity, sten2D_right1, OPS_RW),
      ops_arg_dat(soundspeed, sten2D_right1, OPS_RW));

  //ops_print_dat_to_txtfile_core(density0, "cloverdats.dat");
  //ops_print_dat_to_txtfile_core(density1, "cloverdats.dat");
  //ops_print_dat_to_txtfile_core(energy0, "cloverdats.dat");
  //ops_print_dat_to_txtfile_core(energy1, "cloverdats.dat");
  //ops_print_dat_to_txtfile_core(pressure, "cloverdats.dat");
  //ops_print_dat_to_txtfile_core(viscosity, "cloverdats.dat");
  //ops_print_dat_to_txtfile_core(soundspeed, "cloverdats.dat");

  //int rangexy_bottom1[] = {x_min-2,x_max+2,y_min-2,y_min-1};
  int bottom1[] = {0,0, 0,3};
  ops_stencil s2D_bottom1 = ops_decl_stencil( 2, 2, bottom1, "s2D_bottom1");
  //int rangexy_bottom2[] = {x_min-2,x_max+2,y_min-1,y_min};
  int bottom2[] = {0,0, 0,2};
  ops_stencil s2D_bottom2 = ops_decl_stencil( 2, 2, bottom2, "s2D_bottom2");

  ops_par_loop(update_halo_kernel2, "update_halo_kernel2", 2, rangexy_bottom2,
      ops_arg_dat(xvel0, s2D_bottom2, OPS_RW),
      ops_arg_dat(xvel1, s2D_bottom2, OPS_RW),
      ops_arg_dat(yvel0, s2D_bottom2, OPS_RW),
      ops_arg_dat(yvel1, s2D_bottom2, OPS_RW),
      ops_arg_dat(vol_flux_x,  s2D_bottom2, OPS_RW),
      ops_arg_dat(mass_flux_x, s2D_bottom2, OPS_RW),
      ops_arg_dat(vol_flux_y,  s2D_bottom2, OPS_RW),
      ops_arg_dat(mass_flux_y, s2D_bottom2, OPS_RW));

  ops_par_loop(update_halo_kernel2, "update_halo_kernel2", 2, rangexy_bottom1,
      ops_arg_dat(xvel0, s2D_bottom1, OPS_RW),
      ops_arg_dat(xvel1, s2D_bottom1, OPS_RW),
      ops_arg_dat(yvel0, s2D_bottom1, OPS_RW),
      ops_arg_dat(yvel1, s2D_bottom1, OPS_RW),
      ops_arg_dat(vol_flux_x, s2D_bottom1, OPS_RW),
      ops_arg_dat(mass_flux_x, s2D_bottom1, OPS_RW),
      ops_arg_dat(vol_flux_y, s2D_bottom1, OPS_RW),
      ops_arg_dat(mass_flux_y, s2D_bottom1, OPS_RW));


  //int rangexy_top1[] = {x_min-2,x_max+2,y_max+1,y_max+2};
  int top1[] = {0,0, 0,-3};
  ops_stencil s2D_top1 = ops_decl_stencil( 2, 2, top1, "s2D_top1");
  //int rangexy_top2[] = {x_min-2,x_max+2,y_max,y_max+1};
  int top2[] = {0,0, 0,-2};
  ops_stencil s2D_top2 = ops_decl_stencil( 2, 2, top2, "s2D_top2");

  ops_par_loop(update_halo_kernel2, "update_halo_kernel2", 2, rangexy_top1,
      ops_arg_dat(xvel0, s2D_top1, OPS_RW),
      ops_arg_dat(xvel1, s2D_top1, OPS_RW),
      ops_arg_dat(yvel0, s2D_top1, OPS_RW),
      ops_arg_dat(yvel1, s2D_top1, OPS_RW),
      ops_arg_dat(vol_flux_x,  s2D_top1, OPS_RW),
      ops_arg_dat(mass_flux_x, s2D_top1, OPS_RW),
      ops_arg_dat(vol_flux_y,  s2D_top1, OPS_RW),
      ops_arg_dat(mass_flux_y, s2D_top1, OPS_RW));

  ops_par_loop(update_halo_kernel2, "update_halo_kernel2", 2, rangexy_top2,
      ops_arg_dat(xvel0, s2D_top2, OPS_RW),
      ops_arg_dat(xvel1, s2D_top2, OPS_RW),
      ops_arg_dat(yvel0, s2D_top2, OPS_RW),
      ops_arg_dat(yvel1, s2D_top2, OPS_RW),
      ops_arg_dat(vol_flux_x, s2D_top2, OPS_RW),
      ops_arg_dat(mass_flux_x, s2D_top2, OPS_RW),
      ops_arg_dat(vol_flux_y, s2D_top2, OPS_RW),
      ops_arg_dat(mass_flux_y, s2D_top2, OPS_RW));


  //int rangexy_left1[] = {x_min-2,x_min-1,y_min-2,y_max+2};
  int left1[] = {0,0, 3,0};
  ops_stencil s2D_left1 = ops_decl_stencil( 2, 2, left1, "s2D_left1");

  //int rangexy_left2[] = {x_min-1,x_min,y_min-2,y_max+2};
  int left2[] = {0,0, 2,0};
  ops_stencil s2D_left2 = ops_decl_stencil( 2, 2, left2, "s2D_left2");

  ops_par_loop(update_halo_kernel2, "update_halo_kernel2", 2, rangexy_left2,
      ops_arg_dat(xvel0, s2D_left2, OPS_RW),
      ops_arg_dat(xvel1, s2D_left2, OPS_RW),
      ops_arg_dat(yvel0, s2D_left2, OPS_RW),
      ops_arg_dat(yvel1, s2D_left2, OPS_RW),
      ops_arg_dat(vol_flux_x, s2D_left2, OPS_RW),
      ops_arg_dat(mass_flux_x, s2D_left2, OPS_RW),
      ops_arg_dat(vol_flux_y, s2D_left2, OPS_RW),
      ops_arg_dat(mass_flux_y, s2D_left2, OPS_RW));

  ops_par_loop(update_halo_kernel2, "update_halo_kernel2", 2, rangexy_left1,
      ops_arg_dat(xvel0, s2D_left1, OPS_RW),
      ops_arg_dat(xvel1, s2D_left1, OPS_RW),
      ops_arg_dat(yvel0, s2D_left1, OPS_RW),
      ops_arg_dat(yvel1, s2D_left1, OPS_RW),
      ops_arg_dat(vol_flux_x, s2D_left1, OPS_RW),
      ops_arg_dat(mass_flux_x, s2D_left1, OPS_RW),
      ops_arg_dat(vol_flux_y, s2D_left1, OPS_RW),
      ops_arg_dat(mass_flux_y, s2D_left1, OPS_RW));

  //int rangexy_right1[] = {x_max+1,x_max+2,y_min-2,y_max+2};
  int right1[] = {0,0, -3,0};
  ops_stencil s2D_right1 = ops_decl_stencil( 2, 2, right1, "s2D_right1");

  //int rangexy_right2[] = {x_max,x_max+1,y_min-2,y_max+2};
  int right2[] = {0,0, -2,0};
  ops_stencil s2D_right2 = ops_decl_stencil( 2, 2, right2, "s2D_right2");

  ops_par_loop(update_halo_kernel2, "update_halo_kernel2", 2, rangexy_right2,
      ops_arg_dat(xvel0, s2D_right2, OPS_RW),
      ops_arg_dat(xvel1, s2D_right2, OPS_RW),
      ops_arg_dat(yvel0, s2D_right2, OPS_RW),
      ops_arg_dat(yvel1, s2D_right2, OPS_RW),
      ops_arg_dat(vol_flux_x, s2D_right2, OPS_RW),
      ops_arg_dat(mass_flux_x, s2D_right2, OPS_RW),
      ops_arg_dat(vol_flux_y, s2D_right2, OPS_RW),
      ops_arg_dat(mass_flux_y, s2D_right2, OPS_RW));

  ops_par_loop(update_halo_kernel2, "update_halo_kernel2", 2, rangexy_right1,
      ops_arg_dat(xvel0, s2D_right1, OPS_RW),
      ops_arg_dat(xvel1, s2D_right1, OPS_RW),
      ops_arg_dat(yvel0, s2D_right1, OPS_RW),
      ops_arg_dat(yvel1, s2D_right1, OPS_RW),
      ops_arg_dat(vol_flux_x, s2D_right1, OPS_RW),
      ops_arg_dat(mass_flux_x, s2D_right1, OPS_RW),
      ops_arg_dat(vol_flux_y, s2D_right1, OPS_RW),
      ops_arg_dat(mass_flux_y, s2D_right1, OPS_RW));


  //ops_print_dat_to_txtfile_core(xvel0, "cloverdats.dat");
  //ops_print_dat_to_txtfile_core(xvel1, "cloverdats.dat");
  //ops_print_dat_to_txtfile_core(yvel0, "cloverdats.dat");
  //ops_print_dat_to_txtfile_core(yvel1, "cloverdats.dat");
  //ops_print_dat_to_txtfile_core(vol_flux_x, "cloverdats.dat");
  //ops_print_dat_to_txtfile_core(vol_flux_y, "cloverdats.dat");
  //ops_print_dat_to_txtfile_core(mass_flux_x, "cloverdats.dat");
  //ops_print_dat_to_txtfile_core(mass_flux_y, "cloverdats.dat");


  /**----------------------------field_summary-------------------------------**/

  //call ideal_gas again here
  ops_par_loop(ideal_gas_kernel, "ideal_gas_kernel", 2, rangexy_inner,
      ops_arg_dat(density0, sten2D, OPS_READ),
      ops_arg_dat(energy0, sten2D, OPS_READ),
      ops_arg_dat(pressure, sten2D, OPS_RW),
      ops_arg_dat(soundspeed, sten2D, OPS_WRITE));

  double vol= 0.0 , mass = 0.0, ie = 0.0, ke = 0.0, press = 0.0;

  ops_par_loop(field_summary_kernel, "field_summary_kernel", 2, rangexy_inner,
      ops_arg_dat(volume, sten2D, OPS_READ),
      ops_arg_dat(density0, sten2D, OPS_READ),
      ops_arg_dat(energy0, sten2D, OPS_READ),
      ops_arg_dat(pressure, sten2D, OPS_READ),
      ops_arg_dat(xvel0, sten2D_4point, OPS_READ),
      ops_arg_dat(yvel0, sten2D_4point, OPS_READ),
      ops_arg_gbl(&vol, 1, OPS_WRITE),
      ops_arg_gbl(&mass, 1, OPS_WRITE),
      ops_arg_gbl(&ie, 1, OPS_WRITE),
      ops_arg_gbl(&ke, 1, OPS_WRITE),
      ops_arg_gbl(&press, 1, OPS_WRITE));

  ops_printf("Problem initialised and generated\n\n");

  printf("              %-10s  %-10s  %-10s  %-10s  %-15s  %-15s  %-15s\n",
  "Volume","Mass","Density","Pressure","Internal Energy","Kinetic Energy","Total Energy");
  printf("step:   %3d   %-10.3E  %-10.3E  %-10.3E  %-10.3E  %-15.3E  %-15.3E  %-15.3E\n\n",
          step, vol, mass, mass/vol, press/vol, ie, ke, ie+ke);



  /***************************************************************************
  **-----------------------------hydro loop---------------------------------**
  /**************************************************************************/

  step = step + 1;

  //CALL timestep() - > calls viscosity kernel and calc_dt kernel



  //ops_print_dat_to_txtfile_core(vertexx, "cloverdats.dat");
  //ops_print_dat_to_txtfile_core(vertexdx, "cloverdats.dat");
  //ops_print_dat_to_txtfile_core(vertexy, "cloverdats.dat");
  //ops_print_dat_to_txtfile_core(vertexdy, "cloverdats.dat");
  //ops_print_dat_to_txtfile_core(cellx, "cloverdats.dat");
  //ops_print_dat_to_txtfile_core(celldx, "cloverdats.dat");
  //ops_print_dat_to_txtfile_core(celly, "cloverdats.dat");
  //ops_print_dat_to_txtfile_core(celldy, "cloverdats.dat");
  //ops_print_dat_to_txtfile_core(volume, "cloverdats.dat");
  //ops_print_dat_to_txtfile_core(xarea, "cloverdats.dat");
  //ops_print_dat_to_txtfile_core(yarea, "cloverdats.dat");

  //ops_print_dat_to_txtfile_core(vertexx, "cloverdats.dat");
  //ops_print_dat_to_txtfile_core(vertexy, "cloverdats.dat");
  //ops_print_dat_to_txtfile_core(density0, "cloverdats.dat");
  //ops_print_dat_to_txtfile_core(energy0, "cloverdats.dat");
  //ops_print_dat_to_txtfile_core(xvel0, "cloverdats.dat");
  //ops_print_dat_to_txtfile_core(yvel0, "cloverdats.dat");

  //ops_print_dat_to_txtfile_core(pressure, "cloverdats.dat");
  //ops_print_dat_to_txtfile_core(soundspeed, "cloverdats.dat");


  printf("\n\n");

  ops_exit();
}


/*
initialise -
initialise_chunk_kernel.f90 - strightforward
generate_chunk_kernel.f90 - initialization .. complex
ideal_gas_kernel.f90 - somewhat ok
update_halo_kernel.f90 - boundary updating
field_summary_kernel.f90 - complex


hydro -
PdV_kernel.f90
revert_kernel.f90 - strightforward
accelerate_kernel.f90 - strightforward
flux_calc_kernel.f90 - strightforward
advec_cell_kernel.f90
advec_mom_kernel.f90 - complex
reset_field_kernel.f90 - strightforward


timestep -
calc_dt_kernel.f90 - complex
viscosity_kernel.f90


pack_kernel.f90 - mpi buffer packing
*/
