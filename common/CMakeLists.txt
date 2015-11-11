cmake_minimum_required(VERSION 3.0)

include_directories(
  includes
  )

file(
	GLOB
	source_files
	includes/I*
	includes/Thread.hh
	includes/Socket.hh
)
  
if(${UNIX})

	file(
	GLOB
	source_files
	src/*Unix.cpp
	includes/*Unix.hh
	)
	
else if (WIN32)

	file(
	GLOB
	source_files
	src/*.Win.cpp
	)

endif()
