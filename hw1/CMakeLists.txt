cmake_minimum_required(VERSION 3.17)

project("hw1")

include_directories(src)
file(GLOB actor_src src/Actor/*.cpp src/Actor/*.h)
file(GLOB comp_src src/Component/*.cpp src/Component/*.h)
file(GLOB core_src src/Core/*.cpp src/Core/*.h)
file(GLOB obj_src src/Object/*.cpp src/Object/*.h)
file(GLOB shader_src src/Shader/*.cpp src/Shader/*.h)
set(gui_src src/UI/Gui.cpp src/UI/Gui.h)

file(GLOB IMGUI_SRC ${IMGUI_DIR}/*.h ${IMGUI_DIR}/*.cpp)
set(IMGUI_SRC
    ${IMGUI_SRC}
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.h
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl2.h
    ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
)

add_executable(
  ${PROJECT_NAME}
  src/main.cpp
  src/head.h
  ${util_src}
  ${actor_src}
  ${core_src}
  ${comp_src}
  ${obj_src}
  ${shader_src}
  ${gui_src}
  ${IMGUI_SRC}
)

target_link_libraries(${PROJECT_NAME}
    OpenGL::GL
    ${GLFW_LIBRARIES} 
    ${GLEW_LIBRARIES} 
    SDL2::SDL2
)

CopyAssets(${PROJECT_NAME} assets)
CopyAssets(${PROJECT_NAME} shaders)