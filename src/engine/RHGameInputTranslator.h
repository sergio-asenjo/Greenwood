#ifndef RH_GAME_INPUT_TRANSLATOR_H
#define RH_GAME_INPUT_TRANSLATOR_H

class SBGeoPoint2D;
class SBInputKeyboardState;

class RHGameInputSegment
{
public:
    void FUN_004611c0();
    bool FUN_0060a880(const SBGeoPoint2D &point) const;
    unsigned char m_00[0x10]; // 0x00
};

class RHGameInputTranslator
{
public:
    RHGameInputTranslator();
    void TranslateMouseInput(SBGeoPoint2D &point, short wheel);
    bool TranslateKeyboardInput(SBInputKeyboardState &state, unsigned long time);
    void ResetState();
    void ClearDeadZone();
    void AddToDeadZone(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
    bool IsInDeadZone(const SBGeoPoint2D &point) const;
    void ReflectActiveKeyConfig();
    void DeityCall();
    static RHGameInputTranslator *mpInstance;

    unsigned char m_previousKeys[0x100]; // 0x000
    unsigned char m_100[0x24]; // 0x100
    RHGameInputSegment *m_first; // 0x124
    RHGameInputSegment *m_last; // 0x128
    RHGameInputSegment *m_end; // 0x12c
    unsigned char m_130[4]; // 0x130
    bool m_deadZoneChanged; // 0x134
    unsigned char m_135[0x17]; // 0x135
    unsigned short m_keys[0x25]; // 0x14c
    unsigned char m_196[3]; // 0x196
};

#endif
