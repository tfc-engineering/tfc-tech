cmake_minimum_required(VERSION 3.12)

message(STATUS "Configuring ${CMAKE_BUILD_TYPE} build of TFCTech.")

project(TFCTech LANGUAGES C CXX VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

set(WITH_PETSC ON CACHE BOOL "Add PETSc functionality to the library")

message(STATUS "WITH_PETSC=${WITH_PETSC}")

include(tools/cmake-macros/setup-bin-and-lib.cmake)
include(tools/cmake-macros/lua_dependency.cmake)

#================================================ Setup packages
find_package(MPI)

#================================================ Compiler flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
# Force -O3 in release builds (some OS's might downgrade it)
string(REPLACE "-O2" "-O3" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
string(REPLACE "-O2" "-O3" CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})
string(REPLACE "-O2" "-O3" CMAKE_CXX_FLAGS_MINSIZEREL ${CMAKE_CXX_FLAGS_MINSIZEREL})

list(APPEND TFC_CXX_FLAGS "-pedantic;-Wall;-Wno-unused-variable")

#================================================ Linker flags
set(TFCLIB_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${MPI_CXX_LINK_FLAGS}")

#================================================ Header include directories
# System headers
include_directories(SYSTEM ${MPI_CXX_INCLUDE_PATH})
include_directories(SYSTEM "${LUA_ROOT}/include")
#
# Project headers
include_directories("${PROJECT_SOURCE_DIR}/src")

#================================================ Library directories
link_directories("${LUA_ROOT}/lib")

set(TFC_LIBS stdc++ lua m dl ${MPI_CXX_LIBRARIES})
# set(TFC_LIBS stdc++ lua m dl ${MPI_CXX_LIBRARIES} petsc ${VTK_LIBRARIES})

#================================================ Define targets
set(FRAMEWORK_SOURCES "")
add_subdirectory("${PROJECT_SOURCE_DIR}/src/tfc")

set(TEST_SOURCES)
add_subdirectory("${PROJECT_SOURCE_DIR}/tests")

add_library(TFClib SHARED ${FRAMEWORK_SOURCES})
add_executable(TFCTech "${PROJECT_SOURCE_DIR}/main.cc")
add_executable(TFCTech_test "${TEST_SOURCES}")

target_compile_options(TFClib PUBLIC ${TFC_CXX_FLAGS})
target_link_options(TFClib PUBLIC ${MPI_CXX_LINK_FLAGS})
target_link_libraries(TFClib "${TFC_LIBS}")

target_compile_options(TFCTech PUBLIC ${TFC_CXX_FLAGS})
target_link_options(TFCTech PUBLIC ${MPI_CXX_LINK_FLAGS})
target_link_libraries(TFCTech TFClib)

target_compile_options(TFCTech_test PUBLIC ${TFC_CXX_FLAGS})
target_link_options(TFCTech_test PUBLIC ${MPI_CXX_LINK_FLAGS})
target_link_libraries(TFCTech_test TFClib)
# if(UNIX AND NOT APPLE)
#     target_link_libraries(${TARGET} -Wl,--whole-archive ChiLib -Wl,--no-whole-archive )
#     target_link_libraries(${TARGET}_test -Wl,--whole-archive ChiLib -Wl,--no-whole-archive )
# elseif(APPLE)
#     target_link_libraries(${TARGET} -Wl,-all_load ChiLib )
#     target_link_libraries(${TARGET}_test -Wl,-all_load ChiLib )
# endif()

set_target_properties(TFCTech_test
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/tests/lib"
        LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/tests/lib"
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/tests/bin"
)

# |------------ Write Makefile to root directory
file(WRITE ${PROJECT_SOURCE_DIR}/Makefile "subsystem:\n" "\t$(MAKE) -C cmake-build \n\n"
        "clean:\n\t$(MAKE) -C cmake-build clean\n")
