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


DirectionalLight dirLight(
    glm::vec3(0.2f, 0.2f, 0.2f),  // ambient 
    glm::vec3(1.0f, 1.0f, 1.0f),  // diffuse 
    glm::vec3(1.0f, 1.0f, 1.0f),  // specular
    glm::vec3(0.0f, 1.0f, 0.0f)   // direction
);

SpotLight spotLight(
    glm::vec3(0.2f, 0.2f, 0.2f),  // ambient 
    glm::vec3(1.0f, 1.0f, 1.0f),  // diffuse 
    glm::vec3(1.0f, 1.0f, 1.0f),  // specular
    glm::vec3(0.0f, 5.0f, 0.0f),  // direction
    glm::vec3(0.0f, 5.0f, 0.0f),  // position
    1.0f,                         // inner
    2.0f                          // outer
);

PointLight pointLight(
    glm::vec3(0.2f, 0.2f, 0.2f),   // ambient
    glm::vec3(1.0f, 1.0f, 1.0f),   // diffuse
    glm::vec3(1.0f, 1.0f, 1.0f),   // specular
    glm::vec3(0.0f, 0.0f, 0.0f)    // position
    // constant, linear, quadratic use defaults: 1.0, 0.09, 0.032
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
    glfwWindowHint(GLFW_DEPTH_BITS, 24);

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

    GLfloat vertices[] = {
        // Positions          // Normals
        -1.0f, -1.0f,  1.0f,             0.0f,  0.0f, -1.0f, // Front face
         1.0f, -1.0f,  1.0f,             0.0f,  0.0f, -1.0f, // Front face
         1.0f,  1.0f,  1.0f,             0.0f,  0.0f, -1.0f, // Front face
        -1.0f,  1.0f,  1.0f,             0.0f,  0.0f, -1.0f, // Front face

        -1.0f, -1.0f, -1.0f,             0.0f,  0.0f,  1.0f, // Back face
        -1.0f,  1.0f, -1.0f,             0.0f,  0.0f,  1.0f, // Back face
         1.0f,  1.0f, -1.0f,             0.0f,  0.0f,  1.0f, // Back face
         1.0f, -1.0f, -1.0f,             0.0f,  0.0f,  1.0f, // Back face

         1.0f, -1.0f, -1.0f,            -1.0f,  0.0f,  0.0f, // Left face
         1.0f,  1.0f, -1.0f,            -1.0f,  0.0f,  0.0f, // Left face
         1.0f,  1.0f,  1.0f,            -1.0f,  0.0f,  0.0f, // Left face
         1.0f, -1.0f,  1.0f,            -1.0f,  0.0f,  0.0f, // Left face

        -1.0f, -1.0f, -1.0f,             1.0f,  0.0f,  0.0f, // Right face
        -1.0f, -1.0f,  1.0f,             1.0f,  0.0f,  0.0f, // Right face
        -1.0f,  1.0f,  1.0f,             1.0f,  0.0f,  0.0f, // Right face
        -1.0f,  1.0f, -1.0f,             1.0f,  0.0f,  0.0f, // Right face

        -1.0f,  1.0f,  1.0f,             0.0f, -1.0f,  0.0f, // Top face
         1.0f,  1.0f,  1.0f,             0.0f, -1.0f,  0.0f, // Top face
         1.0f,  1.0f, -1.0f,             0.0f, -1.0f,  0.0f, // Top face
        -1.0f,  1.0f, -1.0f,             0.0f, -1.0f,  0.0f, // Top face

        -1.0f, -1.0f,  1.0f,             0.0f,  1.0f,  0.0f, // Bottom face
        -1.0f, -1.0f, -1.0f,             0.0f,  1.0f,  0.0f, // Bottom face
         1.0f, -1.0f, -1.0f,             0.0f,  1.0f,  0.0f, // Bottom face
         1.0f, -1.0f,  1.0f,             0.0f,  1.0f,  0.0f  // Bottom face
    };


  

    GLuint indices[] = {
      0, 1, 2,
      2, 3, 0,       // Front face
      4, 5, 6,
      6, 7, 4,       // Back face
      8, 9, 10,
      10, 11, 8,
      12, 13, 14,
      14, 15, 12,
      16, 17, 18,
      18, 19, 16, 
      20, 21, 22,
      22, 23, 20  // Bottom face
    };


    float lightVertices[] =
    { //     COORDINATES     //
       -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
       -0.5f,  0.5f,  0.5f,
       -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
       -0.5f,  0.5f, -0.5f
    };

    unsigned int lightIndices[] =
    {

        0, 1, 2, 2, 3, 0,

        4, 5, 6, 6, 7, 4,

        0, 1, 5, 5, 4, 0,

        2, 3, 7, 7, 6, 2,

        0, 3, 7, 7, 4, 0,

        1, 2, 6, 6, 5, 1
    };



    /////////////////////............................Buffers............................//////////////////////////

    // Shader setup
    Shader shader("resource files/shaders/default.vert", "resource files/shaders/default.frag");
    shader.Bind();


    // First Buffer
    unsigned int vao;             // vertex array object
    glGenVertexArrays(1, &vao);   //generate for gen
    glBindVertexArray(vao);


    IndexBuff iv(indices, sizeof(indices));                           //  (6 column) * (36 row)
    VertexBuff vb(vertices,sizeof(vertices));   // 8 vertices, each with 6 floats (3 for position, 3 for color)

    std::cout << "size :" << sizeof(indices) << sizeof(vertices) <<  std::endl;
    //Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // Position
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    iv.Unbind(); 
    vb.Unbind(); 
    glBindVertexArray(0);


    // // Light cube
    Shader lightShader("resource files/shaders/light.vert", "resource files/shaders/light.frag");
    lightShader.Bind();

    unsigned int vao2;             // vertex array object
    glGenVertexArrays(1, &vao2);   //generate for gen
    glBindVertexArray(vao2);


    IndexBuff iv2(lightIndices, sizeof(lightVertices));                          
    VertexBuff vb2(lightVertices, sizeof(lightVertices));     

    //Position Attribute
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);


    iv2.Unbind();
    vb2.Unbind();
    lightShader.Unbind();



    // ImGUI
    ImGui::CreateContext();

    // Initialize ImGui for GLFW and OpenGL3
    ImGui_ImplGlfw_InitForOpenGL(window, true);  // This should be called only once
    ImGui_ImplOpenGL3_Init("#version 130"); // OpenGL 3.3 shader version

    // Set up ImGui style
    ImGui::StyleColorsDark();

    glfwSwapInterval(0);
    
    
    glEnable(GL_DEPTH_TEST);       // Enable depth testing
    glDepthFunc(GL_LESS);         // Depth test function (default is GL_LESS)
    glEnable(GL_CULL_FACE);       // Optional: Enable backface culling
    glCullFace(GL_BACK);          // Cull back faces
    glFrontFace(GL_CCW);          // Counter-clockwise winding order}


    //Variables 
    glm::vec3 color(1.0f, 1.0f, 1.0f);
    glm::vec3 translateModel(0.0, 0.0, 0.0f);
    glm::vec3 rotateModel(0.252f, -0.36f, 0.1f);


    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 lightPosition = glm::vec3(-1.002, 1.338f, 1.388);
    glm::vec3 dirLightPosition(0.0f, 1.0f, 0.0f);

    glm::vec3 translateLight(0.1f, 0.1f, 2.5f);
    glm::vec3 rotateLight(0.0f, 0.0f, 1.0f);


    bool isChecked = false;

    //Camera
    Camera camera(glm::vec3(0.0f, 0.0f, 5.0f), 45.0f, 0.1f,  100.0f, window);   // [ position, fov , near , far , window ]


    // =Render
    while (!glfwWindowShouldClose(window)) {


        glEnable(GL_FRONT);
        // Clear the screen
        rend.Clear();


        //glfwSetWindowTitle(window, std::to_string(rend.FpsCount()).c_str());
        //GUI Start
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Cube
        {
            glBindVertexArray(vao);
            rend.Draw(vb, iv, shader);

            shader.Bind();
            //Model 
            rend.ModelTransform(translateModel);
            rend.ModelRotate(rotateModel);

            //All Matrix Transformation Applied
            rend.UpdateMatrix(shader, "u_MVP", camera);
            shader.SetUniform3fv("color", color);
            

            //SetUniforms
            dirLight.SetLightUniform(shader, "dirLight");
            spotLight.SetLightUniform(shader, "spotLight");
            pointLight.SetLightUniform(shader, "pointLight");

            shader.SetUniformMat4f("model", rend.GetModelMatrix());
            shader.SetUniformMat4f("projection", camera.GetProjectionMatrix());
            shader.SetUniformMat4f("view", camera.GetViewMatrix());
            shader.SetUniform3fv("viewPos", rend.GetModelPosition());

        }

        
        /// Light Cube

        {
            lightShader.Bind();
            glBindVertexArray(vao2);
            rend.Draw(vb2, iv2, lightShader);
                
            rend.ModelTransform(lightPosition);
            rend.ModelScale();
            rend.ModelRotate(rotateLight);
            rend.UpdateMatrix(lightShader, "mvp", camera);
            lightShader.SetUniform3fv("lightColor", lightColor);

        }

            
        //   // GUI: Create window and UI elements
        {

            ImGui::Begin("Dialog!");
            ImGuiIO& io = ImGui::GetIO();
            ImGui::Text("Translations");

            
            /*ImGui::SliderFloat("x", &translateModel.x, -1.0f, 5.0f);
            ImGui::SliderFloat("y", &translateModel.y, -1.0f, 5.0f);
            ImGui::SliderFloat("z", &translateModel.z, -1.0f, 5.0f);*/

            ImGui::Dummy(ImVec2(0.0f, 20.0f));


            /*ImGui::SliderFloat("a", &rotateModel.x, -1.0f, 2.0f);
            ImGui::SliderFloat("b", &rotateModel.y, -1.0f, 1.0f);
            ImGui::SliderFloat("c", &rotateModel.z, -1.0f, 1.0f);*/
            ImGui::ColorPicker3("Color", &color[0]);
            
            ImGui::SliderFloat("inner", &spotLight.m_inner, 0.0f, 15.0f);
            ImGui::SliderFloat("outer", &spotLight.m_outer, 0.0f, 25.0f);

            ImGui::Dummy(ImVec2(0.0f, 20.0f));

            ImGui::SliderFloat("a1", &lightPosition.x, -10.0f, 10.0f);
            ImGui::SliderFloat("b2", &lightPosition.y, -10.0f, 10.0f);
            ImGui::SliderFloat("c2", &lightPosition.z, -10.0f, 10.0f);

            pointLight.m_position = lightPosition;


            /*ImGui::SliderFloat("x1", &dirLight.m_direction.x, -10.0f, 10.0f);
            ImGui::SliderFloat("y2", &dirLight.m_direction.y, -10.0f, 10.0f);
            ImGui::SliderFloat("z2", &dirLight.m_direction.z, -10.0f, 10.0f);*/


            if (ImGui::Checkbox("Wireframe", &isChecked)) {

                if (isChecked) { 
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                }
                else {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
                }
            }
            
            if (spotLight.m_inner > spotLight.m_outer) {

                spotLight.m_outer = spotLight.m_inner + 0.01;
            }

            ImGui::Dummy(ImVec2(0.0f, 20.0f));


            /*
            ImGui::SliderFloat("x", &translateLight.x, -1.0f, 1.0f);
            ImGui::SliderFloat("y", &translateLight.y, -1.0f, 1.0f);
            ImGui::SliderFloat("z", &translateLight.z, 1.0f, 2.8f);

            ImGui::Dummy(ImVec2(0.0f, 20.0f));
            */

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 0, rend.FpsCount());
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
    glDeleteVertexArrays(1, &vao2);

    shader.Unbind();
    lightShader.Unbind();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return NULL;
}

