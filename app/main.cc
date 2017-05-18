#include <flecsi.h>
#include "flecsi/execution/execution.h"
#include "flecsi/concurrency/thread_pool.h"

#if FLECSI_RUNTIME_MODEL == FLECSI_RUNTIME_MODEL_legion
  #include <mpi.h>
  #include <legion.h>
#endif

int main(int argc, char * argv[]){
  
//#ifdef GASNET_CONDUIT_MPI
  int provided;
  MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided);
  //if (provided < MPI_THREAD_MULTIPLE)
  //  printf("ERROR: Your implementation of MPI does not support "
  //   "MPI_THREAD_MULTIPLE which is required for use of the "
  //   "GASNet MPI conduit with the Legion-MPI Interop!\n");
  //assert(provided == MPI_THREAD_MULTIPLE);
//#else
//  MPI_Init(&argc,&argv);
//#endif

  std::cout << "MPI_Init done, Initialize" << std::endl;
  auto retval = flecsi::execution::context_t::instance().initialize(argc,argv);
  //std::cout << "Initialize done" << std::endl;

//#ifndef GASNET_CONDUIT_MPI
  //MPI_Finalize();
//#endif

  return retval;

}
