#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "Sound.hpp"

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