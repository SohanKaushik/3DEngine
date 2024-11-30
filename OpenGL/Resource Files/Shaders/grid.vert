#version 330 core

// Inputs
layout(location = 0) in vec3 aPos; // Object-space vertex position

// Uniforms
uniform mat4 u_model;    // Model matrix
uniform mat4 u_mvp;      // Model-View-Projection matrix

// Outputs
out vec3 FragPos;        // Pass world-space position to the fragment shader

void main() {
    // Compute world-space position
    vec4 worldPosition = u_model * vec4(aPos, 1.0); // Use aPos here
    FragPos = worldPosition.xyz; // Pass world position to the fragment shader

    // Compute clip-space position
    gl_Position = u_mvp * vec4(aPos, 1.0); // Use aPos here as well
}
