#version 330 core
in vec3 fragPos;
out vec4 FragColor;

in vec3 color;

void main()
{
    FragColor = vec4(color, 1.0f);  // White color
}
