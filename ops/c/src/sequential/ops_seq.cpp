/*
* Open source copyright declaration based on BSD open source template:
* http://www.opensource.org/licenses/bsd-license.php
*
* This file is part of the OPS distribution.
*
* Copyright (c) 2013, Mike Giles and others. Please see the AUTHORS file in
* the main source directory for a full list of copyright holders.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
* * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
* * Redistributions in binary form must reproduce the above copyright
* notice, this list of conditions and the following disclaimer in the
* documentation and/or other materials provided with the distribution.
* * The name of Mike Giles may not be used to endorse or promote products
* derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY Mike Giles ''AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL Mike Giles BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/** @file
  * @brief OPS sequential backend implementation
  * @author Gihan Mudalige
  * @details Implements the OPS API calls for the sequential backend
  */

#include <stdlib.h>           // for posix_memalign()
#include <ops_lib_core.h>
#include <ops_util.h>
#include <ops_exceptions.h>


void ops_init(const int argc, char **argv, const int diags) {
  ops_init_core(argc, argv, diags);
}

void ops_exit() { ops_exit_core(); }


ops_dat ops_decl_amrdat_char(ops_block block, int size, int *dat_size, int *base,
                          int *d_m, int *d_p, char *data, int type_size,
                          char const *type, char const *name) {
  int stride[OPS_MAX_DIM];
  for (int i =0; i < OPS_MAX_DIM; i++) stride[i] = 1;
  ops_dat dat = ops_decl_dat_char(block, size, dat_size, base, d_m, d_p,
                                       stride, data, type_size, type, name);
  dat->amr = 1;
  return dat;
}

ops_dat ops_decl_dat_char(ops_block block, int size, int *dat_size, int *base,
                          int *d_m, int *d_p, int *stride, char *data, int type_size,
                          char const *type, char const *name) {

  /** ----             allocate an empty dat             ---- **/
  int d_m2[OPS_MAX_DIM];
  int d_p2[OPS_MAX_DIM];
  int base2[OPS_MAX_DIM];
  int stride2[OPS_MAX_DIM];
  int size2[OPS_MAX_DIM];
  int *dat_size_orig = dat_size;

  if (block->count > 1) {
    for (int d = 0; d < block->batchdim; d++) {
      d_m2[d] = d_m[d];
      d_p2[d] = d_p[d];
      base2[d] = base[d];
      stride2[d] = stride[d];
      size2[d] = dat_size[d];
    }
    d_m2[block->batchdim] = 0;
    d_p2[block->batchdim] = 0;
    base2[block->batchdim] = 0;
    stride2[block->batchdim] = 1;
    size2[block->batchdim] = block->count;
    for (int d = block->batchdim+1; d < block->dims+1; d++) {
      d_m2[d] = d_m[d-1];
      d_p2[d] = d_p[d-1];
      base2[d] = base[d-1];
      stride2[d] = stride[d-1];
      size2[d] = dat_size[d-1];
    }
    d_m = d_m2;
    d_p = d_p2;
    stride = stride2;
    base = base2;
    dat_size = size2;
  }
  ops_dat dat = ops_decl_dat_temp_core(block, size, dat_size, base, d_m, d_p,
                                       stride, data, type_size, type, name);

  if (data != NULL && !OPS_instance::getOPSInstance()->OPS_realloc) {
    // printf("Data read in from HDF5 file or is allocated by the user\n");
    dat->user_managed =
        1; // will be reset to 0 if called from ops_decl_dat_hdf5()
    dat->is_hdf5 = 0;
    dat->hdf5_file = "none"; // will be set to an hdf5 file if called from
                             // ops_decl_dat_hdf5()
    int bytes = size * type_size;
    for (int i = 0; i < block->dims+1; i++)
      bytes = bytes * dat->size[i];
  } else {
    // Allocate memory immediately
    int bytes = size * type_size;

    if (block->batchdim !=0) {
      // Compute    padding x-dim for vecotrization
      int x_pad = (1+((dat->size[0]-1)/SIMD_VEC))*SIMD_VEC - dat->size[0];
      dat->size[0] += x_pad;
      dat->d_p[0] += x_pad;
      //printf("\nPadded size is %d total size =%d \n",x_pad,dat->size[0]);
    }


    for (int i = 0; i < block->dims+1; i++)
      bytes = bytes * dat->size[i];
    dat->data = (char *)ops_calloc(bytes, 1); // initialize data bits to 0
    dat->user_managed = 0;
    dat->mem = bytes;
    if (data != NULL && OPS_instance::getOPSInstance()->OPS_realloc) {
      ops_convert_layout(data, dat->data, block, size,
                            dat->size, dat_size_orig, type_size,
                            OPS_instance::getOPSInstance()->OPS_hybrid_layout ? 
                              OPS_instance::getOPSInstance()->ops_batch_size : 0);
    }
  }

  if (block->count > 1)
    dat->amr = 1;
  else
    dat->amr = 0;

  // Compute offset in bytes to the base index
  dat->base_offset = 0;
  long cumsize = 1;
  for (int i = 0; i < block->dims+1; i++) {
    if (i == block->batchdim) dat->batch_offset = cumsize * (OPS_instance::getOPSInstance()->OPS_soa ? dat->type_size : dat->elem_size);
    dat->base_offset +=
        (OPS_instance::getOPSInstance()->OPS_soa ? dat->type_size : dat->elem_size)
        * cumsize * (-dat->base[i] - dat->d_m[i]);
    cumsize *= ((i == block->batchdim && OPS_instance::getOPSInstance()->OPS_hybrid_layout!=0) ?
                 OPS_instance::getOPSInstance()->ops_batch_size : dat->size[i]);
  }

  if (OPS_instance::getOPSInstance()->OPS_hybrid_layout && block->count > 1) {
    cumsize /= OPS_instance::getOPSInstance()->ops_batch_size;
    dat->batch_offset = cumsize * (OPS_instance::getOPSInstance()->OPS_soa ? dat->type_size : dat->elem_size);
  }

  return dat;
}

