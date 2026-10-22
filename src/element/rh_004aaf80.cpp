#include "SBNullstr.h"
#include "RHElement.h"
#include "../engine/RHEngineWidenedCalls.h"

extern float g_unk0x0067749c;

class RHSprite
{
public:
    int FUN_005b7fd0(float modulation, int progression);
};

void RHSerializeName(SBFile &file, const char *name);

class RHElementFXMasked : public RHElement
{
public:
    bool FUN_004aaf20();
    bool Serialize(SBFile &file);
    undefined m_a8[0x54];
    float m_fc;
    RHElement *m_100;
};

// FUNCTION: GAME 0x004aaf20
bool RHElementFXMasked::FUN_004aaf20()
{
    if (m_12 && (!m_100 || !*((char *)m_100 + 0xa8)))
    {
        float alpha = m_fc;
        if (alpha == g_unk0x0067749c)
            ((RHEngineWidenedCalls *)m_50)->FUN_005b7f60(0);
        else
            ((RHSprite *)m_50)->FUN_005b7fd0(alpha, 0);
    }
    return true;
}

// FUNCTION: GAME 0x004aaf80
bool RHElementFXMasked::Serialize(SBFile &file)
{
    // STRING: GAME 0x006aeaf4
    RHSerializeName(file, "RHElementFXMasked");
    file.Access((char *)this + 0xfc, 4);
    return RHElement::Serialize(file);
}
