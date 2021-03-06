cmake_minimum_required(VERSION 3.0)
find_package(MPI)
enable_language(C CXX)
include(CheckLanguage)
check_language(CUDA)
if(CMAKE_CUDA_COMPILER)
    enable_language(CUDA)
    set(CUDA_FOUND ON)
endif()


# Pass 3rd argument to use HDF5, 4th is a list of additional sources
macro(BUILD_OPS_C_SAMPLE Name InputSource)
    OPS_C_TARGET(${Name} ${InputSource} "${CMAKE_CURRENT_BINARY_DIR}/ops")

    set(DO_MPI ${MPI_FOUND})
    set(DO_SEQ YES)
    if(${ARGC} GREATER 2)
        set(UseHDF5 ${ARGV2})
        if (UseHDF5)
            if ( HDF5_IS_PARALLEL )
                set(DO_SEQ FALSE)
            else()
                set(DO_MPI FALSE)
            endif()
        endif()
    endif()
    if (${ARGC} GREATER 3)
        set(EXTRA_SRC ${ARGV3})
    endif()


    if (DO_SEQ)
        add_executable(${Name}_omp
            ${OPS_${Name}_BASEOUTPUT}
            ${OPS_${Name}_MPI_OpenMP_KERNELS}
            ${${EXTRA_SRC}}
            )
        target_include_directories(${Name}_omp
            PRIVATE
                ${CMAKE_CURRENT_SOURCE_DIR}
                ${OPS_C_INCLUDE_DIR}
                )
        target_link_libraries(${Name}_omp ops_seq)
        if (UseHDF5)
            target_link_libraries(${Name}_omp ops_hdf5_seq)
        endif()


        if (TARGET ops_cuda)
            add_executable(${Name}_cuda
                ${OPS_${Name}_BASEOUTPUT}
                ${OPS_${Name}_CUDA_KERNELS}
                ${${EXTRA_SRC}}
                )
            target_include_directories(${Name}_cuda
                PRIVATE
                    ${CMAKE_CURRENT_SOURCE_DIR}
                    ${OPS_C_INCLUDE_DIR}
                    )
            target_link_libraries(${Name}_cuda ops_cuda)
            if (UseHDF5)
                target_link_libraries(${Name}_cuda ops_hdf5_seq)
            endif()
        endif()
    endif()
    

    if (DO_MPI)
        add_executable(${Name}_mpi
            ${OPS_${Name}_BASEOUTPUT}
            ${OPS_${Name}_MPI_OpenMP_KERNELS}
            ${${EXTRA_SRC}}
            )
        target_include_directories(${Name}_mpi
            PRIVATE
                ${CMAKE_CURRENT_SOURCE_DIR}
                ${OPS_C_INCLUDE_DIR}
                )
        target_link_libraries(${Name}_mpi ops_mpi)
        if (UseHDF5)
            target_link_libraries(${Name}_mpi ops_hdf5_mpi)
        endif()

        if (TARGET ops_mpi_cuda)
            add_executable(${Name}_cuda_mpi
                ${OPS_${Name}_BASEOUTPUT}
                ${OPS_${Name}_CUDA_KERNELS}
                ${${EXTRA_SRC}}
                )
            target_include_directories(${Name}_cuda_mpi
                PRIVATE
                    ${CMAKE_CURRENT_SOURCE_DIR}
                    ${OPS_C_INCLUDE_DIR}
                    )
            target_link_libraries(${Name}_cuda_mpi ops_mpi_cuda)
            if (UseHDF5)
                target_link_libraries(${Name}_cuda_mpi ops_hdf5_mpi)
            endif()
        endif()
    endif()



endmacro()


add_subdirectory(access)
add_subdirectory(CloverLeaf)
#add_subdirectory(CloverLeaf_3D)
#add_subdirectory(CloverLeaf_3D_HDF5)
#add_subdirectory(complex_numbers)
#add_subdirectory(laplace2d_tutorial)
add_subdirectory(lowdim_test)
add_subdirectory(mblock)
#add_subdirectory(mblock4D)
add_subdirectory(mb_shsgc)
#add_subdirectory(mgrid)
#add_subdirectory(multiDim)
#add_subdirectory(multiDim3D)
#add_subdirectory(multiDim_HDF5)
add_subdirectory(poisson)
add_subdirectory(shsgc)
#add_subdirectory(TeaLeaf)
