cmake_minimum_required (VERSION 3.26)

project ("stack")

# Comment out for Debug mode
set(IS_DEBUG_BUILD CMAKE_BUILD_TYPE STREQUAL "Debug")
if ( NOT "${HAS_STACK}")
    message("[stack] Adding stack project")
    set(HAS_STACK true PARENT_SCOPE)
endif()

if (${IS_DEBUG_BUILD})
    add_compile_definitions(NDEBUG)
endif()

# Add source to this project's executable.
add_executable(stack_example)
target_include_directories(stack_example PUBLIC "include")
target_sources(stack_example PRIVATE "stack.c" "main.c")

# Add source to the tester
add_executable (stack_test)
target_include_directories(stack_test PUBLIC "include")
target_sources(stack_test PRIVATE "stack.c" "stack_test.c")

# Add source to the library
add_library(stack SHARED "stack.c")
target_include_directories(stack PUBLIC "include")