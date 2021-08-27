#pragma once

#include <array>

enum class Direction {
    RIGHT,
    LEFT,
    UP,
    DOWN
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

class HorizontalPlatform final : public IPlatform
{
private:
    sf::Sprite m_sprite;
    Direction m_direction = Direction::RIGHT;
public:
    explicit HorizontalPlatform(const sf::Texture &texture)
    {
        m_sprite.setTexture(texture);
    };
    ~HorizontalPlatform() override = default;
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
                m_sprite.setPosition(m_sprite.getPosition().x + 3, m_sprite.getPosition().y);
        }
        else if (m_direction == Direction::LEFT) {
            if (m_sprite.getPosition().x <= 0)
                m_direction = Direction::RIGHT;
            else
                m_sprite.setPosition(m_sprite.getPosition().x - 3, m_sprite.getPosition().y);
        }
    }
    bool jumped() override
    {
        return true;
    }
};

class VerticalPlatform final : public IPlatform
{
private:
    sf::Sprite m_sprite;
    Direction m_direction = Direction::DOWN;
    int m_distance = 0;
public:
    explicit VerticalPlatform(const sf::Texture &texture)
    {
        m_sprite.setTexture(texture);
    };
    ~VerticalPlatform() override = default;
    sf::Sprite& getSprite() override
    {
        return m_sprite;
    };
    void update() override
    {
        if (m_direction == Direction::DOWN) {
            if (m_distance >= 150)
                m_direction = Direction::UP;
            else {
                m_sprite.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y + 2);
                m_distance += 2;
            }
        }
        else if (m_direction == Direction::UP) {
            if (m_distance <= 0)
                m_direction = Direction::DOWN;
            else {
                m_sprite.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y - 2);
                m_distance -= 2;
            }
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
    const std::array<sf::Texture, 4> &m_textures;
    Sound &m_platformBreakSound;
    bool broken = false;
    size_t it = 0;
    size_t tick = 0;
public:
    explicit BrokenPlatform(const std::array<sf::Texture, 4> &textures, Sound &platformBreakSound) : m_textures(textures), m_platformBreakSound(platformBreakSound)
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
        m_sprite.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y + 10);
        if (tick % 5 == 0 and it < 3) {
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