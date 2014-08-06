cmake_minimum_required(VERSION 2.8)

set ( PROJ_NAME "SpiritsToTerraLib" )

project ( ${PROJ_NAME} )

add_executable( ${PROJ_NAME} WIN32 ../../src/console/main.cpp)