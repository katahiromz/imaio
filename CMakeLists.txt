# CMakeLists.txt --- CMake project settings
#    ex) cmake -G "Visual Studio 9 2008"
#    ex) cmake -DCMAKE_BUILD_TYPE=Release -G "MSYS Makefiles"
##############################################################################

# CMake minimum version
cmake_minimum_required(VERSION 2.4)

enable_testing()

# project name and language
project(imaio C)

# check build type
if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# make uppercase string of build type
string(TOUPPER "${CMAKE_BUILD_TYPE}" uppercase_CMAKE_BUILD_TYPE)

# check build type again
if (NOT uppercase_CMAKE_BUILD_TYPE MATCHES "^(DEBUG|RELEASE|RELWITHDEBINFO|MINSIZEREL)$")
    message(FATAL_ERROR "Invalid value for CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
endif()

## set output directory (build/)
#set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
#set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

## enable Win32 resource
#enable_language(RC)

#if (WIN32)
#    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
#        # using Clang
#        set(CMAKE_C_FLAGS "-static")
#        set(CMAKE_CXX_FLAGS "-static")
#    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
#        # using GCC
#        set(CMAKE_C_FLAGS "-static -static-libgcc -static-libstdc++")
#        set(CMAKE_CXX_FLAGS "-static -static-libgcc -static-libstdc++")
#    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
#        # replace "/MD" with "/MT" (building without runtime DLLs)
#        set(CompilerFlags
#            CMAKE_C_FLAGS
#            CMAKE_C_FLAGS_DEBUG
#            CMAKE_C_FLAGS_RELEASE
#            CMAKE_C_FLAGS_RELWITHDEBINFO
#            CMAKE_CXX_FLAGS
#            CMAKE_CXX_FLAGS_DEBUG
#            CMAKE_CXX_FLAGS_RELEASE
#            CMAKE_CXX_FLAGS_RELWITHDEBINFO)
#        foreach(CompilerFlags ${CompilerFlags})
#            string(REPLACE "/MD" "/MT" ${CompilerFlags} "${${CompilerFlags}}")
#        endforeach()
#    endif()
#endif()

##############################################################################

include_directories(.)

find_package(GIF)
if (GIF_FOUND)
    add_definitions(-DHAVE_GIF)
endif()

find_package(JPEG)
if (JPEG_FOUND)
    add_definitions(-DHAVE_JPEG)
endif()

find_package(PNG)
if (PNG_FOUND)
    add_definitions(-DHAVE_PNG)
endif()
add_definitions(${PNG_DEFINITIONS})

find_package(TIFF)
if (TIFF_FOUND)
    add_definitions(-DHAVE_TIFF)
endif()

# add static library
add_library(imaio STATIC
    src/imaio.c
    src/gif.c
    src/jpg.c
    src/png.c
    src/tif.c)

target_include_directories(imaio PRIVATE
    ${GIF_INCLUDE_DIR}
    ${JPEG_INCLUDE_DIRS}
    ${PNG_INCLUDE_DIRS}
    ${TIFF_INCLUDE_DIRS})

target_link_libraries(imaio PRIVATE
    ${GIF_LIBRARIES}
    ${JPEG_LIBRARIES}
    ${PNG_LIBRARIES}
    ${TIFF_LIBRARIES})

# add shared library
add_library(imaio-dll SHARED
    src/imaio.c
    src/gif.c
    src/jpg.c
    src/png.c
    src/tif.c)
set_target_properties(imaio-dll PROPERTIES OUTPUT_NAME "imaio")

target_compile_definitions(imaio-dll PRIVATE -DIMAIO_DLL)

target_include_directories(imaio-dll PRIVATE
    ${GIF_INCLUDE_DIR}
    ${JPEG_INCLUDE_DIRS}
    ${PNG_INCLUDE_DIRS}
    ${TIFF_INCLUDE_DIRS})

target_link_libraries(imaio-dll PRIVATE
    ${GIF_LIBRARIES}
    ${JPEG_LIBRARIES}
    ${PNG_LIBRARIES}
    ${TIFF_LIBRARIES})

# add test program #1
add_executable(imaio_test_1 tests/imaio_test.c)
target_link_libraries(imaio_test_1 PRIVATE imaio)

# add test program #2
add_executable(imaio_test_2 tests/imaio_test.c)
target_link_libraries(imaio_test_2 PRIVATE imaio-dll)
target_compile_definitions(imaio_test_2 PRIVATE -DIMAIO_DLL)

## add test
#add_test(NAME imaio_test_1 COMMAND imaio_test_1 WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
#add_test(NAME imaio_test_2 COMMAND imaio_test_2 WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

##############################################################################
