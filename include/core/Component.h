#pragma once 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <memory>
#include <spdlog/spdlog.h>

class GameObject;
class Mesh;
class Shader;

struct Component
{
    virtual ~Component() = default;
    GameObject* gameObject = nullptr;
};

struct TransformComponent : Component 
{
    glm::vec3 position {glm::vec3(0.0f)};
    glm::vec3 rotation {glm::vec3(0.0f)};
    glm::vec3 scale {glm::vec3(1.0f)};

    glm::mat4 GetModelMatrix() const;
};

struct MeshRendererComponent : Component {
    glm::vec3 color = glm::vec3(1.0f);
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Shader> shader;

    std::string name;

    void assignName(const std::string& _name)
    {
        name = _name;
    }

};

struct RotatorComponent : Component {
    glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f);
    float speed = 45.0f;
};


enum LightType
{
    Point, 
    Area, 
    Directionnal
};

struct LightComponent : Component
{
    LightComponent(
        const std::string& _name,
        LightType _type,
        const glm::vec3& _lightColor,
        const float& _intensity
    ) : name(_name),
        type{_type}, 
        color(_lightColor), 
        intensity(_intensity)
    {}
    std::string name{};
    LightType type{};
    float intensity{};
    glm::vec3 color {};
    

};

struct ErrorMsgComponent : Component
{
    ErrorMsgComponent()
    {

        spdlog::error("Added error component");
    }    
    
};  