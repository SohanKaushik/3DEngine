#version 330 core
in vec2 TexCoords;
out vec4 FragColor;

void main() {
    FragColor = vec4(1.0f, 0, 1.0f, 1.0f);  // Visualize the depth value in grayscale
}
