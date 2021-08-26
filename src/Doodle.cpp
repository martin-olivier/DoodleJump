#include "Doodle.hpp"

Doodle::Doodle(const sf::Texture &texture, std::vector<std::unique_ptr<IPlatform>> &platforms) : m_sprite(texture), m_platforms(platforms)
{
    m_sprite.setPosition(210, 500);
    last_y = 500;
    m_jumpSound.setSound("resource/jump.wav");
}

void Doodle::update()
{
    auto pos = m_sprite.getPosition();

    if (m_mov == Movement::DOWN) {
        for (auto &p : m_platforms) {
            if ((p->getSprite().getPosition().y == m_sprite.getPosition().y + 110 or p->getSprite().getPosition().y == m_sprite.getPosition().y + 115) and m_sprite.getPosition().x > p->getSprite().getPosition().x - 100 and m_sprite.getPosition().x < p->getSprite().getPosition().x + 100) {
                if (p->jumped()) {
                    m_mov = Movement::UP;
                    last_y = m_sprite.getPosition().y;
                    m_jumpSound.play(true);
                }
            }
        }
    }

    if (m_mov == Movement::DOWN) {
        float move;
        if (last_y > pos.y + 200)
            move = 5;
        else
            move = 10;
        m_sprite.setPosition(pos.x, pos.y + move);
    }
    else if (m_mov == Movement::UP) {
        if (last_y > pos.y + 250)
            m_mov = Movement::DOWN;
        else {
            float move;
            if (last_y > pos.y + 200)
                move = 5;
            else
                move = 10;
            if (m_sprite.getPosition().y < 500) {
                for (auto &p : m_platforms)
                    p->getSprite().setPosition(p->getSprite().getPosition().x, p->getSprite().getPosition().y + move);
                last_y += move;
            }
            else
                m_sprite.setPosition(pos.x, pos.y - move);
        }
    }
}