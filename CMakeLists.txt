cmake_minimum_required(VERSION 3.21)

# Force static runtime to match vcpkg x64-windows-static
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

project(Wimzee VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find packages
find_package(spdlog CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

# stb (header-only, peut être tricky)
find_path(STB_INCLUDE_DIRS "stb_image.h")
find_path(STB_INCLUDE_DIRS "miniaudio.h")

# Sources
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(wimzee ${SOURCES})

target_include_directories(wimzee PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${STB_INCLUDE_DIRS}
)

target_link_libraries(wimzee PRIVATE
    spdlog::spdlog_header_only
    glm::glm
    GLEW::GLEW
    glfw
    OpenGL::GL
)

# Copy assets
add_custom_command(TARGET wimzee POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:wimzee>/assets
)