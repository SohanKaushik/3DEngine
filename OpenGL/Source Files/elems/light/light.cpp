#include "pch.h"

#include "Light.h"
#include "shader/shader.h"
#include "ui/viewport.h"

namespace elems {


    DirectionalLight::DirectionalLight(LightParams* data)
        :Light(data)
    {}

    void DirectionalLight::SetLightUniform(Shader& shader, const std::string& uniformName) {

        shader.SetUniform3fv(uniformName + ".direction", glm::normalize(_data->angle));
        shader.SetUniform3fv(uniformName + ".color", _data->albedo);
        shader.SetUniform1f(uniformName + ".intensity", _data->strength);

    };

}


