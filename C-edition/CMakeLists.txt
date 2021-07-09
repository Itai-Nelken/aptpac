cmake_minimum_required(VERSION 3.16)
set(CMAKE_C_COMPILER "/bin/gcc")
project(aptpac VERSION 3.0 LANGUAGES C)
#set some variables
set(BIN "aptpac") #the name of the executable
set(VER "${CMAKE_PROJECT_VERSION}") #the versiongc
set(NAME "${CMAKE_PROJECT_NAME}") #the project name
#set(CONF "$ENV{HOME}/.aptpac")
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

set(archdetect_c_code "
#ifdef __aarch64__
    #error cmake_ARCH aarch64
#elif defined(__arm__)
    #error cmake_ARCH arm
#elif defined(__i386) || defined(__i386__) || defined(_M_IX86)
    #error cmake_ARCH i386
#elif defined(__x86_64__)
    #error cmake_ARCH x86_64
#else
#error cmake_ARCH unknown
#endif
")

function(target_architecture output_var)
	file(WRITE "${CMAKE_BINARY_DIR}/arch.c" "${archdetect_c_code}")

	enable_language(C)

	# Detect the architecture in a rather creative way...
	# This compiles a small C program which is a series of ifdefs that selects a
	# particular #error preprocessor directive whose message string contains the
	# target architecture. The program will always fail to compile (both because
	# file is not a valid C program, and obviously because of the presence of the
	# #error preprocessor directives... but by exploiting the preprocessor in this
	# way, we can detect the correct target architecture even when cross-compiling,
	# since the program itself never needs to be run (only the compiler/preprocessor)
	try_run(
		run_result_unused
		compile_result_unused
		"${CMAKE_BINARY_DIR}"
		"${CMAKE_BINARY_DIR}/arch.c"
		COMPILE_OUTPUT_VARIABLE ARCH
	)

	# Parse the architecture name from the compiler output
	string(REGEX MATCH "cmake_ARCH ([a-zA-Z0-9_]+)" ARCH "${ARCH}")

	# Get rid of the value marker leaving just the architecture name
	string(REPLACE "cmake_ARCH " "" ARCH "${ARCH}")

    set(${output_var} "${ARCH}" PARENT_SCOPE)
    file(REMOVE "${CMAKE_BINARY_DIR}/arch.c")
endfunction()

set(TARGET_ARCH)
target_architecture(TARGET_ARCH)
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

# uninstall target
if(NOT TARGET uninstall)
	configure_file(
		"${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
		"${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
	IMMEDIATE @ONLY)
	add_custom_target(uninstall
	COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
