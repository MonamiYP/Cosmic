#include "Camera.hpp"

Camera::Camera(Player* player) : m_fov(70.0f), m_distanceFromPlayer(25.0f) {
    m_player = player;

    UpdateVectors();
}

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : m_fov(40.0f), m_distanceFromPlayer(10.0f) {
    m_position = position;
    m_worldUp = up;
}

glm::mat4 Camera::GetCameraView() {
    return glm::lookAt(m_position, m_position + m_forwards, m_up);
}

void Camera::UpdateVectors() {
    float pitch = glm::radians(15.0f);
    m_forwards = m_player->GetForwardDir()*cos(pitch) - m_player->GetUpDir()*sin(pitch);
    m_forwards = glm::normalize(m_forwards);
    m_right = m_player->GetRightDir();
    m_up = m_player->GetUpDir()*cos(pitch) + m_player->GetForwardDir()*sin(pitch);
    m_up = glm::normalize(m_up);

    m_position = m_player->GetPosition() - m_forwards*m_distanceFromPlayer;
}

float Camera::GetFOV() {
    return glm::radians(m_fov);
}

glm::vec3 Camera::GetPosition() {
    return m_position;
}

glm::vec3 Camera::GetForwards() {
    return m_forwards;
}