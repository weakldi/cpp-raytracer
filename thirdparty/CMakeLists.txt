# glm
set(GLM_LIB_NAME "glm")
set(GLM_INC_PATH ${GLM_LIB_NAME}/glm)

add_library(${GLM_LIB_NAME} INTERFACE)

target_include_directories(${GLM_LIB_NAME}
    INTERFACE
        ${GLM_INC_PATH}
)