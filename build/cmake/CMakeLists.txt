cmake_minimum_required(VERSION 2.8)

set ( PROJ_NAME "TerralibConverterLib" )
project ( ${PROJ_NAME} )

set ( ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../.." )
set ( SRC_DIR "${ROOT}/src" )


file ( GLOB SRCS ${SRC_DIR}/library/*.cpp )
file ( GLOB HEADERS ${SRC_DIR}/library/*.h)


add_definitions(-DTERRALIB_CONVERTER_AS_DLL)
add_library( ${PROJ_NAME} SHARED ${SRCS} ${HEADERS})