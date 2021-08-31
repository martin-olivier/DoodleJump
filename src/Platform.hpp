#pragma once

#include "Boost.hpp"
#include "Data.hpp"

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
    virtual const sf::Vector2f &getPosition() const = 0;
    virtual void setPosition(float x, float y) = 0;
    virtual void setPosition(const sf::Vector2f &pos) = 0;
    virtual void update() = 0;
    virtual int jumped() = 0;
};

class APlatform : public IPlatform
{
protected:
    sf::Sprite m_sprite{};
    std::unique_ptr<IBoost> m_boost = nullptr;
public:
    ~APlatform() override = default;
    sf::Sprite& getSprite() override
    {
        return m_sprite;
    };
    std::unique_ptr<IBoost> &getBoost() override
    {
        return m_boost;
    };
    const sf::Vector2f& getPosition() const override
    {
        return m_sprite.getPosition();
    }
    void setPosition(float x, float y) override
    {
        m_sprite.setPosition(x, y);
        if (m_boost)
            m_boost->getSprite().setPosition(x, y - m_boost->getSize().y);
    }
    void setPosition(const sf::Vector2f &pos) override
    {
        setPosition(pos.x, pos.y);
    }
};

class BoostedPlatform : public APlatform
{
public:
    BoostedPlatform()
    {
        std::uniform_int_distribution<std::mt19937::result_type> dist(0,50);
        auto rand = dist(Data::rng);
        if (rand == 0 or rand == 1)
            m_boost = std::make_unique<FederBoost>();
        else if (rand == 2)
            m_boost = std::make_unique<TrampolineBoost>();
    };
    ~BoostedPlatform() override = default;
};

class Platform final : public BoostedPlatform
{
public:
    Platform();
    ~Platform() override = default;
    void update() override;
    int jumped() override;
};

class HorizontalPlatform final : public BoostedPlatform
{
private:
    Direction m_direction = Direction::RIGHT;
public:
    HorizontalPlatform();
    ~HorizontalPlatform() override = default;
    void update() override;
    int jumped() override;
};

class VerticalPlatform final : public BoostedPlatform
{
private:
    Direction m_direction = Direction::DOWN;
    int m_distance = 0;
public:
    VerticalPlatform();
    ~VerticalPlatform() override = default;
    void update() override;
    int jumped() override;
};

class BrokenPlatform final : public APlatform
{
private:
    bool m_broken = false;
    size_t m_it = 0;
    size_t m_tick = 0;
public:
    BrokenPlatform();
    ~BrokenPlatform() override = default;
    void update() override;
    int jumped() override;
};

class ExplosivePlatform final : public APlatform
{
private:
    size_t m_it = 0;
    size_t m_tick = 0;
public:
    ExplosivePlatform();
    ~ExplosivePlatform() override = default;
    void update() override;
    int jumped() override;
};