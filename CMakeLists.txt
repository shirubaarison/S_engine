cmake_minimum_required(VERSION 4.1.1)
project(s_engine LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(VENDOR_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor")

include(FetchContent)

# GLFW
FetchContent_Declare(
  glfw 
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.4)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_X11 ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# GLM
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 1.0.1)
FetchContent_MakeAvailable(glm)

# GLAD
add_library(glad STATIC ${VENDOR_DIR}/glad/src/glad.c)
target_include_directories(glad PUBLIC ${VENDOR_DIR}/glad/include)

# stb
add_library(stb STATIC ${VENDOR_DIR}/stb/stb_image.c)
target_include_directories(stb PUBLIC ${VENDOR_DIR}/stb)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    ${VENDOR_DIR}/glad/include
    ${VENDOR_DIR}/stb
)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
    glad
    stb
    glfw
    glm
)

if (UNIX AND NOT APPLE)
  target_link_libraries(${PROJECT_NAME} PRIVATE dl)
endif()

if (MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic
    -Wuninitialized)
endif()
