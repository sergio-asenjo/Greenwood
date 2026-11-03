#ifndef RH_GAME_INPUT_TRANSLATOR_H
#define RH_GAME_INPUT_TRANSLATOR_H

#ifndef SBGEO_BOUNDINGBOX2D_VIEW
#include "SBGeoBoundingBox2DCore.h"
#endif
#include "RHUnk004e4500.h"
#include "RHGameInputSegment.h"

class SBGeoPoint2D;
class SBInputKeyboardState;

class RHGameInputTranslator
{
public:
    RHGameInputTranslator();
    void TranslateMouseInput(SBGeoPoint2D &point, short wheel);
    bool TranslateKeyboardInput(SBInputKeyboardState &state, unsigned long flags);
    void ResetState();
    void ClearDeadZone();
    void AddToDeadZone(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
    bool IsInDeadZone(const SBGeoPoint2D &point) const;
    void ReflectActiveKeyConfig();
    void DeityCall();
    static RHGameInputTranslator *mpInstance;

    unsigned char m_previousKeys[0x100]; // 0x000
    unsigned char m_100[0xc]; // 0x100
    SBGeoBoundingBox2D m_bounds; // 0x10c
    RHUnk004e4500 m_deadZone; // 0x120
    unsigned short m_keys[0x25]; // 0x14c
    unsigned char m_196[3]; // 0x196
};

#endif
