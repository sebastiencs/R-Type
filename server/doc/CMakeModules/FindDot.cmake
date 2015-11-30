string(REPLACE ":" " " PATH $ENV{PATH})

find_file(
    DOT
    "dot"
    PATHS ${PATH}
    DOC "dot executable path"
)

if( ${DOT} STREQUAL "DOT-NOTFOUND" )
    set(DOT_FOUND FALSE)
    message(STATUS "Dot not found")
else()
    set(DOT_FOUND TRUE)
    execute_process(COMMAND dot -V ERROR_VARIABLE DOT_VERSION)
    string(REGEX MATCH "version (([0-9]+)\\.*)+" DOT_VERSION ${DOT_VERSION})
    message(STATUS "Found dot (${DOT_VERSION})")
endif()
