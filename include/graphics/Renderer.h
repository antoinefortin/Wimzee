#pragma once

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