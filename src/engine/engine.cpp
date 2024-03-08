#include "Engine.hpp"
#include "Scenes/TestScene.hpp"

Engine* Engine::GetInstance = nullptr;

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // if(!guiActive) {
    //     if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    //         player.ProcessKeyboardInput(FORWARDS, deltaTime);
    //     if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    //         player.ProcessKeyboardInput(BACKWARDS, deltaTime);
    //     if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    //         player.ProcessKeyboardInput(LEFT, deltaTime);
    //     if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    //         player.ProcessKeyboardInput(RIGHT, deltaTime);
    //     if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    //         player.ProcessKeyboardInput(UP, deltaTime);
    //     if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    //         player.ProcessKeyboardInput(DOWN, deltaTime);
    // }
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
    float xOffset = xPos - Engine::GetInstance->config.lastX;
    float yOffset = Engine::GetInstance->config.lastY - yPos;
    Engine::GetInstance->Engine::GetInstance->config.lastX = xPos;
    Engine::GetInstance->Engine::GetInstance->config.lastY = yPos;

    // player.ProcessMouseInput(xOffset, yOffset);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {
        if (!Engine::GetInstance->config.guiActive) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            glfwSetCursorPosCallback(window, 0);
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetCursorPos(window, Engine::GetInstance->config.lastX, Engine::GetInstance->config.lastY);
            glfwSetCursorPosCallback(window, mouse_callback);
        }
        Engine::GetInstance->config.guiActive = !Engine::GetInstance->config.guiActive;
    }
}

void window_focus_callback(GLFWwindow* window, int focused) {
    if (focused) {
        glfwSetCursorPos(window, Engine::GetInstance->config.lastX, Engine::GetInstance->config.lastY);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}  

Engine::Engine(EngineConfig config) : m_config(config) {
    if (Engine::GetInstance != nullptr) {
        std::cout << "Engine already initialised" << std::endl;
        return;
    }

    Engine:GetInstance = this;
}

bool Engine::Init() {
    if (!glfwInit())
        return false;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    m_window = glfwCreateWindow(m_config.WINDOW_WIDTH, m_config.WINDOW_HEIGHT, "Space Exploration", NULL, NULL);
    if (!m_window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
    glfwSetCursorPosCallback(m_window, 0);
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    glfwSetKeyCallback(m_window, key_callback);
    glfwSetWindowFocusCallback(m_window, window_focus_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    ImguiInit();

    glPatchParameteri(GL_PATCH_VERTICES, 4);

    return true;
}

void Engine::Run() {
    TestScene scene;
    Engine::GetInstance->SetActiveScene(&scene);

    while(!glfwWindowShouldClose(m_window)) {
        float currentTime = glfwGetTime();
        m_config.deltaTime = currentTime - m_config.lastTime;
        m_config.lastTime = currentTime;

        processInput(m_window);
        
        m_scene->Update(m_config.deltaTime);
        ImguiUpdate();

        m_scene->Render();
        ImguiRender();

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

void Engine::SetActiveScene(IScene* scene) {
    m_scene = scene;
}

void Engine::Destroy() {
    ImguiDestroy();
    glfwTerminate();
}

glm::vec2 Engine::GetWindowSize() {
    int width, height;
    glfwGetWindowSize(m_window, &width, &height);
    return glm::vec2(width, height);
}

void Engine::ImguiInit() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void Engine::ImguiUpdate() {
    ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("A window");
        // ImGui::Text("Application average %.2f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        // ImGui::Text("Player position: x:%.2f y:%.2f z:%.2f", player.GetPosition().x, player.GetPosition().y, player.GetPosition().z);
        ImGui::End();
}

void Engine::ImguiRender() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Engine::ImguiDestroy() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}