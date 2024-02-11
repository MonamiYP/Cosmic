#include "Player.hpp"

Player::Player(glm::vec3 position, float yaw, float pitch) {
    m_forwards = glm::vec3(0.0f, 0.0f, -1.0f);
    m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    m_right = glm::vec3(1.0f, 0.0f, 0.0f);

    m_movementSpeed = 8.0f;
    m_rollSpeed = 50.0f;
    m_mouseSensitivity = 0.02f;

    m_position = position;
}

void Player::SetModelFromSource(std::string const& path) {
    m_playerModel.SetModelFromSource(path);
}

void Player::Render(Shader& shader) {
    m_playerModel.Draw(shader);
}

glm::mat4 Player::GetQuaternionMatrix() {
    glm::quat q_forwards = glm::angleAxis(glm::radians(m_rotation.z), m_forwards);
    glm::quat q_right = glm::angleAxis(glm::radians(m_rotation.x), m_right);
    glm::quat q_up = glm::angleAxis(glm::radians(m_rotation.y), m_up);
    m_rotation.x = 0.0f;
    m_rotation.y = 0.0f;
    m_rotation.z = 0.0f;

    glm::mat4 forward_mat = glm::toMat4(q_forwards);
    glm::mat4 right_mat = glm::toMat4(q_right);
    glm::mat4 up_mat = glm::toMat4(q_up);

    glm::quat quat_forwards = q_up * q_right * q_forwards * glm::quat(0, m_forwards) * glm::inverse(q_forwards) * glm::inverse(q_right) * glm::inverse(q_up);
    m_forwards = glm::normalize(glm::vec3(quat_forwards.x, quat_forwards.y, quat_forwards.z));

    glm::quat quat_up = q_up * q_right * q_forwards * glm::quat(0, m_up) * glm::inverse(q_forwards) * glm::inverse(q_right) * glm::inverse(q_up);
    m_up = glm::normalize(glm::vec3(quat_up.x, quat_up.y, quat_up.z));
    glm::quat quat_right =  q_up * q_right * q_forwards * glm::quat(0, m_right) * glm::inverse(q_forwards) * glm::inverse(q_right) * glm::inverse(q_up);
    m_right = glm::normalize(glm::vec3(quat_right.x, quat_right.y, quat_right.z));

    glm::mat4 rotation_mat = up_mat * right_mat * forward_mat;

    return rotation_mat;
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
    m_rotation.y = -xOffset * m_mouseSensitivity;
    m_rotation.x = yOffset * m_mouseSensitivity;
}

glm::mat4 Player::GetModelMatrix() {;
    glm::mat4 m_quatRotationMatrix = GetQuaternionMatrix();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, m_position);
    model = model * m_quatRotationMatrix * m_prev_rot;
    m_prev_rot = m_quatRotationMatrix * m_prev_rot;

    return model;
}