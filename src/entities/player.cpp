#include "Player.hpp"

Player::Player(glm::vec3 position, float yaw, float pitch) {
    m_forwards = glm::vec3(0.0f, 0.0f, 1.0f);
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

void Player::UpdateLocalVectors() {
    glm::vec3 front;
    front.x = -sin(glm::radians(m_rotation.y)) * cos(glm::radians(m_rotation.x));
    front.y = sin(glm::radians(m_rotation.x));
    front.z = -cos(glm::radians(m_rotation.y)) * cos(glm::radians(m_rotation.x));
    m_forwards = glm::normalize(front);
    m_right = glm::normalize(glm::cross(m_forwards, glm::vec3(0.0f, 1.0f, 0.0f)));
    m_up = glm::normalize(glm::cross(m_right, m_forwards));
}

void Player::ProcessKeyboardInput(MovementDir dir, float deltaTime) {
    float move_speed = m_movementSpeed * deltaTime;
    float roll_speed = m_rollSpeed * deltaTime;

    // if (dir == UP)
    //     m_rotation.x += roll_speed;
    // if (dir == DOWN)
    //     m_rotation.x -= roll_speed;
    if (dir == LEFT)
        m_rotation.z -= roll_speed;
    if (dir == RIGHT)
        m_rotation.z += roll_speed;
    if (dir == FORWARDS)
        m_position += move_speed * m_forwards;
    if (dir == BACKWARDS)
        m_position -= move_speed * m_forwards;

    UpdateLocalVectors();
}

void Player::ProcessMouseInput(float xOffset, float yOffset) {
    m_rotation.y -= xOffset * m_mouseSensitivity;
    m_rotation.x += yOffset * m_mouseSensitivity;

    UpdateLocalVectors();
}

glm::mat4 Player::GetModelMatrix() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, m_position);
    model = glm::rotate(model, glm::radians(m_rotation.z), m_forwards);
    model = glm::rotate(model, glm::radians(m_rotation.y), m_up);
    model = glm::rotate(model, glm::radians(m_rotation.x), m_right);

    return model;
}