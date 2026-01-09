#include "graphics/Renderer.h"
#include <GL/glew.h>
#include <spdlog/spdlog.h>

Renderer::Renderer() : m_Initialized(false) {
    spdlog::info("Constructor");
}

Renderer::~Renderer() {
    spdlog::info("Renderer destroyed");
}

bool Renderer::Initialize() {
    // Initialise GLEW

    if(true)
    {
        
    
        GLenum err = glewInit();
        if (err != GLEW_OK) {
            spdlog::error("Failed to initialize GLEW");
            return false;
        }
        spdlog::info("Initializing Renderer");
        spdlog::info("OpenGL Version: {}", (const char*)glGetString(GL_VERSION));
        spdlog::info("GLEW Version: {}", (const char*)glewGetString(GLEW_VERSION));
        
        // Config de base
        glEnable(GL_DEPTH_TEST);
        
        m_Initialized = true;
        spdlog::info("Renderer Initialized!");
    }

    return true;
}

void Renderer::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::SetClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}