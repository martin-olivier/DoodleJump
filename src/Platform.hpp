#pragma once

#include <array>
#include <random>
#include "Boost.hpp"

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
    virtual const std::unique_ptr<IBoost> &getBoost() = 0;
    virtual void setPosition(float x, float y) = 0;
    virtual void update() = 0;
    virtual int jumped() = 0;
};

class BoostedPlatform : public IPlatform
{
public:
    std::unique_ptr<IBoost> m_boost = nullptr;
    BoostedPlatform()
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist526(0,20);
        auto rand = dist526(rng);
        if (rand == 0) {
            m_boost = std::make_unique<FederBoost>();
        }
        else if (rand == 1) {
            m_boost = std::make_unique<TrampolineBoost>();
        }
    };
    ~BoostedPlatform() override = default;
};

class Platform final : public BoostedPlatform
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
    std::unique_ptr<IBoost> &getBoost() override
    {
        return m_boost;
    };
    void update() override
    {

    }
    int jumped() override
    {
        if (m_boost) {
            m_boost->action();
            return m_boost->getTravel();
        }
        return 250;
    }
    void setPosition(float x, float y) override
    {
        m_sprite.setPosition(x, y);
        if (m_boost)
            m_boost->getSprite().setPosition(x, y - m_boost->getSize().y);
    }
};

class HorizontalPlatform final : public BoostedPlatform
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
    std::unique_ptr<IBoost> &getBoost() override
    {
        return m_boost;
    };
    void update() override
    {
        if (m_direction == Direction::RIGHT) {
            if (m_sprite.getPosition().x >= 526)
                m_direction = Direction::LEFT;
            else
                setPosition(m_sprite.getPosition().x + 3, m_sprite.getPosition().y);
        }
        else if (m_direction == Direction::LEFT) {
            if (m_sprite.getPosition().x <= 0)
                m_direction = Direction::RIGHT;
            else
                setPosition(m_sprite.getPosition().x - 3, m_sprite.getPosition().y);
        }
    }
    int jumped() override
    {
        if (m_boost) {
            m_boost->action();
            return m_boost->getTravel();
        }
        return 250;
    }
    void setPosition(float x, float y) override
    {
        m_sprite.setPosition(x, y);
        if (m_boost)
            m_boost->getSprite().setPosition(x, y - m_boost->getSize().y);
    }
};

class VerticalPlatform final : public BoostedPlatform
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
    std::unique_ptr<IBoost> &getBoost() override
    {
        return m_boost;
    };
    void update() override
    {
        if (m_direction == Direction::DOWN) {
            if (m_distance >= 150)
                m_direction = Direction::UP;
            else {
                setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y + 2);
                m_distance += 2;
            }
        }
        else if (m_direction == Direction::UP) {
            if (m_distance <= 0)
                m_direction = Direction::DOWN;
            else {
                setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y - 2);
                m_distance -= 2;
            }
        }
    }
    int jumped() override
    {
        if (m_boost) {
            m_boost->action();
            return m_boost->getTravel();
        }
        return 250;
    }
    void setPosition(float x, float y) override
    {
        m_sprite.setPosition(x, y);
        if (m_boost)
            m_boost->getSprite().setPosition(x, y - m_boost->getSize().y);
    }
};

class BrokenPlatform final : public IPlatform
{
private:
    sf::Sprite m_sprite;
    const std::array<sf::Texture, 4> &m_textures;
    std::unique_ptr<IBoost> m_boost = nullptr;
    Sound &m_platformBreakSound;
    bool broken = false;
    size_t it = 0;
    size_t tick = 0;
public:
    BrokenPlatform(const std::array<sf::Texture, 4> &textures, Sound &platformBreakSound) : m_textures(textures), m_platformBreakSound(platformBreakSound)
    {
        m_sprite.setTexture(textures[0]);
    };
    ~BrokenPlatform() override = default;
    sf::Sprite& getSprite() override
    {
        return m_sprite;
    };
    std::unique_ptr<IBoost> &getBoost() override
    {
        return m_boost;
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
    int jumped() override
    {
        if (!broken)
            m_platformBreakSound.play(true);
        broken = true;
        return 0;
    }
    void setPosition(float x, float y) override
    {
        m_sprite.setPosition(x, y);
    }
};