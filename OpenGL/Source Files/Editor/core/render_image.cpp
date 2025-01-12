#include "pch.h"

#include "render_image.h"
#include "shader/shader.h"
#include "Editor/EditorCamera.h"
#include "render/Texture.h"

void core::RenderImage::render()
{
    float quadVertices[] = {
        // Positions          // Normals          // Texture Coordinates
        -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
         0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f
    };

    unsigned int quadIndices[] = {
        0, 1, 2,   // First Triangle
        0, 2, 3    // Second Triangle
    };

    // Create VAO, VBO, and EBO for the quad
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture 
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Load the shader
    Shader image_shader;
    image_shader.load("Resource Files/Shaders/image_render.vert", "Resource Files/Shaders/image_render.frag");
    image_shader.use();

    Texture texture("Resource Files/Textures/chill_guy.png");
    glActiveTexture(GL_TEXTURE0);
    texture.bind();
    image_shader.SetUniform1i("u_texture", 0);

    // ...

    // Draw the quad
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear the screen
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
