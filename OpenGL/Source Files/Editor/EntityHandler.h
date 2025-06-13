#pragma once
#include "pch.h"

#include "entity.h"
#include "component.h"
#include "system.h"

namespace Editor {

    class EntityHandler {
    public:
        static std::shared_ptr<Entity> CreateEntity();
        static void SetSelectedEntity(uint32_t id);
        static std::shared_ptr<Entity> GetSelectedEntity();
        static std::shared_ptr<Entity> GetEntityById(uint32_t id);
        static int GetID();
        static void TerminateEntity();

        static void render(Shader& shader, Camera& camera);
        static void render(Shader& shader, uint32_t id);

        static void rlight(Shader& shader);

    private:
        static uint32_t ID;
        static int _selectedID;

        static std::vector<std::shared_ptr<Entity>> entities;

        static std::unique_ptr<Editor::RenderSystem> _rendersys;
        static std::unique_ptr<Editor::LightSystem> _lightsystem;
    };

}
