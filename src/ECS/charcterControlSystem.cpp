#include "Systems/CharacterControlSystem.hpp"

extern ECS ecs;

void CharacterControlSystem::Init() {

}

void CharacterControlSystem::Update(float deltaTime) {
    for (auto const& entity : m_Entities) {
        auto const& transform = ecs.GetComponent<TransformComponent>(entity);
        ProcessKeyboardInput(&entity, RIGHT, deltaTime);
        SetRotationMatrix(&entity);
    }
}

void CharacterControlSystem::ProcessKeyboardInput(const Entity* entity, MovementDir dir, float deltaTime) {
    auto& transform = ecs.GetComponent<TransformComponent>(*entity);
    auto& orientation = ecs.GetComponent<OrientationComponent>(*entity);

    float move_speed = m_movementSpeed * deltaTime;
    float roll_speed = m_rollSpeed * deltaTime;

    if (dir == LEFT)
        transform.rotation.z = -roll_speed;
    if (dir == RIGHT)
        transform.rotation.z = roll_speed;
    if (dir == FORWARDS)
        transform.position += move_speed * orientation.forwards;
    if (dir == BACKWARDS)
        transform.position -= move_speed * orientation.forwards;
}

void CharacterControlSystem::ProcessMouseInput(const Entity* entity, float xOffset, float yOffset) {
    auto& transform = ecs.GetComponent<TransformComponent>(*entity);
    transform.rotation.y = -xOffset * m_mouseSensitivity;
    transform.rotation.x = yOffset * m_mouseSensitivity;
}

glm::mat4 CharacterControlSystem::GetQuaternionMatrix(const Entity* entity) {
    auto& orientation = ecs.GetComponent<OrientationComponent>(*entity);
    auto& transform = ecs.GetComponent<TransformComponent>(*entity);

    glm::quat q_forwards = glm::angleAxis(glm::radians(transform.rotation.z), orientation.forwards);
    glm::quat q_right = glm::angleAxis(glm::radians(transform.rotation.x), orientation.right);
    glm::quat q_up = glm::angleAxis(glm::radians(transform.rotation.y), orientation.up);
    transform.rotation.x = 0.0f;
    transform.rotation.y = 0.0f;
    transform.rotation.z = 0.0f;

    glm::mat4 forward_mat = glm::toMat4(q_forwards);
    glm::mat4 right_mat = glm::toMat4(q_right);
    glm::mat4 up_mat = glm::toMat4(q_up);

    glm::quat quat_forwards = q_up * q_right * q_forwards * glm::quat(0, orientation.forwards) * glm::inverse(q_forwards) * glm::inverse(q_right) * glm::inverse(q_up);
    orientation.forwards = glm::normalize(glm::vec3(quat_forwards.x, quat_forwards.y, quat_forwards.z));

    glm::quat quat_up = q_up * q_right * q_forwards * glm::quat(0, orientation.up) * glm::inverse(q_forwards) * glm::inverse(q_right) * glm::inverse(q_up);
    orientation.up = glm::normalize(glm::vec3(quat_up.x, quat_up.y, quat_up.z));
    glm::quat quat_right =  q_up * q_right * q_forwards * glm::quat(0, orientation.right) * glm::inverse(q_forwards) * glm::inverse(q_right) * glm::inverse(q_up);
    orientation.right = glm::normalize(glm::vec3(quat_right.x, quat_right.y, quat_right.z));

    glm::mat4 rotation_mat = up_mat * right_mat * forward_mat;

    return rotation_mat;
}

void CharacterControlSystem::SetRotationMatrix(const Entity* entity) {;
    auto& orientation = ecs.GetComponent<OrientationComponent>(*entity);

    glm::mat4 rotMatrix = GetQuaternionMatrix(entity) * m_prev_rot;
    m_prev_rot = rotMatrix;

    orientation.rotMatrix = rotMatrix;
}