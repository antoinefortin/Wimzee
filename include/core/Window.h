#pragma once


#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>


class Window
{
public:
    Window(int width, int height, const std::string& title);
    ~Window();
    void Update();
    bool ShouldClose() const;

    int GetWidth() const {return m_Width;}
    int GetHeight() const {return m_Height;}
    GLFWwindow* GetNativeWindow() const { return m_Window; }  
private:

    GLFWwindow* m_Window;
    int m_Width;
    int m_Height;
    
};