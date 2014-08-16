cmake_minimum_required(VERSION 2.8)

set ( PROJ_NAME "TerralibConverterLib" )
project ( ${PROJ_NAME} )

IF( MSVC_IDE AND ( MSVC90 OR MSVC10 ) )
	add_definitions(/MP)
ENDIF()

set ( ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../.." )
set ( SRC_DIR "${ROOT}/src" )


file ( GLOB SRCS ${SRC_DIR}/library/*.cpp )
file ( GLOB HEADERS ${SRC_DIR}/library/*.h)

find_package ( terralib REQUIRED COMPONENTS shp)

add_definitions(-DTERRALIB_CONVERTER_AS_DLL )
add_library( ${PROJ_NAME} SHARED ${SRCS} ${HEADERS} )

include_directories ( ${TE_INCLUDE_DIRS} ${TV_DIRS}} )
target_link_libraries(${PROJ_NAME} ${TE_LIBRARIES})


# Add all targets to the build-tree export set
export(TARGETS TerralibConverterLib
  FILE "${PROJECT_BINARY_DIR}/TerralibConverterLibTargets.cmake")
 
# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE TerralibConverterLib)
 
# Create the FooBarConfig.cmake and FooBarConfigVersion files
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
   "${INSTALL_INCLUDE_DIR}")
# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(TerralibConverterLibConfig.cmake.in
  "${PROJECT_BINARY_DIR}/TerralibConverterLibConfig.cmake" @ONLY)
# ... for the install tree
set(CONF_INCLUDE_DIRS "\${TERRALIBCONVETERLIB_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(TerralibConverterLibConfig.cmake.in
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/TerralibConverterLibConfig.cmake" @ONLY)
# ... for both
configure_file(TerralibConverterLibConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/TerralibConverterLibConfigVersion.cmake" @ONLY)
 
# Install the TerralibConverterLibConfig.cmake and TerralibConverterLibConfigVersion.cmake
install(FILES
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/TerralibConverterLibConfig.cmake"
  "${PROJECT_BINARY_DIR}/TerralibConverterLibConfigVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)
 
# Install the export set for use with the install-tree
install(EXPORT TerralibConverterLibTargets DESTINATION
  "${INSTALL_CMAKE_DIR}" COMPONENT dev)
