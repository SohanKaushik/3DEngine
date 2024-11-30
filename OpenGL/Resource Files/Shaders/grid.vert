#version 330 core

// Inputs
layout(location = 0) in vec3 aPos; // Object-space vertex position
layout(location = 1) in vec3 aColor;  // Vertex color


// Uniforms
uniform mat4 u_model;    // Model matrix
uniform mat4 u_mvp;      // Model-View-Projection matrix

// Outputs
out vec3 FragPos;        // Pass world-space position to the fragment shader
out vec3 fragClr;


void main() {
    // Compute world-space position
    vec4 worldPosition = u_model * vec4(aPos, 1.0);
    FragPos = worldPosition.xyz; 

    fragClr = aColor;
    // Compute clip-space position
    gl_Position = u_mvp * vec4(aPos, 1.0); 
}
