#include "Tile.hpp"

Tile::Tile(const std::string &path)
{
    setTexture(path);
}

Tile::Tile(const Tile& a)
{
    setTexture(a.m_path);
}

Tile& Tile::operator=(const Tile &a)
{
    if (&a == this)
        return *this;
    setTexture(a.m_path);
    return *this;
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}

void Tile::setTexture(const std::string &path)
{
    if (path.empty())
        return;
    m_path = path;
    if (!m_texture.loadFromFile(path))
        throw std::exception();
    m_texture.setSmooth(true);
    m_sprite.setTexture(m_texture, true);
}

void Tile::setPosition(float x, float y)
{
    m_sprite.setPosition(x, y);
}

const sf::Vector2f &Tile::getPosition()
{
    return m_sprite.getPosition();
}
