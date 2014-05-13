//
// auto-generated by ops.py on 2014-05-13 15:00
//


// host stub function
void ops_par_loop_advec_mom_kernel_mass_flux_x(char const *name, ops_block Block, int dim, int* range,
 ops_arg arg0, ops_arg arg1) {

  buildOpenCLKernels();
  ops_arg args[2] = { arg0, arg1};

  sub_block_list sb = OPS_sub_block_list[Block->index];
  //compute localy allocated range for the sub-block
  int start_add[2];
  int end_add[2];
  for ( int n=0; n<2; n++ ){
    start_add[n] = sb->istart[n];end_add[n] = sb->iend[n]+1;
    if (start_add[n] >= range[2*n]) {
      start_add[n] = 0;
    }
    else {
      start_add[n] = range[2*n] - start_add[n];
    }
    if (end_add[n] >= range[2*n+1]) {
      end_add[n] = range[2*n+1] - sb->istart[n];
    }
    else {
      end_add[n] = sb->sizes[n];
    }
  }


  int x_size = end_add[0]-start_add[0];
  int y_size = end_add[1]-start_add[1];

  int xdim0 = args[0].dat->block_size[0]*args[0].dat->dim;
  int xdim1 = args[1].dat->block_size[0]*args[1].dat->dim;


  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(14,"advec_mom_kernel_mass_flux_x");
  ops_timers_core(&c1,&t1);

  //set up OpenCL thread blocks
  size_t globalWorkSize[3] = {((x_size-1)/OPS_block_size_x+ 1)*OPS_block_size_x, ((y_size-1)/OPS_block_size_y + 1)*OPS_block_size_y, 1};
  size_t localWorkSize[3] =  {OPS_block_size_x,OPS_block_size_y,1};




  int dat0 = args[0].dat->size;
  int dat1 = args[1].dat->size;

  cl_mem p_a[2];

  //set up initial pointers
  int base0 = dat0 * 1 * 
  (start_add[0] * args[0].stencil->stride[0] - args[0].dat->offset[0]);
  base0 = base0  + dat0 * args[0].dat->block_size[0] * 
  (start_add[1] * args[0].stencil->stride[1] - args[0].dat->offset[1]);
  base0 = base0/dat0;

  //set up initial pointers
  int base1 = dat1 * 1 * 
  (start_add[0] * args[1].stencil->stride[0] - args[1].dat->offset[0]);
  base1 = base1  + dat1 * args[1].dat->block_size[0] * 
  (start_add[1] * args[1].stencil->stride[1] - args[1].dat->offset[1]);
  base1 = base1/dat1;


  ops_H_D_exchanges_cuda(args, 2);


  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[14], 0, sizeof(cl_mem), (void*) &arg0.data_d ));
  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[14], 1, sizeof(cl_mem), (void*) &arg1.data_d ));
  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[14], 2, sizeof(cl_int), (void*) &xdim0 ));
  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[14], 3, sizeof(cl_int), (void*) &xdim1 ));
  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[14], 4, sizeof(cl_int), (void*) &base0 ));
  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[14], 5, sizeof(cl_int), (void*) &base1 ));
  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[14], 6, sizeof(cl_int), (void*) &x_size ));
  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[14], 7, sizeof(cl_int), (void*) &y_size ));

  //call/enque opencl kernel wrapper function
  clSafeCall( clEnqueueNDRangeKernel(OPS_opencl_core.command_queue, OPS_opencl_core.kernel[14], 3, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL) );
  clSafeCall( clFinish(OPS_opencl_core.command_queue) );

  ops_set_dirtybit_cuda(args, 2);
  ops_H_D_exchanges(args, 2);

  //Update kernel record
  ops_timers_core(&c2,&t2);
  OPS_kernels[14].count++;
  OPS_kernels[14].time += t2-t1;
  OPS_kernels[14].transfer += ops_compute_transfer(dim, range, &arg0);
  OPS_kernels[14].transfer += ops_compute_transfer(dim, range, &arg1);
}
