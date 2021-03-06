/*~--------------------------------------------------------------------------~*
 * Copyright (c) 2017 Los Alamos National Security, LLC
 * All rights reserved.
 *~--------------------------------------------------------------------------~*/

 /*~--------------------------------------------------------------------------~*
 * 
 * /@@@@@@@@  @@           @@@@@@   @@@@@@@@ @@@@@@@  @@      @@
 * /@@/////  /@@          @@////@@ @@////// /@@////@@/@@     /@@
 * /@@       /@@  @@@@@  @@    // /@@       /@@   /@@/@@     /@@
 * /@@@@@@@  /@@ @@///@@/@@       /@@@@@@@@@/@@@@@@@ /@@@@@@@@@@
 * /@@////   /@@/@@@@@@@/@@       ////////@@/@@////  /@@//////@@
 * /@@       /@@/@@//// //@@    @@       /@@/@@      /@@     /@@
 * /@@       @@@//@@@@@@ //@@@@@@  @@@@@@@@ /@@      /@@     /@@
 * //       ///  //////   //////  ////////  //       //      //  
 *
 *~--------------------------------------------------------------------------~*/

/**
 * @file main.cc
 * @author Julien Loiseau
 * @date April 2017
 * @brief Main function, start MPI with Gasnet. Then launch fleCSI runtime.  
 */

#include <flecsi.h>
#include "flecsi/execution/execution.h"
#include "flecsi/concurrency/thread_pool.h"

#if FLECSI_RUNTIME_MODEL == FLECSI_RUNTIME_MODEL_legion
  #include <mpi.h>
  #include <legion.h>
#endif

#include <unistd.h>

int main(int argc, char * argv[]){
  
//#ifdef GASNET_CONDUIT_MPI
  int provided;

#if 1


  // Normal way 
  MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);
  if (provided < MPI_THREAD_MULTIPLE)
    printf("ERROR: Your implementation of MPI does not support "
     "MPI_THREAD_MULTIPLE which is required for use of the "
     "GASNet MPI conduit with the Legion-MPI Interop!\n");
  assert(provided == MPI_THREAD_MULTIPLE);

#else
  MPI_Init_thread(&argc,&argv,MPI_THREAD_FUNNELED,&provided); 
#endif

  int rank, size; 
  char hostname[256];
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  gethostname(hostname,256);

  std::cout<<"MPI "<<rank<<"/"<<size<<" Host="<<hostname<<std::endl;


  std::cout << "MPI_Init done, Initialize" << std::endl;
  auto retval = flecsi::execution::context_t::instance().initialize(argc,argv);
  //std::cout << "Initialize done" << std::endl;

//#ifndef GASNET_CONDUIT_MPI
  //MPI_Finalize();
//#endif

  return retval;

}


