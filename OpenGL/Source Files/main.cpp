#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include "VertexBuff.h"
#include "Rend.h"
#include "IndexBuff.h"
#include <Texture.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include "Camera.h"
#include "Light.h"
#include "InputManager.h"

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "ShadowMap.h"
#include "window.h"
#include <glm/gtx/string_cast.hpp>

#define WIDTH 940
#define HEIGHT 540


DirectionalLight dirLight(
    glm::vec3(0.5f, 0.5f, 0.5f),  // ambient 
    glm::vec3(1.0f, 1.0f, 1.0f),  // diffuse 
    glm::vec3(1.0f, 1.0f, 1.0f),  // specular
    glm::vec3(0.0, 0.0, 0.0)   // direction
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
    glm::vec3(0.5f, 0.5f, 0.5f),   // ambient
    glm::vec3(1.0f, 1.0f, 1.0f),   // diffuse
    glm::vec3(0.5f, 0.5f, 0.5f),   // specular
    glm::vec3(0.0f, 10.0f, 0.0f)    // position
    // constant, linear, quadratic use defaults: 1.0, 0.09, 0.032
);


Camera camera(glm::vec3(0.0f, 0.0f, -1.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    -90.0f,
    0.0f,
    45.0f,
    0.1, 2000.0f);

float lastTime = 0.0f;


void processCameraInputs(Camera& camera, float deltaTime) {
    InputManager& input = InputManager::getInstance();

    glm::vec3 direction(0.0f);

    if (input.isKeyPressed(GLFW_KEY_W)) direction += camera.GetCameraFront();   // Forward
    if (input.isKeyPressed(GLFW_KEY_S)) direction -= camera.GetCameraFront();   // Backward
    if (input.isKeyPressed(GLFW_KEY_A)) direction -= camera.GetCameraRight();   // Left
    if (input.isKeyPressed(GLFW_KEY_D)) direction += camera.GetCameraRight();   // Right

    camera.CalKeyboardMovement(direction, deltaTime);

    // Mouse rotation
    double mouseX, mouseY;
    input.getMousePosition(mouseX, mouseY);

    static double lastX = mouseX, lastY = mouseY;
    float xOffset = mouseX - lastX;
    float yOffset = lastY - mouseY;  // Inverted Y-axis

    lastX = mouseX;
    lastY = mouseY;

    camera.CalMouseRotation(xOffset, yOffset, true);
}






int main() {


    // variables
    Rend rend(camera);
    ShadowMap shadow;

    //opengl context
    glfwInit();
   
    ////window context
    WindowManager::WindowInit(WIDTH, HEIGHT);
    GLFWwindow* window = WindowManager::GetWindow(); 

    //Initializing Input Manager
    InputManager::getInstance().Initialize(window);

    // // Configure OpenGL state
    glEnable(GL_DEPTH_TEST);

    //Aspect Ratio
    camera.SetAspectRatio(window);

    //Disabling Cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

    // Vertices of a quad (rectangle)
    float planeVertices[] = {
        // Positions         
        -1.0f,  0.0f, -1.0f, 
         1.0f,  0.0f, -1.0f, 
         1.0f,  0.0f,  1.0f, 
        -1.0f,  0.0f,  1.0f
    };

    unsigned int planeIndices[] = {
        0, 1, 2,   
        0, 2, 3   
    };



    /////////////////////............................Buffers............................//////////////////////////

    // Create shaders
    Shader shader("resource files/shaders/default.vert", "resource files/shaders/default.frag");
    Shader depth("resource files/shaders/DirectionalShadowMap.vert", "resource files/shaders/DirectionalShadowMap.frag");
   


    //Cube
    shader.Bind();
    unsigned int vao;             // vertex array object
    glGenVertexArrays(1, &vao);   // generate for gen
    glBindVertexArray(vao);


    IndexBuff iv(indices, sizeof(indices));                           //  (6 column) * (36 row)
    VertexBuff vb(vertices,sizeof(vertices));   // 8 vertices, each with 6 floats (3 for position, 3 for color)


    //Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // Position
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);


    // Light cube
    Shader lightShader("resource files/shaders/light.vert", "resource files/shaders/light.frag");
    lightShader.Bind();

    unsigned int vao2;              // vertex array object
    glGenVertexArrays(1, &vao2);    //generate for gen
    glBindVertexArray(vao2);


    IndexBuff iv2(lightIndices, sizeof(lightVertices));                          
    VertexBuff vb2(lightVertices, sizeof(lightVertices));     

    //Position Attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);


    // Plane
    Shader planeShader("resource files/shaders/plane.vert", "resource files/shaders/plane.frag");
    planeShader.Bind();

    unsigned int vao3;                                     
    glGenVertexArrays(1, &vao3);                           
    glBindVertexArray(vao3);


    IndexBuff iv3(planeIndices, sizeof(planeIndices));
    VertexBuff vb3(planeVertices, sizeof(planeVertices));


    //Position Attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);


    // Axes
    Shader axis("resource files/shaders/axis.vert", "resource files/shaders/axis.frag");

    // Grid
    Shader gridShader("resource files/shaders/grid.vert", "resource files/shaders/grid.frag");
 
 
 
    // Configure matrices
    glm::mat4 lightProjection, lightView, lightSpaceMatrix;
    float nearPlane = 1.0f, farPlane = 7.5f;
    lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);



    // ImGUI
    ImGui::CreateContext();

    // Initialize ImGui for GLFW and OpenGL3
    ImGui_ImplGlfw_InitForOpenGL(window, true);  // This should be called only once
    ImGui_ImplOpenGL3_Init("#version 130"); // OpenGL 3.3 shader version

    // Set up ImGui style
    ImGui::StyleColorsDark();

    glfwSwapInterval(0);
    glDepthFunc(GL_LESS);         // Depth test function (default is GL_LESS)
    glEnable(GL_CULL_FACE);       // Optional: Enable backface culling
    //glCullFace(GL_BACK);          // Cull back faces
    //glFrontFace(GL_CCW);          // Counter-clockwise winding order}
    //glDepthFunc(GL_ALWAYS);  // Force the axes to always be drawn


    //Variables 
    glm::vec3 color(1.0f, 1.0f, 1.0f);
    glm::vec3 translateModel(0.0, 0.0, 0.0f);
    glm::vec3 rotateModel(0.252f, -0.36f, 0.1f);


    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 lightPosition = glm::vec3(0.0, 2.0, 0.0);
    glm::vec3 dirLightPosition(0.0f, 1.0f, 0.0f);

    glm::vec3 translateLight(0.1f, 0.1f, 2.5f);
    glm::vec3 rotateLight(0.0f, 0.0f, 1.0f);

    glm::vec3 transformPlane(0.0, 0.0, 8.0f);

    bool isChecked = false;
    float radian = 45.0f;

    float lastFrame = 0.0f;

    rend.Blend();



    // =Render
    while (!glfwWindowShouldClose(window)) {
      
        rend.Clear();
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        axis.Bind();
        //rend.RenderAxes(
        // , axis);


        // Draw a red line
        glColor3f(1.0f, 0.0f, 0.0f);  // Red color
        glBegin(GL_LINES);  // Start drawing a line
        glVertex3f(-0.5f, -0.5f, 0.0f);  // Start point
        glVertex3f(0.5f, 0.5f, 0.0f);    // End point
        glEnd();  // End drawing lines
        //1. Render depth map (shadow pass)
        depth.Bind();

        lightView = glm::lookAt(dirLightPosition, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        lightSpaceMatrix = lightProjection * lightView;
        depth.SetUniformMat4f("DirectionalShadowMap", lightSpaceMatrix);

        shadow.Write();
        glClear(GL_DEPTH_BUFFER_BIT);
 


        glEnable(GL_FRONT);
        rend.Clear();


        //GUI Start
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();



        //Second Pass
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, WIDTH, HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // Cube
        {
            glBindVertexArray(vao);
            rend.Draw(vb, iv, shader);

            
            //Model 
            rend.ModelTransform(translateModel);
            rend.ModelRotate(rotateModel, 0.0f);

            //All Matrix Transformation Applied
            shader.SetUniform3fv("color", color);

        }


        {
            //SetUniforms
           
            dirLight.SetLightUniform(shader, "dirLight");
            spotLight.SetLightUniform(shader, "spotLight");
            pointLight.SetLightUniform(shader, "pointLight");

            shader.Bind();
            shader.SetUniformMat4f("model", rend.GetModelMatrix());
            shader.SetUniformMat4f("projection", camera.GetProjectionMatrix());
            shader.SetUniformMat4f("view", camera.GetViewMatrix());
            shader.SetUniform3fv("viewPos", camera.GetCameraPosition());
        }
        
        /// Light Cube

        {
            lightShader.Bind();
            glBindVertexArray(vao2);
            rend.Draw(vb2, iv2, lightShader);
                
            rend.ModelTransform(lightPosition);
            rend.ModelScale();
            rend.ModelRotate(rotateLight, 0.0f);
            rend.UpdateMatrix(lightShader, "mvp", camera);
            lightShader.SetUniform3fv("lightColor", lightColor);

        }

        {
            planeShader.Bind();
            glBindVertexArray(vao3);
            rend.Draw(vb3, iv3, planeShader);

            rend.ModelTransform(transformPlane);
            rend.ModelRotate(glm::vec3(0.0f, 1.0f, 0.0f), radian);
            //rend.ModelScale();
            rend.UpdateMatrix(planeShader, "mvp2", camera);
            planeShader.SetUniform3fv("planeColor", glm::vec3(1.0f, 1.0f, 1.0f));
        }


        // Grid and Axis
        {       

            rend.DrawGrid(10.0f, 0.01f, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.235, 0.235, 0.235), gridShader, camera);
            rend.UpdateMatrix(gridShader, "u_mvp", camera);
            gridShader.Unbind();
        }

        shadow.Read(GL_TEXTURE0);
        shader.SetUniform1f("shadow", 0);
            
        //   // GUI: Create window and UI elements
        {

            ImGui::Begin("Dialog!");
            ImGuiIO& io = ImGui::GetIO();
            ImGui::Text("Translations");

            
            ImGui::SliderFloat("x", &transformPlane.x, -1.0f, 5.0f);
            ImGui::SliderFloat("y", &transformPlane.y, -1.0f, 5.0f);
            ImGui::SliderFloat("z", &transformPlane.z, -1.0f, 10.0f);
            ImGui::SliderFloat("r", &radian, -360.0f, 360.0f);
            ImGui::Dummy(ImVec2(0.0f, 20.0f));


            /*ImGui::SliderFloat("a", &rotateModel.x, -1.0f, 2.0f);
            ImGui::SliderFloat("b", &rotateModel.y, -1.0f, 1.0f);
            ImGui::SliderFloat("c", &rotateModel.z, -1.0f, 1.0f);*/
            ImGui::ColorPicker3("Color", &color[0]);
            
           /* ImGui::SliderFloat("inner", &spotLight.m_inner, 0.0f, 15.0f);
            ImGui::SliderFloat("outer", &spotLight.m_outer, 0.0f, 25.0f);*/

            ImGui::Dummy(ImVec2(0.0f, 20.0f));

            /*ImGui::SliderFloat("a1", &lightPosition.x, -10.0f, 10.0f);
            ImGui::SliderFloat("b2", &lightPosition.y, -10.0f, 10.0f);
            ImGui::SliderFloat("c2", &lightPosition.z, -10.0f, 10.0f);*/

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

            ImGui::Text("Frame Per Second (%.1f FPS)", rend.FpsCount());
            ImGui::End();

            
        }


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        //GUI END



        glfwSwapBuffers(window);
        glfwPollEvents();
        processCameraInputs(camera, deltaTime);
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

