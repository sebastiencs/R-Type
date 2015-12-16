
set(COMMON_INCLUDES
  ${CMAKE_CURRENT_SOURCE_DIR}/includes
  ${CMAKE_CURRENT_SOURCE_DIR}/includes/Paquet
  PARENT_SCOPE
  )

file (GLOB
  COMMON_SOURCES
  src/Timer.cpp
  src/Addr.cpp
  src/Buffer.cpp
  src/Player.cpp
  src/IOEvent.cpp
  src/PaquetTCP.cpp
  src/Patern.cpp
  src/Tools.cpp
  src/Mutex.cpp
  src/Enemy.cpp
  src/Object.cpp
  src/Bullet.cpp
  src/Physics.cpp
  src/Obstacle.cpp
  src/TaskScheduler.cpp
  )

file (GLOB
  COMMON_HEADERS
  includes/Debug.hh
  includes/I*
  includes/Thread.hh
  includes/Socket.hh
  includes/Player.hh
  includes/Timer.hh
  includes/Addr.hh
  includes/Mutex.hh
  includes/PaquetTCP.hh
  includes/Patern.hh
  includes/Enemy.hh
  includes/Bullet.hh
  includes/Obstacle.hh
  includes/Object.hh
  includes/ListSecure.hh
  includes/Physics.hh
  includes/DequeSecure.hh
  includes/QueueSecure.hh
  includes/Disconnected.hh
  includes/TaskScheduler.hh
  )

file(GLOB
  PAQUETSOURCES
  src/Paquet/*
  )

file(GLOB
  PAQUETHEADERS
  includes/Paquet/*
  )

set(PAQUETSOURCES
  ${PAQUETSOURCES}
  PARENT_SCOPE
)

set(PAQUETHEADERS
  ${PAQUETHEADERS}
  PARENT_SCOPE
)

if (${UNIX})

  file(GLOB
    COMMON_PLATE_SOURCES
    src/*Unix.cpp
    )

  file(GLOB
    COMMON_PLATE_HEADERS
    includes/*Unix.hh
	includes/WSA.hh
    )

elseif (WIN32)

  file(GLOB
    COMMON_PLATE_SOURCES
    src/*Win.cpp
    )

  file(GLOB
    COMMON_PLATE_HEADERS
    includes/*Win.hh
	includes/WSA.hh
    )

endif()


  set(COMMON_SOURCES
    ${COMMON_SOURCES}
    ${COMMON_PLATE_SOURCES}
    PARENT_SCOPE
  )

  set(COMMON_HEADERS
    ${COMMON_HEADERS}
    ${COMMON_PLATE_HEADERS}
    PARENT_SCOPE
  )
