#pragma once

#include "pch.h"
#include <shader/shader.h>
#include "material_data.h"

namespace elems {

    class IMaterial {
    public:
        virtual void apply() = 0;
        virtual Shader& GetShader() = 0;
        virtual ~IMaterial() = default;
    };

    template<typename ShaderModel>
    class Material : public IMaterial {
    private:
        ShaderModel shadermodel;

    public:
        Material() = default;

        void apply() override {
            shadermodel.apply();
        }

        Shader& GetShader() override {
            return shadermodel.GetShader();
        }

        ShaderModel& GetModel() {
            return shadermodel;
        }
    };

    class Lambert {
    public:
        elems::LambertParams _lambert;
        Lambert() {
            _lambert.shader.load("Resource Files/Shaders/default.vert", "Resource Files/Shaders/default.frag");
        }

        void apply() {
            _lambert.shader.use();  
            _lambert.shader.SetUniform3fv("albedo", _lambert.albedo);
            _lambert.shader.SetUniform1f("ambient", _lambert.ambient);
        }

        Shader& GetShader() {
            return _lambert.shader;
        }
    };


    class Phong {
    public:
        void apply() {
            std::cout << "Applying Phong shading\n";
        }
    };

}
