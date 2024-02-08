#include "Player.hpp"

Player::Player(glm::vec3 position, glm::vec3 up, float yaw, float pitch) {
    m_movementSpeed = 5.0f;
    m_rollSpeed = 50.0f;
    m_mouseSensitivity = 0.1f;
    m_forwards = glm::vec3(0.0f, 0.0f, -1.0f);
    m_position = position;
    m_worldUp = up;
    m_roll = 0.0f;
}

void Player::SetModelFromSource(std::string const& path) {
    m_playerModel.SetModelFromSource(path);
}

void Player::Render(Shader& shader) {
    m_playerModel.Draw(shader);
}

void Player::UpdateVectors() {

}

void Player::ProcessKeyboardInput(MovementDir dir, float deltaTime) {
    float move_speed = m_movementSpeed * deltaTime;
    float roll_speed = m_rollSpeed * deltaTime;

    if (dir == UP)
        m_position += move_speed * m_up;
    if (dir == DOWN)
        m_position -= move_speed * m_up;
    if (dir == LEFT)
        m_roll -= roll_speed;
    if (dir == RIGHT)
        m_roll += roll_speed;
    if (dir == FORWARDS)
        m_position += move_speed * m_forwards;
    if (dir == BACKWARDS)
        m_position -= move_speed * m_forwards;
}

void Player::ProcessMouseInput(float xOffset, float yOffset) {
    m_yaw += xOffset * m_mouseSensitivity;
}

glm::mat4 Player::GetModelMatrix() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, m_position);
    model = glm::rotate(model, glm::radians(m_roll), m_forwards);

    return model;
}

glm::vec3 Player::GetPosition() {
    return m_position;
}

glm::vec3 Player::GetForwardDir() {
    return m_forwards;
}