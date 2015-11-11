
set(COMMON_INCLUDES
  ${CMAKE_CURRENT_SOURCE_DIR}/includes
  PARENT_SCOPE
  )

file(GLOB
  CURRENTSOURCES
  includes/Debug.hh
  includes/I*
  includes/Thread.hh
  includes/Socket.hh
  )

set(COMMON_SOURCES
  ${CURRENTSOURCES}
  )

if (${UNIX})

  file(GLOB
    CURRENTSOURCES
    src/*Unix.cpp
    includes/*Unix.hh
    )

elseif (WIN32)

  file(GLOB
    CURRENTSOURCES
    src/*.Win.cpp
    includes/*Win.hh
    )

endif()

set(COMMON_SOURCES
  ${COMMON_SOURCES}
  ${CURRENTSOURCES}
  PARENT_SCOPE
  )
