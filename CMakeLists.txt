cmake_minimum_required(VERSION 3.2)

cmake_policy(SET CMP0022 NEW) # enable >2.8 behavior for INTERFACE_LINK_LIBRARIES
cmake_policy(SET CMP0048 NEW) # enable project versioning by CMake
cmake_policy(SET CMP0053 NEW) # simplify variable reference and escape sequence evaluation

project(BenchmarkExpected VERSION 1.0 LANGUAGES CXX)

if(WIN32)
    set(OS_NAME Win)
elseif(APPLE)
    set(OS_NAME OSX)
elseif(UNIX)
    set(OS_NAME Linux)
else()
    message(FATAL_ERROR "Operating system not supported")
endif()
message(STATUS "System: ${OS_NAME}")

add_executable(BenchmarkExpected
    BenchmarkExpected.cpp
    FastRand.h
    BenchOptimizations.h
    BenchOptimizations.cpp
    BenchPerfCategories.h
    BenchPerfCategories.cpp
    BenchSuccessRates.h
    BenchSuccessRates.cpp
)

set_target_properties(BenchmarkExpected PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

message("")
message("LLVM")

# add LLVM libraries, set LLVM_* variables
find_package(LLVM 5.0 REQUIRED PATHS ${LLVM_DIR})
message(STATUS "LLVM_DIR: ${LLVM_DIR}")
message(STATUS "LLVM_PACKAGE_VERSION: ${LLVM_PACKAGE_VERSION}")

message(STATUS "LLVM Source Directory: ${LLVM_BUILD_MAIN_SRC_DIR}")
message(STATUS "LLVM Build Directory: ${LLVM_BUILD_BINARY_DIR}")

message("")
message("Google Benchmark")
find_package(benchmark) # ?!?!

target_include_directories(BenchmarkExpected PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${LLVM_INCLUDE_DIRS}
    /usr/local/include
)

# LLVM definitions
separate_arguments(LLVM_DEFINITIONS)
target_compile_definitions(BenchmarkExpected PRIVATE
    ${LLVM_DEFINITIONS}
)

target_compile_options(BenchmarkExpected PRIVATE
    -fno-rtti
    -fno-exceptions
    -fomit-frame-pointer
    -fno-stack-protector
)

llvm_map_components_to_libnames(LLVM_LIBS 
    core 
    support
)

target_link_libraries(BenchmarkExpected PRIVATE
    ${LLVM_LIBS}
    /usr/local/lib/libbenchmark.a
)

message("")
message("BenchmarkExpected")

get_target_property(ALL_ID BenchmarkExpected INCLUDE_DIRECTORIES)
message(STATUS "Include directories: ${ALL_ID}")

get_target_property(ALL_LL BenchmarkExpected LINK_LIBRARIES)
message(STATUS "Link libraries: ${ALL_LL}")

get_target_property(ALL_CO BenchmarkExpected COMPILE_OPTIONS)
message(STATUS "Compile options: ${ALL_CO}")

get_target_property(ALL_CD BenchmarkExpected COMPILE_DEFINITIONS)
message(STATUS "Compile definitions: ${ALL_CD}")

message(STATUS "Other flags: ${CMAKE_CXX_FLAGS}")
message(STATUS "Other flags Debug: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "Other flags Release: ${CMAKE_CXX_FLAGS_RELEASE}")
