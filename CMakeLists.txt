cmake_minimum_required(VERSION 3.0.0)
project(raytracer VERSION 0.1.0)

#LIBS
#GLM
set(GLM_LIB_NAME "glm")
set(GLM_INCLUDE_PATH ${GLM_LIB_NAME}/glm)

add_library(${GLM_LIB_NAME} INTERFACE)
target_include_directories(${GLM_LIB_NAME}
    INTERFACE
        ${GLM_INCLUDE_PATH}
)

include(CTest)
enable_testing()

add_executable(raytracer main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
