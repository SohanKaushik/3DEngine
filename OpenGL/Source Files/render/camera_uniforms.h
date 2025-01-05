#pragma once
#include "pch.h"

namespace render {

    struct CameraUniforms {
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
        glm::vec3 cameraPosition;
        float padding; // Ensure 16-byte alignment if needed
    };
};