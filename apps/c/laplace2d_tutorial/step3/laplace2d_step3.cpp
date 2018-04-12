#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//Including main OPS header file, and setting 2D
#define OPS_2D
#include <ops_seq.h>
//Including applicaiton-specific "user kernels"
#include "laplace_kernels.h" 

int main(int argc, char** argv)
{
  //Initialise the OPS library, passing runtime args, and setting diagnostics level to low (1)
  ops_init(argc, argv,1);

  //Size along y
  int jmax = 1022;
  //Size along x
  int imax = 1022;
  int iter_max = 1000;

  double pi  = 2.0 * asin(1.0);
  const double tol = 1.0e-6;
  double error     = 1.0;

  double *A;
  double *Anew;

  A    = (double *)malloc((imax+2) * (jmax+2) * sizeof(double));
  Anew = (double *)malloc((imax+2) * (jmax+2) * sizeof(double));

  memset(A, 0, (imax+2) * (jmax+2) * sizeof(double));

  //
  //Declare & define key data structures
  //
  
  //The 2D block
  ops_block block = ops_decl_block(2, "my_grid");
  //The two datasets
  int size[] = {imax, jmax};
  int base[] = {0,0};
  int d_m[] = {-1,-1};
  int d_p[] = {1,1};
  ops_dat d_A    = ops_decl_dat(block, 1, size, base,
                               d_m, d_p, A,    "double", "A");
  ops_dat d_Anew = ops_decl_dat(block, 1, size, base,
                               d_m, d_p, Anew, "double", "Anew");
  //Two stencils, a 1-point, and a 5-point
  int s2d_00[] = {0,0};
  ops_stencil S2D_00 = ops_decl_stencil(2,1,s2d_00,"0,0");
  int s2d_5pt[] = {0,0, 1,0, -1,0, 0,1, 0,-1};
  ops_stencil S2D_5pt = ops_decl_stencil(2,5,s2d_5pt,"5pt");

  // set boundary conditions
  int bottom_range[] = {-1, imax+1, -1, 0};
  ops_par_loop(set_zero, "set_zero", block, 2, bottom_range,
      ops_arg_dat(d_A, 1, S2D_00, "double", OPS_WRITE));

  int top_range[] = {-1, imax+1, jmax, jmax+1};
  ops_par_loop(set_zero, "set_zero", block, 2, top_range,
      ops_arg_dat(d_A, 1, S2D_00, "double", OPS_WRITE));

  for (int j = 0; j < jmax+2; j++)
  {
    A[(j)*(imax+2)+0] = sin(pi * j / (jmax+1));
  }

  for (int j = 0; j < imax+2; j++)
  {
    A[(j)*(imax+2)+imax+1] = sin(pi * j / (jmax+1))*exp(-pi);
  }

  printf("Jacobi relaxation Calculation: %d x %d mesh\n", imax+2, jmax+2);

  int iter = 0;

  ops_par_loop(set_zero, "set_zero", block, 2, bottom_range,
      ops_arg_dat(d_Anew, 1, S2D_00, "double", OPS_WRITE));

  ops_par_loop(set_zero, "set_zero", block, 2, top_range,
      ops_arg_dat(d_Anew, 1, S2D_00, "double", OPS_WRITE));

  for (int j = 1; j < jmax+2; j++)
    Anew[(j)*(imax+2)+0]   = sin(pi * j / (jmax+1));

  for (int j = 1; j < jmax+2; j++)
    Anew[(j)*(imax+2)+jmax+1] = sin(pi * j / (jmax+1))*expf(-pi);


  while ( error > tol && iter < iter_max )
  {
    error = 0.0;
    for( int j = 1; j < jmax+1; j++ )
    {
      for( int i = 1; i < imax+1; i++)
      {
        Anew[(j)*(imax+2)+i] = 0.25f * ( A[(j)*(imax+2)+i+1] + A[(j)*(imax+2)+i-1]
            + A[(j-1)*(imax+2)+i] + A[(j+1)*(imax+2)+i]);
        error = fmax( error, fabs(Anew[(j)*(imax+2)+i]-A[(j)*(imax+2)+i]));
      }
    }

    int interior_range[] = {0,imax,0,jmax};
    ops_par_loop(copy, "copy", block, 2, interior_range,
        ops_arg_dat(d_A,    1, S2D_00, "double", OPS_WRITE),
        ops_arg_dat(d_Anew, 1, S2D_00, "double", OPS_READ));

    if(iter % 100 == 0) printf("%5d, %0.6f\n", iter, error);        
    iter++;
  }

  printf("%5d, %0.6f\n", iter, error);        

  double err_diff = fabs((100.0*(error/2.413562747621e-04))-100.0);
  printf("Total error is within %3.15E %% of the expected error\n",err_diff);
  if(err_diff < 0.001)
    printf("This run is considered PASSED\n");
  else
    printf("This test is considered FAILED\n");

  //Finalising the OPS library
  ops_exit();
  free(A);
  free(Anew);
  return 0;
}

