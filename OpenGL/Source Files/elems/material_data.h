#pragma once
#include "pch.h"
#include <shader/shader.h>

namespace elems {
    struct LambertParams {
        Shader shader;

        glm::vec3 albedo = glm::vec3(1.0f);
        float ambient = 1.0f;
    };

    struct PhongParams {
        Shader shader;

        glm::vec3 albedo;
        glm::vec3 specular;
        float shininess;
    };
}
