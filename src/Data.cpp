#include "Data.hpp"

void Data::load()
{
    loadAsset(rightTexture, "resource/right.png");
    loadAsset(leftTexture, "resource/left.png");
    loadAsset(platformTexture, "resource/platform.png");
    loadAsset(horizontalPlatformTexture, "resource/horizontal_platform.png");
    loadAsset(verticalPlatformTexture, "resource/vertical_platform.png");
    loadAsset(backgroundTexture, "resource/background.png");
    loadAsset(federBoostTexture, "resource/feder.png");
    loadAsset(federBoostUpTexture, "resource/feder_up.png");
    loadAsset(trampolineBoostTexture, "resource/trampoline.png");
    loadAsset(trampolineBoostUpTexture, "resource/trampoline_up.png");
    loadAsset(gameOverTexture, "resource/game_over.png");
    loadAsset(playAgainTexture, "resource/play_again.png");

    for (size_t i = 0; i < 4; i++)
        loadAsset(brokenPlatformTextures[i], "resource/broken_platform" + std::to_string(i) + ".png");

    loadAsset(font, "resource/arial.ttf");

    loadAsset(platformBreakSoundBuffer, "resource/platform_break.wav");
    loadAsset(jumpSoundBuffer, "resource/jump.wav");
    loadAsset(fallSoundBuffer, "resource/fall.wav");
    loadAsset(federSoundBuffer, "resource/feder.wav");
    loadAsset(trampolineSoundBuffer, "resource/trampoline.wav");
}