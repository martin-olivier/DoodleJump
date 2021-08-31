#include "Boost.hpp"

// Feder Boost

FederBoost::FederBoost()
{
    m_size = {40, 60};
    m_travel = 1000;
    m_sprite.setTexture(Data::m_federBoostTexture);
    m_sound.setBuffer(Data::m_federSoundBuffer);
}

void FederBoost::action()
{
    m_sprite.setTexture(Data::m_federBoostUpTexture);
    m_sound.play();
}

// Trampoline Boost

TrampolineBoost::TrampolineBoost()
{
    m_size = {80, 35};
    m_travel = 2000;
    m_sprite.setTexture(Data::m_trampolineBoostTexture);
    m_sound.setBuffer(Data::m_trampolineSoundBuffer);
}

void TrampolineBoost::action()
{
    m_sprite.setTexture(Data::m_trampolineBoostUpTexture);
    m_sound.play();
}