#version 330 core

in vec3 aPlaneColor;
out vec4 FragColor;


void main()
{
	FragColor = vec4(aPlaneColor, 1.0f);
}