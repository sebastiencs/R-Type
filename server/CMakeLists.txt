cmake_minimum_required(VERSION 3.0)

function(ForceBuildDir)
  if("${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")
    message("######################################################")
    message("# Run cmake in a build directory:")
    message("#")
    message("# rm -rf CMakeFiles/ cmake_install.cmake CMakeCache.txt")
    message("# mkdir build")
    message("# cd build")
    message("# cmake ..")
    message("#")
    message("######################################################")
    message(FATAL_ERROR "Quitting configuration")
  endif()
endfunction()

ForceBuildDir()

project(Server)

include_directories(
  includes
  ../common/includes
  )

file(
  GLOB_RECURSE
  source_files
  src/*
  includes/*
  ../common/src/*
  ../common/includes/*
  )

add_executable(
  server
  ${source_files}
  )

add_definitions(
  -std=c++11
  -DDEBUG
  )

target_link_libraries(
  server
  pthread
  dl
  )
