#include "Data.hpp"

void Data::load()
{
    const std::string fonts_path = "./resource/fonts/";
    const std::string sounds_path = "./resource/sounds/";
    const std::string sprites_path = "./resource/sprites/";

    loadAsset(rightTexture, sprites_path + "right.png");
    loadAsset(leftTexture, sprites_path + "left.png");
    loadAsset(platformTexture, sprites_path + "platform.png");
    loadAsset(horizontalPlatformTexture, sprites_path + "horizontal_platform.png");
    loadAsset(verticalPlatformTexture, sprites_path + "vertical_platform.png");
    loadAsset(voidPlatformTexture, sprites_path + "void_platform.png");
    loadAsset(backgroundTexture, sprites_path + "background.png");
    loadAsset(federBoostTexture, sprites_path + "feder.png");
    loadAsset(federBoostUpTexture, sprites_path + "feder_up.png");
    loadAsset(trampolineBoostTexture, sprites_path + "trampoline.png");
    loadAsset(trampolineBoostUpTexture, sprites_path + "trampoline_up.png");
    loadAsset(gameOverTexture, sprites_path + "game_over.png");
    loadAsset(playAgainTexture, sprites_path + "play_again.png");

    for (size_t i = 0; i < 4; i++)
        loadAsset(brokenPlatformTextures[i], sprites_path + "broken_platform" + std::to_string(i) + ".png");
    for (size_t i = 0; i < 3; i++)
        loadAsset(explosivePlatformTextures[i], sprites_path + "explosive_platform" + std::to_string(i) + ".png");

    loadAsset(font, fonts_path + "arial.ttf");

    loadAsset(platformBreakSoundBuffer, sounds_path + "platform_break.wav");
    loadAsset(platformExplosionSoundBuffer, sounds_path + "exploding_platform.wav");
    loadAsset(jumpSoundBuffer, sounds_path + "jump.wav");
    loadAsset(fallSoundBuffer, sounds_path + "fall.wav");
    loadAsset(federSoundBuffer, sounds_path + "feder.wav");
    loadAsset(trampolineSoundBuffer, sounds_path + "trampoline.wav");

    platformBreakSound.setBuffer(platformBreakSoundBuffer);
    platformExplosionSound.setBuffer(platformExplosionSoundBuffer);
}