cmake_minimum_required(VERSION 3.2)

project(sfml_project)

set(CMAKE_CXX_FLAGS "-Wall")

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/Shader.cpp
    src/VAO.cpp
    src/VBO.cpp
    src/EBO.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_directories(${PROJECT_NAME}
    PUBLIC bin
)

target_link_libraries(${PROJECT_NAME}
    sfml-graphics-2.dll
    sfml-window-2.dll
    sfml-system-2.dll
    glew32.dll
    opengl32.dll
)