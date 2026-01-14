#include "core/Window.h"
#include <spdlog/spdlog.h>


Window::Window(int width, int height, const std::string& title)
    : m_Width(width), m_Height(height), m_Window(nullptr)
{
    if(!glfwInit())
    {
        spdlog::error("Failed to initialize GLTF");
        return;
    }

#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#elif defined(__linux__)
    // Linux - using OpenGL 3.3 (FOr VM VM)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    m_Window = glfwCreateWindow(width, height, title.c_str(),nullptr, nullptr);

    if(!m_Window)
    {
        spdlog::error("Faled to create window");
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_Window);

    spdlog::info("Window Created");
}

Window::~Window()
{
    if(m_Window)
    {
        glfwDestroyWindow(m_Window);
    }
    glfwTerminate();
    spdlog::info("Window Destroy");
}

void Window::Update()
{
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}

bool Window::ShouldClose() const 
{
    return glfwWindowShouldClose(m_Window);
}