#pragma once

class IBoost
{
public:
    virtual ~IBoost() = default;
    virtual sf::Sprite& getSprite() = 0;
    virtual const sf::Vector2f &getSize() const = 0;
    virtual int getTravel() = 0;
    virtual void action() = 0;
};

class FederBoost final : public IBoost
{
private:
    sf::Sprite m_sprite{};
    sf::Texture m_texture;
    sf::Texture m_textureUp;
    Sound m_sound;
    int m_travel = 1000;
    sf::Vector2f m_size = {40, 60};
public:
    FederBoost()
    {
        m_texture.loadFromFile("resource/feder.png");
        m_textureUp.loadFromFile("resource/feder_up.png");
        m_sprite.setTexture(m_texture);
        m_sound.setSound("resource/feder.wav");
    }
    ~FederBoost() override = default;
    sf::Sprite& getSprite() override
    {
        return m_sprite;
    };
    const sf::Vector2f &getSize() const override
    {
        return m_size;
    }
    int getTravel() override
    {
        return m_travel;
    };
    void action() override
    {
        m_sprite.setTexture(m_textureUp);
        m_sound.play(true);
    }
};

class TrampolineBoost final : public IBoost
{
private:
    sf::Sprite m_sprite{};
    sf::Texture m_texture;
    sf::Texture m_textureUp;
    Sound m_sound;
    int m_travel = 2000;
    sf::Vector2f m_size = {80, 35};
public:
    TrampolineBoost()
    {
        m_texture.loadFromFile("resource/trampoline.png");
        m_textureUp.loadFromFile("resource/trampoline_up.png");
        m_sprite.setTexture(m_texture);
        m_sound.setSound("resource/trampoline.wav");
    }
    ~TrampolineBoost() override = default;
    sf::Sprite& getSprite() override
    {
        return m_sprite;
    };
    const sf::Vector2f &getSize() const override
    {
        return m_size;
    }
    int getTravel() override
    {
        return m_travel;
    };
    void action() override
    {
        m_sprite.setTexture(m_textureUp);
        m_sound.play(true);
    }
};