#include "Engine.hpp"
#include <random>

Engine::Engine()
{
    m_window.create(sf::VideoMode(640, 1024), "Doodle Jump");
    m_window.setFramerateLimit(60);

    m_app_icon.loadFromFile("resource/app_icon.png");
    m_window.setIcon(m_app_icon.getSize().x, m_app_icon.getSize().y, m_app_icon.getPixelsPtr());

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    m_window.setPosition(sf::Vector2i(desktop.width / 2 - m_window.getSize().x/2, desktop.height/2 - m_window.getSize().y/2));

    if (!m_rightTexture.loadFromFile("resource/right.png"))
        throw std::exception();
    if (!m_leftTexture.loadFromFile("resource/left.png"))
        throw std::exception();
    if (!m_platformTexture.loadFromFile("resource/platform.png"))
        throw std::exception();
    if (!m_backgroundTexture.loadFromFile("resource/background.png"))
        throw std::exception();
    m_background.setTexture(m_backgroundTexture);
    m_doodle = std::make_unique<Doodle>(m_rightTexture, m_platforms);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0,526);

    for (int i = 1000; i >= 0; i -= 100) {
        m_platforms.emplace_back();
        m_platforms.back().setTexture(m_platformTexture);
        m_platforms.back().setPosition(dist6(rng), i);
    }
    m_doodle->m_sprite.setPosition(m_platforms.front().getPosition().x, m_doodle->m_sprite.getPosition().y);
    start();
}

void Engine::start()
{
    while (m_window.isOpen()) {
        platforms();
        event();
        m_doodle->update();
        m_window.clear(sf::Color::Black);
        draw();
        m_window.display();
        sf::sleep(sf::milliseconds(15));
    }
}

void Engine::event()
{
    while (m_window.pollEvent(m_event)) {
        if (m_event.type == sf::Event::Closed)
            m_window.close();
    }
    auto pos = m_doodle->m_sprite.getPosition();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_doodle->m_sprite.setPosition(pos.x + 5, pos.y);
        m_doodle->m_sprite.setTexture(m_rightTexture);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_doodle->m_sprite.setPosition(pos.x - 5, pos.y);
        m_doodle->m_sprite.setTexture(m_leftTexture);
    }
}

void Engine::draw()
{
    m_window.draw(m_background);
    for (const auto &p : m_platforms)
        m_window.draw(p);
    m_window.draw(m_doodle->m_sprite);
}

void Engine::platforms()
{
    for (size_t i = 0; i < m_platforms.size(); i++) {
        if (m_platforms[i].getPosition().y > 1024)
            m_platforms.erase(m_platforms.begin() + i);
    }
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0,526);

    if (!m_platforms.empty() and m_platforms.back().getPosition().y > 100) {
        m_platforms.emplace_back();
        m_platforms.back().setTexture(m_platformTexture);
        m_platforms.back().setPosition(dist6(rng), 0);
    }
}
