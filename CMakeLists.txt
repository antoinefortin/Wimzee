# CMakeLists.txt
cmake_minimum_required(VERSION 3.16)

# Silence deprecation warnings
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)
cmake_policy(SET CMP0169 OLD)
cmake_policy(SET CMP0174 OLD)

project(Wimzee)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Allow old CMake in dependencies
set(CMAKE_POLICY_VERSION_MINIMUM 3.5 CACHE STRING "" FORCE)

include(FetchContent)

# spdlog
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.13.0
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(spdlog)

# GLM (header-only)
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.9.8
    GIT_SHALLOW TRUE
)
FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
    FetchContent_Populate(glm)
endif()

# stb (header-only)
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_SHALLOW TRUE
)
FetchContent_GetProperties(stb)
if(NOT stb_POPULATED)
    FetchContent_Populate(stb)
endif()

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(glfw)

# GLEW
if(APPLE)
    find_package(GLEW REQUIRED)
    set(GLEW_TARGET GLEW::GLEW)
else()
    set(glew-cmake_BUILD_SHARED OFF CACHE BOOL "" FORCE)
    set(glew-cmake_BUILD_STATIC ON CACHE BOOL "" FORCE)
    set(ONLY_LIBS ON CACHE BOOL "" FORCE)
    FetchContent_Declare(
        glew
        GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
        GIT_TAG glew-cmake-2.2.0
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(glew)
    set(GLEW_TARGET libglew_static)
endif()


# Find all sources
file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

# Includes
target_include_directories(${PROJECT_NAME} PRIVATE
    include
    ${glm_SOURCE_DIR}
    ${stb_SOURCE_DIR}
)

# Link dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE 
    spdlog::spdlog
    glfw
    ${GLEW_TARGET}
)

# Platform-specific
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
elseif(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework OpenGL")
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE GL)
endif()