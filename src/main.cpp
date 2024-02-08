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

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xScroll, double yScroll);
void window_focus_callback(GLFWwindow* window, int focused);

Camera camera(glm::vec3(0.0f, 0.0f, 8.0f));

const float WINDOW_WIDTH = 1200.0f;
const float WINDOW_HEIGHT = 800.0f;

float lastX =  WINDOW_WIDTH / 2.0;
float lastY =  WINDOW_HEIGHT / 2.0;

float deltaTime;
float lastTime;

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
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
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
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f
};

    VertexBuffer VBO(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.AddAttribute(3);
    VertexArray lightVAO;
    lightVAO.AddBuffer(VBO, layout);

    Shader shader;
    std::string vertex_source = shader.ParseShader("../res/shaders/vertex_shader.vs");
    std::string fragment_source = shader.ParseShader("../res/shaders/fragment_shader.fs");
    shader.CreateShaderProgram(vertex_source, fragment_source);

    Shader lightShader;
    std::string light_fragment_source = shader.ParseShader("../res/shaders/light_shader.fs");
    lightShader.CreateShaderProgram(vertex_source, light_fragment_source);

    lightShader.Bind();
    lightShader.SetVector3("lightColor",  glm::vec3(1.0f, 0.6f, 0.6f));
    shader.Bind();
    shader.SetVector3("lightColor",  glm::vec3(1.0f, 0.6f, 0.6f));
    shader.SetVector3("lightPos", glm::vec3(1.0f, 0.0f, 0.0f));

    Texture texture("../res/assets/container.jpg");
    texture.Bind();

    Player player;
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

        // Spaceship
        shader.Bind();
        shader.SetMatrix4("u_view", view);
        shader.SetMatrix4("u_projection", projection);
        model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        shader.SetMatrix4("u_model", model);
        shader.SetVector3("viewPos", camera.GetPosition()); 
        player.Render(shader);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("A window");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
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
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboardInput(FORWARDS, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboardInput(BACKWARDS, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboardInput(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboardInput(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.ProcessKeyboardInput(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.ProcessKeyboardInput(DOWN, deltaTime);
}

void scroll_callback(GLFWwindow* window, double xScroll, double yScroll) {
    camera.ProcessScrollInput(yScroll);
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos;
    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseInput(xOffset, yOffset);
}

void window_focus_callback(GLFWwindow* window, int focused) {
    if (focused) {
        glfwSetCursorPos(window, lastX, lastY);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}  