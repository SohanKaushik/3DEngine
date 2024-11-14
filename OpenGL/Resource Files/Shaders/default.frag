#version 330 core

in vec3 aColor;  // Color passed from the vertex shader
out vec4 FragColor;

void main()
{
    FragColor = vec4(aColor, 1.0);  // Set the final color output
}
