#include "pch.h"

#include "Light.h"
#include "shader/shader.h"
#include "Rend.h"

using namespace elems;

Light::Light(const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec)
	: m_ambient(amb), m_diffuse(diff), m_specular(spec)
{}

void elems::Light::render(const std::vector<std::unique_ptr<elems::Light>> lights, Shader& shader)
{
    int lightIndex = 0;
    for (const auto& light : lights) {
        std::string uniformBase = "lights[" + std::to_string(lightIndex) + "]";
        light->SetLightUniform(shader, uniformBase);
        ++lightIndex;
    }
};


DirectionalLight::DirectionalLight(const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec, const glm::vec3& dir)
	: Light(amb, diff, spec), m_direction(dir)
{
    /*mShadowFBO->create_buffer(1024, 1024);
    mShadowFBO->bind();*/

    // Updating Matrices
    //this->UpdadeShadowMatrices();
};




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
}

void elems::DirectionalLight::UpdadeShadowMatrices(Shader& shadowShader)
{
    // Projecting light as a Camera
    glm::mat4 orthogonalProj = glm::ortho(-35.0f, 35.0f, -35.0f, 35.0f, 0.1f, 75.0f);
    glm::vec3 lightPos = -2.0f * m_direction;
    glm::vec3 lightTarget = glm::vec3(0.0f);            
    glm::vec3 lightUp = glm::vec3(0.0f, 1.0f, 0.0f);    
    glm::mat4 lightView = glm::lookAt(lightPos, lightTarget, lightUp);
    glm::mat4 lightSpaceMatrix = orthogonalProj * lightView;

    shadowShader.use();
    shadowShader.SetUniformMat4f("lightSpaceMatrix", lightSpaceMatrix);
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


