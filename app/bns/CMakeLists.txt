#----------------------------------------------------------------------------#
# Copyright (c) 2017 Los Alamos National Security, LLC
# All rights reserved.
#----------------------------------------------------------------------------#

 #------------------------------------------------------------------------------#
# Debug and release flags     
#------------------------------------------------------------------------------#

set(CMAKE_CXX_FLAGS_DEBUG 
  "-g -pg -O2 -Wall -Wno-return-type -Wno-unused -Wno-comment -Wno-parentheses")
set(CMAKE_CXX_FLAGS_RELEASE 
  "-O2 -Wall -Wno-return-type -Wno-unused -Wno-comment -Wno-parentheses") 

#------------------------------------------------------------------------------#
# Includes
#------------------------------------------------------------------------------#
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include/bodies/)
include_directories(${CMAKE_SOURCE_DIR}/include/physics/default)
include_directories(${CMAKE_SOURCE_DIR}/app/bns/include)
include_directories(${CMAKE_SOURCE_DIR}/mpisph)
include_directories(
  ${CMAKE_SOURCE_DIR}/third-party-libraries/ScalingFramework/IOTests)

#------------------------------------------------------------------------------#
# Executables    
#------------------------------------------------------------------------------#
# Binary Neutron Star
add_executable(bns 
  main.cc 
  main_driver.cc 
  ${FleCSI_RUNTIME}/runtime_driver.cc
)

target_link_libraries(bns ${FleCSPH_LIBRARIES})

add_definitions(-DFLECSI_ENABLE_SPECIALIZATION_TLT_INIT)
add_definitions(-DFLECSI_OVERRIDE_DEFAULT_SPECIALIZATION_DRIVER)
