#version 330 core

out vec4 FragColor;

uniform int _id;

vec3 EncodeIDToColor(int id) {
    float r = float((id >> 0) & 0xFF) / 255.0;
    float g = float((id >> 8) & 0xFF) / 255.0;
    float b = float((id >> 16) & 0xFF) / 255.0;
    return vec3(r, g, b);
}


void main()
{
    FragColor = vec4(EncodeIDToColor(_id), 1.0);
}
