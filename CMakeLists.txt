cmake_minimum_required(VERSION 3.5)
project(raceGame)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp loading.cpp algebra.cpp texture.cpp)
add_executable(solar ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

target_link_libraries (solar ${CMAKE_THREAD_LIBS_INIT})

include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
target_link_libraries(solar ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})