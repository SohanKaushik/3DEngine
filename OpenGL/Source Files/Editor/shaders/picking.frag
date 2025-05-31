#version 330 core

uniform vec3 color;  // RGB encoded from entity ID

out vec4 FragColor;

void main()
{
    FragColor = vec4(color, 1.0);
}
