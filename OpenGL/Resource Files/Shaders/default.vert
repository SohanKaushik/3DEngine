#version 330 core 

layout(location = 0) in vec3 aPos;         // VertexHolder position attribute
layout(location = 1) in vec3 aNormal;      // VertexHolder normal attribute
layout(location = 2) in vec2 aTexture;

// Uniforms                    
uniform vec3 planeColor;


uniform mat4 model;              // Model matrix
uniform mat4 view;               // View matrix
uniform mat4 projection;         // Projection matrix


out vec3 FragPos;    // Fragment position in world space
out vec3 Normal;   

out vec2 TexCoord;


void main()
{

    // Pass data to the fragment shader
    FragPos = vec3(model * vec4(aPos, 1.0));                          // Transform VertexHolder to world space
    Normal = mat3(transpose(inverse(model))) * aNormal;               // Transform normal to world space
    TexCoord = aTexture;

    gl_Position = projection * view * vec4(FragPos, 1.0);
}
 