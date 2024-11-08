#version 330 core
layout (location = 0) in vec3 aPos;       // Position of the vertex
layout (location = 1) in vec3 aColor;     // Color of the vertex
layout (location = 2) in vec2 aTexCoord;  // Texture coordinates of the vertex

out vec3 color;         // Passes the color to the fragment shader
out vec2 TexCoord;      // Passes the texture coordinate to the fragment shader

uniform float scale; 
uniform sampler2D text;



void main()
{
    // Apply the scale to the position
    gl_Position = vec4(aPos * scale, 1.0);
    
    // Pass the color to the fragment shader
    color = aColor;

    // Pass the texture coordinates to the fragment shader
    TexCoord = aTexCoord;
}
