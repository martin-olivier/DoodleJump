#pragma once

#include "Tile.hpp"
#include "Sound.hpp"
#include <vector>

enum class Movement {
    UP,
    DOWN
};

class Doodle
{
public:
    sf::Sprite m_sprite;
    std::vector<sf::Sprite> &m_platforms;
    Movement m_mov = Movement::DOWN;
    float last_y{};
    Sound m_jumpSound{};

    Doodle(const sf::Texture &texture, std::vector<sf::Sprite> &platforms);
    ~Doodle() = default;
    void update();
};