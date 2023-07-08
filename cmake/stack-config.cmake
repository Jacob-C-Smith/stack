# Stack CMake configuration file:
# This file is meant to be placed in a cmake subfolder of STACK-devel-2.x.y-VC

cmake_minimum_required(VERSION 3.0)

include(FeatureSummary)
set_package_properties(STACK PROPERTIES
    URL "https://www.g10.app/ADT/stack"
    DESCRIPTION "stack ADT"
)

# Copied from `configure_package_config_file`
macro(set_and_check _var _file)
    set(${_var} "${_file}")
    if(NOT EXISTS "${_file}")
        message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
    endif()
endmacro()

# Copied from `configure_package_config_file`
macro(check_required_components _NAME)
    foreach(comp ${${_NAME}_FIND_COMPONENTS})
        if(NOT ${_NAME}_${comp}_FOUND)
            if(${_NAME}_FIND_REQUIRED_${comp})
                set(${_NAME}_FOUND FALSE)
            endif()
        endif()
    endforeach()
endmacro()

set(STACK_FOUND TRUE)

# For compatibility with autotools STACK-config.cmake, provide STACK_* variables.

set_and_check(STACK_PREFIX       "${CMAKE_CURRENT_LIST_DIR}/..")
set_and_check(STACK_EXEC_PREFIX  "${CMAKE_CURRENT_LIST_DIR}/..")
set_and_check(STACK_INCLUDE_DIR  "${STACK_PREFIX}/include")
set(STACK_INCLUDE_DIRS           "${STACK_INCLUDE_DIR}")
set_and_check(STACK_BINDIR       "${CMAKE_CURRENT_LIST_DIR}/../build/Debug/")
set_and_check(STACK_LIBDIR       "${CMAKE_CURRENT_LIST_DIR}/../build/Debug/")

set(STACK_LIBRARIES stack::stack)

# All targets are created, even when some might not be requested though COMPONENTS.
# This is done for compatibility with CMake generated STACK-target.cmake files.

set(_STACK_library     "${STACK_LIBDIR}/stack.lib")
set(_STACK_dll_library "${STACK_BINDIR}/stack.dll")
if(EXISTS "${_STACK_library}" AND EXISTS "${_STACK_dll_library}")
    if(NOT TARGET stack::stack)
        add_library(stack::stack SHARED IMPORTED)
        set_target_properties(stack::stack
            PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${STACK_INCLUDE_DIRS}"
                IMPORTED_IMPLIB "${_STACK_library}"
                IMPORTED_LOCATION "${_STACK_dll_library}"
                COMPATIBLE_INTERFACE_BOOL "STACK_SHARED"
                INTERFACE_STACK_SHARED "ON"
        )
    endif()
    set(STACK_STACK_FOUND TRUE)
else()
    set(STACK_STACK_FOUND FALSE)
endif()
unset(_STACK_library)
unset(_STACK_dll_library)

check_required_components(STACK)
