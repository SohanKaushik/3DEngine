#pragma once
#include "pch.h"
#include "Editor/entity.h"
#include "component.h"
#include "shader/shader.h"
#include "elems/mesh.h"

namespace Editor {

    class System {
    public:
        virtual ~System() = default;
    };

    class RenderSystem : public System {
    public:
        void update(const std::vector<std::shared_ptr<Editor::Entity>>& entities, Shader& shader, Camera& camera) {
            for (auto& entity : entities) {
                auto index = &entity - &entities[0];

                if (!entity->HasComponent<TransformComponent>() ||
                    !entity->HasComponent<MeshComponent>() ||
                    !entity->HasComponent<MaterialComponent>()) {
                    std::cerr << "Entity [" << index << "] missing required components.\n";
                    continue;
                }


                // components
                auto transformc = entity->GetComponent<TransformComponent>();
                auto meshc = entity->GetComponent<Editor::MeshComponent>();
                auto* materialc = entity->GetComponent<MaterialComponent>();

                // to get
                auto* meshes = meshc->GetMesh();
                Shader& shader1 = materialc->GetShader();

                if (meshes) {
                    shader1.use();
                    camera.UpdateCameraMatrix(shader1);
                    shader1.SetUniformMat4f("model", transformc->GetModelUniforms());
                    materialc->GetMaterial()->apply();
                    meshes->draw();
                }

            
            }
        }
    };

    class LightSystem : public System {
    public:
        void update(const std::vector<std::shared_ptr<Editor::Entity>>& entities, Shader& shader) {
            for (auto& entity : entities) {
                auto index = &entity - &entities[0];

                
                if (!entity->HasComponent<LightComponent>()) {
                    continue;
                }

                auto lightcom = entity->GetComponent<LightComponent>();
                auto* light = lightcom->GetLight();

                if (light) {
                    switch (light->GetType())
                    {
                      case elems::LightType::Directional:
                           light->SetLightUniform(shader, "dirLight");
                           break;

                      case elems::LightType::Spot:
                          light->SetLightUniform(shader, "SpotLight");
                          break;

                      case elems::LightType::Point:
                          light->SetLightUniform(shader, "PointLight");
                          break;
                    }
                }
            }
        }
    };
}