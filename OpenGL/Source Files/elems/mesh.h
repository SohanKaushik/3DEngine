#pragma once

#include "pch.h"
#include "render/VertexIndexBuffer.h"
#include "elems/Primitive.h"
#include "shader/shader.h"

namespace elems {

    struct Transform {
        glm::vec3 position;
        glm::vec3 scale;
        glm::vec3 rotation;
    };

    class Mesh {
    public:
        Mesh(Transform transform);
        void draw();

    private:
        std::string m_id; // Unique identifier
        
    public:
        Transform transform;

        // Setters for Transform data
        void setPosition(const glm::vec3& pos) { transform.position = pos; }
        void setScale(const glm::vec3& sca) { transform.scale = sca; }
        void setRotation(const glm::vec3& rot) { transform.rotation = rot; }

        // Getters for Transform data
        glm::vec3 getPosition() const { return transform.position; }
        glm::vec3 getScale() const { return transform.scale; }
        glm::vec3 getRotation() const { return transform.rotation; }

    private:
        glm::mat4 m_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

        std::unique_ptr<render::VertexIndexBuffer> mBuffer = std::make_unique<render::VertexIndexBuffer>();
        std::unique_ptr<elems::Primitive> mPrimitives = std::make_unique<elems::Primitive>();
        std::unique_ptr<Shader> mShader = std::make_unique<Shader>();
                                                  
    };
}