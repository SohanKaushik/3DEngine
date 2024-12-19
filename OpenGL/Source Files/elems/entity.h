#pragma once
#include "pch.h"
#include "elems/mesh.h"
#include "elems/camera.h"
#include "shader/shader.h"
#include "elems/entity.h"

namespace elems {

    enum EntityType {
        mesh,
        light,
    };

    struct Transform {
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
    };

     
    // Base class for entities
    class Entity {
    public:

        virtual void init() = 0;  // Pure virtual method for initialization
        virtual void render(Shader& shader) = 0;
        virtual void update() = 0; // Pure virtual method for updating the entity

        virtual ~Entity() = default; // Virtual destructor for polymorphism
    };

 
    class MeshEntity : public Entity {
    private:
        std::unique_ptr<elems::Mesh> mMesh;
        glm::vec3 mColor;
        glm::mat4 m_model;

    public:
        Transform m_transform;

        MeshEntity(PrimitiveType type, const Transform& transform, const glm::vec3& color)
            : mColor(color), m_model(glm::mat4(1.0f)), m_transform(transform){
           
            mMesh = std::make_unique<elems::Mesh>(type);
        };
      
        void init() override {

        };

        void update() override {
            // Update entity logic (e.g., transformations or animations)
            // For example, you could rotate or move the mesh over time
        };

        void render(Shader& shader) override {

            m_model = glm::mat4(1.0f);

            m_model = glm::translate(m_model, m_transform.position);
            m_model = glm::rotate(m_model, glm::radians(0.0f), glm::normalize(m_transform.rotation));
            m_model = glm::scale(m_model, m_transform.scale);

            // Pass the model matrix and color to the shader
            shader.SetUniformMat4f("model", m_model);
            shader.SetUniform3fv("color", mColor);

            // Draw the mesh
            mMesh->draw();
        }
    };
}
