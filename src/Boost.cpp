#include "Boost.hpp"

// Feder Boost

FederBoost::FederBoost()
{
    m_size = {40, 60};
    m_travel = 1000;
    m_sprite.setTexture(Data::federBoostTexture);
    m_sound.setBuffer(Data::federSoundBuffer);
}

void FederBoost::action()
{
    m_sprite.setTexture(Data::federBoostUpTexture);
    m_sound.play();
}

// Trampoline Boost

TrampolineBoost::TrampolineBoost()
{
    m_size = {80, 35};
    m_travel = 2000;
    m_sprite.setTexture(Data::trampolineBoostTexture);
    m_sound.setBuffer(Data::trampolineSoundBuffer);
}

void TrampolineBoost::action()
{
    m_sprite.setTexture(Data::trampolineBoostUpTexture);
    m_sound.play();
}