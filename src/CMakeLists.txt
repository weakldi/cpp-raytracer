include(CTest)
enable_testing()

include_directories("./include")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "..")
add_executable(raytracer main.cpp)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    glm
)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
