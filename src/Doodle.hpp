#pragma once

#include <vector>
#include "Data.hpp"
#include "Platform.hpp"

enum class Movement {
    UP,
    DOWN
};

class Doodle
{
public:
    sf::Sprite m_sprite;
    sf::Sound m_jumpSound;
    sf::Sound m_fallSound;
    size_t &m_score;
    std::vector<std::unique_ptr<IPlatform>> &m_platforms;
    Movement m_mov = Movement::DOWN;
    float m_last_y{};
    float m_travel{};

    Doodle(size_t &score, std::vector<std::unique_ptr<IPlatform>> &platforms);
    ~Doodle() = default;
    void update();
};