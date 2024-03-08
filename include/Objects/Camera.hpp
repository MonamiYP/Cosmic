#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
    public:
        Camera();
        ~Camera() {}

        glm::mat4 GetCameraView();
        void UpdateVectors();

        float GetFOV() { return glm::radians(m_fov); }
        glm::vec3 GetPosition() { return m_position; }
        glm::vec3 GetForwards() { return m_forwards; }
        glm::vec3 GetUpDir() { return m_up; }

        void SetTargetPosition(glm::vec3 position);
    private:
        glm::vec3 m_position;
        glm::vec3 m_forwards;
        glm::vec3 m_up;
        glm::vec3 m_right;

        glm::vec3 m_targetPosition;
        glm::vec3 m_targetForwards;
        glm::vec3 m_targetUp;
        glm::vec3 m_targetRight;
        float m_distanceFromTarget;

        glm::vec3 m_worldUp;

        float m_fov;
};