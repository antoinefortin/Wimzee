#pragma once
#include <cstdint>
#include <memory>
#include "core/RenderableObject.h"
#include <vector>
class Window;
class Renderer;
class Mesh;
class Shader;
class Camera;
class Application
{

public:
    Application();
    ~Application();
    void Run();
private:
    void Update(float deltaTime);
    void Render();
    void HandleCameraInput(float deltaTime);
    void ProcessInput();

    bool m_Running;
    uint64_t frameNumber;
    std::unique_ptr<Window> m_Window;
    std::unique_ptr<Renderer> m_Renderer;
    

    std::shared_ptr<Mesh> m_CubeMesh;
    std::shared_ptr<Mesh> m_SphereMesh;
    
    std::shared_ptr<Shader> m_BasicShader;

    std::vector<RenderableObject> m_Objects; 
    bool renderCube =  false;
    // Camera
    std::unique_ptr<Camera> m_Camera;
    float m_CameraSpeed = 5.0f;
    float m_MouseSensitivity = 0.1f;
    bool m_FirstMouse = true;
    float m_LastMouseX = 0.0f;
    float m_LastMouseY = 0.0f;

};