ops_halo ops_decl_halo(ops_dat from, ops_dat to, int *iter_size, int *from_base,
                       int *to_base, int *from_dir, int *to_dir) {
  return ops_decl_halo_core(from, to, iter_size, from_base, to_base, from_dir,
                            to_dir);
}

void ops_halo_transfer(ops_halo_group group) {
  ops_execute();
  // Test contents of halo group
  /*ops_halo halo;
  for(int i = 0; i<group->nhalos; i++) {
    halo = group->halos[i];
    printf("halo->from->name = %s, halo->to->name %s\n",halo->from->name,
  halo->to->name);
    for (int i = 0; i < halo->from->block->dims; i++) {
      printf("halo->iter_size[i] %d ",halo->iter_size[i]);
      printf("halo->from_base[i] %d ",halo->from_base[i]);
      printf("halo->to_base[i] %d ",halo->to_base[i]);
      printf("halo->from_dir[i] %d ",halo->from_dir[i]);
      printf("halo->to_dir[i] %d \n",halo->to_dir[i]);
    }
  }
  //return;*/
  // printf("group->nhalos %d\n",group->nhalos);
  for (int h = 0; h < group->nhalos; h++) {
    ops_halo halo = group->halos[h];
    int size = halo->from->elem_size * halo->iter_size[0];
    for (int i = 1; i < halo->from->block->dims; i++)
      size *= halo->iter_size[i];
    if (size > OPS_instance::getOPSInstance()->ops_halo_buffer_size) {
      OPS_instance::getOPSInstance()->ops_halo_buffer = (char *)ops_realloc(OPS_instance::getOPSInstance()->ops_halo_buffer, size);
      OPS_instance::getOPSInstance()->ops_halo_buffer_size = size;
    }

    // copy to linear buffer from source
    int ranges[OPS_MAX_DIM * 2] = {0};
    int step[OPS_MAX_DIM] = {0};
    int buf_strides[OPS_MAX_DIM] = {0};
    for (int i = 0; i < OPS_MAX_DIM; i++) {
      if (halo->from_dir[i] > 0) {
        ranges[2 * i] =
            halo->from_base[i] - halo->from->d_m[i] - halo->from->base[i];
        ranges[2 * i + 1] =
            ranges[2 * i] + halo->iter_size[abs(halo->from_dir[i]) - 1];
        step[i] = 1;
      } else {
        ranges[2 * i + 1] =
            halo->from_base[i] - 1 - halo->from->d_m[i] - halo->from->base[i];
        ranges[2 * i] =
            ranges[2 * i + 1] + halo->iter_size[abs(halo->from_dir[i]) - 1];
        step[i] = -1;
      }
      buf_strides[i] = 1;
      for (int j = 0; j != abs(halo->from_dir[i]) - 1; j++)
        buf_strides[i] *= halo->iter_size[j];
    }
    int OPS_soa = OPS_instance::getOPSInstance()->OPS_soa;
    char *ops_halo_buffer =  OPS_instance::getOPSInstance()->ops_halo_buffer;
  #if OPS_MAX_DIM>4
    #if OPS_MAX_DIM == 5
    #ifdef _OPENMP
    #pragma omp parallel for collapse(5)
    #endif
    #endif
    for (int m = MIN(ranges[8], ranges[9] + 1);
         m < MAX(ranges[8] + 1, ranges[9]); m++) {
  #else
    int m = 0;
    {
  #endif
    #if OPS_MAX_DIM>3
      #if OPS_MAX_DIM == 4
      #ifdef _OPENMP
      #pragma omp parallel for collapse(4)
      #endif
      #endif
      for (int l = MIN(ranges[6], ranges[7] + 1);
           l < MAX(ranges[6] + 1, ranges[7]); l++) {
    #else
      int l = 0;
      {
    #endif
      #if OPS_MAX_DIM>2
        #if OPS_MAX_DIM == 3
        #ifdef _OPENMP
        #pragma omp parallel for collapse(3)
        #endif
        #endif
        for (int k = MIN(ranges[4], ranges[5] + 1);
             k < MAX(ranges[4] + 1, ranges[5]); k++) {
      #else
        int k = 0;
        {
      #endif
        #if OPS_MAX_DIM>1
          #if OPS_MAX_DIM == 2
          #ifdef _OPENMP
          #pragma omp parallel for collapse(2)
          #endif
          #endif
          for (int j = MIN(ranges[2], ranges[3] + 1);
               j < MAX(ranges[2] + 1, ranges[3]); j++) {
        #else
          int j = 0;
          {
        #endif
            for (int i = MIN(ranges[0], ranges[1] + 1);
                 i < MAX(ranges[0] + 1, ranges[1]); i++) {
              for (int d = 0; d < halo->from->dim; d++) {
                memcpy(ops_halo_buffer +
                         (
                        #if OPS_MAX_DIM > 4
                          (m - ranges[8]) * step[4] * buf_strides[4] +
                        #endif
                        #if OPS_MAX_DIM > 3
                          (l - ranges[6]) * step[3] * buf_strides[3] +
                        #endif
                        #if OPS_MAX_DIM > 2
                          (k - ranges[4]) * step[2] * buf_strides[2] +
                        #endif
                        #if OPS_MAX_DIM > 1
                          (j - ranges[2]) * step[1] * buf_strides[1] +
                        #endif
                          (i - ranges[0]) * step[0] * buf_strides[0]) *
                             halo->from->elem_size + d * halo->from->type_size,
                     halo->from->data +
                         (OPS_soa ? 
                           ((
                            #if OPS_MAX_DIM > 4
                            m * halo->from->size[0] * halo->from->size[1] * halo->from->size[2] * halo->from->size[3] +
                            #endif
                            #if OPS_MAX_DIM > 3
                            l * halo->from->size[0] * halo->from->size[1] * halo->from->size[2] +
                            #endif
                            #if OPS_MAX_DIM > 2
                            k * halo->from->size[0] * halo->from->size[1] +
                            #endif
                            #if OPS_MAX_DIM > 1
                            j * halo->from->size[0] +
                            #endif
                            i) +
                             d * halo->from->size[0]
                              #if OPS_MAX_DIM > 4
                              * halo->from->size[4]
                              #endif
                              #if OPS_MAX_DIM > 3
                              * halo->from->size[3]
                              #endif
                              #if OPS_MAX_DIM > 2
                              * halo->from->size[2]
                              #endif
                              #if OPS_MAX_DIM > 1
                              * halo->from->size[1]
                              #endif
                            ) * halo->from->type_size

                         : (
                            #if OPS_MAX_DIM > 4
                            m * halo->from->size[0] * halo->from->size[1] * halo->from->size[2] * halo->from->size[3] +
                            #endif
                            #if OPS_MAX_DIM > 3
                            l * halo->from->size[0] * halo->from->size[1] * halo->from->size[2] +
                            #endif
                            #if OPS_MAX_DIM > 2
                            k * halo->from->size[0] * halo->from->size[1] +
                            #endif
                            #if OPS_MAX_DIM > 1
                            j * halo->from->size[0] +
                            #endif
                            i) *
                            halo->from->elem_size + d * halo->from->type_size),
                     halo->from->type_size);
              }
            }
          }
        }
      }
    }

    // copy from linear buffer to target
    for (int i = 0; i < OPS_MAX_DIM; i++) {
      if (halo->to_dir[i] > 0) {
        ranges[2 * i] = halo->to_base[i] - halo->to->d_m[i] - halo->to->base[i];
        ranges[2 * i + 1] =
            ranges[2 * i] + halo->iter_size[abs(halo->to_dir[i]) - 1];
        step[i] = 1;
      } else {
        ranges[2 * i + 1] =
            halo->to_base[i] - 1 - halo->to->d_m[i] - halo->to->base[i];
        ranges[2 * i] =
            ranges[2 * i + 1] + halo->iter_size[abs(halo->to_dir[i]) - 1];
        step[i] = -1;
      }
      buf_strides[i] = 1;
      for (int j = 0; j != abs(halo->to_dir[i]) - 1; j++)
        buf_strides[i] *= halo->iter_size[j];
    }
    OPS_soa = OPS_instance::getOPSInstance()->OPS_soa;
    ops_halo_buffer =  OPS_instance::getOPSInstance()->ops_halo_buffer;
  #if OPS_MAX_DIM>4
    #if OPS_MAX_DIM == 5
    #ifdef _OPENMP
    #pragma omp parallel for collapse(5)
    #endif
    #endif
    for (int m = MIN(ranges[8], ranges[9] + 1);
         m < MAX(ranges[8] + 1, ranges[9]); m++) {
  #else
    int m = 0;
    {
  #endif
    #if OPS_MAX_DIM>3
      #if OPS_MAX_DIM == 4
      #ifdef _OPENMP
      #pragma omp parallel for collapse(4)
      #endif
      #endif
      for (int l = MIN(ranges[6], ranges[7] + 1);
           l < MAX(ranges[6] + 1, ranges[7]); l++) {
    #else
      int l = 0;
      {
    #endif
      #if OPS_MAX_DIM>2
        #if OPS_MAX_DIM == 3
        #ifdef _OPENMP
        #pragma omp parallel for collapse(3)
        #endif
        #endif
        for (int k = MIN(ranges[4], ranges[5] + 1);
             k < MAX(ranges[4] + 1, ranges[5]); k++) {
      #else
        int k = 0;
        {
      #endif
        #if OPS_MAX_DIM>1
          #if OPS_MAX_DIM == 2
          #ifdef _OPENMP
          #pragma omp parallel for collapse(2)
          #endif
          #endif
          for (int j = MIN(ranges[2], ranges[3] + 1);
               j < MAX(ranges[2] + 1, ranges[3]); j++) {
        #else
          int j = 0;
          {
        #endif
            for (int i = MIN(ranges[0], ranges[1] + 1);
                 i < MAX(ranges[0] + 1, ranges[1]); i++) {
              for (int d = 0; d < halo->to->dim; d++) {
                memcpy(halo->to->data +
                       (OPS_soa ?
                         (
                          #if OPS_MAX_DIM > 4
                          m * halo->to->size[0] * halo->to->size[1] * halo->to->size[2] * halo->to->size[3] +
                          #endif
                          #if OPS_MAX_DIM > 3
                          l * halo->to->size[0] * halo->to->size[1] * halo->to->size[2] +
                          #endif
                          #if OPS_MAX_DIM > 2
                          k * halo->to->size[0] * halo->to->size[1] +
                          #endif
                          #if OPS_MAX_DIM > 1
                          j * halo->to->size[0] +
                          #endif
                          i +
                          d * halo->to->size[0]
                            #if OPS_MAX_DIM > 4
                            * halo->to->size[4]
                            #endif
                            #if OPS_MAX_DIM > 3
                            * halo->to->size[3]
                            #endif
                            #if OPS_MAX_DIM > 2
                            * halo->to->size[2]
                            #endif
                            #if OPS_MAX_DIM > 1
                            * halo->to->size[1]
                            #endif
                          ) * halo->to->type_size
                        :(
                          #if OPS_MAX_DIM > 4
                          m * halo->to->size[0] * halo->to->size[1] * halo->to->size[2] * halo->to->size[3] +
                          #endif
                          #if OPS_MAX_DIM > 3
                          l * halo->to->size[0] * halo->to->size[1] * halo->to->size[2] +
                          #endif
                          #if OPS_MAX_DIM > 2
                          k * halo->to->size[0] * halo->to->size[1] +
                          #endif
                          #if OPS_MAX_DIM > 1
                          j * halo->to->size[0] +
                          #endif
                          i) *
                             halo->to->elem_size + d * halo->to->type_size),
                     ops_halo_buffer +
                         (
                        #if OPS_MAX_DIM > 4
                          (m - ranges[8]) * step[4] * buf_strides[4] +
                        #endif
                        #if OPS_MAX_DIM > 3
                          (l - ranges[6]) * step[3] * buf_strides[3] +
                        #endif
                        #if OPS_MAX_DIM > 2
                          (k - ranges[4]) * step[2] * buf_strides[2] +
                        #endif
                        #if OPS_MAX_DIM > 1
                          (j - ranges[2]) * step[1] * buf_strides[1] +
                        #endif
                          (i - ranges[0]) * step[0] * buf_strides[0]) *
                             halo->to->elem_size + d * halo->to->type_size,
                     halo->to->type_size);
              }
            }
          }
        }
      }
    }
  }
}

ops_arg ops_arg_dat(ops_dat dat, int dim, ops_stencil stencil, char const *type,
                    ops_access acc) {
  ops_arg temp = ops_arg_dat_core(dat, stencil, acc);
  (&temp)->dim = dim;
  return temp;
}

ops_arg ops_arg_dat_opt(ops_dat dat, int dim, ops_stencil stencil,
                        char const *type, ops_access acc, int flag) {
  ops_arg temp = ops_arg_dat_core(dat, stencil, acc);
  (&temp)->dim = dim;
  (&temp)->opt = flag;
  return temp;
}

ops_arg ops_arg_gbl_char(char *data, int dim, int size, ops_access acc) {
  return ops_arg_gbl_core(data, dim, size, acc);
}

ops_arg ops_arg_dat2(ops_dat dat, int idx, int dim, ops_stencil stencil, char const *type,
                    ops_access acc) {
  ops_arg temp = ops_arg_dat_core(dat, stencil, acc);
  temp.dim = dim;
  temp.idx = idx;
  temp.argtype = OPS_ARG_DAT2;
  return temp;
}

ops_arg ops_arg_restrict(ops_dat dat, int idx, int dim, ops_stencil stencil, char const *type,
                    ops_access acc) {
  ops_arg temp = ops_arg_dat_core(dat, stencil, acc);
  temp.argtype = OPS_ARG_RESTRICT;
  temp.dim = dim;
  temp.idx = idx;
  if (stencil->type != 2) {ops_printf("Error, ops_arg_restrict used, but stencil is not restrict stencil\n");exit(-1);}
  return temp;
}

ops_arg ops_arg_prolong(ops_dat dat, int idx, int dim, ops_stencil stencil, char const *type,
                    ops_access acc) {
  ops_arg temp = ops_arg_dat_core(dat, stencil, acc);
  temp.argtype = OPS_ARG_PROLONG;
  temp.dim = dim;
  temp.idx = idx;
  if (stencil->type != 2) {ops_printf("Error, ops_arg_prolong used, but stencil is not prolong stencil\n");exit(-1);}
  return temp;
}


void ops_reduction_result_char(ops_reduction handle, int type_size, char *ptr) {
  ops_execute();
  ops_checkpointing_reduction(handle);
  ops_amr_reduction_result(handle);
  memcpy(ptr, handle->data, handle->size * handle->batchsize);
  handle->initialized = 0;
}

void ops_print_dat_to_txtfile(ops_dat dat, const char *file_name) {
  ops_print_dat_to_txtfile_core(dat, file_name);
}

void ops_get_data(ops_dat dat) {
  // data already on the host .. do nothing
  (void)dat;
}

void ops_put_data(ops_dat dat) {
  // data already on the host .. do nothing
  (void)dat;
}

void ops_decl_const_char(int dim, char const *type, int typeSize, char *data,
                         char const *name) {
  (void)dim;
  (void)type;
  (void)typeSize;
  (void)data;
  (void)name;
}

void ops_partition(const char *routine) {
  (void)routine;
  // printf("Partitioning ops_dats\n");
}

void ops_H_D_exchanges_host(ops_arg *args, int nargs) {
  (void)nargs;
  (void)args;
}

void ops_H_D_exchanges_device(ops_arg *args, int nargs) {
  (void)nargs;
  (void)args;
}

void ops_set_dirtybit_device(ops_arg *args, int nargs) {
  (void)nargs;
  (void)args;
}

void ops_cpHostToDevice(void **data_d, void **data_h, int size) {
  (void)data_d;
  (void)data_h;
  (void)size;
}

void ops_download_dat(ops_dat dat) { (void)dat; }

void ops_upload_dat(ops_dat dat) { (void)dat; }

void ops_timers(double *cpu, double *et) { ops_timers_core(cpu, et); }
