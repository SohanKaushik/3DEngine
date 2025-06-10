#pragma once

#include "pch.h"
#include "shader/Shader.h"

namespace elems {

    struct MaterialData {
        glm::vec3 albedo = glm::vec3(1.0f);
        glm::vec3 ambient = glm::vec3(1.0f);
        glm::vec3 specular = glm::vec3(1.0f);
        float shininess = 32.0f;
    };

    class Material {
    private:
        MaterialData* _material = nullptr;

    public:
        Material() = default;

        Material(MaterialData* matt)
            : _material(matt){
        }

        void apply(Shader& shader) const {
            if (!_material) return;

            shader.SetUniform3fv("color", _material->albedo);
            shader.SetUniform3fv("ambient", _material->ambient);
            shader.SetUniform3fv("specular", _material->specular);
            shader.SetUniform1f("shininess", _material->shininess);
        }

        MaterialData* GetMaterial() { return _material; }
        const MaterialData* GetMaterial() const { return _material; }

    };
}
