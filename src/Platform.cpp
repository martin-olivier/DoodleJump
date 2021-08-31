#include "Platform.hpp"

// Platform

Platform::Platform()
{
    m_sprite.setTexture(Data::platformTexture);
}

void Platform::update()
{

}

int Platform::jumped()
{
    if (m_boost) {
        m_boost->action();
        return m_boost->getTravel();
    }
    return 250;
}

// Horizontal Platform

HorizontalPlatform::HorizontalPlatform()
{
    m_sprite.setTexture(Data::horizontalPlatformTexture);
}

void HorizontalPlatform::update()
{
    if (m_direction == Direction::RIGHT) {
        if (getPosition().x >= 526)
            m_direction = Direction::LEFT;
        else
            setPosition(getPosition().x + 3, getPosition().y);
    }
    else if (m_direction == Direction::LEFT) {
        if (getPosition().x <= 0)
            m_direction = Direction::RIGHT;
        else
            setPosition(getPosition().x - 3, getPosition().y);
    }
}

int HorizontalPlatform::jumped()
{
    if (m_boost) {
        m_boost->action();
        return m_boost->getTravel();
    }
    return 250;
}

// Vertical Platform

VerticalPlatform::VerticalPlatform()
{
    m_sprite.setTexture(Data::verticalPlatformTexture);
};

void VerticalPlatform::update()
{
    if (m_direction == Direction::DOWN) {
        if (m_distance >= 150)
            m_direction = Direction::UP;
        else {
            setPosition(getPosition().x, getPosition().y + 2);
            m_distance += 2;
        }
    }
    else if (m_direction == Direction::UP) {
        if (m_distance <= 0)
            m_direction = Direction::DOWN;
        else {
            setPosition(getPosition().x, getPosition().y - 2);
            m_distance -= 2;
        }
    }
}

int VerticalPlatform::jumped()
{
    if (m_boost) {
        m_boost->action();
        return m_boost->getTravel();
    }
    return 250;
}

// Broken Platform

BrokenPlatform::BrokenPlatform()
{
    m_sprite.setTexture(Data::brokenPlatformTextures[0]);
}

void BrokenPlatform::update()
{
    if (!m_broken)
        return;
    m_tick++;
    setPosition(getPosition().x, getPosition().y + 10);
    if (m_tick % 5 == 0 and m_it < 3) {
        m_it = m_tick / 5;
        m_sprite.setTexture(Data::brokenPlatformTextures[m_it]);
    }
}

int BrokenPlatform::jumped()
{
    if (!m_broken)
        Data::platformBreakSound.play();
    m_broken = true;
    return 0;
}

// Explosive Platform

ExplosivePlatform::ExplosivePlatform()
{
    m_sprite.setTexture(Data::explosivePlatformTextures[0]);
}

void ExplosivePlatform::update()
{
    if (m_it == 0)
        return;
    m_tick++;
    if (m_tick == 50) {
        m_it = 2;
        m_sprite.setTexture(Data::explosivePlatformTextures[m_it]);
        Data::platformExplosionSound.play();
    }
    if (m_tick >= 60)
        m_sprite.setTexture(Data::voidPlatformTexture);
}

int ExplosivePlatform::jumped()
{
    if (m_it == 2)
        return 0;
    if (m_it == 0) {
        m_it = 1;
        m_sprite.setTexture(Data::explosivePlatformTextures[m_it]);
    }
    return 250;
}
