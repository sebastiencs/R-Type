
set(COMMON_INCLUDES
  ${CMAKE_CURRENT_SOURCE_DIR}/includes
  ${CMAKE_CURRENT_SOURCE_DIR}/includes/Paquet
  PARENT_SCOPE
  )

file(GLOB
  CURRENTSOURCES
  includes/Debug.hh
  includes/I*
  includes/Thread.hh
  includes/Socket.hh
  includes/Player.hh
  includes/Timer.hh
  includes/Addr.hh
  includes/Paquet/*
  src/Timer.cpp
  src/Addr.cpp
  src/Buffer.cpp
  src/Paquet/*
  src/Player.cpp
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
    src/*Win.cpp
    includes/*Win.hh
    includes/WSA.hh
    )

endif()

set(COMMON_SOURCES
  ${COMMON_SOURCES}
  ${CURRENTSOURCES}
  PARENT_SCOPE
  )
