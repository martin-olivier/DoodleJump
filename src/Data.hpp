#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <array>
#include <random>
#include <exception>

namespace Data {
    class MissingAsset : public std::exception {
    private:
        const std::string m_error{};
    public:
        explicit MissingAsset(const std::string &path) : m_error("missing asset : " + path) {}
        ~MissingAsset() override = default;
        [[nodiscard]] inline const char *what() const noexcept override {return m_error.c_str();}
    };

    inline sf::Texture backgroundTexture{};
    inline sf::Texture rightTexture{};
    inline sf::Texture leftTexture{};
    inline sf::Texture platformTexture{};
    inline sf::Texture verticalPlatformTexture{};
    inline sf::Texture horizontalPlatformTexture{};
    inline sf::Texture federBoostTexture{};
    inline sf::Texture federBoostUpTexture{};
    inline sf::Texture trampolineBoostTexture{};
    inline sf::Texture trampolineBoostUpTexture{};
    inline sf::Texture gameOverTexture{};
    inline sf::Texture playAgainTexture{};
    inline std::array<sf::Texture, 4> brokenPlatformTextures{};

    inline sf::Font font{};

    inline sf::SoundBuffer jumpSoundBuffer{};
    inline sf::SoundBuffer fallSoundBuffer{};
    inline sf::SoundBuffer platformBreakSoundBuffer{};
    inline sf::SoundBuffer federSoundBuffer{};
    inline sf::SoundBuffer trampolineSoundBuffer{};

    inline std::random_device dev{};
    inline std::mt19937 rng(dev());

    void load();

    template<typename T>
    void loadAsset(T &asset, const std::string &path)
    {
        if (!asset.loadFromFile(path))
            throw MissingAsset(path);
    }
};