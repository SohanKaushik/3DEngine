#pragma once

#include "pch.h"
#include "render/VertexIndexBuffer.h"
#include "elems/Primitive.h"
#include "shader/shader.h"

namespace elems {

    enum class PrimitiveType {
        cube,
        plane,
        sphere
    };

    class Mesh {
    public:

        Mesh(PrimitiveType type);
        void draw();
     

    public:
      
      /*  glm::vec3 mColor = glm::vec3(1.0);*/

        // Setters for Transform data
      /*  void setPosition(const glm::vec3& pos) { transform.position = pos; }
        void setScale(const glm::vec3& sca) { transform.scale = sca; }
        void setRotation(const glm::vec3& rot) { transform.rotation = rot; }*/

       /* void setColor(const glm::vec3 color) { mColor = color; }*/
        // Getters for Transform data
       /* glm::vec3 getPosition() const { return transform.position; }
        glm::vec3 getScale() const { return transform.scale; }
        glm::vec3 getRotation() const {
            if(transform.rotation == glm::vec3(0.0f)) return glm::vec3(1.0f, 0.0f, 0.0f); }*/

       /* glm::vec3 getColor() const { return mColor; }*/

    private:
        glm::mat4 m_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

        std::unique_ptr<render::VertexIndexBuffer> mBuffer = std::make_unique<render::VertexIndexBuffer>();
        std::unique_ptr<elems::Primitive> mPrimitives = std::make_unique<elems::Primitive>();
        std::unique_ptr<Shader> mShader = std::make_unique<Shader>();
                                                  
    };
}