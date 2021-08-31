#include "Doodle.hpp"

Doodle::Doodle(size_t &score, std::vector<std::unique_ptr<IPlatform>> &platforms)
    : m_score(score), m_platforms(platforms)
{
    m_sprite.setTexture(Data::m_rightTexture);
    m_sprite.setPosition(210, 500);
    m_jumpSound.setBuffer(Data::m_jumpSoundBuffer);
    m_fallSound.setBuffer(Data::m_fallSoundBuffer);
    m_last_y = 500;
    m_travel = 250;
}

void Doodle::update()
{
    auto pos = m_sprite.getPosition();

    // Handle Doodle death

    if (pos.y >= 1020 and pos.y < 1030)
        m_fallSound.play();
    else if (pos.y > 1030) {
        for (auto &p : m_platforms)
            p->setPosition(p->getPosition().x, p->getPosition().y - 20);
        return;
    }

    // Handle View

    if (m_mov == Movement::DOWN) {
        for (auto &p : m_platforms) {
            if ((p->getPosition().y >= pos.y + 110 and p->getPosition().y <= pos.y + 125) and pos.x > p->getPosition().x - 100 and pos.x < p->getPosition().x + 100) {
                auto jump = p->jumped();
                if (jump > 0) {
                    m_mov = Movement::UP;
                    m_travel = static_cast<float>(jump);
                    m_last_y = pos.y;
                    m_jumpSound.play();
                }
            }
        }
    }

    // Handle Doodle fall

    if (m_mov == Movement::DOWN) {
        float move;
        if (m_last_y > pos.y + (4 * m_travel / 5))
            move = 5;
        else
            move = 10;
        if (m_travel > 250)
            move = 10;
        m_sprite.setPosition(pos.x, pos.y + move);
    }

    // Handle Doodle jump

    else if (m_mov == Movement::UP) {
        if (m_last_y > pos.y + m_travel)
            m_mov = Movement::DOWN;
        else {
            float move;
            if (m_travel > 250 and m_last_y > pos.y + (4 * m_travel / 5))
                move = 10;
            else if (m_travel > 250)
                move = 20;
            else if (m_last_y > pos.y + (4 * m_travel / 5))
                move = 5;
            else
                move = 10;
            if (pos.y < 500) {
                for (auto &p : m_platforms)
                    p->setPosition(p->getPosition().x, p->getPosition().y + move);
                m_last_y += move;
                m_score += static_cast<size_t>(move);
            }
            else
                m_sprite.setPosition(pos.x, pos.y - move);
        }
    }
}