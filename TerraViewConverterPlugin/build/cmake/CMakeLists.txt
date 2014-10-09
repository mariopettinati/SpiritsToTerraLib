cmake_minimum_required(VERSION 2.8)

set ( PROJ_NAME "TerraViewConverterPlugin" )
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

find_package ( terralib REQUIRED )

set(QT_MT_REQUIRED, TRUE)
FIND_PACKAGE(Qt3 REQUIRED)

set (
	TO_MOC
	${SRC_DIR}/converterPlugin.h
)

message("QT_INCLUDE_DIR=${QT_INCLUDE_DIR}")

QT_WRAP_CPP ( ${PROJ_NAME} moc_files ${TO_MOC} )

add_definitions ( ${QT_DEFINITIONS} -DQT_THREAD_SUPPORT )
include_directories ( ${SRC_DIR} ${CONVERTER_LIBRARY_INCLUDE_DIRS} ${TE_INCLUDE_DIRS} ${TV_DIRS} ${QT_INCLUDE_DIR} )
add_library( ${PROJ_NAME} SHARED ${SRCS} ${HEADERS} ${moc_files})
target_link_libraries(${PROJ_NAME} ${CONVERTER_LIBRARY_BINARIES} ${TE_LIBRARIES} )
