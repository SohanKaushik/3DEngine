#version 330 core

layout (location = 0) in vec3 aPlanePos;

// Uniforms
uniform mat4 model;            // Model matrix
uniform mat4 view;               // View matrix
uniform mat4 projection;         // Projection matrix

uniform vec3 planeColor;


out vec3 aPlaneColor;

void main()
{
	gl_Position = projection * view * model * vec4(aPlanePos, 1.0f);
	aPlaneColor = planeColor;
}