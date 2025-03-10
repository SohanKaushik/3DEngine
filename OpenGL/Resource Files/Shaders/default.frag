#version 330 core

out vec4 FragColor;

uniform vec3 color;
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
    float alpha;
};
uniform Material material;

void main()
{
    FragColor = vec4(color, material.alpha); // White color
}
