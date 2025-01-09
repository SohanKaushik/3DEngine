#pragma once
#include "pch.h"
#include "entity.h"
#include "component.h"
#include "system.h"

namespace Editor {

    class EntityHandler {

    public:
    public:
        static std::shared_ptr<EntityHandler> GetInstance() {
            static EntityHandler* instance = new EntityHandler();
            return std::shared_ptr<EntityHandler>(instance);
        }

        // Create a new entity
        std::shared_ptr<Entity> CreateEntity() {
            int entityId = ID++; 
            entities.emplace_back(std::make_unique<Entity>(entityId));
            std::shared_ptr<Entity> entityPtr = entities.back();

            std::cout << "Entity: [" << ID  << "]" << std::endl;
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
            m_tsystem->update(entities, shader);
            m_msytem->update(entities, shader);
        }

        auto GetSelectedEntity() const {
           
            if (entities.empty()) {
                std::cerr << "Entity is Empty!! \n";
                throw std::runtime_error("No selected entity");
            }
            return entities[0]->GetComponent<TransformComponent>();
        }


    private:
        int ID = 0;  // To generate unique IDs for entities
        std::vector<std::shared_ptr<Entity>> entities;

        std::unique_ptr<Editor::TransformSystem> m_tsystem = std::make_unique<Editor::TransformSystem>();
        std::unique_ptr<Editor::MeshSystem> m_msytem = std::make_unique<Editor::MeshSystem>();

        EntityHandler() = default;  
        // Prevent copying
        EntityHandler(const EntityHandler&) = delete;
        EntityHandler& operator=(const EntityHandler&) = delete;
    };

}
