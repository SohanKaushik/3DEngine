#version 330 core 

layout(location = 0) in vec3 aPos;         // Vertex position attribute
layout(location = 1) in vec3 aNormal;      // Vertex normal attribute
layout(location = 2) in vec2 aTexture;

// Uniforms                    
uniform vec3 color;              // Color passed as a uniform
uniform vec3 planeColor;


uniform mat4 model;              // Model matrix
uniform mat4 view;               // View matrix
uniform mat4 projection;         // Projection matrix


// Outputs to the fragment shader
out vec3 FragPos;    // Fragment position in world space
out vec3 Normal;     // Normal vector in world space
out vec3 aColor;     // Output color for the fragment shader

// Shadows
uniform mat4 DirLightSpaceMatrix;
out vec4 FragPosDirLightSpace; 



void main()
{


    //FragPosDirLightSpace = DirLightSpaceMatrix * model * vec4(aPos, 1.0f);


    // Pass data to the fragment shader
    FragPos = vec3(model * vec4(aPos, 1.0));  // Transform vertex to world space
    Normal = mat3(transpose(inverse(model))) * aNormal;  // Transform normal to world space
    aColor = color;  

   // gl_Position = projection * view * model * vec4(aPos, 1.0);
      gl_Position = vec4(aPos * 0.5, 1.0);
}
 