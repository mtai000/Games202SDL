cmake_minimum_required(VERSION 3.17)

project("hw1")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE /NODEFAULTLIB:library")

include_directories(src)

file(GLOB actor_src src/Actor/*.cpp src/Actor/*.h)
file(GLOB comp_src src/Component/*.cpp src/Component/*.h)
file(GLOB core_src src/Core/*.cpp src/Core/*.h)
file(GLOB obj_src src/Object/*.cpp src/Object/*.h)
file(GLOB shader_src src/Shader/*.cpp src/Shader/*.h)

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
)
# add_executable(${PROJECT_NAME} "src/test.cpp")

target_link_libraries(${PROJECT_NAME}
    OpenGL::GL
    ${GLFW_LIBRARIES} 
    ${GLEW_LIBRARIES} 
    SDL2::SDL2
)

CopyShaders(${PROJECT_NAME})
CopyAssets(${PROJECT_NAME})
if(WIN32)
CopyDLL(${PROJECT_NAME})
endif()
