cmake_minimum_required(VERSION 2.8)

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

project("R-Type")

add_subdirectory(common)
add_subdirectory(server)
add_subdirectory(client)

include_directories(
  ${COMMON_INCLUDES}
  ${SERVER_INCLUDES}
  ${CLIENT_INCLUDES}
  )

add_executable(
  Server
  ${COMMON_SOURCES}
  ${SERVER_SOURCES}
  )

add_executable(
  Client
  ${COMMON_SOURCES}
  ${CLIENT_SOURCES}
  )

set_property(GLOBAL PROPERTY CXX_STANDARD 11)
set_property(GLOBAL PROPERTY CXX_STANDARD_REQUIRED ON)

if (${UNIX})

  add_definitions(
    -std=c++11
    -ggdb
    -Wall -Wextra
    -DDEBUG
    )

  target_link_libraries(
    Server
    pthread
    dl
    )

  target_link_libraries(
    Client
    pthread
    dl
    )

endif()
