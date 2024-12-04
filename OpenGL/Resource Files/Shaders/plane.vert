#version 330 core

layout (location = 0) in vec3 aPlanePos;

// Uniforms
uniform mat4 model;           
uniform mat4 view;              
uniform mat4 projection;        

uniform vec3 planeColor;


out vec3 aPlaneColor;

void main()
{
	gl_Position = projection * view * model * vec4(aPlanePos, 1.0f);
	aPlaneColor = planeColor;
}