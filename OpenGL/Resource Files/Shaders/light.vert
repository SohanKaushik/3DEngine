#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 mvp;
uniform vec3 lightColor;


out vec3 aLightColor;

void main()
{
	gl_Position = mvp * vec4(aPos, 1.0f);
	aLightColor = lightColor;
}