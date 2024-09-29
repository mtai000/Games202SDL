cmake_minimum_required (VERSION 3.8)

project ("Games202")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

if(WIN32 AND "${CMAKE_GENERATOR}" MATCHES "^(Visual Studio).*")
  set(MODULE_TARGET_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(ConfigurationName)")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
else()
  set(MODULE_TARGET_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endif()

if(WIN32)
    include($ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
endif()

include(cmake/copy.cmake)
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(SDL2 REQUIRED)
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/deps/imgui)

include_directories(
    ${GLEW_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
    ${SDL2_INCLUDE_DIRS}
    deps/stb_image
    deps/imgui
)

add_subdirectory ("hw1")
