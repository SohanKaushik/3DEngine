#pragma once
#include "pch.h"
#include "entity.h"
#include "component.h"
#include "system.h"

namespace Editor {

    class EntityHandler {
    public:

        // Create a new entity
        Entity* CreateEntity() {
            int entityId = nextEntId++;
            auto entity = std::make_unique<Entity>(entityId);
            Entity* entityPtr = entity.get();
            entities.push_back(std::move(entity));
            return entityPtr;
        }

        template <typename T>
        void AttachEntity(Entity* entity, std::unique_ptr<T> component) {
            if (entity) {
                if (!entity->HasComponent<T>()) {
                    entity->AddComponent(std::move(component));
                }
                else {
                    std::cerr << "Entity already has component of this type!" << std::endl;
                }
            }
        }

        template <typename T>
        void DeAttachEntity(Entity* entity) {
           /* if (entity) {
                entity->RemoveComponent<T>();
            }*/
        }

        void RemoveEntity(int entityId) {
           /* entities.erase(std::remove_if(entities.begin(), entities.end(),
                [entityId](const std::unique_ptr<Entity>& entity) {
                    return entity->GetID() == entityId;
                }), entities.end());*/
        }

        void update(Shader& shader) {
            entities[0]->GetComponent<TransformComponent>()->SetPosition(glm::vec3(5.0f, 0.0f, 0.0f));
            m_tsystem->update(entities, shader);
            m_msytem->update(entities, shader);
        }

    private:
        int nextEntId = 0;  // To generate unique IDs for entities
        std::vector<std::shared_ptr<Entity>> entities;
        std::unique_ptr<Editor::TransformSystem> m_tsystem = std::make_unique<Editor::TransformSystem>();
        std::unique_ptr<Editor::MeshSystem> m_msytem = std::make_unique<Editor::MeshSystem>();
    };

}
