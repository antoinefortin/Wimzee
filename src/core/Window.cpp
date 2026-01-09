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