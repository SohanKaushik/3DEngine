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




SpotLight::SpotLight(const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec, const glm::vec3& dir, const glm::vec3& position, const float inner, const float outer)
    : Light(amb, diff, spec), m_direction(dir) , m_position(position) , m_inner(inner) , m_outer(outer)
{};

PointLight::PointLight(const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec, const glm::vec3& position)
    : Light(amb,diff,spec), m_position(position)
{}



void DirectionalLight::SetLightUniform(Shader& shader, const std::string& uniformName) const {

    shader.SetUniform3fv(uniformName + ".direction", m_direction);
    shader.SetUniform3fv(uniformName + ".ambient", m_ambient);
    shader.SetUniform3fv(uniformName + ".diffuse", m_diffuse);
    shader.SetUniform3fv(uniformName + ".specular", m_specular);
};


void SpotLight::SetLightUniform(Shader& shader, const std::string& uniformName) const {

    shader.SetUniform3fv(uniformName + ".direction", m_direction);
    shader.SetUniform3fv(uniformName + ".ambient", m_ambient);
    shader.SetUniform3fv(uniformName + ".diffuse", m_diffuse);
    shader.SetUniform3fv(uniformName + ".specular", m_specular);
    shader.SetUniform3fv(uniformName + ".position", m_position);
    shader.SetUniform1f(uniformName + ".inner", glm::cos(glm::radians(m_inner)));
    shader.SetUniform1f(uniformName + ".outer", glm::cos(glm::radians(m_outer)));
};

void PointLight::SetLightUniform(Shader& shader, const std::string& uniformName) const
{
    shader.SetUniform3fv(uniformName + ".ambient", m_ambient);
    shader.SetUniform3fv(uniformName + ".diffuse", m_diffuse);
    shader.SetUniform3fv(uniformName + ".specular", m_specular);
    shader.SetUniform3fv(uniformName + ".position", m_position);
};

