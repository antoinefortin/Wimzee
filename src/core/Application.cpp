#include "core/Application.h"
#include "core/Window.h"
#include "graphics/Renderer.h"
#include "input/Input.h"
#include <spdlog/spdlog.h>
#include <chrono>

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
}

Application::~Application() {
    spdlog::info("Application destroyed");
}

void Application::ProcessInput()
{
    if(Input::IsKeyPressed(KEY_W))
    {
        spdlog::info("W pressed");
    }

    if(Input::IsKeyPressed(KEY_SPACE))
    {
        spdlog::info("Space pressed");
        m_Renderer->SetClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    }

    if (Input::IsKeyPressed(KEY_ESCAPE)) {
        spdlog::info("Escape - closing...");
        m_Running = false;
    }
    float mx, my;
    Input::GetMousePosition(mx, my);
    
    float dx, dy;
    Input::GetMouseDelta(dx, dy);
    
    if (dx != 0 || dy != 0) {
        spdlog::info("Mouse: ({:.0f}, {:.0f}) Delta: ({:.1f}, {:.1f})", mx, my, dx, dy);
    }

}


void Application::Run() {
    auto lastTime = std::chrono::high_resolution_clock::now();
    
    while (m_Running && !m_Window->ShouldClose()) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
        lastTime = currentTime;
        
        Input::Update();
        ProcessInput();
        Update(deltaTime);
        Render();
        m_Window->Update();

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
    // Ton rendering ici plus tard
}