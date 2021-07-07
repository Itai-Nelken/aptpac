cmake_minimum_required(VERSION 3.16)

project(aptpac VERSION 2.6 LANGUAGES C)
#set some variables
set(BIN "aptpac") #the name of the executable
set(VER "${CMAKE_PROJECT_VERSION}") #the version
set(NAME "${CMAKE_PROJECT_NAME}") #the project name
set(CONF "$ENV{HOME}/.aptpac")
add_compile_definitions(VER="${VER}")

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
endif()

#functions.h
add_library(
	functions
	src/functions.h
	src/functions.c
)

add_executable(${BIN} src/main.c)
target_link_libraries(${BIN} PRIVATE functions)

#install target
install(
	#CODE "execute_process(COMMAND ./install_checks.sh)"
	TARGETS aptpac
	DESTINATION /usr/local/bin
)
install(DIRECTORY DESTINATION ${CONF})

# uninstall target
if(NOT TARGET uninstall)
	configure_file(
		"${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
		"${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
	IMMEDIATE @ONLY)
	add_custom_target(uninstall
	COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
