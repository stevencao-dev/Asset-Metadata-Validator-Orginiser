cmake_minimum_required(VERSION 3.16)
project(AssetValidationUtility)

set(CMAKE_CXX_STANDARD 20)

# Include headers
include_directories(includes)

# Add all source files
file(GLOB SOURCES "src/*.cpp")

# Create the executable
add_executable(AssetValidationUtility ${SOURCES})