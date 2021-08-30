#include "Engine.hpp"
#include "Score.hpp"
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
    if (!m_horizontalPlatformTexture.loadFromFile("resource/horizontal_platform.png"))
        throw std::exception();
    if (!m_verticalPlatformTexture.loadFromFile("resource/vertical_platform.png"))
        throw std::exception();
    if (!m_backgroundTexture.loadFromFile("resource/background.png"))
        throw std::exception();

    if (!m_brokenPlatformTextures[0].loadFromFile("resource/broken_platform0.png"))
        throw std::exception();
    if (!m_brokenPlatformTextures[1].loadFromFile("resource/broken_platform1.png"))
        throw std::exception();
    if (!m_brokenPlatformTextures[2].loadFromFile("resource/broken_platform2.png"))
        throw std::exception();
    if (!m_brokenPlatformTextures[3].loadFromFile("resource/broken_platform3.png"))
        throw std::exception();

    m_platformBreakSound.setSound("resource/platform_break.wav");

    m_font.loadFromFile("resource/arial.ttf");
    m_score_display.setFont(m_font);
    m_score_display.setPosition(10, 10);
    m_score_display.setCharacterSize(40);
    m_score_display.setFillColor(sf::Color::Black);

    m_background.setTexture(m_backgroundTexture);
    reset();
    start();
}

void Engine::reset()
{
    m_score = 0;
    m_platforms.clear();
    m_doodle = std::make_unique<Doodle>(m_rightTexture, m_score, m_platforms);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist526(0,526);

    for (int i = 1000; i >= 0; i -= 100) {
        m_platforms.emplace_back(std::make_unique<Platform>(m_platformTexture));
        m_platforms.back()->getSprite().setPosition(dist526(rng), i);
    }
    m_doodle->m_sprite.setPosition(m_platforms.front()->getSprite().getPosition().x, m_doodle->m_sprite.getPosition().y);
}


void Engine::start()
{
    while (m_window.isOpen()) {
        platforms();
        event();
        update();
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
        m_doodle->m_sprite.setPosition(pos.x + 8, pos.y);
        m_doodle->m_sprite.setTexture(m_rightTexture);
        if (m_doodle->m_sprite.getPosition().x >= 640)
            m_doodle->m_sprite.setPosition(-110, m_doodle->m_sprite.getPosition().y);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_doodle->m_sprite.setPosition(pos.x - 8, pos.y);
        m_doodle->m_sprite.setTexture(m_leftTexture);
        if (m_doodle->m_sprite.getPosition().x <= -110)
            m_doodle->m_sprite.setPosition(640, m_doodle->m_sprite.getPosition().y);
    }
}

void Engine::update()
{
    m_doodle->update();
    for (auto &p : m_platforms)
        p->update();

    // Handle Game Over

    float lower_y = -60;
    for (auto &p : m_platforms) {
        if (p->getSprite().getPosition().y > lower_y)
            lower_y = p->getSprite().getPosition().y;
    }
    if (lower_y == -60)
        gameOver();
}

void Engine::draw()
{
    m_window.draw(m_background);
    for (const auto &p : m_platforms) {
        m_window.draw(p->getSprite());
        if (p->getBoost())
            m_window.draw(p->getBoost()->getSprite());
    }
    m_window.draw(m_doodle->m_sprite);
    m_score_display.setString(std::to_string(m_score));
    m_window.draw(m_score_display);
}

void Engine::platforms()
{
    for (size_t i = 0; i < m_platforms.size(); i++) {
        if (m_platforms[i]->getSprite().getPosition().y > 1024)
            m_platforms.erase(m_platforms.begin() + i);
    }
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist526(0,526);
    std::uniform_int_distribution<std::mt19937::result_type> dist20(0,8);

    static bool last_was_broken = false;

    if (!m_platforms.empty() and m_platforms.back()->getSprite().getPosition().y > 100) {
        auto rand = dist20(rng);
        if (rand < 4) {
            last_was_broken = false;
            m_platforms.emplace_back(std::make_unique<HorizontalPlatform>(m_horizontalPlatformTexture));
        }
        else if (rand == 4) {
            last_was_broken = false;
            m_platforms.emplace_back(std::make_unique<VerticalPlatform>(m_verticalPlatformTexture));
        }
        else if ((rand == 5 or rand == 6) and !last_was_broken) {
            last_was_broken = true;
            m_platforms.emplace_back(std::make_unique<BrokenPlatform>(m_brokenPlatformTextures, m_platformBreakSound));
        }
        else {
            last_was_broken = false;
            m_platforms.emplace_back(std::make_unique<Platform>(m_platformTexture));
        }
        m_platforms.back()->getSprite().setPosition(dist526(rng), 0);
    }
}

void Engine::gameOver()
{
    sf::Text score;
    sf::Sprite game_over;
    sf::Texture game_over_texture;
    sf::Sprite play_again;
    sf::Texture play_again_texture;

    auto best_score = Score::Load("score.txt");
    if (m_score > best_score) {
        Score::Save("score.txt", m_score);
        best_score = m_score;
    }

    game_over_texture.loadFromFile("resource/game_over.png");
    play_again_texture.loadFromFile("resource/play_again.png");
    game_over.setTexture(game_over_texture);
    play_again.setTexture(play_again_texture);
    game_over.setPosition(100, 200);
    play_again.setPosition(200, 800);
    score.setFont(m_font);
    score.setPosition(150, 500);
    score.setCharacterSize(40);
    score.setFillColor(sf::Color::Black);
    score.setString("your score: " + std::to_string(m_score) + "\nyour best score: " + std::to_string(best_score));

    while (m_window.isOpen()) {
        while (m_window.pollEvent(m_event)) {
            if (m_event.type == sf::Event::Closed)
                m_window.close();
            if (m_event.type == sf::Event::MouseButtonReleased && m_event.mouseButton.button == sf::Mouse::Left) {
                if (m_event.mouseButton.x >= 200 and m_event.mouseButton.x <= 424 and m_event.mouseButton.y >= 800 and m_event.mouseButton.y <= 885) {
                    reset();
                    start();
                }
            }
        }
        m_window.clear(sf::Color::Black);
        m_window.draw(m_background);
        m_window.draw(game_over);
        m_window.draw(play_again);
        m_window.draw(score);
        m_window.display();
        sf::sleep(sf::milliseconds(15));
    }
}