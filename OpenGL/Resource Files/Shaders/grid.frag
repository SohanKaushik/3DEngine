#version 330 core

// Uniforms
uniform vec3 u_cameraPosition; // Camera's world-space position

// Inputs
in vec3 FragPos;               // World-space position from the vertex shader
in vec3 fragClr;


// Outputs
out vec4 fragColor;            // Final color output

// Hardcoded fade distances
const float dMin = 10.0;       // Fade start distance
const float dMax = 300.0;       // Fade end distance

void main() {
    // Calculate distance from fragment to camera
    float distance = length(FragPos - u_cameraPosition);

    // Compute opacity using linear fade
    float opacity = clamp((dMax - distance) / (dMax - dMin), 0.0, 1.0);

    // Set final color with fade applied 
    vec4 baseColor = vec4(0.32, 0.32, 0.32, 1.0); // Replace with your actual base color
    fragColor = vec4(fragClr, baseColor.a * opacity);
};
