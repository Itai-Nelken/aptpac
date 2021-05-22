cmake_minimum_required(VERSION 3.16)

project(aptpac VERSION 2.5 LANGUAGES C)

option(CALLCOMMAND "The command to use when calling aptpac e.g './aptpac' or 'aptpac'" ${CALLCOMMAND})
option(LEARN "Print the commands being run so you can learn how to use pacman" ${LEARN})

#CALLCOMMAND
if(CALLCOMMAND STREQUAL "./aptpac")
    add_compile_definitions(CALLCOMMAND="./aptpac")
elseif(CALLCOMMAND STREQUAL "aptpac")
    add_compile_definitions(CALLCOMMAND="aptpac")
elseif(CALLCOMMAND STREQUAL "OFF")
    message(STATUS "Using default value for 'CALLCOMMAND'...")
    add_compile_definitions(CALLCOMMAND="aptpac")
else()
    message(WARNING )
    execute_process(COMMAND 
        ${CMAKE_COMMAND} -E env CLICOLOR_FORCE=1
        ${CMAKE_COMMAND} -E cmake_echo_color --red --bold "Unknown option for 'CALLCOMMAND'! using default 'aptpac'"
    )
    add_compile_definitions(CALLCOMMAND="aptpac")
endif()
#LEARN
if(LEARN)
    message(STATUS "Configuring with learning mode on...")
    add_compile_definitions(LEARN)
endif()
    
#functions.h
add_library(
	functions
	src/functions.h
	src/functions.c
)

add_executable(aptpac src/main.c)
target_link_libraries(aptpac PRIVATE functions)

#install target
install(
	#CODE "execute_process(COMMAND ./install_checks.sh)"
	TARGETS aptpac
	DESTINATION /usr/local/bin
)

# uninstall target
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
