cmake_minimum_required(VERSION 2.8)

set(CONVERTER_LIBRARY_MAJOR_VERSION 0)
set(CONVERTER_LIBRARY_MINOR_VERSION 1)
set(CONVERTER_LIBRARY_PATCH_VERSION 0)
set(CONVERTER_LIBRARY_VERSION
  ${CONVERTER_LIBRARY_MAJOR_VERSION}.${CONVERTER_LIBRARY_MINOR_VERSION}.${CONVERTER_LIBRARY_PATCH_VERSION})
  
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")
set(INSTALL_SRC_DIR src CACHE PATH "Installation directory for source files")
set(INSTALL_CMAKE_DIR build/cmake CACHE PATH "Installation directory for CMake files")

set ( PROJ_NAME "TerralibConverterLib" )
project ( ${PROJ_NAME} )

SET( CMAKE_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

if( UNIX ) 	
	SET( EXECUTABLE_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}) 
	SET( LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}) 
else()
	SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release)
	SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug)  

	SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release)
	SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug)  

	SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release)
	SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug) 
endif()  

IF( MSVC_IDE AND ( MSVC90 OR MSVC10 ) )
	add_definitions(/MP)
ENDIF()

set ( ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../.." )
set ( SRC_DIR "${ROOT}/src" )

file ( GLOB SRCS ${SRC_DIR}/*.cpp )
file ( GLOB HEADERS ${SRC_DIR}/*.h)

find_package ( terralib REQUIRED COMPONENTS shp)

add_definitions(-DTERRALIB_CONVERTER_AS_DLL )
add_library( ${PROJ_NAME} SHARED ${SRCS} ${HEADERS} )

include_directories ( ${TE_INCLUDE_DIRS} ${TV_DIRS}} )

target_link_libraries(${PROJ_NAME} ${TE_LIBRARIES})

set (CONVERTER_LIBRARY_INCLUDE_DIRS ${SRC_DIR} )
set (CONVERTER_LIBRARY_BINS "${CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG}/${PROJ_NAME}.lib" )

# Add all targets to the build-tree export set
export(TARGETS TerralibConverterLib
  FILE "${PROJECT_BINARY_DIR}/TerralibConverterLibTargets.cmake")
 
# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE TerralibConverterLib)
 
# Create the FooBarConfig.cmake and FooBarConfigVersion files
file(RELATIVE_PATH CONF_REL_INCLUDE_DIR "${CMAKE_INSTALL_PREFIX}/${INSTALL_CMAKE_DIR}" "${CMAKE_INSTALL_PREFIX}/${INSTALL_INCLUDE_DIR}" )
file(RELATIVE_PATH CONF_REL_LIB_DIR "${CMAKE_INSTALL_PREFIX}/${INSTALL_CMAKE_DIR}" "${CMAKE_INSTALL_PREFIX}/${INSTALL_LIB_DIR}" )
file(RELATIVE_PATH CONF_REL_BIN_DIR "${CMAKE_INSTALL_PREFIX}/${INSTALL_CMAKE_DIR}" "${CMAKE_INSTALL_PREFIX}/${INSTALL_BIN_DIR}" )
file(RELATIVE_PATH CONF_REL_CMAKE_DIR "${CMAKE_INSTALL_PREFIX}" "${CMAKE_INSTALL_PREFIX}/${INSTALL_CMAKE_DIR}" )
	
# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(TerralibConverterLib-config.cmake.in
  "${PROJECT_BINARY_DIR}/TerralibConverterLibConfig.cmake" @ONLY)
# ... for the install tree
set(CONF_INCLUDE_DIRS "\${TERRALIBCONVETERLIB_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(TerralibConverterLib-config.cmake.in
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/TerralibConverterLibConfig.cmake" @ONLY)

set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")  
configure_file(TerralibConverterLibBuildTreeSettings.cmake.in
  "${PROJECT_BINARY_DIR}/TerralibConverterLibBuildTreeSettings.cmake" @ONLY)
  
set(CONF_INCLUDE_DIRS "\${TERRALIBCONVETERLIB_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(TerralibConverterLibBuildTreeSettings.cmake.in
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/TerralibConverterLibBuildTreeSettings.cmake" @ONLY)
  
# ... for both
configure_file(TerralibConverterLibConfigVersion.cmake.in "${PROJECT_BINARY_DIR}/TerralibConverterLibConfigVersion.cmake" @ONLY)
 
# Install the TerralibConverterLibConfig.cmake and TerralibConverterLibConfigVersion.cmake
#install(FILES
  #"${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/TerralibConverterLibConfig.cmake"
  #"${PROJECT_BINARY_DIR}/TerralibConverterLibConfigVersion.cmake"
  #DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)
 
# Install the export set for use with the install-tree
#install(EXPORT TerralibConverterLibTargets DESTINATION
  #"${INSTALL_CMAKE_DIR}" COMPONENT dev)
