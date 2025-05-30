#version 330 core

out vec4 FragColor;

void main() {
    float depth = gl_FragCoord.z;
    FragColor = vec4(vec3(depth), 1.0); // grayscale
}