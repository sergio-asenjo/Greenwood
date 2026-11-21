#ifndef RHELEMENTACTORNPC_H
#define RHELEMENTACTORNPC_H

#include "RHActorCommand.h"
#include "RHElementActorHumanCore.h"
#include "RHviewParameters.h"
#include <list>

class SBFile;
class SBGeoPoint2D;
class RHSequenceElement;
class RHElementActorHuman;
class RHActorTranslationSequenceCalls;
struct RHMalignityPosition;
class RHUnk00613e90;
class RHShadowPolygon;
class RHElementObject;
class RHStimulus;
class RHArtificialIntelligence;
class RHPath;
template <class T> struct RHArtificialIntelligenceValueList;

// SIZE 0x10
struct RHAnimalNoisePosition
{
    float m_x; // 0x00
    float m_y; // 0x04
    int m_8; // 0x08
    unsigned short m_c; // 0x0c
};

class RHDetectable
{
public:
    RHDetectable()
    {
        m_04 = 7;
        m_0a = 0;
        m_08 = 0;
        m_09 = 0;
        m_0c = 0;
        m_10 = 0;
    }
    ~RHDetectable() {}
    bool Serialize(SBFile &file);
    void *m_00;
    int m_04;
    char m_08;
    char m_09;
    char m_0a;
    char m_0b;
    char m_0c;
    char m_0d[3];
    int m_10;
};

struct RHNPCDetectableList : public std::list<RHDetectable>
{
    RHNPCDetectableList();
    ~RHNPCDetectableList();
    void ClearNodes();
    void Seek(int wanted);
    iterator m_cursor;
    bool m_dirty;
    char m_11[3];
    int m_index;
    bool m_searching;
    char m_19[3];
    int m_found;
    RHDetectable m_value;
};

// SIZE 0x1c
struct RHnoise
{
    float m_x;
    float m_y;
    int m_08;
    unsigned short m_0c;
    unsigned short m_0e;
    int m_10;
    unsigned short m_14;
    unsigned short m_16;
    unsigned short m_18;
    unsigned short m_1a;
};

class RHElementActorNPC : public RHElementActorHuman
{
public:
    virtual bool Serialize(SBFile &file);
    void Emit(SBFile &file);
    int FUN_00486790();
    void Translate(RHSequenceElement *element, RHcommand command);
    void GetTransitionFlags(RHSequenceElement *element, unsigned long &first, unsigned long &second, unsigned long &third);
    static void FUN_00486940(unsigned long first, unsigned long second, unsigned long third);
    void FUN_00486f30(unsigned char status);
    void FUN_00486f70();
    void FUN_00487aa0(void *target);
    void FUN_00487ad0(const RHMalignityPosition &position);
    void FUN_00487b70();
    void FUN_00487b90(const SBGeoBoundingBox2D &box, float zoom, unsigned long flags, int unused);
    void FUN_00487ce0();
    bool FUN_004887a0(int kind);
    void CleanUpDetectables(int kind);
    void FUN_00488a40(unsigned char index, unsigned short timer);
    bool HandleDetection(RHDetectable &value, bool visible, RHArtificialIntelligenceValueList<RHStimulus> &stimuli);
    void HandlePredetection(RHDetectable &value, unsigned short amount, RHArtificialIntelligenceValueList<RHStimulus> &stimuli);
    const RHElement *AIOpponent(const int *baseOffsets) const;
    RHArtificialIntelligence &Intelligence();
    RHPath &ActorPath();
    void Unk0048b4e0(int mode);
    void ClearCompletedSequence();
    void FUN_0048d050();
    void FUN_0048e420(void *actor);
    __forceinline RHArtificialIntelligence *Intelligence(int offset)
    {
        return reinterpret_cast<RHArtificialIntelligence *>(reinterpret_cast<char *>(&m_aiBaseOffsets) + offset);
    }
    __forceinline int CurrentAIState() const
    {
        return *reinterpret_cast<const int *>(
            reinterpret_cast<const char *>(&m_aiBaseOffsets) + m_aiBaseOffsets[1] + 0x14);
    }
    float ComputeVisibility(RHElementObject *object);
    float FUN_00489d00(const RHUnk00613e90 &offset);
    bool IsDetecting(RHUnk00613e90 &point, bool checkRange);
    void FUN_0048a650(unsigned char &red, unsigned char &green, unsigned char &blue);
    unsigned short FUN_0048a830();
    bool FUN_0048af40(const SBGeoPoint2D &point, RHElementActorHuman *pc, int focus);
    bool FUN_0048be40(void *context, unsigned flags, RHElementActorHuman *target);
    void *FUN_0048c380(RHElementActorHuman *target);
    void FUN_0048c4d0();
    static void FUN_0048c620(void *actor);
    static void FUN_0048c6a0(void *actor, unsigned mode);
    static void Noise(int type, RHAnimalNoisePosition &position, float radius, void *source);
    unsigned short FUN_0048cec0(const RHnoise *noise);
    bool FUN_0048d460(unsigned flags, RHActorTranslationSequenceCalls *sequence);
    void FUN_0048d990(unsigned short amount, void *source, bool force);
    void FUN_0048da80(RHSequenceElement *element);
    void FUN_0048ec70();
    void FUN_0048ed90(unsigned short state);
    int FUN_0048d510(class RHOrder *order);
    int FUN_0048efa0();
    static void SetUniversalFrameCounter(unsigned long &counter);
    enum
    {
        OffsetAI = 0x49c,
        OffsetRaw4a0 = 0x4a0,
        OffsetWord4c8 = 0x4c8,
        OffsetWord4ca = 0x4ca,
        OffsetWord4d0 = 0x4d0,
        OffsetPoint4d4 = 0x4d4,
        OffsetRaw4dc = 0x4dc,
        OffsetPointer4e4 = 0x4e4,
        OffsetWord4ec = 0x4ec,
        OffsetByte4ee = 0x4ee,
        OffsetInt4f0 = 0x4f0,
        OffsetByte4f4 = 0x4f4,
        OffsetWord4f6 = 0x4f6,
        OffsetWord4f8 = 0x4f8,
        OffsetWord4fa = 0x4fa,
        OffsetInt4fc = 0x4fc,
        OffsetPointer500 = 0x500,
        OffsetDetectableLists = 0x504,
        DetectableListStride = 0x34,
        OffsetDetectableWords = 0x63c,
        OffsetWord648 = 0x648,
        OffsetInt64c = 0x64c,
        OffsetByte652 = 0x652,
        OffsetRaw654 = 0x654,
        OffsetPointer6bc = 0x6bc,
        OffsetByte6e4 = 0x6e4,
        OffsetByte6e5 = 0x6e5,
        ObjectSize = 0x704
    };
    const int *m_aiBaseOffsets;
    char m_4a0[0x2c];
    RHShadowPolygon *m_4cc;
    char m_4d0[0x34];
    RHNPCDetectableList m_detectables[6];
    unsigned short m_detectableStrength[6];
    char m_648[0xc];
    RHviewParameters m_654;
    char m_6e4[0x20];
};

#endif
