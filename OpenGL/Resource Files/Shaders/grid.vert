#version 330 core

// Inputs
layout(location = 0) in vec3 aPos; // Object-space VertexHolder position
layout(location = 1) in vec3 aColor;  // VertexHolder color


// Uniforms
uniform mat4 model;            // Model matrix
uniform mat4 view;               // View matrix
uniform mat4 projection;         // Projection matrix



// Outputs
out vec3 FragPos;        // Pass world-space position to the fragment shader
out vec3 fragClr;


void main() {

    // Compute world-space position
    vec4 worldPosition = model * vec4(aPos, 1.0);
    FragPos = worldPosition.xyz; 

    fragClr = aColor;
    // Compute clip-space position
    gl_Position = projection * view * model * vec4(aPos, 1.0); 
}