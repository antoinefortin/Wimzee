#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Input
{
public:
    static void Initialize(GLFWwindow* window);

    //Keyboard
    static bool IsKeyPressed(int keycode);
    static bool IsKeyDown(int keycode);
    static bool IsKeyUp(int keycode);    
    //Mouse
    static bool IsMouseButtonPressed(int button);
    static void GetMousePosition(float& x, float& y);
    static void GetMouseDelta(float& dx, float& dy);

    // Called by GLFW Callback

    static void Update();

private:

    // keybaord
    static GLFWwindow* s_Window;
    static bool s_Keys[GLFW_KEY_LAST];
    static bool s_KeysLast[GLFW_KEY_LAST];

    // Mouse
    static bool s_MouseButtons[GLFW_MOUSE_BUTTON_LAST];
    static bool s_MouseButtonsLast[GLFW_MOUSE_BUTTON_LAST];
    static float s_MouseX, s_MouseY;
    static float s_MouseLastX, s_MouseLastY;
};


/*
    Just a way to wrap around GLFW kley
*/
#define KEY_W GLFW_KEY_W
#define KEY_A GLFW_KEY_A
#define KEY_S GLFW_KEY_S
#define KEY_D GLFW_KEY_D
#define KEY_SPACE GLFW_KEY_SPACE
#define KEY_ESCAPE GLFW_KEY_ESCAPE
#define KEY_Q GLFW_KEY_Q
#define KEY_E GLFW_KEY_E

#define KEY_P GLFW_KEY_P // Audio shortcut


#define MOUSE_LEFT GLFW_MOUSE_BUTTON_LEFT
#define MOUSE_RIGHT GLFW_MOUSE_BUTTON_RIGHT



