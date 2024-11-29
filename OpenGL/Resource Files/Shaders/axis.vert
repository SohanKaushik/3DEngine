#version 330 core

layout(location = 0) in vec3 aPos;    // Vertex position
layout(location = 1) in vec3 aColor;  // Vertex color

out vec3 vertexColor;  // Pass to fragment shader

uniform mat4 u_mvp;    // Model-View-Projection matrix

void main()
{
    gl_Position = u_mvp * vec4(aPos, 1.0); // Transform vertex
    vertexColor = aColor;                 // Pass color to fragment shader
}
