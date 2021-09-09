cmake_minimum_required(VERSION 3.16)
set(CMAKE_C_COMPILER "/bin/gcc")
project(aptpac VERSION 3.0 LANGUAGES C)
#set some variables
set(BIN "aptpac") #the name of the executable
set(VER "${CMAKE_PROJECT_VERSION}") #the versiongc
set(NAME "${CMAKE_PROJECT_NAME}") #the project name
set(HOME_DIR "$ENV{HOME}")
set(CONF_FILE "${HOME_DIR}/.config/aptpac.config")
add_compile_definitions(VER="${VER}")
add_compile_definitions(CONF_FILE_VERSION=1)

#options for cmake
option(CALLCOMMAND "The command to use when calling aptpac e.g './aptpac' or 'aptpac'" ${CALLCOMMAND})
option(DEBUG "Print debug info in some places" ${DEBUG})
#CALLCOMMAND
if(CALLCOMMAND STREQUAL "./${BIN}")
    add_compile_definitions(CALLCOMMAND="./${BIN}")
elseif(CALLCOMMAND STREQUAL "${BIN}")
    add_compile_definitions(CALLCOMMAND="${BIN}")
elseif(CALLCOMMAND STREQUAL "OFF")
    message(STATUS "Using default value for 'CALLCOMMAND'...")
    add_compile_definitions(CALLCOMMAND="${BIN}")
else()
    message(WARNING )
    execute_process(COMMAND 
        ${CMAKE_COMMAND} -E env CLICOLOR_FORCE=1
        ${CMAKE_COMMAND} -E cmake_echo_color --red --bold "Unknown option for 'CALLCOMMAND'! using default '${BIN}'"
    )
    add_compile_definitions(CALLCOMMAND="${BIN}")
endif()
#DEBUG
if(DEBUG)
	message(STATUS "Configuring with debug mode on...")
	add_compile_definitions(DEBUG)
	add_compile_options(-Wall)
	set(CMAKE_BUILD_TYPE Debug)
endif()

#functions.h
add_library(
	functions
	src/functions.h
	src/functions.c
)

add_executable(${BIN} src/main.c)
target_link_libraries(${BIN} PRIVATE functions)

set(TARGET_ARCH ${CMAKE_HOST_SYSTEM_PROCESSOR})
if(NOT CPACK_GENERATOR)
        set(CPACK_GENERATOR "STGZ")
endif()
set(CPACK_PACKAGE_NAME "aptpac")
set(CPACK_PACKAGE_CONTACT "itainelken@gmail.com")
#set(CPACK_PACKAGE_DESCRIPTION "")
set(CPACK_VERSION_MAJOR ${CMAKE_PROJECT_VERSION_MAJOR})
set(CPACK_VERSION_MINOR ${CMAKE_PROJECT_VERSION_MINOR})
set(CPACK_VERSION_PATCH ${CMAKE_PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION ${CMAKE_PROJECT_VERSION})
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}_Linux-${TARGET_ARCH}")
include(CPack)

#install target
install(
	#CODE "execute_process(COMMAND ./install_checks.sh)"
	TARGETS aptpac
	DESTINATION /usr/local/bin
)
add_custom_command(TARGET aptpac POST_BUILD COMMAND touch $ENV{HOME}/.config/aptpac.config)

# uninstall target
if(NOT TARGET uninstall)
	configure_file(
		"${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
		"${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
	IMMEDIATE @ONLY)
	add_custom_target(uninstall
	COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
