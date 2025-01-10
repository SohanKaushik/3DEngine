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

        void update(Shader& shader) {
            m_tsystem->update(entities, shader);
            m_msytem->update(entities, shader);
        }

        auto GetSelectedEntity() const {
            if (ID - 1 >= 0 && ID - 1 < entities.size()) {
                return entities[ID - 1];
            }
            else {
                return std::shared_ptr<Entity>(); // Return an empty shared pointer
            }
        }

       void TerminateEntity() {
           if (ID > 0 && ID <= entities.size()) {
               entities.erase(entities.begin() + (ID - 1));
               std::cout << "Entity: [" << ID << "] : Removed" << std::endl;

               // Decrement ID if needed
               if (ID > 0) {
                   --ID;
               }
           }
           else {
               std::cerr << "Error: Invalid entity ID." << std::endl;
           }
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
