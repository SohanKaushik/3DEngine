#version 330 core
out vec4 FragColor;

in vec3 color;      // Color from the vertex shader
in vec2 TexCoord;   // Texture coordinates from the vertex shader

uniform sampler2D text;

void main()
{
    // Sample the texture using the coordinates
    vec4 texColor = texture(text, TexCoord);
    
    // Combine the sampled texture color with the vertex color
    //FragColor = texColor * vec4(color, 1.0);      // texture + color blend
    FragColor = texColor;
}
