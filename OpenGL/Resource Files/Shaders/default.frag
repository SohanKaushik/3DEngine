#version 330 core

in vec3 aColor; 
in vec2 TexCoord;

out vec4 FragColor;

in vec3 FragPos;     

uniform vec3 albedo;              
 
uniform float ambient;

void main()
{
    FragColor = vec4(albedo * ambient, 1.0f);
}                                 