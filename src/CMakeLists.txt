cmake_minimum_required(VERSION 3.2)
project(test_client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(MazeNavCommon)

set(SOURCE_FILES main.cpp MazeRenderer.cpp MazeRenderer.h MazeRenderingProperties.cpp MazeRenderingProperties.h MazeEditor.cpp MazeEditor.h Cursor.h RemoteControl.cpp RemoteControl.h)
add_executable(test_client ${SOURCE_FILES} main.cpp)
TARGET_LINK_LIBRARIES(test_client pthread MazeNavCommon)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics audio network)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(test_client ${SFML_LIBRARIES})
endif()