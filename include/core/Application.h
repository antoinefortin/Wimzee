#pragma once
#include <cstdint>
#include <memory>

class Window;
class Renderer;

class Application
{

public:
    Application();
    ~Application();
    void Run();
private:
    void Update(float deltaTime);
    void Render();

    void ProcessInput();

    bool m_Running;
    uint64_t frameNumber;
    std::unique_ptr<Window> m_Window;
    std::unique_ptr<Renderer> m_Renderer;


};