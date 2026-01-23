#pragma once
#include <cstdint>
#include <memory>
#include "core/RenderableObject.h"
#include "core/GameObject.h"
#include <vector>


class AudioManager;
class Window;
class Renderer;
class Mesh;
class Shader;
class Camera;
//class GameObject;

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
    std::unique_ptr<AudioManager> m_AudioManager;
    
    // All game object
    std::vector<GameObject> gameObjects;
    GameObject test;

    // Test mesh
    std::shared_ptr<Mesh> m_CubeMesh;
    std::shared_ptr<Mesh> m_SphereMesh;
    std::shared_ptr<Mesh> m_PlaneMesh;
    // Baswic shader
    std::shared_ptr<Shader> m_BasicShader;
    std::shared_ptr<Shader> m_BasicLigthShader;

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
