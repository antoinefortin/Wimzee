#pragma once
#include "Component.h"
#include <memory>
#include <vector>
#include <typeindex>
#include <unordered_map>
#include <string>
class GameObject
{

public:
    GameObject(const std::string& name = "GO");
    ~GameObject();

    template<typename __Component> __Component* AddComponent();
    template<typename __Component> __Component* GetComponent();
    template<typename __Component> bool HasComponent() const;

    TransformComponent* transform;
    std::string name;
    bool active = true;
private:
    std::vector<std::unique_ptr<Component>> m_Components;
    std::unordered_map<std::type_index, Component*> m_ComponentMap;
};

template<typename __Component>
__Component GameObject::AddComponent()
{
    static_assert(std::is_base_of<Component, __Component>::value, "Component must derive from Component");
    auto component = std::make_unique<T>();
    __Component* ptr = component.get();

    return ptr;
}
