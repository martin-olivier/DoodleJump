#pragma once

#include <memory>
#include <array>
#include "Sound.hpp"
#include "Doodle.hpp"
#include "Platform.hpp"

class Engine
{
private:
    sf::RenderWindow m_window{};
    sf::Image m_app_icon{};
    sf::Event m_event{};

    sf::Texture m_rightTexture{};
    sf::Texture m_leftTexture{};
    sf::Texture m_platformTexture{};
    sf::Texture m_verticalPlatformTexture{};
    sf::Texture m_horizontalPlatformTexture{};
    std::array<sf::Texture, 4> m_brokenPlatformTextures{};
    sf::Texture m_backgroundTexture{};
    sf::Sprite m_background{};

    Sound m_platformBreakSound{};

    std::vector<std::unique_ptr<IPlatform>> m_platforms{};
    std::unique_ptr<Doodle> m_doodle{};
public:
    Engine();
    ~Engine() = default;
    Engine(const Engine &) = delete;
    Engine &operator=(const Engine &) = delete;

    void start();
    void event();
    void update();
    void draw();
    void platforms();
};