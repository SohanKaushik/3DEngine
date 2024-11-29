#version 330 core

in vec3 FragPos;             // Position of the vertex in world space
in float distanceToGrid;     // Distance from the camera to the grid

uniform vec3 u_gridColor;    // Grid color

out vec4 FragColor;

void main()
{
    // Fade the grid lines based on the distance to the grid (this formula can be adjusted)
    // The further the distance, the more faded the grid lines become
    float fade = 1.0 / (1.0 + distanceToGrid * .005); 

   
    // Set the grid color with fading
    FragColor = vec4(u_gridColor, clamp(fade, 0.0, 1.0));  // Set alpha based on distance to grid
}
