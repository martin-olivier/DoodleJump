#pragma once

#include <SFML/Audio.hpp>

class Sound
{
public:
    Sound() = default;
    explicit Sound(const std::string &path);
    void setSound(const std::string &path);
    void play(bool sound_settings);

    sf::SoundBuffer buffer{};
    sf::Sound sound{};
};