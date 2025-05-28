#include "Entityhandler.h"

namespace Editor {

    int EntityHandler::ID = 0;
    std::vector<std::shared_ptr<Entity>> EntityHandler::entities;
    std::unique_ptr<Editor::TransformSystem> EntityHandler::m_tsystem = std::make_unique<Editor::TransformSystem>();
    std::unique_ptr<Editor::MeshSystem> EntityHandler::m_msytem = std::make_unique<Editor::MeshSystem>();

    std::shared_ptr<Entity> EntityHandler::CreateEntity() {
        int entityId = ID++;
        auto entity = std::make_shared<Entity>(entityId);
        entities.emplace_back(entity);
        std::cout << "Entity: [" << entityId << "] : Added" << std::endl;
        return entity;
    }

    std::shared_ptr<Entity> EntityHandler::GetSelectedEntity() {
        if (ID - 1 >= 0 && ID - 1 < entities.size()) {
            return entities[ID - 1];
        }
        return nullptr;
    }

    std::shared_ptr<Entity> EntityHandler::GetSelectedEntityById(int id) {
        if (id >= 0 && id < entities.size()) {
            return entities[id];
        }
        return nullptr;
    }

    int EntityHandler::GetID() {
        return ID;
    }

    void EntityHandler::TerminateEntity() {
        if (ID > 0 && ID <= entities.size()) {
            std::cout << "Entity: [" << ID - 1 << "] : Removed" << std::endl;
            entities.erase(entities.begin() + (ID - 1));
            --ID;
        }
        else {
            std::cerr << "Error: Invalid entity ID." << std::endl;
        }
    }

    void EntityHandler::render(Shader& shader) {
        m_tsystem->update(entities, shader);
        m_msytem->update(entities, shader);
    }
}
