#pragma once

#include "Data.hpp"

class IBoost
{
public:
    virtual ~IBoost() = default;
    virtual sf::Sprite& getSprite() = 0;
    virtual const sf::Vector2f &getSize() const = 0;
    virtual int getTravel() const = 0;
    virtual void action() = 0;
};

class ABoost : public IBoost
{
protected:
    sf::Sprite m_sprite{};
    sf::Sound m_sound{};
    sf::Vector2f m_size{};
    int m_travel{};
public:
    ~ABoost() override = default;
    sf::Sprite& getSprite() override
    {
        return m_sprite;
    };
    const sf::Vector2f &getSize() const override
    {
        return m_size;
    }
    int getTravel() const override
    {
        return m_travel;
    };
};

class FederBoost final : public ABoost
{
public:
    FederBoost();
    ~FederBoost() override = default;
    void action() override;
};

class TrampolineBoost final : public ABoost
{
public:
    TrampolineBoost();
    ~TrampolineBoost() override = default;
    void action() override;
};