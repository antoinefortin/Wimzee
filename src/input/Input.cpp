#include "input/Input.h"
#include <cstring>

GLFWwindow* Input::s_Window = nullptr;

bool Input::s_Keys[GLFW_KEY_LAST] = {};
bool Input::s_KeysLast[GLFW_KEY_LAST] = {};
bool Input::s_MouseButtons[GLFW_MOUSE_BUTTON_LAST] = {};
bool Input::s_MouseButtonsLast[GLFW_MOUSE_BUTTON_LAST] = {};
float Input::s_MouseX = 0.0f;
float Input::s_MouseY = 0.0f;
float Input::s_MouseLastX = 0.0f;
float Input::s_MouseLastY = 0.0f;

void Input::Initialize(GLFWwindow* window) {
    s_Window = window;
}


void Input::Update() 
{

    std::memcpy(s_KeysLast, s_Keys, sizeof(s_Keys));
    std::memcpy(s_MouseButtonsLast, s_MouseButtons, sizeof(s_MouseButtons));

    for (int i = 0; i < GLFW_KEY_LAST; i++) {
        s_Keys[i] = glfwGetKey(s_Window, i) == GLFW_PRESS;
    }
    
    // Update mouse buttons
    for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++) {
        s_MouseButtons[i] = glfwGetMouseButton(s_Window, i) == GLFW_PRESS;
    }


    // Update mouse position
    double x, y;
    glfwGetCursorPos(s_Window, &x, &y);
    s_MouseLastX = s_MouseX;
    s_MouseLastY = s_MouseY;
    s_MouseX = (float)x;
    s_MouseY = (float)y;

}


bool Input::IsKeyPressed(int keycode) {
    return s_Keys[keycode];
}

bool Input::IsKeyDown(int keycode) {
    return s_Keys[keycode] && !s_KeysLast[keycode];
}

bool Input::IsKeyUp(int keycode) {
    return !s_Keys[keycode] && s_KeysLast[keycode];
}

bool Input::IsMouseButtonPressed(int button) {
    return s_MouseButtons[button];
}

void Input::GetMousePosition(float& x, float& y) {
    x = s_MouseX;
    y = s_MouseY;
}

void Input::GetMouseDelta(float& dx, float& dy) {
    dx = s_MouseX - s_MouseLastX;
    dy = s_MouseY - s_MouseLastY;
}
