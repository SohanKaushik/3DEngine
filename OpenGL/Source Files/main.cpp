#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;
#include "Shader.h"
#include "VertexBuff.h"
#include "Rend.h"
#include "IndexBuff.h"
#include <Texture.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include "Camera.h"


#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#define WIDHT 800.0f
#define HEIGHT 600.0f

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

    Rend rend;

    //opengl context
    glfwInit();



    //window context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(WIDHT, HEIGHT, "Window", NULL, NULL);
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



    // Define vertex
    float vertices[] = {

        // coordinates                               //colors                            // Text Co_ordinates
        -0.5f, -0.5f, 0.0f,                        1.0f, 0.0f, 0.0f,                    0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,                        0.0f, 1.0f, 0.0f,                    1.0f, 0.0f,
         0.5f,  0.5f, 0.0f,                        0.0f, 0.0f, 1.0f,                    1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f,                        1.0f, 1.0f, 0.0f,                    0.0f, 1.0f
    };
    
 
 float vertices2[] =
{
     // Positions          Color (RGB)
      -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,  // TLF (Red)
       0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,  // TRF (Green)
       0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,  // BRF (Blue)
      -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,  // BLF (Yellow)

      -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 1.0f,  // TLB (Cyan)
       0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 1.0f,  // TRB (Magenta)
       0.5f,  0.5f, -0.5f,   0.5f, 0.5f, 0.5f,  // BRB (Gray)
      -0.5f,  0.5f, -0.5f,   0.5f, 1.0f, 0.5f   // BLB (Lime)

};





    // Indices
    unsigned int indices[] = {
         1, 0, 2,  // First triangle
         2, 3, 0   // Second triangle
    };


    // 6 faces , 2 triangles per face, 12 triangles
    unsigned int indices2[] =
    {
        // Front face (TRF, TLF, BLF, BRF)
        0, 1, 2, 2, 3, 0,
        // Back face (TLB, TRB, BRB, BLB)
        4, 5, 6, 6, 7, 4,
        // Top face (TLF, TRF, TRB, TLB)
        0, 1, 5, 5, 4, 0,
        // Bottom face (BRF, BLF, BLB, BRB)
        2, 3, 7, 7, 6, 2,
        // Left face (TLF, BLF, BLB, TLB)
        0, 3, 7, 7, 4, 0,
        // Right face (TRF, BRF, BRB, TRB)
        1, 2, 6, 6, 5, 1
    };







    /////////////////////............................Buffers............................//////////////////////////

    // First Buffer
    unsigned int vao;             // vertex array object
    glGenVertexArrays(1, &vao);   //generate for gen
    glBindVertexArray(vao);


    IndexBuff iv(indices2, 36);                           //  (6 column) * (36 row)
    VertexBuff vb(vertices2, 8 * 6 * sizeof(float), 0);   // 8 vertices, each with 6 floats (3 for position, 3 for color)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr); // Position: first 3 floats


    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // Color: next 3 floats
    glEnableVertexAttribArray(1);



    // Shader setup
    Shader shader("shaders/default.vert", "shaders/default.frag"); 


    //Texture setup
    Texture texture("Textures/image.jpg");
    texture.Bind();
    shader.SetUniform1i("text", 0);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));


    // Blend
    rend.Blend();

    // Scale
    GLuint uniID = glGetUniformLocation(shader.ID, "scale");

    //Unbinding 
    iv.Unbind();
    vb.Unbind();
    shader.Unbind();



    // ImGUI
    ImGui::CreateContext();

    // Initialize ImGui for GLFW and OpenGL3
    ImGui_ImplGlfw_InitForOpenGL(window, true);  // This should be called only once
    ImGui_ImplOpenGL3_Init("#version 130"); // OpenGL 3.3 shader version

    // Set up ImGui style
    ImGui::StyleColorsDark();






    glm::vec3 translateModel(0.0f, 0.0f, -1.0f);
    glm::vec3 rotateModel(0.1f, 0.1f, 0.1f);

    glfwSwapInterval(0);
    glDisable(GL_CULL_FACE);  // Disable face culling to see both sides


    // =Render
    while (!glfwWindowShouldClose(window)) {


        //GUI Start
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        //Camera
        Camera camera(glm::vec3(0.0f,0.0f,0.0f), 45.0f, 0.1f, 1000.0f, window);                // [ position, fov , near , far , window ]

        //Model 
        rend.ModelTransform(translateModel);
        rend.ModelScale();
        rend.ModelRotate(rotateModel);


        //All Matrix Transformation Applied
        rend.UpdateMatrix(shader, "u_MVP", camera);

        // Clear the screen
        rend.Clear();


        // scale
        glUniform1f(uniID, 5.0f);

        // Activates the setup of buffers
        glBindVertexArray(vao);
        iv.Bind();

        // draws
        rend.Draw(vb, iv, shader);
        //glDrawArrays(GL_TRIANGLES, 3, 3); // Draw inner triangle




        //   // GUI: Create window and UI elements
        {

            ImGui::Begin("Dialog!");                       
            ImGuiIO& io = ImGui::GetIO();
            ImGui::Text("Translations");               
            ImGui::SliderFloat("x", &translateModel.x, -1.0f, 1.0f);     
            ImGui::SliderFloat("y", &translateModel.y, -1.0f, 1.0f);
            ImGui::SliderFloat("z", &translateModel.z, -1.0f, -0.44f);
            ImGui::Dummy(ImVec2(0.0f,20.0f));


            ImGui::SliderFloat("a", &rotateModel.x, -1.0f, 1.0f);
            
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 0 , rend.FpsCount());
            ImGui::End();
        }


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        //GUI END


        glfwSwapBuffers(window);
        glfwPollEvents();

    }


        // Clean up
        glDeleteVertexArrays(1, &vao);
        shader.Unbind();

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(window);
        glfwTerminate();
        return NULL;
}