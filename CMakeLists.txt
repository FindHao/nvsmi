cmake_minimum_required(VERSION 3.10)

# Set project name and language
project(nvsmi)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
            "Default build type: Debug" FORCE)
endif()


# Find NVML library
find_library(NVML_LIBRARY NAMES nvidia-ml)

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/include/
    ${CMAKE_CURRENT_LIST_DIR}/src/
)
add_compile_options(-fstack-usage)

# include all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add executable target
add_executable(nvsmi ${SOURCES})

# Link with NVML library
target_link_libraries(nvsmi PRIVATE ${NVML_LIBRARY}  -fstack-usage)

# Set include directories
target_include_directories(nvsmi PRIVATE
    /usr/local/cuda/include)
