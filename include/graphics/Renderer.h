
#pragma once
// GLEW DOIT être inclus AVANT tout autre header OpenGL
#define GLEW_STATIC
#include <GL/glew.h>

class Renderer
{
public:
    Renderer();
    ~Renderer();

    bool Initialize();
    void Clear();
    void SetClearColor(float r, float g, float b, float a);
private:
    bool m_Initialized;
};