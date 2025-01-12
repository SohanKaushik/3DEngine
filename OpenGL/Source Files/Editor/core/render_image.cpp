#include "pch.h"

#include "render_image.h"
#include "shader/shader.h"
#include "Editor/EditorCamera.h"

void core::RenderImage::render()
{
    float quadVertices[] = {
        // Positions          // Normals
        -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  // Top-left
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  // Bottom-left
         0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  // Bottom-right
         0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f   // Top-right
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // Normal
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Load the shader
    Shader image_shader;
    image_shader.load("Resource Files/Shaders/default.vert", "Resource Files/Shaders/default.frag");


    // Editor Camera for now
    Editor::Camera mCamera(
        glm::vec3(5.35f, -4.92f, 2.95f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        -90.0f, 0.0f, 45.0f, 0.1, 1000.0f
    );

    // Active Camera
    image_shader.use();
    mCamera.UpdateCameraMatrix(image_shader);

    mEntityHandler->RenderEntities(image_shader); 

    // Draw the quad
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear the screen
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
