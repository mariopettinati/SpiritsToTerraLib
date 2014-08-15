cmake_minimum_required(VERSION 2.8)

set ( PROJ_NAME "TerralibConverterLib" )
project ( ${PROJ_NAME} )

set ( ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../.." )
set ( SRC_DIR "${ROOT}/src" )


file ( GLOB SRCS ${SRC_DIR}/library/*.cpp )
file ( GLOB HEADERS ${SRC_DIR}/library/*.h)

find_package ( terralib REQUIRED COMPONENTS shp)

add_definitions(-DTERRALIB_CONVERTER_AS_DLL )
add_library( ${PROJ_NAME} SHARED ${SRCS} ${HEADERS} )

include_directories ( ${TE_INCLUDE_DIRS} ${TV_DIRS}} )
target_link_libraries(${PROJ_NAME} ${TE_LIBRARIES})