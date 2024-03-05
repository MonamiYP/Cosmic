#include "Requirements.hpp"
#include "ECSRequirements.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void window_focus_callback(GLFWwindow* window, int focused);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

ECS ecs;

extern const float WINDOW_WIDTH = 1200.0f;
extern const float WINDOW_HEIGHT = 800.0f;

float lastX =  WINDOW_WIDTH / 2.0;
float lastY =  WINDOW_HEIGHT / 2.0;

float deltaTime;
float lastTime;

bool guiActive = false;
int outerTesselationLevel = 15;
int innerTesselationLevel = 15;

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
    glfwSetCursorPosCallback(window, 0);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowFocusCallback(window, window_focus_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glPatchParameteri(GL_PATCH_VERTICES, 4);

    ecs.Init();
    ecs.RegisterComponent<TransformComponent>();
    ecs.RegisterComponent<OrientationComponent>();
    ecs.RegisterComponent<CameraComponent>();

    auto renderSystem = ecs.RegisterSystem<RenderSystem>();
    {
        Signature signature;
        signature.set(ecs.GetComponentType<TransformComponent>());
        ecs.SetSystemSignature<RenderSystem>(signature);
    }
    renderSystem->Init();

    Entity lightEntity = ecs.CreateEntity();
    ecs.AddComponent(lightEntity, TransformComponent {
        .position = glm::vec3(0.0f, 0.0f, -10.0f),
        .scale = glm::vec3(1.0f)});

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);  

    while(!glfwWindowShouldClose(window)) {
        float currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        processInput(window);
        
        renderSystem->Update(deltaTime);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {
        if (!guiActive) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            glfwSetCursorPosCallback(window, 0);
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetCursorPos(window, lastX, lastY);
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

    // player.ProcessMouseInput(xOffset, yOffset);
}

void window_focus_callback(GLFWwindow* window, int focused) {
    if (focused) {
        glfwSetCursorPos(window, lastX, lastY);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}  