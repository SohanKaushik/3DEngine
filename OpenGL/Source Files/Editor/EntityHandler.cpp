#include "pch.h"
#include "Entityhandler.h"

namespace Editor {

    uint32_t EntityHandler::ID = 0;
    int EntityHandler::_selectedID = -1;

    std::vector<std::shared_ptr<Entity>> EntityHandler::entities;
    std::unique_ptr<Editor::RenderSystem> EntityHandler::_rendersys = std::make_unique<Editor::RenderSystem>();
    std::unique_ptr<Editor::LightSystem> EntityHandler::_lightsystem = std::make_unique<Editor::LightSystem>();

    std::shared_ptr<Entity> EntityHandler::CreateEntity() {
        int entityId = ID++;
        _selectedID = entityId;
        auto entity = std::make_shared<Entity>(entityId);
        entities.emplace_back(entity);
        std::cout << "Entity: [" << entityId << "] : Added" << std::endl;
        return entity;
    }

    void EntityHandler::SetSelectedEntity(uint32_t id)
    {
        if (id < entities.size()) {
            _selectedID = id;
            return;
        }
        _selectedID = -1;
    }


    std::shared_ptr<Entity> EntityHandler::GetSelectedEntity() {
        if (_selectedID >= 0 && _selectedID < entities.size()) {
            return entities[_selectedID];
        }
        return nullptr;
    }

    std::shared_ptr<Entity> EntityHandler::GetEntityById(uint32_t id) {
        if (id >= 0 && id < entities.size()) {
            return entities[id];
        }
        return nullptr;
    }

    int EntityHandler::GetID() {
        return ID;
    }

    void EntityHandler::TerminateEntity() {
        if (_selectedID >= 0 && _selectedID < entities.size()) {
            std::cout << "Entity: [" << _selectedID << "] : Removed" << std::endl;
            entities.erase(entities.begin() + _selectedID);
            --ID;

            // Optionally clear selection
            _selectedID = -1;
        }
        else {
            std::cerr << "Error: Invalid entity index." << std::endl;
        }
    }

    void EntityHandler::render(Shader& shader, Camera& camera) {
        _rendersys->update(entities, shader, camera);
    }

    void EntityHandler::render(Shader& shader, uint32_t id)
    {
        if (id >= entities.size()) return;

        auto& entity = entities[id];
        if (!entity->HasComponent<MeshComponent>()) {
            std::cerr << "Entity [" << id << "] has no Mesh Component" << std::endl;
        }

        auto mesh_com = entity->GetComponent<Editor::MeshComponent>();
        auto transform = entity->GetComponent<TransformComponent>();
        auto* meshes = mesh_com->GetMesh();
        if (meshes) {
            shader.SetUniformMat4f("model", transform->GetModelUniforms());
            meshes->draw();
        }

    }

    void EntityHandler::rlight(Shader& shader)
    {
        _lightsystem->update(entities, shader);
    }
  
}
