#include "Sound.hpp"

Sound::Sound(const std::string &path)
{
    if (!buffer.loadFromFile(path))
        throw std::exception();
    sound.setBuffer(buffer);
}

void Sound::setSound(const std::string &path)
{
    if (!buffer.loadFromFile(path))
        throw std::exception();
    sound.setBuffer(buffer);
}

void Sound::play(bool sound_settings)
{
    if (sound_settings)
        sound.play();
}