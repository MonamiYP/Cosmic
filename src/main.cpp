#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "Player.hpp"
#include "DebugLine.hpp"
#include "SkyBox.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void window_focus_callback(GLFWwindow* window, int focused);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

Player player(glm::vec3(0.0f, 0.0f, 0.0f));
Camera camera(&player);

const float WINDOW_WIDTH = 1200.0f;
const float WINDOW_HEIGHT = 800.0f;

float lastX =  WINDOW_WIDTH / 2.0;
float lastY =  WINDOW_HEIGHT / 2.0;

float deltaTime;
float lastTime;

bool guiActive = false;

int main() {
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    GLFWwindow* window;
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Space Exploration", NULL, NULL);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowFocusCallback(window, window_focus_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    
    float vertices[] = {
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};

    VertexBuffer VBO(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.AddAttribute(3);
    VertexArray lightVAO;
    lightVAO.AddBuffer(VBO, layout);
    VertexArray skyboxVAO;
    skyboxVAO.AddBuffer(VBO, layout);

    SkyBox skybox;
    std::vector<std::string> faces { 
        "../res/assets/space_cubemap/right.png", 
        "../res/assets/space_cubemap/left.png", 
        "../res/assets/space_cubemap/top.png", 
        "../res/assets/space_cubemap/bottom.png", 
        "../res/assets/space_cubemap/front.png", 
        "../res/assets/space_cubemap/back.png" };
    unsigned int skyBoxTexture = skybox.loadSkyBox(faces);

    DebugLine x_line(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 0.0f, 0.0f));
    DebugLine y_line(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 10.0f, 0.0f));
    DebugLine z_line(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 10.0f));
    std::vector<float> x_line_vertex = x_line.GetVertices();
    std::vector<float> y_line_vertex = y_line.GetVertices();
    std::vector<float> z_line_vertex = z_line.GetVertices();
    VertexBuffer x_lineVBO(&x_line_vertex[0], sizeof(x_line_vertex));
    VertexBuffer y_lineVBO(&y_line_vertex[0], sizeof(y_line_vertex));
    VertexBuffer z_lineVBO(&z_line_vertex[0], sizeof(z_line_vertex));
    VertexArray x_lineVAO;
    VertexArray y_lineVAO;
    VertexArray z_lineVAO;
    x_lineVAO.AddBuffer(x_lineVBO, layout);
    y_lineVAO.AddBuffer(y_lineVBO, layout);
    z_lineVAO.AddBuffer(z_lineVBO, layout);

    Shader shader;
    std::string vertex_source = shader.ParseShader("../res/shaders/vertex_shader.vs");
    std::string fragment_source = shader.ParseShader("../res/shaders/fragment_shader.fs");
    shader.CreateShaderProgram(vertex_source, fragment_source);

    Shader lightShader;
    std::string light_fragment_source = shader.ParseShader("../res/shaders/light_shader.fs");
    lightShader.CreateShaderProgram(vertex_source, light_fragment_source);

    Shader lineShader;
    vertex_source = lineShader.ParseShader("../res/shaders/debug_line.vs");
    fragment_source = lineShader.ParseShader("../res/shaders/debug_line.fs");
    lineShader.CreateShaderProgram(vertex_source, fragment_source);

    Shader skyBoxShader;
    vertex_source = skyBoxShader.ParseShader("../res/shaders/skybox.vs");
    fragment_source = skyBoxShader.ParseShader("../res/shaders/skybox.fs");
    skyBoxShader.CreateShaderProgram(vertex_source, fragment_source);
    skyBoxShader.Bind();
    skyBoxShader.SetInt("skybox", 0);

    lightShader.Bind();
    lightShader.SetVector3("lightColor",  glm::vec3(1.0f, 0.6f, 0.6f));
    shader.Bind();
    shader.SetVector3("lightColor",  glm::vec3(1.0f, 0.6f, 0.6f));
    shader.SetVector3("lightPos", glm::vec3(1.0f, 0.0f, 0.0f));

    player.SetModelFromSource("../res/assets/spaceship/space_ship3.obj");

    Renderer renderer;

    while(!glfwWindowShouldClose(window)) {
        float currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        processInput(window);
        renderer.Clear();

        // Light
        lightVAO.Bind();
        lightShader.Bind();
        glm::mat4 view = camera.GetCameraView();
        glm::mat4 projection = glm::perspective(camera.GetFOV(), WINDOW_WIDTH/WINDOW_HEIGHT, 0.1f, 100.0f);
        lightShader.SetMatrix4("u_view", view);
        lightShader.SetMatrix4("u_projection", projection);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.2f)); 
        lightShader.SetMatrix4("u_model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Line
        lineShader.Bind();
        lineShader.SetMatrix4("u_view", view);
        lineShader.SetMatrix4("u_projection", projection);
        lineShader.SetMatrix4("u_model", x_line.GetModelMatrix());
        lineShader.SetVector3("color",  glm::vec3(1.0f, 0.0f, 0.0f));
        x_line.Render(x_lineVAO);
        lineShader.SetVector3("color",  glm::vec3(1.0f, 1.0f, 0.0f));
        y_line.Render(y_lineVAO);
        lineShader.SetVector3("color",  glm::vec3(0.0f, 1.0f, 1.0f));
        z_line.Render(z_lineVAO);
    
        // Spaceship
        shader.Bind();
        shader.SetMatrix4("u_view", view);
        shader.SetMatrix4("u_projection", projection);
        shader.SetMatrix4("u_model", player.GetModelMatrix());
        camera.UpdateVectors();
        shader.SetVector3("viewPos", camera.GetPosition()); 
        player.Render(shader);

        //SkyBox
        glDepthFunc(GL_LEQUAL);
        skyBoxShader.Bind();
        skyBoxShader.SetMatrix4("u_view", glm::mat4(glm::mat3(camera.GetCameraView())));
        skyBoxShader.SetMatrix4("u_projection", projection);

        skyboxVAO.Bind();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyBoxTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDepthFunc(GL_LESS);

        // ImGUI
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("A window");
        ImGui::Text("Application average %.2f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::Text("Forward direction: x:%.2f y:%.2f z:%.2f", player.GetForwardDir().x, player.GetForwardDir().y, player.GetForwardDir().z);
        ImGui::Text("Right direction: x:%.2f y:%.2f z:%.2f", player.GetRightDir().x, player.GetRightDir().y, player.GetRightDir().z);
        ImGui::Text("Up direction: x:%.2f y:%.2f z:%.2f", player.GetUpDir().x, player.GetUpDir().y, player.GetUpDir().z);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        player.ProcessKeyboardInput(FORWARDS, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        player.ProcessKeyboardInput(BACKWARDS, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        player.ProcessKeyboardInput(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        player.ProcessKeyboardInput(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        player.ProcessKeyboardInput(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        player.ProcessKeyboardInput(DOWN, deltaTime);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {
        if (!guiActive) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            glfwSetCursorPosCallback(window, 0);
        } else {
            glfwSetCursorPosCallback(window, mouse_callback);
        }
        guiActive = !guiActive;
    }
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos;
    lastX = xPos;
    lastY = yPos;

    player.ProcessMouseInput(xOffset, yOffset);
}

void window_focus_callback(GLFWwindow* window, int focused) {
    if (focused) {
        glfwSetCursorPos(window, lastX, lastY);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}  