#ifndef RH_ARTIFICIAL_INTELLIGENCE_CORE_H
#define RH_ARTIFICIAL_INTELLIGENCE_CORE_H

class SBFile;
class SBGeoPoint2D;
class RHUnk005fc3b0;
class RHArtificialIntelligenceActor;
class RHArtificialIntelligenceList;
struct RHArtificialIntelligencePosition;
struct RHUnk00571160Position;

class RHArtificialIntelligence
{
public:
    virtual void V00(int value) = 0;
    virtual void V04(int value) = 0;
    virtual bool V08(SBFile &file) = 0;
    virtual void V0c() = 0;
    virtual void V10(int first, int second) = 0;
    virtual void V14() = 0;
    virtual void V18() = 0;
    virtual void V1c() = 0;
    virtual void V20() = 0;
    virtual void V24() = 0;
    virtual bool V28() = 0;
    virtual void V2c() = 0;
    virtual void V30() = 0;
    virtual void V34() = 0;
    virtual void V38() = 0;
    virtual void V3c(int value) = 0;
    virtual void V40(unsigned short first, unsigned short second, unsigned short third) = 0;
    bool InitState();
    void Unk00416710(unsigned value);
    unsigned short Unk0041a420();
    void FUN_0041a490();
    void Unk00486f60();
    static bool SerializeAllAI(SBFile &file);
    static bool SerializeListOfPointersToActorsNPC(RHArtificialIntelligenceList &list, SBFile &file);
    static bool SerializeListOfPointersToHumans(RHArtificialIntelligenceList &list, SBFile &file);
    static bool SerializeListOfPointersToObjects(RHArtificialIntelligenceList &list, SBFile &file);
    static bool SerializePosition(RHArtificialIntelligencePosition &position, SBFile &file);
    void Emit(SBFile &file, RHArtificialIntelligencePosition &position);
    void Unk00410010(bool mode);
    bool Unk00414be0(SBFile &file);
    bool Unk00418600(unsigned short path);
    void *FUN_00417ed0(SBGeoPoint2D *position, bool active);
    void FUN_00417580();
    void Unk00418c40(int remark, unsigned flags);
    void Unk00410600();
    void FUN_004121a0();
    void FUN_00411a00(unsigned flags);
    bool Unk00412c80(void *waypoint, unsigned short flags);
    bool Unk00412f40(RHUnk005fc3b0 *direction, int mode);
    bool Unk00412f70(unsigned short value, int mode);
    bool Unk00412240(const RHUnk00571160Position &position, unsigned short flags, float length);
    bool Unk00419cc0();
    void Unk0041a960(unsigned short direction);
    void Unk00422b70(int property, int value);
    void Unk004195f0(unsigned short flags);
    bool Unk00419b20(int remark);
    void Unk00419970(int remark, int time, int flags);
    unsigned char Unk00419c50();
    unsigned char Unk00419c80();
    void Unk0041ab10(unsigned short direction);

    RHArtificialIntelligenceActor *m_actor;
    char m_08[0x20];
    int m_initialAction;
    char m_2c[0x143];
    char m_16f;
    char m_170;
    char m_171[2];
    char m_173;
};

#endif
