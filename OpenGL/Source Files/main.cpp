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
#include "Light.h"

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#define WIDHT 800
#define HEIGHT 600




// Set up and configure your directional light
DirectionalLight dirLight(
    glm::vec3(0.1f, 0.1f, 0.1f),   // ambient
    glm::vec3(0.8f, 0.8f, 0.8f),   // diffuse
    glm::vec3(1.0f, 1.0f, 1.0f),   // specular
    glm::vec3(-1.0f, -1.0f, -1.0f) // direction

);


int main() {


    // variables
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


    float vertices2[] = {
        // Positions                    // Normals
        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,  1.0f,  // Front face
         0.5f, -0.5f,  0.5f,    0.0f, 0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,    0.0f, 0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,    0.0f, 0.0f,  1.0f,

        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, -1.0f,  // Back face
         0.5f, -0.5f, -0.5f,    0.0f, 0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,    0.0f, 0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,    0.0f, 0.0f, -1.0f,
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
    VertexBuff vb(vertices2, 8 * 6 * sizeof(float));   // 8 vertices, each with 6 floats (3 for position, 3 for color)

    //Position Attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);



    //Normal Attribute 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // Shader setup
    Shader shader("shaders/default.vert", "shaders/default.frag"); 
    shader.Bind();

    // Blend
    rend.Blend();

  
    //Light
    // 
    // 
    // Assuming DirectionalLight is a class with a proper constructor
    // Calculate lighting color on the CPU side


    // ImGUI
    ImGui::CreateContext();

    // Initialize ImGui for GLFW and OpenGL3
    ImGui_ImplGlfw_InitForOpenGL(window, true);  // This should be called only once
    ImGui_ImplOpenGL3_Init("#version 130"); // OpenGL 3.3 shader version

    // Set up ImGui style
    ImGui::StyleColorsDark();

    glfwSwapInterval(0);
    glDisable(GL_CULL_FACE);  // Disable face culling to see both sides



    //Variables 
    glm::vec3 color(1.0f, 0.0f, 0.0f);
    glm::vec3 translateModel(0.0f, 0.0f, 2.5f);
    glm::vec3 rotateModel(0.1f, 0.1f, 0.1f);

    //Camera
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), 45.0f, 0.1f, 1000.0f, window);   // [ position, fov , near , far , window ]


    // =Render
    while (!glfwWindowShouldClose(window)) {


        //GUI Start
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        //Model 
        rend.ModelTransform(translateModel);
        rend.ModelScale();
        rend.ModelRotate(rotateModel);


        //All Matrix Transformation Applied
        rend.UpdateMatrix(shader, "u_MVP", camera);

        // Clear the screen
        rend.Clear();

        ////cube color
        shader.SetUniform3fv("color", color);


        // Activates the setup of buffers
        glBindVertexArray(vao);
        iv.Bind();


        dirLight.SetLightUniform(shader, "dirLight");
        // **Calculate light color and set uniform for lighting**
        
        /*
        glm::vec3 normal = glm::vec3(0.0f, 0.0f, 1.0f); 
        glm::vec3 viewDir = glm::normalize(camera.GetCameraPosition() - translateModel);  // Direction to the camera

        // Calculate the lighting color using the DirectionalLight instance
        glm::vec3 lightColor = dirLight.CalculateLight(normal, viewDir);
        glm::vec3 lightDir = camera.GetCameraFront();

        shader.SetUniform3fv("lightColorr", lightColor); // Pass to shader
        shader.SetUniform3fv("lightDir", lightDir);
        */

        shader.SetUniformMat4f("model", rend.GetModelMatrix());
        shader.SetUniformMat4f("projection", camera.GetProjectionMatrix());
        shader.SetUniformMat4f("view", camera.GetViewMatrix());

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
            ImGui::SliderFloat("z", &translateModel.z,  1.0f, 2.8f);

            ImGui::Dummy(ImVec2(0.0f,20.0f));


            ImGui::SliderFloat("a", &rotateModel.x, -1.0f, 1.0f);
            ImGui::SliderFloat("b", &rotateModel.y, -1.0f, 1.0f);
            ImGui::ColorPicker3("Color", &color[0]);

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
