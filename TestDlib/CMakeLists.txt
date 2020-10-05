project(TestsDlib)
cmake_minimum_required(VERSION 2.8)

find_package( OpenCV REQUIRED )

set(DLIB_SRC $ENV{DLIB_SRC})
set(DLIB_LIB $ENV{DLIB_LIB})


include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${DLIB_SRC})

link_directories(${DLIB_LIB})

set ( CMAKE_CXX_FLAGS "-O3 --std=c++14")

set(SOURCES
    main.cpp)

set (LIBRARIES
    ${OpenCV_LIBS}
    dlib
    )
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
