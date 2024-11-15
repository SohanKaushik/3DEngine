#version 330 core

in vec3 aLightColor;
out vec4 FragColor;


void main()
{
	FragColor = vec4(aLightColor, 1.0f);
}