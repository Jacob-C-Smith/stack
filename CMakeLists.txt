# Need CMake 3.20
cmake_minimum_required (VERSION 3.20)

# This is the name of the repository
project ("stack")

# Set the correct paths
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/extern/)

# Set compiler warnings
if(MSVC)
    # TODO
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -Wextra -Wpedantic -Weverything -Wno-declaration-after-statement -Ofast")
endif()

# Comment out for Debug mode
set(IS_DEBUG_BUILD CMAKE_BUILD_TYPE STREQUAL "Debug")

# Set for debug mode
if (${IS_DEBUG_BUILD})
    add_compile_definitions(NDEBUG)
endif()

# Find the sync module
if ( NOT "${HAS_SYNC}")

    # Log
    message("[stack] Adding sync project")

    # Add the sync directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/sync ${CMAKE_SOURCE_DIR}/build/sync)

    # Let any parent project know that this project has sync
    set(HAS_SYNC true PARENT_SCOPE)
endif()

# Add the stack project
if ( NOT "${HAS_STACK}")

    # Log
    message("[stack] Adding stack project")

    # Let any parent project know that it has the stack project
    set(HAS_STACK true PARENT_SCOPE)
endif()

# Add source to this project's executable.
add_executable(stack_example "stack.c" "main.c")
add_dependencies(stack_example sync)
target_include_directories(stack_example PUBLIC include include/stack)
target_link_libraries(stack_example sync)

# Add source to the tester
add_executable (stack_test "stack.c" "stack_test.c")
add_dependencies(stack_test sync)
target_include_directories(stack_test PUBLIC include include/stack ${CMAKE_SOURCE_DIR}/extern/sync/include/)
target_link_libraries(stack_test sync)

# Add source to the library
add_library(stack SHARED "stack.c")
add_dependencies(stack sync)
target_include_directories(stack PUBLIC include include/stack ${CMAKE_SOURCE_DIR}/extern/sync/include/)
target_link_libraries(stack sync)
