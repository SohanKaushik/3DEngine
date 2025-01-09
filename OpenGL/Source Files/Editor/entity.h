#pragma once
#include "pch.h"
#include "component.h"
#include <typeindex>
#include <iostream>
#include <unordered_map>
#include <memory>

namespace Editor {

    class Entity {
    public:
        explicit Entity(int id) : id(id) {}

        // Add a component of type T
        template <typename T, typename... Args>
        T& AddComponent(Args&&... args) {
            static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");

            auto type = std::type_index(typeid(T));
            if (components.find(type) != components.end()) {
                throw std::runtime_error("Component already exists for this entity");
            }

            auto component = std::make_shared<T>(std::forward<Args>(args)...);
            components[type] = component;

            return *component;
        }

        // Get a component of type T
        template <typename T>
        T* GetComponent() {
            static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");

            auto it = components.find(std::type_index(typeid(T)));
            if (it != components.end()) {
                return static_cast<T*>(it->second.get());
            }
            return nullptr;  // Return nullptr if not found
        }

        // Check if a component of type T exists
        template <typename T>
        bool HasComponent() const {
            return components.find(std::type_index(typeid(T))) != components.end();
        }

        int GetID() {
            return id;
        }

    private:
        int id;

        std::unordered_map<std::type_index, std::shared_ptr<Component>> components;
    };

}
