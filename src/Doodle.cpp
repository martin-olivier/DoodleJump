#include "Doodle.hpp"

Doodle::Doodle(const sf::Texture &texture, std::vector<sf::Sprite> &platforms) : m_sprite(texture), m_platforms(platforms)
{
    m_sprite.setPosition(210, 500);
    last_y = 500;
    m_jumpSound.setSound("resource/jump.wav");
}

void Doodle::update()
{
    auto pos = m_sprite.getPosition();

    if (m_mov == Movement::DOWN) {
        for (const auto &p : m_platforms) {
            if (p.getPosition().y == m_sprite.getPosition().y + 110 and m_sprite.getPosition().x > p.getPosition().x - 114 and m_sprite.getPosition().x < p.getPosition().x + 114) {
                m_mov = Movement::UP;
                last_y = m_sprite.getPosition().y;
                m_jumpSound.play(true);
            }
        }
    }

    if (m_mov == Movement::DOWN)
        m_sprite.setPosition(pos.x, pos.y + 10);
    else if (m_mov == Movement::UP) {
        if (last_y > pos.y + 250)
            m_mov = Movement::DOWN;
        else {
            if (m_sprite.getPosition().y < 200) {
                for (auto &p : m_platforms)
                    p.setPosition(p.getPosition().x, p.getPosition().y + 10);
                last_y += 10;
            }
            else
                m_sprite.setPosition(pos.x, pos.y - 10);
        }
    }
}