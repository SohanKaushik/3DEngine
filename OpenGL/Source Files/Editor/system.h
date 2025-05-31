#pragma once
#include "pch.h"
#include "Editor/entity.h"
#include "component.h"
#include "shader/shader.h"
#include "elems/mesh.h"

namespace Editor {

    class System {
    public:
        ~System() = default;
    };


    class TransformSystem : System{
    public:

        void update(std::vector<std::shared_ptr<Editor::Entity>>& entities, Shader& shader) {
            for (auto& entity : entities) {
                 auto index = &entity - &entities[0] + 1;


                 if (!entity->HasComponent<TransformComponent>()) {
                     std::cerr << "Entity [" << index << "] has no Transform Component" << std::endl;
                     continue;
                  }
                   
                auto transform = entity->GetComponent<TransformComponent>();
                shader.SetUniformMat4f("model", transform->GetModelUniforms());
            }
        }
    };

    class MeshSystem : public System {
    public:
        void update(const std::vector<std::shared_ptr<Editor::Entity>>& entities, Shader& shader) {
            for (auto& entity : entities) {
                auto index = &entity - &entities[0];

                if (!entity->HasComponent<MeshComponent>()) {
                    std::cerr << "Entity [" << index << "] has no Mesh Component" << std::endl;
                    continue;
               }

                auto mesh_com = entity->GetComponent<Editor::MeshComponent>();
                auto transform = entity->GetComponent<TransformComponent>();
                auto* meshes = mesh_com->GetMesh();
                if (meshes) {
                    shader.SetUniformMat4f("model", transform->GetModelUniforms());
                    shader.SetUniform3fv("color", mesh_com->GetColor());
                    meshes->draw();
                }
            }
        }
    };
}