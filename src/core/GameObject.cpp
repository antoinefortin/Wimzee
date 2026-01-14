#include "core/GameObject.h"

GameObject::GameObject(const std::string& name) : name(name)
{
    transform = AddComponent<TransformComponent>();
}

GameObject::~GameObject()
{
    // What cleanup is needed?
}


