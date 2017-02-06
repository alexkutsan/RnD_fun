project(distcc_host_synchroniser)
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

find_package(Boost REQUIRED COMPONENTS coroutine thread system filesystem)

INCLUDE_DIRECTORIES(
    ${BOOST_INCLUDE_DIRS}
    Synca
)

set ( LIBRARIES
    ${Boost_LIBRARIES}
)

set (SRC_LIST
    main.cpp
    Synca/dispatcher.cpp
    Synca/task.cpp
)


set (CMAKE_CXX_STANDARD 14)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
