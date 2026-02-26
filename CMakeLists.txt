cmake_minimum_required(VERSION 3.10)
project(TDMM)

# Set output directory for libraries to root build directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Add the libtdmm subdirectory
add_subdirectory(libtdmm)

# Create the main executable
add_executable(mftester main.c)
target_link_libraries(mftester PRIVATE tdmm)
target_include_directories(mftester PRIVATE libtdmm)
