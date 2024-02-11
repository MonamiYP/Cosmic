#include "Player.hpp"

Player::Player(glm::vec3 position, float yaw, float pitch) {
    m_forwards = glm::vec3(0.0f, 0.0f, -1.0f);
    m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    m_right = glm::vec3(1.0f, 0.0f, 0.0f);
    m_position = position;
}

void Player::SetModelFromSource(std::string const& path) {
    m_playerModel.SetModelFromSource(path);
}

void Player::Render(Shader& shader) {
    m_playerModel.Draw(shader);
}

glm::mat4 Player::GetQuaternionRotation() {
    glm::quat q_forwards = glm::angleAxis(glm::radians(m_rotation.z), m_forwards);
    m_rotation.z = 0.0f;

    glm::mat4 rotationMat = glm::toMat4(q_forwards);

    glm::quat quat_forwards = q_forwards * glm::quat(0, m_forwards.x, m_forwards.y, m_forwards.z) * glm::inverse(q_forwards);
    m_forwards = glm::normalize(glm::vec3(quat_forwards.x, quat_forwards.y, quat_forwards.z));
    glm::quat quat_up = q_forwards * glm::quat(0, m_up.x, m_up.y, m_up.z) * glm::inverse(q_forwards);
    m_up = glm::normalize(glm::vec3(quat_up.x, quat_up.y, quat_up.z));
    glm::quat quat_right = q_forwards * glm::quat(0, m_right.x, m_right.y, m_right.z) * glm::inverse(q_forwards);
    m_right = glm::normalize(glm::vec3(quat_right.x, quat_right.y, quat_right.z));

    return rotationMat;
}

void Player::ProcessKeyboardInput(MovementDir dir, float deltaTime) {
    float move_speed = m_movementSpeed * deltaTime;
    float roll_speed = m_rollSpeed * deltaTime;

    if (dir == LEFT)
        m_rotation.z = -roll_speed;
    if (dir == RIGHT)
        m_rotation.z = roll_speed;
    if (dir == FORWARDS)
        m_position += move_speed * m_forwards;
    if (dir == BACKWARDS)
        m_position -= move_speed * m_forwards;
}

void Player::ProcessMouseInput(float xOffset, float yOffset) {
    m_rotation.y -= xOffset * m_mouseSensitivity;
    m_rotation.x += yOffset * m_mouseSensitivity;
}

glm::mat4 Player::GetModelMatrix() {;
    glm::mat4 m_quatRotationMatrix = GetQuaternionRotation();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, m_position);
    model = model * m_quatRotationMatrix * m_prev_rot;
    m_prev_rot = m_quatRotationMatrix * m_prev_rot;

    return model;
}