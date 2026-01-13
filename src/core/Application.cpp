#include "core/Application.h"
#include "core/Window.h"
#include "graphics/Renderer.h"
#include "graphics/Camera.h"

#include "graphics/Mesh.h"
#include "graphics/Shader.h"
#include "input/Input.h"
#include <spdlog/spdlog.h>
#include <chrono>


#ifndef M_PI
    #define M_PI 3.14159
#endif

std::vector<Vertex> GenerateSphereVertices(float radius, int segments)
{
    std::vector<Vertex> vertices;
    
    for (int lat = 0; lat <= segments; lat++) {
        for (int lon = 0; lon <= segments; lon++) {
            float theta = lat * M_PI / segments;        
            
            float phi = lon * 2 * M_PI / segments;      
            
            
            // Position sur la sphere
            float x = radius * sin(theta) * cos(phi);
            float y = radius * cos(theta);
            float z = radius * sin(theta) * sin(phi);
            
            glm::vec3 position(x, y, z);
            glm::vec3 normal = glm::normalize(position);  // Normal pointe vers l'extérieur
            glm::vec2 texCoord(lon / (float)segments, lat / (float)segments);
            
            vertices.push_back(Vertex(position, normal, texCoord));
        }
    }
    
    return vertices;
}

std::vector<uint32_t> GenerateSphereIndices(int segments)
{
    std::vector<uint32_t> indices;
    
    for (int lat = 0; lat < segments; lat++) {
        for (int lon = 0; lon < segments; lon++) {
            int current = lat * (segments + 1) + lon;
            int next = current + segments + 1;
            
            // Premier triangle
            indices.push_back(current);
            indices.push_back(next);
            indices.push_back(current + 1);
            
            // Deuxième triangle
            indices.push_back(current + 1);
            indices.push_back(next);
            indices.push_back(next + 1);
        }
    }
    
    return indices;
}

std::vector<Vertex> GenerateCubeVertices()
{

    std::vector<Vertex> vertices = {
            Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0, 0, 1), glm::vec2(0, 0)),
            Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3(0, 0, 1), glm::vec2(1, 0)),
            Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3(0, 0, 1), glm::vec2(1, 1)),
            Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0, 0, 1), glm::vec2(0, 1)),
            
            Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0, 0, -1), glm::vec2(1, 0)),
            Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0, 0, -1), glm::vec2(1, 1)),
            Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3(0, 0, -1), glm::vec2(0, 1)),
            Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3(0, 0, -1), glm::vec2(0, 0)),
            
            // Top face
            Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0, 1, 0), glm::vec2(0, 1)),
            Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0, 1, 0), glm::vec2(0, 0)),
            Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3(0, 1, 0), glm::vec2(1, 0)),
            Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3(0, 1, 0), glm::vec2(1, 1)),
            
            // Bottom face
            Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0, -1, 0), glm::vec2(1, 1)),
            Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3(0, -1, 0), glm::vec2(0, 1)),
            Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3(0, -1, 0), glm::vec2(0, 0)),
            Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0, -1, 0), glm::vec2(1, 0)),
            
            // Right face
            Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3(1, 0, 0), glm::vec2(1, 0)),
            Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3(1, 0, 0), glm::vec2(1, 1)),
            Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3(1, 0, 0), glm::vec2(0, 1)),
            Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3(1, 0, 0), glm::vec2(0, 0)),
            
            // Left face
            Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1, 0, 0), glm::vec2(0, 0)),
            Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1, 0, 0), glm::vec2(1, 0)),
            Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1, 0, 0), glm::vec2(1, 1)),
            Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-1, 0, 0), glm::vec2(0, 1))
        };

    return vertices;
}

std::vector<uint32_t> GenerateCubeIndices()
{
    
    std::vector<uint32_t> indices = {
        0,  1,  2,   2,  3,  0,   // Front
        4,  5,  6,   6,  7,  4,   // Back
        8,  9, 10,  10, 11,  8,   // Top
        12, 13, 14,  14, 15, 12,   // Bottom
        16, 17, 18,  18, 19, 16,   // Right
        20, 21, 22,  22, 23, 20    // Left
    };

    return indices;
}

