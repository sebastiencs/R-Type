# Author:
#  Nicolas Granger <nicolas.granger at telecom-sudparis.eu>
# Resources:
#  http://mementocodex.wordpress.com/2013/01/19/how-to-generate-code-documentation-with-doxygen-and-cmake-a-slightly-improved-approach/

# Variables and options
option(DISABLE_DOT      "Disable class graph (HAVE_DOT) in doxygen" OFF)
option(DOC_GEN_HTML     "Generate HTML documentation"    ON)
option(DOC_GEN_RTF      "Generate RTF documentation"     OFF)
option(DOC_GEN_PDF      "Generate PDF documentation"     OFF)
option(DOC_GEN_MAN      "Generate manpage documentation" OFF)
set(DOC_PROJECT_ROOT    ${PROJECT_SOURCE_DIR}          CACHE PATH   "Root of the project sources")
set(DOC_PROJECT_VERSION ""                             CACHE STRING "Documentation version")
# Or use current project version from git (empty if not a git repository)
#execute_process(COMMAND git -C ${PROJECT_SOURCE_DIR} describe --always
#                OUTPUT_VARIABLE DOC_PROJECT_VERSION ERROR_QUIET)

# Extra Cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules)
find_package(Doxygen REQUIRED) # Doxygen
find_package(Dot) # GraphViz

# Doxyfile variables
if(DOC_GEN_HTML)
  set(DOC_GENERATE_HTML "YES")
else()
  set(DOC_GENERATE_HTML "NO")
endif()

if(DOC_GEN_PDF)
  set(DOC_GENERATE_PDF "YES")
else()
  set(DOC_GENERATE_PDF "NO")
endif()

if(DOC_GEN_RTF)
  set(DOC_GENERATE_RTF "YES")
else()
  set(DOC_GENERATE_RTF "NO")
endif()

if(DOC_GEN_MAN)
  set(DOC_GENERATE_MAN "YES")
else()
  set(DOC_GENERATE_MAN "NO")
endif()

if(DOT_FOUND AND (NOT DISABLE_DOT))
  set(HAVE_DOT "YES" )
else()
  set(HAVE_DOT "NO" )
endif()

# generate Doxyfile
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

# create output directory because Doxygen won't do it
file(MAKE_DIRECTORY @DOC_OUTPUT_PATH@)

# build targets
add_custom_target(
  doc
  COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
  COMMENT "Generating documentation"
  SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
  )
  set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile PROPERTIES GENERATED 1)

# Example of extra target for any kind of preprocessing
# if(NOT DISABLE_MyPreprocessing)
#   add_custom_target(
#     docPreprocessing
#     COMMAND docpreprocessor arguments
#     COMMENT "Preprocessing documentation documentation"
#     )
#   add_dependencies(doc docPreprocessing)
# endif()
