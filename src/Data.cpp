#include "Data.hpp"

void Data::Load()
{
    if (!m_rightTexture.loadFromFile("resource/right.png"))
        throw std::exception();
    if (!m_leftTexture.loadFromFile("resource/left.png"))
        throw std::exception();
    if (!m_platformTexture.loadFromFile("resource/platform.png"))
        throw std::exception();
    if (!m_horizontalPlatformTexture.loadFromFile("resource/horizontal_platform.png"))
        throw std::exception();
    if (!m_verticalPlatformTexture.loadFromFile("resource/vertical_platform.png"))
        throw std::exception();
    if (!m_backgroundTexture.loadFromFile("resource/background.png"))
        throw std::exception();
    if (!m_gameOverTexture.loadFromFile("resource/game_over.png"))
        throw std::exception();
    if (!m_playAgainTexture.loadFromFile("resource/play_again.png"))
        throw std::exception();

    if (!m_brokenPlatformTextures[0].loadFromFile("resource/broken_platform0.png"))
        throw std::exception();
    if (!m_brokenPlatformTextures[1].loadFromFile("resource/broken_platform1.png"))
        throw std::exception();
    if (!m_brokenPlatformTextures[2].loadFromFile("resource/broken_platform2.png"))
        throw std::exception();
    if (!m_brokenPlatformTextures[3].loadFromFile("resource/broken_platform3.png"))
        throw std::exception();

    if (!m_font.loadFromFile("resource/arial.ttf"))
        throw std::exception();

    if (!m_platformBreakSoundBuffer.loadFromFile("resource/platform_break.wav"))
        throw std::exception();
    if (!m_jumpSoundBuffer.loadFromFile("resource/jump.wav"))
        throw std::exception();
    if (!m_fallSoundBuffer.loadFromFile("resource/fall.wav"))
        throw std::exception();
    if (!m_federSoundBuffer.loadFromFile("resource/feder.wav"))
        throw std::exception();
    if (!m_trampolineSoundBuffer.loadFromFile("resource/trampoline.wav"))
        throw std::exception();

    m_federBoostTexture.loadFromFile("resource/feder.png");
    m_federBoostUpTexture.loadFromFile("resource/feder_up.png");

    m_trampolineBoostTexture.loadFromFile("resource/trampoline.png");
    m_trampolineBoostUpTexture.loadFromFile("resource/trampoline_up.png");
}