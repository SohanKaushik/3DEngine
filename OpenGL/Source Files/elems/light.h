#pragma once

#include "pch.h"
#include "shader/shader.h"  // Include the Shader class
#include "render/ShadowMap.h"

//enum class LightType {
//    Directional,
//    Point,
//    Spotlight
//};

namespace ui {
    class Viewport;
}

namespace elems {

    class Light {

        enum class LightType {
            Point,
            Directional,
            Spot
        };

    public:
        glm::vec3 m_diffuse;
        glm::vec3 m_ambient;
        glm::vec3 m_specular;
       // std::unique_ptr<render::ShadowMap> mShadowFBO = std::make_unique<render::ShadowMap>();

        //std::shared_ptr<ui::Viewport> mViewport = std::make_shared<ui::Viewport>();

        Light(const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec);


        // Getters and setters
       /* const glm::vec3& getColor() const { return m_color; }
        void setColor(const glm::vec3& color) { m_color = color; }

        float getIntensity() const { return m_intensity; }
        void setIntensity(float intensity) { m_intensity = intensity; }

        LightType getType() const { return m_type; }*/

        // Common lighting computation to be reused in derived classes
        virtual void SetLightUniform(Shader& shader, const std::string& uniformName) const = 0;
        virtual glm::mat4 getLightMatrix() = 0;
        //virtual void UpdadeShadowMatrices(Shader& shader, ui::Viewport& viewport) = 0;

        static void render(const std::vector<std::unique_ptr<elems::Light>> lights, Shader& shader);

    };

    class DirectionalLight : public Light {

    public:
        glm::vec3 m_direction;
        glm::mat4 m_lightSpaceMatrix;
        std::unique_ptr<render::ShadowMap> mShadowFBO = std::make_unique<render::ShadowMap>();

    public:
        DirectionalLight(const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec, const glm::vec3& dir);

        void SetLightUniform(Shader& shader, const std::string& uniformName) const override;
        unsigned int GetShadowMapTexture() const;
        void UpdadeShadowMatrices(Shader& shadowShader, ui::Viewport& viewport);
        glm::mat4 getLightMatrix() override;
    };


    class SpotLight : public Light {

    public:
        glm::vec3 m_direction;
        glm::vec3 m_position;
        float m_inner;
        float m_outer;

    public:
        SpotLight(const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec, const glm::vec3& dir,
            const glm::vec3& position, const float inner, const float outer);

        void SetLightUniform(Shader& shader, const std::string& uniformName) const override;

    };


    class PointLight : public Light {

    public:
        glm::vec3 m_position;



    public:
        PointLight(const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec, const glm::vec3& position);

        void SetLightUniform(Shader& shader, const std::string& uniformName) const override;
    };

}