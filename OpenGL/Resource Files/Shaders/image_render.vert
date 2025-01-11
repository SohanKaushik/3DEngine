#version 330 core
layout (location = 0) in vec3 aPos;     
layout (location = 1) in vec3 aNormal;  

uniform mat4 model;            
uniform mat4 view;             
uniform mat4 projection;       
uniform vec3 color;            



out vec3 aColor;   
out vec3 FragColor;         

void main()
{
    // Pass the color to the fragment shader
    aColor = color;

    // Transform the vertex position to world space and apply the camera transforms
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
