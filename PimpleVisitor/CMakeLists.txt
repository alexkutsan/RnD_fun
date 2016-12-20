project(PimpleVisitor)
cmake_minimum_required(VERSION 2.8)
 add_compile_options(-std=c++14 -g)
set (SRC_LIST
     main.cpp
    secretclass.cpp
    generator.cpp
    processor.cpp
    class_transferer.cpp
)

add_executable(${PROJECT_NAME} ${SRC_LIST})

