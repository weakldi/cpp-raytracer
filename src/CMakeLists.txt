include(CTest)
enable_testing()

include_directories("./include")

file(GLOB SOURCES
    *.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "..")
add_executable(raytracer ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    glm
)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

target_compile_options(raytracer PRIVATE -Wall -g)
include(CPack)
