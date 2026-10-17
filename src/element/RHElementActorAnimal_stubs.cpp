#include "RHElementActorAnimal.h"

// Target 0x005883a0.

// Target 0x0048cca0.
void RHElementActorNPC::Noise(int, RHAnimalNoisePosition &, float, void *) {}

// FUNCTION: GAME 0x005fc4d0
RHUnk005fc3b0 &RHUnk005fc3b0::FUN_005fc4d0(float factor)
{
    m_x *= factor;
    m_y *= factor;
    return *this;
}

// Target 0x00607da0.
SBGeoBoundingBox2D &SBGeoBoundingBox2D::FUN_00607da0(const SBGeoBoundingBox2D &) { return *this; }

// FUNCTION: GAME 0x005fc7c0
void RHUnk005fc3b0::FUN_005fc7c0(float value)
{
    float factor = Unk005fc6a0(value);
    m_x /= factor;
    m_y /= factor;
}
