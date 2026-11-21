#include "SBNullstr.h"
#include "RHElementFXMasked.h"
#include "RHElementMobileCore.h"
#include "RHSpriteCore.h"
#include "RHspriteRenderingInfoCore.h"
#include "RHFrameHolder.h"
#include "RHEngine.h"
#include "RHMessenger.h"
#include "SBDrawManagerCore.h"
#include "../engine/RHEngineWidenedCalls.h"


RHMessenger *RHUnk00546050();

// FUNCTION: GAME 0x004aacb0
void *RHElementFXMasked::Refresh(unsigned long surface, float scale, const SBGeoBoundingBox2D &box, unsigned long)
{
    if (g_pEngine->ShowMobileGeometry())
        return 0;
    if (!m_12)
        return 0;

    RHspriteRenderingInfo info;
    SBGeoBoundingBox2D source;
    SBGeoBoundingBox2D destination;
    if (m_100 && !m_100->m_12)
        return 0;
    RHUnk0045aaf0 *result;
    unsigned short frame = m_50->FUN_005bb5f0();
    if (frame)
    {
        m_14.FUN_0045abf0(frame, FUN_00462920(), 9, 0);
        result = &m_14;
    }
    else
        result = 0;
    if (m_50->FUN_005b9b60(box, scale))
    {
        info.m_surface = m_54;
        info.m_05 = RHUnk00546050()->SpriteMaskMode();
        info.m_masks = 1;
        m_50->CreateTargetSprite(info);
        if (m_50->FUN_005ba130(box, scale, source, destination))
        {
            switch (m_a8)
            {
            default:
                static_cast<SBDrawManager *>(m_60)->FUN_005e6440(m_54, &source, surface, &destination, 1);
                break;
            case 1:
                if (m_8e == 1)
                    static_cast<SBDrawManager *>(m_60)->BlitAlphaKeying(m_54, &source, surface, &destination,
                        m_90, static_cast<const RHFrameHolder *>(m_68)->BlitOpacity(), 1);
                else
                    static_cast<SBDrawManager *>(m_60)->FUN_005e6440(m_54, &source, surface, &destination, 1);
                break;
            }
        }
    }
    return result;
}

// FUNCTION: GAME 0x004aaf20
char RHElementFXMasked::FUN_004b9f40()
{
    if (m_12 && (!m_100 || !m_100->m_a8))
    {
        float alpha = m_fc;
        if (alpha == 1.0f)
            ((RHEngineWidenedCalls *)m_50)->FUN_005b7f60(0);
        else
            m_50->FUN_005b7fd0(alpha, 0);
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
