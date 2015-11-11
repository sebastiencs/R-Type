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

add_subdirectory(common)
add_subdirectory(server)


add_executable(
  server
  ${source_files}
  )

add_definitions(
  -std=c++11
  -DDEBUG
  )

set_property(TARGET server PROPERTY CXX_STANDARD 11)
set_property(TARGET server PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(
  server
  pthread
  dl
  )
