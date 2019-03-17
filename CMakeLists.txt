cmake_minimum_required(VERSION 3.0)

project(shmup)
enable_testing()

set(CMAKE_CXX_FLAGS "-std=c++2a -ggdb")
set(CMAKE_C_FLAGS "-std=c99 -ggdb")
option(BUILD_DEMOSAICER "Build the application mandated task")
option(BUILD_TESTS "Build a suite of tests")

SET(CMAKE_C_COMPILER /usr/bin/clang)
SET(CMAKE_CXX_COMPILER /usr/bin/clang++)


find_program(CLANG_TIDY_EXE
             NAMES "clang-tidy"
             DOC "Path to clang-tidy executable")
if(NOT CLANG_TIDY_EXE)
  message(STATUS "clang-tidy not found.")
else()
  message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
  set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "-checks=-*,clang-analyzer-*,android-*,performance-*, portability-* ")# modernize-*
endif()

#macro(add_files name)
#    file(GLOB ${name} src/${name}/*.h src/${name}/*.cpp src/${name}/*.c)
#    include_directories(src/${name})
#endmacro()

set(src_files src/nearest.c src/utilities.c)
set(demosaicer src/main.cpp)
include_directories(src)

if (BUILD_DEMOSAICER)
    add_executable(T872 ${demosaicer} ${src_files})

    if(CLANG_TIDY_EXE)
      set_target_properties(T872 PROPERTIES
                            CXX_CLANG_TIDY "${DO_CLANG_TIDY}")
    endif()
endif()

if (BUILD_TESTS)
    macro(add_custom_test file)
        string(REGEX REPLACE "(^.*/|\\.[^.]*$)" "" bare_name ${file})
        add_executable(${bare_name} ${file} ${ARGV})
        add_test(${bare_name} ${bare_name})
        target_link_libraries(${bare_name} ${LIBRARIES})
    endmacro()

    add_custom_test(tests/test_nearest_neighbour.cpp ${src_files})
    add_custom_test(tests/test_split_raw12.cpp ${src_files})
endif()
