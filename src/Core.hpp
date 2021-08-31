#pragma once

#include <memory>
#include <array>
#include "Data.hpp"
#include "Doodle.hpp"
#include "Platform.hpp"

class Core final
{
private:
    sf::RenderWindow m_window{};
    sf::Image m_app_icon{};
    sf::Event m_event{};

    sf::Sprite m_background{};

    std::vector<std::unique_ptr<IPlatform>> m_platforms{};
    std::unique_ptr<Doodle> m_doodle{};

    size_t m_score{};
    sf::Text m_score_display{};
public:
    Core();
    ~Core() = default;
    Core(const Core &) = delete;
    Core &operator=(const Core &) = delete;

    void reset();
    void start();
    void event();
    void update();
    void draw();
    void platforms();
    void gameOver();
};