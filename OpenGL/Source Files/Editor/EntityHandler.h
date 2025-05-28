#pragma once
#include "pch.h"

#include "entity.h"
#include "component.h"
#include "system.h"

namespace Editor {

    class EntityHandler {
    public:
        static std::shared_ptr<Entity> CreateEntity();
        static std::shared_ptr<Entity> GetSelectedEntity();
        static std::shared_ptr<Entity> GetSelectedEntityById(int id);
        static int GetID();
        static void TerminateEntity();

        static void render(Shader& shader);

    private:
        static int ID;
        static std::vector<std::shared_ptr<Entity>> entities;

        static std::unique_ptr<Editor::TransformSystem> m_tsystem;
        static std::unique_ptr<Editor::MeshSystem> m_msytem;
    };

}
