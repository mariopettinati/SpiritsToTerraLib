cmake_minimum_required(VERSION 2.8)

set ( PROJ_NAME "TerralibConverter" )
project ( ${PROJ_NAME} )

set ( ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../.." )
set ( SRC_DIR "${ROOT}/src" )

add_subdirectory ( library )

#Build console application.
OPTION ( BUILD_CONSOLE_APPLICATION "Build the console application?" ON )

if( BUILD_CONSOLE_APPLICATION )
	add_subdirectory ( console )
endif ( BUILD_CONSOLE_APPLICATION )