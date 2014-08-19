cmake_minimum_required(VERSION 2.8)

set ( PROJ_NAME "TerralibConverterConsole" )
project ( ${PROJ_NAME} )

IF (WIN32)
	SET(GUI_TYPE WIN32)
ELSEIF (APPLE)
	# Set some Apple MacOS Specific settings
	SET(GUI_TYPE MACOSX_BUNDLE)
ENDIF ()

IF( MSVC_IDE AND ( MSVC90 OR MSVC10 ) )
	add_definitions(/MP)
ENDIF()

set ( ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../.." )
set ( SRC_DIR "${ROOT}/src" )


file ( GLOB SRCS ${SRC_DIR}/*.cpp )
file ( GLOB HEADERS ${SRC_DIR}/*.h)

find_package ( TerralibConverterLib REQUIRED)

include_directories ( ${CONVERTER_LIBRARY_INCLUDE_DIRS} )
add_executable( ${PROJ_NAME} ${GUI_TYPE} ${SRC_DIR}/main.cpp)
target_link_libraries(${PROJ_NAME} ${CONVERTER_LIBRARY_BINARIES} )

#include_directories ( ${TE_INCLUDE_DIRS} ${TV_DIRS}} )
#target_link_libraries(${PROJ_NAME} ${TE_LIBRARIES})