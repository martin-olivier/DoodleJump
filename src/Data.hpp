#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <array>
#include <random>

namespace Data {
    inline sf::Texture m_backgroundTexture{};
    inline sf::Texture m_rightTexture{};
    inline sf::Texture m_leftTexture{};
    inline sf::Texture m_platformTexture{};
    inline sf::Texture m_verticalPlatformTexture{};
    inline sf::Texture m_horizontalPlatformTexture{};
    inline sf::Texture m_federBoostTexture{};
    inline sf::Texture m_federBoostUpTexture{};
    inline sf::Texture m_trampolineBoostTexture{};
    inline sf::Texture m_trampolineBoostUpTexture{};
    inline sf::Texture m_gameOverTexture{};
    inline sf::Texture m_playAgainTexture{};
    inline std::array<sf::Texture, 4> m_brokenPlatformTextures{};

    inline sf::Font m_font{};

    inline sf::SoundBuffer m_jumpSoundBuffer{};
    inline sf::SoundBuffer m_fallSoundBuffer{};
    inline sf::SoundBuffer m_platformBreakSoundBuffer{};
    inline sf::SoundBuffer m_federSoundBuffer{};
    inline sf::SoundBuffer m_trampolineSoundBuffer{};

    inline std::random_device dev{};
    inline std::mt19937 rng(dev());

    void Load();
};