Application::Application() : m_Running(true) {
    m_Window = std::make_unique<Window>(1280, 720, "Wimzee Engine");
    m_Renderer = std::make_unique<Renderer>();
    
    if (!m_Renderer->Initialize()) {
        spdlog::error("Failed to initialize renderer");
        m_Running = false;
        return;
    }
    
    Input::Initialize(m_Window->GetNativeWindow());  // ← Ajoute

    // basic background color
    m_Renderer->SetClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    spdlog::info("Application initialized");

    // Creating cube
    std::vector<Vertex> cubeVertices = GenerateCubeVertices();
    std::vector<uint32_t> cubeIndices = GenerateCubeIndices();    
    m_CubeMesh = std::make_shared<Mesh>(cubeVertices, cubeIndices);

     // Sphere mesh
    std::vector<Vertex> sphereVertices = GenerateSphereVertices(0.5f, 32);  // radius 0.5, 32 segments
    std::vector<uint32_t> sphereIndices = GenerateSphereIndices(32);
    m_SphereMesh = std::make_shared<Mesh>(sphereVertices, sphereIndices);

    // Shader
    m_BasicShader = std::make_shared<Shader>
    (
        "assets/shaders/basic.vert",
        "assets/shaders/basic.frag"
    );
    // Camera shit 
    float aspectRatio = (float)m_Window->GetWidth() / (float)m_Window->GetHeight();
    m_Camera = std::make_unique<Camera>(45.0f, aspectRatio, 0.1f, 100.0f);
    m_Camera->SetPosition(glm::vec3(0.0f, 2.0f, 5.0f));
    float offset = 12.5;
    for(int i{0}; i <5; i++)
    {
        for(int y{0}; y < 5; y++)
        {
            m_Objects.push_back({
            .position = glm::vec3(i, 0, y),
            .rotation = glm::vec3(0, 0, 0),
            .scale = glm::vec3(1, 1, 1),
            .color = glm::vec3(abs(sin(i)), 0.0f, abs(cos(y)))
        });
        }

    }

    if(false)
    {
        m_Objects.push_back({
            .position = glm::vec3(3, 5, 0),
            .rotation = glm::vec3(0, 0, 0),
            .scale = glm::vec3(1, 1, 1),
            .color = glm::vec3(0, 1, 0)
        });
        
        m_Objects.push_back({
            .position = glm::vec3(-3, 0, 0),
            .rotation = glm::vec3(0, 45, 0),  // Rotation Y
            .scale = glm::vec3(1, 1, 1),
            .color = glm::vec3(0, 0, 1.0f)
        });
    }


}

Application::~Application() {
    spdlog::info("Application destroyed");
}

/*
    this is just for tesitng, will be moved per component 
    just dont know for now 
*/
void Application::ProcessInput()
{
    if(Input::IsKeyPressed(KEY_SPACE))
    {
        spdlog::info("Space pressed");
        m_Renderer->SetClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    }

}


void Application::Run() {
    auto lastTime = std::chrono::high_resolution_clock::now();
    
    while (m_Running && !m_Window->ShouldClose()) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
        lastTime = currentTime;
        
        Input::Update();
        HandleCameraInput(deltaTime);

        ProcessInput();
        Update(deltaTime);
        Render();
        m_Window->Update();

    }
}


void Application::HandleCameraInput(float deltaTime)
{

    // kb. 
    if (Input::IsKeyPressed(KEY_W)) {
        m_Camera->MoveForward(m_CameraSpeed * deltaTime);
        spdlog::info("WPressed");
    }
    if (Input::IsKeyPressed(KEY_S)) {
        m_Camera->MoveForward(-m_CameraSpeed * deltaTime);
    }
    if (Input::IsKeyPressed(KEY_A)) {
        m_Camera->MoveRight(-m_CameraSpeed * deltaTime);
    }
    if (Input::IsKeyPressed(KEY_D)) {
        m_Camera->MoveRight(m_CameraSpeed * deltaTime);
    }
    if (Input::IsKeyPressed(KEY_Q)) {

        renderCube = false;

        m_Camera->MoveUp(m_CameraSpeed * deltaTime);
    }

    if(Input::IsKeyPressed(KEY_E))
    {
        renderCube = true;
        m_Camera->MoveUp(-m_CameraSpeed * deltaTime);

    }

        // Mouse look (right click to rotate)
    if (Input::IsMouseButtonPressed(MOUSE_RIGHT)) {
        float mouseX, mouseY;
        Input::GetMousePosition(mouseX, mouseY);
        
        if (m_FirstMouse) {
            m_LastMouseX = mouseX;
            m_LastMouseY = mouseY;
            m_FirstMouse = false;
        }
        
        float deltaX = mouseX - m_LastMouseX;
        float deltaY = m_LastMouseY - mouseY;
        
        m_LastMouseX = mouseX;
        m_LastMouseY = mouseY;
        
        m_Camera->Rotate(deltaY * m_MouseSensitivity, deltaX * m_MouseSensitivity);
    } else {
        m_FirstMouse = true;
    }

}
void Application::Update(float deltaTime) {


    static int frameCount = 0;
    if (++frameCount % (60 * 50) == 0) {
        spdlog::info("FPS: {:.1f}", 1.0f / deltaTime);
    }
}




void Application::Render() {
    m_Renderer->Clear();
    
    glm::mat4 view = m_Camera->GetViewMatrix();
    glm::mat4 projection = m_Camera->GetProjectionMatrix();
    
    m_BasicShader->Bind();
    m_BasicShader->SetMat4("uView", view);
    m_BasicShader->SetMat4("uProjection", projection);
    

    
    for (size_t i = 0; i < m_Objects.size(); i++) {
        const auto& obj = m_Objects[i];
        
        m_BasicShader->SetMat4("uModel", obj.GetModelMatrix());
        m_BasicShader->SetVec3("uColor", obj.color);
        
        // sphere and cube rendering...
        if (i < 500) {
            if(renderCube == false)
            {
                m_SphereMesh->Draw();
            }
            else 
            {
                m_CubeMesh->Draw();
            }
            
        } 
    }
    
    m_BasicShader->Unbind();

}
