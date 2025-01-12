#version 330 core

uniform sampler2D u_texture;

in vec2 TexCoord;

out vec4 FragColor;

void main()
{
    FragColor = texture(u_texture, TexCoord);
}