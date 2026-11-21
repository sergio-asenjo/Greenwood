#ifndef RHELEMENTMOBILECORE_H
#define RHELEMENTMOBILECORE_H

#include "Decomp.h"
#include "RHElementCore.h"
#include "RHSectorCore.h"
#include "RHMobileVectorArray.h"
#include "RHEngineElementArray.h"
#include "RHTransientPointerList.h"

class SBFile;
class RHSoundSource;
class RHMobileEvent;
class RHUnkTargetSprite;
struct RHMobileElement;
class RHPath;
class RHWaypoint;
class RHUnk005a3450;
class RHUnk00520ae0;
class RHMobileUnk0051fd10;

// VTABLE: GAME 0x00678570
// SIZE 0x270
class RHElementMobile : public RHElement
{
public:
    RHElementMobile();
    virtual ~RHElementMobile();
    virtual bool FUN_004b23c0(const void *first, void *second, int third);
    virtual void *FUN_004b29c0(void *value);
    virtual bool FUN_004b26a0(const SBGeoPoint2D *first, unsigned short second, RHElementActorPC *selectedPC) { return false; }
    virtual void *Refresh(unsigned long surface, float value, const SBGeoBoundingBox2D &box, unsigned long flags);
    virtual char FUN_004b9f40();
    virtual void v14(SBFile &file) {}
    virtual void InitializeFromMissionStream(SBFile &file);
    virtual bool Serialize(SBFile &file);
    virtual void v21(unsigned value);
    bool ExecuteMacroCommand();
    void CheckForLineCrossing();
    void FUN_004af060(int direction);
    void FUN_004af0f0(int value);
    void FUN_004af170(void *value);
    void FUN_004af1d0(bool value);
    void FUN_004abfe0();
    void FUN_004ab720();
    void FUN_004ab7e0(float distance);
    void TranslateGeometry(const SBGeoVector2D &value);
    void InitializeSound();
    void Emit(SBFile &file);
    unsigned short Size() const { return (unsigned short)m_children.VolatileSize(); }

    bool m_a8;
    undefined m_a9[3];
    RHEngineElementArray<RHMobileElement> m_children;
    RHEngineElementArray<RHUnk005a3450> m_cc;
    RHSector m_ec;
    RHEngineElementArray<RHUnk00520ae0> m_144;
    RHEngineElementArray<RHMobileUnk0051fd10> m_164;
    unsigned short m_184;
    undefined m_186[2];
    RHPath *m_188;
    RHWaypoint *m_18c;
    unsigned char *m_190;
    unsigned short m_194;
    undefined m_196[2];
    int m_198;
    float m_19c;
    float m_1a0;
    float m_1a4;
    bool m_1a8;
    undefined m_1a9[3];
    SBGeoBoundingBox2D m_1ac;
    bool m_1c0;
    undefined m_1c1[7];
    RHMobileVectorArray m_1c8;
    unsigned m_1ec;
    bool m_1f0;
    bool m_1f1;
    undefined m_1f2[2];
    SBGeoPoint2D m_1f4;
    RHMobileElement *m_1fc;
    bool m_200;
    undefined m_201[3];
    RHUnk00613e90 m_204;
    int m_210;
    int m_214;
    SBGeoPoint2D m_218;
    SBGeoPoint2D m_220;
    SBGeoPoint2D m_228;
    SBGeoPoint2D m_230;
    bool m_238;
    undefined m_239[3];
    RHSoundSource *m_23c;
    RHSoundSource *m_240;
    RHSoundSource *m_244;
    bool m_248;
    undefined m_249[3];
    RHTransientPointerList<void> m_24c;
};

#endif
