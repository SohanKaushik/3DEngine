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
        //virtual void update(const std::vector<std::shared_ptr<Editor::Entity>>& entities, Shader& shader) = 0;
    };

    class TransformSystem : public System {
    public:

        void update(const std::vector<std::shared_ptr<Editor::Entity>>& entities)  {
            for (auto& entity : entities){
                 auto index = &entity - &entities[0] + 1;


                 if (!entity->HasComponent<TransformComponent>()) {
                     std::cerr << "Entity [" << index << "] has no Transform Component" << std::endl;
                     continue;
                  }
                   
                auto transform = entity->GetComponent<TransformComponent>();
                auto material = entity->GetComponent<MaterialComponent>();
                Shader shader = material->GetShader();
                shader.SetUniformMat4f("model", transform->GetModelUniforms());
            }
        }
    };

    class MeshSystem : public System {
    public:
        void update(const std::vector<std::shared_ptr<Editor::Entity>>& entities)  {
            for (auto& entity : entities) {
                auto index = &entity - &entities[0];

                if (!entity->HasComponent<MeshComponent>()) {
                    std::cerr << "Entity [" << index << "] has no Mesh Component" << std::endl;
                    continue;
               }

                auto mesh_com = entity->GetComponent<Editor::MeshComponent>();
                auto transform = entity->GetComponent<TransformComponent>();
                auto material = entity->GetComponent<MaterialComponent>();
                
                Shader shader = material->GetShader();
                auto* meshes = mesh_com->GetMesh();
                if (meshes) {
                    shader.SetUniformMat4f("model", transform->GetModelUniforms());
                    meshes->draw();
                }
            }
        }
    };

   class MaterialSystem : public System {
    public:
        void update(const std::vector<std::shared_ptr<Editor::Entity>>& entities)  {
            for (auto& entity : entities) {

               if (!entity->HasComponent<MeshComponent>()) {
                    continue;
                }

                auto material = entity->GetComponent<Editor::MaterialComponent>();
                Shader shader = material->GetShader();

                shader.SetUniform3fv("color", material->GetColor());
                shader.SetUniform1f("material.alpha", material->GetAlpha());

             /*   shader.SetUniform3fv("material.ambient", material->GetAmbient());
                shader.SetUniform3fv("material.diffuse", material->GetAmbient());
                shader.SetUniform3fv("material.specular", material->GetAmbient());
                shader.SetUniform1i("material.shininess", material->GetShininess());*/
            }
        };
    };
}