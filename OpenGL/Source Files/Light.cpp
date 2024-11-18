#include <glm/glm.hpp>
#include "Light.h"
#include "Shader.h"
#include "Rend.h"

Light::Light(const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec)
	: m_ambient(amb), m_diffuse(diff), m_specular(spec)
{};



DirectionalLight::DirectionalLight(const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec, const glm::vec3& dir)
	: Light(amb, diff, spec), m_direction(dir)
{};




class SpotLight : public Light {};

class PointLight : public Light {};



void DirectionalLight::SetLightUniform(Shader& shader, const std::string& uniformName) const {

    shader.SetUniform3fv(uniformName + ".direction", m_direction);
    shader.SetUniform3fv(uniformName + ".ambient", m_ambient);
    shader.SetUniform3fv(uniformName + ".diffuse", m_diffuse);
    shader.SetUniform3fv(uniformName + ".specular", m_specular);
};

