#version 330 core

out vec4 FragColor;

uniform vec2 u_viewportSize;  // Screen resolution
uniform float u_spacing;      // Distance between grid lines
uniform float u_thickness;    // Thickness of grid lines
uniform vec3 u_color;         // Grid line color
uniform vec3 u_bgColor;       // Background color

void main() {

    vec2 uv = gl_FragCoord.xy / u_viewportSize;      // Normalized coordinates

    // Compute fractional position in the grid
    vec2 grid = fract(uv / u_spacing);
    grid = min(grid, 1.0 - grid); // Mirror around 0.5 for symmetry

    // Calculate grid line strength
    float line = max(grid.x, grid.y);
    line = smoothstep(0.0, u_thickness, line);

    // Mix grid and background colors
    vec3 color = mix(u_color, u_bgColor, line);

    FragColor = vec4(color, 1.0);
}
