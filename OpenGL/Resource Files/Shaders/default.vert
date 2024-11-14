#version 330 core

layout(location = 0) in vec3 aPos;  // Vertex position attribute
layout(location = 1) in vec3 aNormal;  // Vertex normal attribute



uniform mat4 u_MVP;  // Model-View-Projection matrix
uniform vec3 color;  // Color passed as a uniform

out vec3 aColor;  // Output color for the fragment shader

void main()
{
    gl_Position = u_MVP * vec4(aPos, 1.0);  // Apply transformation
    aColor = color;  // Pass uniform color to fragment shader
}
