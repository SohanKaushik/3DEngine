#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

#include "Shader.h"
#include "VertexBuff.h"
#include "Rend.h"
#include "IndexBuff.h"
#include <Texture.h>


// Notes
/*

1.  Initialize Opengl and window context
2.  Shader Program of Vertex and Fragment
3.  Define vertex data
4.  Generate and Bind VAO
5.  Generate and Bind VBO
6.  Set Vertex Attribute Pointers
7.  Generate & Bind EBO (If needed)
8.  Unbind VAO and VBO
9.  Render
10. Clean Up



*/
int main() {

    //opengl context
    glfwInit();

    //window context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Bindow", NULL, NULL);
    if (window == NULL) {
        cerr << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Load OpenGL functions using glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cerr << "Failed to initialize GLAD" << endl;
        return -1;
    }


    // Shader initialization





    // Define vertex
    float vertices[] = {

        // coordinates                               //colors                            // Text Co_ordinates
        -0.5f, -0.5f, 0.0f,                        1.0f, 0.0f, 0.0f,                    0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,                        0.0f, 1.0f, 0.0f,                    1.0f, 0.0f,
         0.5f,  0.5f, 0.0f,                        0.0f, 0.0f, 1.0f,                    1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f,                        1.0f, 1.0f, 0.0f,                    0.0f, 1.0f
    };



    // Indices
    unsigned int indices[] = {
         1, 0, 2,  // First triangle
         2, 3, 0   // Second triangle
    };


    // Buffers
    unsigned int vao;
    glGenVertexArrays(1, &vao);   //generate for gen
    glBindVertexArray(vao);


    IndexBuff iv(indices, 6);                  //count = 6 and size = 4 (row and column)
    VertexBuff vb(vertices, 4 * 6 * 2  * sizeof(float));      // Vertex Buffer
    glEnableVertexAttribArray(0);                        /// enable
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);  
 

  

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);       //just comment when wanst without colors


    // Shader setup
    Shader shader("shaders/default.vert", "shaders/default.frag");


    //Texture setup
    Texture texture("Textures/image.jpg");
    texture.Bind();
    shader.SetUniform1i("text", 0);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));



    // Scale
    GLuint uniID = glGetUniformLocation(shader.ID, "scale");




    // =Render
    Rend rend;
    while (!glfwWindowShouldClose(window)) {

        // Clear the screen
        rend.Clear();

        // scale
        glUniform1f(uniID, 0.5f);

        // Activates the setup of buffers
        glBindVertexArray(vao);
        iv.Bind();

        // draws
        rend.Draw(vb, iv, shader);
        //glDrawArrays(GL_TRIANGLES, 3, 3); // Draw inner triangle
                 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glDeleteVertexArrays(1, &vao);
    shader.Unbind();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}