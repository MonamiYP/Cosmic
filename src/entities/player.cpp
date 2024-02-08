#include "Player.hpp"

Player::Player() {}

void Player::SetModelFromSource(std::string const& path) {
    m_playerModel.SetModelFromSource(path);
}

void Player::Render(Shader& shader) {
    m_playerModel.Draw(shader);
}

glm::vec3 Player::GetPosition() {
    return m_position;
}