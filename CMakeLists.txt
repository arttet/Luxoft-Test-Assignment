cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(LuxoftTestAssignment VERSION 0.0.1 LANGUAGES CXX)

############################################################################################
# Conan

if (EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
  include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
  conan_basic_setup()
endif ()

############################################################################################
# Options

set(WITH_COVERAGE OFF CACHE BOOL "Enable coverage reporting")
set(WITH_TESTS OFF CACHE BOOL "Build test suites")

include(CMakePrintHelpers)

cmake_print_variables(WITH_COVERAGE)
cmake_print_variables(WITH_TESTS)

############################################################################################
# CMake Options

# Set required C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate the compile_commands.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_HEADERS_IN_COMPILE_COMMANDS ON)

############################################################################################
# Linter Options

if (CMAKE_CXX_CLANG_TIDY)
  list(APPEND CMAKE_CXX_CLANG_TIDY
    "-format-style='file'"
  )
endif()

if (WITH_COVERAGE)
  add_compile_options(
    "--coverage"
  )

  add_link_options(
    "--coverage"
  )
endif()

cmake_print_variables(CMAKE_CXX_CLANG_TIDY)

############################################################################################
# Compiler Options

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  add_compile_options(
    "-Wall"
    "-Wextra"
  )

  add_compile_options(
    "-Wno-c++98-compat"
    "-Wno-c++98-compat-pedantic"
  )

  if (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
    # Using clang with clang-cl front end
  elseif (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "GNU")
    # Using clang with regular front end
    add_compile_options(
      "-Werror"
    )
  endif()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  add_compile_options(
    "-Wall"
    "-Wextra"
    "-Werror"
  )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  add_compile_definitions(
    UNICODE
    _UNICODE

    _SCL_SECURE_NO_WARNINGS
    _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
    _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
  )

  add_compile_options(
    "/W4"
    "/WX"
    "/utf-8"
    "/MP"
    "/EHa"
  )
endif()

############################################################################################

# Requirements & Build Requirements

find_package(Boost 1.76.0 EXACT REQUIRED)
find_package(fmt REQUIRED)
find_package(Microsoft.GSL REQUIRED)
find_package(Threads REQUIRED)

if (WITH_TESTS)
  find_package(GTest REQUIRED)
endif()

############################################################################################

enable_testing()

add_subdirectory(lib)
add_subdirectory(src)

if (WITH_TESTS)
  add_subdirectory(test)
endif()
