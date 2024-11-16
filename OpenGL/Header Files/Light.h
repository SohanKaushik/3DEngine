#pragma once

#include <glm/glm.hpp>
#include "Shader.h"  // Include the Shader class


class Light {
public:


    glm::vec3 m_diffuse;
    glm::vec3 m_ambient;
    glm::vec3 m_specular;

    Light(const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec);


    // Common lighting computation to be reused in derived classes
    glm::vec3 ComputeCommonLight(const glm::vec3& lightDir, const glm::vec3& normal, const glm::vec3& viewDir) const;
    virtual void SetLightUniform(Shader& shader, const std::string& uniformName) const = 0;


private:
    glm::vec3 m_color;
    float m_intensity;
};

class DirectionalLight : public Light {

private:
    glm::vec3 m_direction;

public:
    DirectionalLight(const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec, const glm::vec3& dir);
    glm::vec3 CalculateLight(const glm::vec3& normal, const glm::vec3& viewDir) const;

    void SetLightUniform(Shader& shader, const std::string& uniformName) const override;
};



class PointLight;
class SpotLight;