#version 330 core

layout (location = 0) in vec3 aPos; // Vertex position

// Uniforms
uniform mat4 u_mvp;         // Model-view-projection matrix
uniform vec3 u_cameraPos;   // Camera position

// Outputs to fragment shader
out vec3 FragPos;           // Position of the vertex in world space
out float distanceToGrid;   // Distance from the camera to the grid (to apply fading)

void main()
{
    // Transform the vertex position to clip space
    gl_Position = u_mvp * vec4(aPos, 1.0);

    // Pass the world position to the fragment shader
    FragPos = aPos;

    // Calculate the distance from the camera to the current vertex (this is in world space)
    distanceToGrid = length(u_cameraPos - aPos);
}
