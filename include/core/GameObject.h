#pragma once
#include "Component.h"
#include <memory>
#include <vector>
#include <typeindex>
#include <unordered_map>
#include <string>
#include <iostream>
class GameObject
{

public:
    GameObject(const std::string& name = "GameObject");
    ~GameObject();

    template<typename __Component> __Component* AddComponent();
    template<typename __Component> __Component* GetComponent();
    template<typename __Component> bool HasComponent();

    TransformComponent* transform;
    std::string name;
    bool active = true;
private:
    std::vector<std::unique_ptr<Component>> m_Components;
    std::unordered_map<std::type_index, Component*> m_ComponentMap;
};


template<typename __Component>
__Component* GameObject::AddComponent()
{

    spdlog::info("Fuck yeah compoenent added");
    static_assert(std::is_base_of<Component, __Component>::value, "Component must derive from Component");
    auto component = std::make_unique<__Component>();
    __Component* ptr = component.get();
    
    m_Components.push_back(std::move(component));
    m_ComponentMap[std::type_index(typeid(__Component))] = ptr;
    
    return ptr;
}


template<typename __Component>
__Component* GameObject::GetComponent()
{
    auto it = m_ComponentMap.find(std::type_index(typeid(__Component)));
    
    if (it != m_ComponentMap.end()) {
        return static_cast<__Component*>(it->second);
    }
    
    return nullptr;
}

template<typename __Component>
bool GameObject::HasComponent()
{
    return m_ComponentMap.count(std::type_index(typeid(__Component))) > 0;
}   


struct TestComponent : Component {

    TestComponent() 
    {

        std::cout << "Added test component";
    }
    int health = 100;
    std::string message = "Hello!";
};