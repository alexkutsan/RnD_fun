project(SyncaLib)
cmake_minimum_required(VERSION 2.8)

set (BOOST_HOME CACHE STRING "Path to custom boost")

if(BOOST_HOME STREQUAL "")
   message (STATUS "BOOST_HOME is empty. Use system Boost")
else()
  message (STATUS "Use Boost from ${BOOST_HOME}")
  set(BOOST_ROOT ${BOOST_HOME})
  set(BOOST_INCLUDE_DIRS ${BOOST_ROOT}/include/)
  set(BOOST_LIBRARY_DIRS ${BOOST_ROOT}/lib)
endif()

find_package(Boost REQUIRED COMPONENTS system  coroutine thread context filesystem)

INCLUDE_DIRECTORIES(
    ${BOOST_INCLUDE_DIRS}
    ./
)

set ( LIBRARIES
    ${Boost_LIBRARIES}
)

set (SRC_LIST
    dispatcher.cpp
    task.cpp

)

set (CMAKE_CXX_STANDARD 14)
add_library(synca ${SRC_LIST})
add_executable(${PROJECT_NAME} ${SRC_LIST} test.cpp)
target_link_libraries(${PROJECT_NAME} ${LIBRARIES} synca)
