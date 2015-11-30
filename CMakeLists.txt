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

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)

add_subdirectory(common)
add_subdirectory(server)
add_subdirectory(client)

source_group("Header Files\\Common" FILES ${COMMON_HEADERS})
source_group("Source Files\\Common" FILES ${COMMON_SOURCES})
source_group("Source Files\\Common\\Paquet" FILES ${PAQUETSOURCES})
source_group("Header Files\\Common\\Paquet" FILES ${PAQUETHEADERS})


include_directories(
  ${COMMON_INCLUDES}
  ${SERVER_INCLUDES}
  ${CLIENT_INCLUDES}
  ${SFML_INCLUDE_DIR}
  )

add_executable(
  Server
  ${COMMON_SOURCES}
  ${COMMON_HEADERS}
  ${PAQUETSOURCES}
  ${PAQUETHEADERS}
  ${SERVER_SOURCES}
  )

add_executable(
  Client
  ${COMMON_SOURCES}
  ${COMMON_HEADERS}
  ${PAQUETSOURCES}
  ${PAQUETHEADERS}
  ${CLIENT_SOURCES}
  )

set_property(GLOBAL PROPERTY CXX_STANDARD 11)
set_property(GLOBAL PROPERTY CXX_STANDARD_REQUIRED ON)

add_custom_command(TARGET Client POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:Client>/ressources
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/client/ressources" $<TARGET_FILE_DIR:Client>/ressources
  )

if (${UNIX})

  add_definitions(
    -fdiagnostics-color=always
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
    sfml-graphics
    sfml-window
    sfml-system
    )

elseif (WIN32)

  add_definitions(
    -D_SCL_SECURE_NO_WARNINGS
    -DDEBUG
    )

  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  add_custom_command(TARGET Client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${SFML_ROOT}/bin" $<TARGET_FILE_DIR:Client>
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/client/ressources" ${CMAKE_CURRENT_BINARY_DIR}
    )

  target_link_libraries(
    Client
    ${SFML_LIBRARIES}
    )

endif()
