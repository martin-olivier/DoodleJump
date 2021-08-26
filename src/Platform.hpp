#pragma once

#include <array>

enum class Direction {
    RIGHT,
    LEFT
};

class IPlatform
{
public:
    virtual ~IPlatform() = default;
    virtual sf::Sprite& getSprite() = 0;
    virtual void update() = 0;
    virtual bool jumped() = 0;
};

class Platform final : public IPlatform
{
private:
    sf::Sprite m_sprite;
public:
    explicit Platform(const sf::Texture &texture)
    {
        m_sprite.setTexture(texture);
    };
    ~Platform() override = default;
    sf::Sprite& getSprite() override
    {
        return m_sprite;
    };
    void update() override
    {

    }
    bool jumped() override
    {
        return true;
    }
};

class MovingPlatform final : public IPlatform
{
private:
    sf::Sprite m_sprite;
    Direction m_direction = Direction::RIGHT;
public:
    explicit MovingPlatform(const sf::Texture &texture)
    {
        m_sprite.setTexture(texture);
    };
    ~MovingPlatform() override = default;
    sf::Sprite& getSprite() override
    {
        return m_sprite;
    };
    void update() override
    {
        if (m_direction == Direction::RIGHT) {
            if (m_sprite.getPosition().x >= 526)
                m_direction = Direction::LEFT;
            else
                m_sprite.setPosition(m_sprite.getPosition().x + 5, m_sprite.getPosition().y);
        }
        else if (m_direction == Direction::LEFT) {
            if (m_sprite.getPosition().x <= 0)
                m_direction = Direction::RIGHT;
            else
                m_sprite.setPosition(m_sprite.getPosition().x - 5, m_sprite.getPosition().y);
        }
    }
    bool jumped() override
    {
        return true;
    }
};

class BrokenPlatform final : public IPlatform
{
private:
    sf::Sprite m_sprite;
    const std::array<sf::Texture, 5> &m_textures;
    Sound &m_platformBreakSound;
    bool broken = false;
    size_t it = 0;
    size_t tick = 0;
public:
    explicit BrokenPlatform(const std::array<sf::Texture, 5> &textures, Sound &platformBreakSound) : m_textures(textures), m_platformBreakSound(platformBreakSound)
    {
        m_sprite.setTexture(textures[0]);
    };
    ~BrokenPlatform() override = default;
    sf::Sprite& getSprite() override
    {
        return m_sprite;
    };
    void update() override
    {
        if (!broken)
            return;
        tick++;
        if (tick % 5 == 0 and it < 4) {
            it = tick / 5;
            m_sprite.setTexture(m_textures[it]);
        }
    }
    bool jumped() override
    {
        if (!broken)
            m_platformBreakSound.play(true);
        broken = true;
        return false;
    }
};