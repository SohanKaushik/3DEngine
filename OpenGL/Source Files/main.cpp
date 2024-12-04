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
#include "Object.h"
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
    glm::vec3(0.0f, 0.0f, 0.0f),  // ambient 
    glm::vec3(1.0f, 1.0f, 1.0f),  // diffuse 
    glm::vec3(1.0f, 1.0f, 1.0f),  // specular
    glm::vec3(1.0, 3.0, 0.0)   // direction
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
    glm::vec3(0.3f, 0.3f, 0.3f),   // ambient
    glm::vec3(1.0f, 1.0f, 1.0f),   // diffuse
    glm::vec3(0.5f, 0.5f, 0.5f),   // specular
    glm::vec3(0.0f, 10.0f, 5.0f)    // position
    // constant, linear, quadratic use defaults: 1.0, 0.09, 0.032
);


Camera camera(glm::vec3(0.0f, 0.0f, -1.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    -90.0f,
    0.0f,
    45.0f,
    0.1, 2000.0f);


void renderObject(const Object& obj, Shader& shader) {
    glBindVertexArray(obj.VAO);
    shader.SetUniform3fv("color", obj.color); // Assuming Shader is your utility class for managing shaders
    shader.SetUniformMat4f("model", obj.m_model);
    glDrawElements(GL_TRIANGLES, obj.indexCount, GL_UNSIGNED_INT, 0);
}

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
   

    /////////////////////............................Buffers............................//////////////////////////

    // Create shaders
    Shader shader("resource files/shaders/default.vert", "resource files/shaders/default.frag");
    Shader lightShader("resource files/shaders/light.vert", "resource files/shaders/light.frag");
    Shader planeShader("resource files/shaders/plane.vert", "resource files/shaders/plane.frag");
    Shader depth("resource files/shaders/DirectionalShadowMap.vert", "resource files/shaders/DirectionalShadowMap.frag");
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
    //ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

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
    glm::vec3 lightPosition = glm::vec3(-5.0, 0.0, 0.0);
    glm::vec3 dirLightPosition(0.0f, 1.0f, 0.0f);

    glm::vec3 translateLight(0.1f, 0.1f, 2.5f);
    glm::vec3 rotateLight(0.0f, 0.0f, 1.0f);

    glm::vec3 transformPlane(0.0, 0.0, 8.0f);

    bool isChecked = false;
    float radian = 45.0f;

    float lastFrame = 0.0f;

    rend.Blend();
    bool isZero = true;

    // Create two cubes with different positions
    Object cube1(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Red cube at origin
    Object cube2(glm::vec3(2.0f, 5.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Green cube at x = 2
   
    // Setup camera


    glm::mat4 model1;

    // =Render
    while (!glfwWindowShouldClose(window)) {
      
        rend.Clear();
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
       

        //GUI Start
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //Second Pass
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, WIDTH, HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        // Calculate view and projection matrices
        camera.UpdateCameraMatrix(shader);

        // Update model matrix (e.g., apply rotation or translation here)
        cube1.SetModelPosition(glm::vec3(0.0f, 0.0f, 0.0f), shader);
        cube2.SetModelPosition(glm::vec3(0.0f, -1.0f, 0.0f), shader);
        cube2.SetModelScale(glm::vec3(5.0f, 0.2f, 5.0f));

        // Render your object
        renderObject(cube1, shader);
        renderObject(cube2, shader);

        dirLight.SetLightUniform(shader, "dirLight");
        spotLight.SetLightUniform(shader, "spotLight");
        pointLight.SetLightUniform(shader, "pointLight");
        shader.Unbind();


       
       
        // Grid and Axis
        gridShader.Bind();
        rend.DrawGrid(5.0f, 0.01f, glm::vec3(0.3, 0.3, 0.3), glm::vec3(0.235, 0.235, 0.235), gridShader, camera);
        rend.SetModelPosition(glm::vec3(0, 0, 0));
        rend.UpdateMatrix(gridShader, { "model", "projection", "view", "u_cameraPosition" }, camera);
        gridShader.Unbind();

        //GUI: Create window and UI elements
        {

            ImGui::Begin("Dialog!");
            ImGuiIO& io = ImGui::GetIO();
            ImGui::Text("Translations");


            /* ImGui::SliderFloat("x", &transformPlane.x, -1.0f, 5.0f);
             ImGui::SliderFloat("y", &transformPlane.y, -1.0f, 5.0f);
             ImGui::SliderFloat("z", &transformPlane.z, -1.0f, 10.0f);*/
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


        };


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        //GUI END



        glfwSwapBuffers(window);
        glfwPollEvents();
        processCameraInputs(camera, deltaTime);
    }

    shader.Unbind();
    lightShader.Unbind();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return NULL;
};

