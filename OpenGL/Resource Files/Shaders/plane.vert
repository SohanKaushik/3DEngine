#version 330 core

layout (location = 0) in vec3 aPlanePos;

uniform mat4 mvp2;
uniform vec3 planeColor;


out vec3 aPlaneColor;

void main()
{
	gl_Position = mvp2 * vec4(aPlanePos, 1.0f);
	aPlaneColor = planeColor;
}