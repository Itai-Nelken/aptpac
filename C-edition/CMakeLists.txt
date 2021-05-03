cmake_minimum_required(VERSION 3.16)

project(aptpac VERSION 0.1)

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
