#pragma once
#include "pch.h"
#include "elems/mesh.h"
#include "elems/camera.h"
#include "shader/shader.h"
#include "elems/entity.h"

namespace elems {

    enum EntityType { mesh, light, camera };
    //enum class MeshType { Cube, Plane, Sphere };

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

        virtual void setPosition(const glm::vec3& position) = 0;
        virtual void setRotation(const glm::vec3& position) = 0;
        virtual void setScale(const glm::vec3& scale) = 0;

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

        void setPosition(const glm::vec3& position) {
            m_transform.position = position;
        };
        
        void setScale(const glm::vec3& scale) {
            m_transform.scale = scale;
        };

        void setRotation(const glm::vec3& rot) {
            m_transform.rotation = rot;
        };

        void update() override {
            // Update entity logic (e.g., transformations or animations)
            // For example, you could rotate or move the mesh over time
        };

        void render(Shader& shader) override {

            m_model = glm::mat4(1.0f);

            m_model = glm::translate(m_model, m_transform.position);

       
            glm::mat4 rotMatrix = glm::mat4(1.0f);

            rotMatrix = glm::rotate(rotMatrix, glm::radians(m_transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate around X
            rotMatrix = glm::rotate(rotMatrix, glm::radians(m_transform.rotation.y), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate around Y
            rotMatrix = glm::rotate(rotMatrix, glm::radians(m_transform.rotation.z), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate around Z
            

           /* m_transform.rotation = rotx * m_transform.rotation;
            m_transform.rotation = roty * m_transform.rotation;
            m_transform.rotation = rotz * m_transform.rotation;*/


           
            m_model = rotMatrix * m_model;
            m_model = glm::scale(m_model, m_transform.scale);

            // Pass the model matrix and color to the shader
            shader.SetUniformMat4f("model", m_model);
            shader.SetUniform3fv("color", mColor);

            // Draw the mesh
            mMesh->draw();
        }
    };
    
   class CameraEntity : public Entity {

      private:
        Transform m_transform;

   public:
        float m_fov;
        float m_clipStart;
        float m_clipEnd;
        std::unique_ptr<elems::Camera> mCamera;

        CameraEntity(elems::ProjectionType type, float fov, const Transform& transform, float startclip, float endclip)
            :m_transform(transform), m_fov(fov), m_clipStart(startclip), m_clipEnd(m_clipEnd){
            mCamera = std::make_unique<elems::Camera>(type, m_fov,  m_clipStart, m_clipEnd);
        };

        void init(){}
        void render(Shader& shader) {

            glm::mat4 view = glm::mat4(1.0f);
            view = glm::rotate(view, glm::radians(m_transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
            view = glm::rotate(view, glm::radians(m_transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
            view = glm::rotate(view, glm::radians(m_transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
            view = glm::translate(view, -m_transform.position);

            //mCamera->SetViewMatrix(m_transform.position, m_transform.rotation, glm::vec3(0.0f, 0.0f, 0.0f));

            shader.SetUniformMat4f("view", mCamera->GetViewMatrix()); 
            shader.SetUniformMat4f("projection", mCamera->GetProjectionMatrix()); 
        };
        
        void update() {

        };


        void setPosition(const glm::vec3& position) {
            m_transform.position = position;
        };

        void setScale(const glm::vec3& scale) {
            m_transform.scale = scale;
        };

        void setRotation(const glm::vec3& rot) {
            m_transform.rotation = rot;
        };
    };
}
