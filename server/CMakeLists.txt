
set(SERVER_INCLUDES
  ${CMAKE_CURRENT_SOURCE_DIR}/includes
  PARENT_SCOPE
  )

file(GLOB
  CURRENTSOURCES
  includes/*
  src/*
  )

set(SERVER_SOURCES
  ${CURRENTSOURCES}
  PARENT_SCOPE
  )
