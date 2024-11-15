#include <glm/glm.hpp>
#include "Light.h"
#include "Shader.h"
#include "Rend.h"

Light::Light(const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec, const glm::vec3& position)
	: m_ambient(amb), m_diffuse(diff), m_specular(spec) , m_position(position)
{};



DirectionalLight::DirectionalLight(const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec, const glm::vec3& dir, const glm::vec3& position)
	: Light(amb, diff, spec, position), m_direction(dir)
{};




class SpotLight : public Light {};

class PointLight : public Light {};



glm::vec3 Light::ComputeCommonLight(const glm::vec3& lightDir, const glm::vec3& normal, const glm::vec3& viewDir) const {

    // Ambient component: A constant base light level for all surfaces
    glm::vec3 ambientComp = m_ambient;

    // Diffuse component: Light intensity based on the angle between light direction and surface normal
    float diff = std::max(glm::dot(normal, lightDir), 0.0f); 
    glm::vec3 diffuseComp = m_diffuse * diff;


    // Specular component: Reflective highlights, stronger when the view direction aligns with the reflection
    glm::vec3 reflectDir = glm::reflect(-lightDir, normal);
    float spec = std::pow(std::max(glm::dot(viewDir, reflectDir), 0.0f), 32.0f); // 32 is the shininess factor
    glm::vec3 specularComp = m_specular * spec;

    // Combine all components to get the final lighting effect at the point
    return ambientComp + diffuseComp + specularComp;
};

glm::vec3 DirectionalLight::CalculateLight(const glm::vec3& normal, const glm::vec3& viewDir) const {
    return ComputeCommonLight(-m_direction, normal, viewDir);
};


glm::vec3 Light::GetPosition() const {
    return m_position;
}

void DirectionalLight::SetLightUniform(Shader& shader, const std::string& uniformName) const {

    shader.SetUniform3fv(uniformName + ".position", m_position);
    shader.SetUniform3fv(uniformName + ".direction", m_direction);
    shader.SetUniform3fv(uniformName + ".ambient", m_ambient);
    shader.SetUniform3fv(uniformName + ".diffuse", m_diffuse);
    shader.SetUniform3fv(uniformName + ".specular", m_specular);
};

