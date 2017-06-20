![logo](doc/flecsph_logo_bg.png)


<aside class="warning">
The distributed version of gravitation with FMM is not working yet
Working on it
</aside>

# SPH on FleCSI 

This project is an implementation of SPH problem using FleCSI framework.

# Getting the Code 

    % git clone --recursive git@gitlab.lanl.gov:laristra/flecsph.git

# Requirements

Before trying to compile you need to install on your system: 

- FleCSI thrird party
- FleCSI = compile legion

The installation steps are the followings: 

On DARWIN load the modules: 

    % module load gcc/6.2.0
    % module load openmpi/2.0.1-gcc_6.2.0
    % module load git/2.8.0
    % module load cinch/cinch-utils
    % module load cmake/3.7.1
    % module load boost/1.59.0_gcc-6.2.0

Then install the flecsi third libraries

    % git clone --recursive https://github.com/laristra/flecsi-third-party.git
    % mkdir build ; cd build
    % ccmake ../

Here have all ON except: 
- ENABLE_EXODUS OFF 
- ENABLE_SCOTCH OFF
- METIS_INT64 OFF
- USE_SYSTEM_LIBS OFF
- GASnet_CONDUIT mpi
and set a path for the CMAKE_INSTALL_PREFIX like /home/XXX/local/

And

    % make ; make install 

Then you will have to install FleCSI. 

    % git clone --recursive https://github.com/laristra/flecsi.git

here we need to change to the flecsph branch 

    % git checkout flecsph 
    % mkdir build ; cd build 
    % ccmake ../

Here add:
- ENABLE_MPI and ENABLE_OPENMP 
- Set FLECSI_RUNTIME_MODEL legion
and set a path for 
- CMAKE_INSTALL_PREFIX like /home/XXX/local/

    % make ; make install 

Then download and build FleCSPH.


# Build 

    % mkdir build
    % cd build 
    % ccmake ../ 
Here the settings are: 
- 
- ENABLE_MPI: ON
- ENABLE_OPENMPI: ON
- FLECSI_RUNTIME_MODEL: legion
    % make 


# Input File structure 

For the input file we are using the H5hut format. 
Headers containts general informations like: 

- Number of particles: "nparticles"
- Dimension: "dimension"
- Timestep: "timestep"
- Is fixed timestep used ? "used_fixed_timestep"

Not implemented yet: 
- Physics constants ? 
- Different files for output ? See Oleg for that

Then for each Step we save:

Header:
- Timestep "timestep"
- ???

Particles:
- Position X: "x"
- Position Y: "y" 
- Position Z: "z" 
- Velocity X: "vx"
- Velocity Y: "vy" 
- Velocity Z: "vz"
- Acceleration X: "ax"
- Acceleration Y: "ay"
- Acceleration Z: "az"
- Smoothing Length: "h"
- Density: "rho"
- Internal Energy: "u"
- Pressure: "P"
- Mass: "m"
- Id: "id" 
- Time step: "dt"
 
Not implemented yet:
- Particle type: "type"
- Electron fraction: "Ye"

Types are all double except for:

- id = int64_t
- nparticles = int64_t 
