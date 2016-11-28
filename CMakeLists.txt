project(RoadAnalyzer)
cmake_minimum_required(VERSION 2.8.12)

if(USE_CONAN)
include(${PROJECT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
endif(USE_CONAN)

set(SOURCES
    "src/road_analyzer.cpp"
    "src/road_analyzer_impl.cpp"
    "src/interface.cpp"
)

set(HEADERS
    "include/road_analyzer.h"
    "include/road_analyzer_impl.h"
)

#set compiler flags
if((${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang") OR (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU"))
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wreturn-type -Wpedantic ")
endif()

include_directories("include")

add_library(road_analyzer MODULE ${SOURCES} ${HEADERS})

if(USE_CONAN)
target_link_libraries(road_analyzer ${CONAN_LIBS} street_environment)
else()
target_link_libraries(road_analyzer PRIVATE lmscore lms_math street_environment)
endif(USE_CONAN)
