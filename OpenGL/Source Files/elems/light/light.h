#pragma once

#include "pch.h"
#include "shader/shader.h" 
#include "render/ShadowMap.h"
#include "lightparams.h"

namespace elems {

    enum class LightType {
        Point,
        Directional,
        Spot
    };

    class Light {
    protected:
        elems::LightParams* _data;

    public:
        Light(LightParams* ldata) : _data(ldata) {}
        virtual ~Light() = default;

        virtual LightType GetType() const = 0;
        virtual void SetLightUniform(Shader& shader, const std::string& uniformName) = 0;
    };

    class DirectionalLight : public Light {

    public:
        glm::vec3 _direction = glm::vec3(1.0f, 1.0f, 1.0f);

    public:
        DirectionalLight(LightParams* data);

        LightType GetType() const override { return LightType::Directional; }
        void SetLightUniform(Shader& shader, const std::string& uniformName) override;
    };

}