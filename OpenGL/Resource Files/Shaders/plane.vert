#version 330 core

layout (location = 0) in vec3 aPos;       // VertexHolder position
layout (location = 1) in vec2 aTexCoords; // Texture coordinates (optional)

uniform mat4 model;       // Model transformation matrix
uniform mat4 view;        // View transformation matrix
uniform mat4 projection;  // Projection transformation matrix

out vec2 TexCoords;       // Pass to fragment shader

void main() {

    TexCoords = aTexCoords;                                   
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
