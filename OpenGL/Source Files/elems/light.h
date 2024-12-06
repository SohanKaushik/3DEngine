#pragma once

#include <glm/glm.hpp>
#include "shader/shader.h"  // Include the Shader class


class Light {
public:


    glm::vec3 m_diffuse;
    glm::vec3 m_ambient;
    glm::vec3 m_specular;

    Light(const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec);


    // Common lighting computation to be reused in derived classes
    virtual void SetLightUniform(Shader& shader, const std::string& uniformName) const = 0;

};

class DirectionalLight : public Light {

public:
    glm::vec3 m_direction;

public:
    DirectionalLight(const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec, const glm::vec3& dir);

    void SetLightUniform(Shader& shader, const std::string& uniformName) const override;
};



class SpotLight : public Light {

public:
    glm::vec3 m_direction;
    glm::vec3 m_position;
    float m_inner;
    float m_outer;

public:
    SpotLight(const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec, const glm::vec3& dir,
        const glm::vec3& position, const float inner, const float outer);

    void SetLightUniform(Shader& shader, const std::string& uniformName) const override;

};


class PointLight : public Light {

public:
    glm::vec3 m_position;
    


public: 
    PointLight(const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec, const glm::vec3& position);

    void SetLightUniform(Shader& shader, const std::string& uniformName) const override;
};