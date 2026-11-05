#ifndef RHELEMENTMOBILECORE_H
#define RHELEMENTMOBILECORE_H

#include "Decomp.h"
#include "RHMobileVectorArray.h"
#include "RHEngineElementArray.h"

class SBFile;
class RHUnkTargetSprite;
class RHMobileElement;
class RHMobilePath;

// SIZE 0x260
class RHElementMobile
{
public:
    bool ExecuteMacroCommand();
    void InitializeFromMissionStream(SBFile &file);
    bool Serialize(SBFile &file);
    void CheckForLineCrossing();
    void FUN_004af0f0(int value);
    void FUN_004af170(void *value);
    void FUN_004abfe0();
    bool FUN_004ab600();
    void FUN_004ab720();
    void FUN_004ab7e0(float distance);
    void TranslateGeometry(const SBGeoVector2D &value);
    void FUN_004af210(class RHMobileEvent *event);
    class RHUnk0045aaf0 *FUN_004ac750(void *actor);
    bool FUN_004ac7c0(void *value, void *unused, int type);
    unsigned short Size() const { return (unsigned short)m_children.VolatileSize(); }
    void Emit(SBFile &file);

    undefined m_0[0x50];
    RHUnkTargetSprite *m_50;
    undefined m_54[0x58];
    RHEngineElementArray<RHMobileElement> m_children;
    undefined m_cc[0xbc];
    RHMobilePath *m_188;
    undefined m_18c[4];
    unsigned char *m_190;
    unsigned short m_194;
    undefined m_196[2];
    int m_198;
    float m_19c;
    float m_1a0;
    float m_1a4;
    undefined m_1a8[0x20];
    RHMobileVectorArray m_1c8;
    unsigned m_1ec;
    undefined m_1f0[4];
    SBGeoPoint2D m_1f4;
    RHMobileElement *m_1fc;
    undefined m_200[4];
    SBGeoPoint2D m_204;
    undefined m_20c[0xc];
    SBGeoPoint2D m_218;
    SBGeoPoint2D m_220;
    undefined m_228[0x30];
    undefined m_258[8];
};

#endif
