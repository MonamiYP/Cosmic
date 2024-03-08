#include "Camera.hpp"

#include <iostream>

Camera::Camera() {
    m_fov = 40.0f;
    m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    m_worldUp = m_up;
}

glm::mat4 Camera::GetCameraView() {
    return glm::lookAt(m_position, m_position + m_forwards, m_up);
}

void Camera::UpdateVectors() {
    float pitch = glm::radians(15.0f);
    m_forwards = m_targetForwards*cos(pitch) - m_targetUp*sin(pitch);
    m_forwards = glm::normalize(m_forwards);
    m_right = m_targetRight;
    m_up = m_targetUp*cos(pitch) + m_targetForwards*sin(pitch);
    m_up = glm::normalize(m_up);

    m_position = m_targetPosition - m_forwards*m_distanceFromTarget;
}

void Camera::SetTargetPosition(glm::vec3 position) {
    m_targetPosition = position;
}