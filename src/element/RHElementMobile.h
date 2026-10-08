#ifndef RHELEMENTMOBILE_H
#define RHELEMENTMOBILE_H

#include "SB.h"
#include "Decomp.h"
#include <new>

// SIZE 0x08
class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(float x, float y);
    SBGeoPoint2D(const SBGeoPoint2D &other);
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    SBGeoPoint2D Unk005fc110(const SBGeoPoint2D &other) const;
    bool operator==(const SBGeoPoint2D &other) const;
    bool FUN_005fc0e0(const SBGeoPoint2D &other) const;
    SBGeoPoint2D &FUN_005fc1e0(const SBGeoPoint2D &other);
    void FUN_005fc390(const SBGeoPoint2D &other) throw();
    float m_x; // 0x00
    float m_y; // 0x04
};

// SIZE 0x08
class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D();
    SBGeoVector2D(const SBGeoPoint2D &other);
    ~SBGeoVector2D() {}
};

class RHUnk005fc3b0 : public SBGeoPoint2D
{
public:
    RHUnk005fc3b0();
    ~RHUnk005fc3b0() {}
    float Unk005fc6a0(float value);
    RHUnk005fc3b0 &FUN_005fc430(const SBGeoPoint2D &other);
    float FUN_005fc680(const RHUnk005fc3b0 &other, float value) const;
};

class RHUnk005bd5b0
{
public:
    bool Unk(bool value);
};

class RHUnk004af1d0
{
public:
    void Unk(bool value);
};

class RHUnkTargetSprite
{
public:
    bool FUN_005b76e0(unsigned index, unsigned row);
    char m_0[0x24];
    SBGeoPoint2D m_24;
    char m_2c[0x14];
    SBGeoPoint2D m_40;
    char m_48[0x96];
    unsigned short m_de;
    char m_e0[0xc];
    void *m_ec;
};

struct RHMobileElement
{
    char m_0[0x50];
    RHUnkTargetSprite *m_50;
    char m_54[0x10];
    short m_64;
    short m_66;
    char m_68[0x94];
    float m_fc;
};

struct RHMobileWaypoints
{
    int m_0;
    RHMobileElement **m_4;
    RHMobileElement **m_8;
    unsigned short Size() const { if (!m_4) return 0; return (unsigned short)(m_8 - m_4); }
};

// SIZE 0x08
struct RHMobilePath
{
    undefined4 m_0; // 0x00
    RHMobileWaypoints *m_4; // 0x04
    SBGeoVector2D FUN_004ae380() const;
    unsigned short Size() const { return m_4 == 0 ? 0 : m_4->m_4 == 0 ? 0 : (unsigned short)(m_4->m_8 - m_4->m_4); }
};

class RHMobileSegment
{
public:
    RHMobileSegment(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
    ~RHMobileSegment();
    SBGeoPoint2D m_0;
    SBGeoPoint2D m_8;
};

class RHMobileGrid
{
public:
    void FUN_004ed370(void *lines, unsigned short layer, const RHMobileSegment &segment, unsigned mask);
};

class RHMobilePosition
{
public:
    void FUN_0055fc20(bool value);
    void FUN_0055fa20(void *value);
    void SetFieldD6(int value) { *(unsigned short *)((char *)this + 0xd6) = (unsigned short)value; }
};

class RHUnk0042fde0
{
public:
    SBGeoPoint2D FUN_0042fde0() const;
    SBGeoPoint2D m_0;
    SBGeoPoint2D m_8;
};

class RHMobileUnk0051fd90
{
public:
    void FUN_0051fd90(float first, float second);
    char m_0[0x24];
    float m_24;
    float m_28;
    float m_2c;
    float m_30;
};

class RHMobileUnk00520c50
{
public:
    void FUN_00520c50(float first, float second);
    char m_0[0x24];
    float m_24;
    float m_28;
    float m_2c;
    float m_30;
};

class RHMobileUnk006091b0
{
public:
    RHMobileUnk006091b0 &FUN_006091b0(const SBGeoPoint2D &value);
    SBGeoPoint2D m_0;
    SBGeoPoint2D m_8;
};

class RHMobileUnk0060a820
{
public:
    RHMobileUnk0060a820 &FUN_0060a820(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
    void FUN_006158b0(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
};

class RHMobileUnk00611360
{
public:
    void FUN_00611360(const SBGeoPoint2D &value);
    unsigned short Size() const { SBGeoPoint2D *first = *(SBGeoPoint2D *volatile *)&m_4; if (!first) return 0; return (unsigned short)(m_8 - first); }
    int m_0;
    SBGeoPoint2D *m_4;
    SBGeoPoint2D *m_8;
};

class RHMobileUnk004b06f0
{
public:
    RHUnk005fc3b0 *FUN_004b06f0(RHUnk005fc3b0 *first, RHUnk005fc3b0 *last);
    int m_0;
    RHUnk005fc3b0 *m_4;
    RHUnk005fc3b0 *m_8;
};

class RHMobileUnk00607da0
{
public:
    RHMobileUnk00607da0 &FUN_00607da0(const RHMobileUnk00607da0 &other);
    void FUN_00607990(const RHMobileUnk00607da0 &other);
    char m_0[0x14];
};

class RHMobileUnk006100e0 : public SBGeoPoint2D
{
public:
    ~RHMobileUnk006100e0();
    void FUN_00578c50();
    char m_8[8];
};

class RHSoundSource;
class RHMobileUnk005b4fa0
{
public:
    int FUN_005b4fa0(RHSoundSource *value);
    char m_0[8];
    RHSoundSource **m_8;
    RHSoundSource **m_c;
    char m_10[4];
    RHSoundSource **m_14;
    bool m_18;
    bool m_19;
    char m_1a[2];
    int m_1c;
    RHSoundSource *m_20;
};

// SIZE 0x1c
struct RHMobileNode005504d0
{
    RHMobileNode005504d0 *next; // 0x00
    RHMobileNode005504d0 *previous; // 0x04
    undefined m_8[0x14]; // 0x08
};

// SIZE 0x20
class RHMobileUnk005504d0
{
public:
    RHMobileUnk005504d0();
    bool m_0; // 0x00
    bool m_1; // 0x01
    bool m_2; // 0x02
    undefined m_3; // 0x03
    undefined4 m_4; // 0x04
    unsigned short m_8; // 0x08
    undefined m_a[2]; // 0x0a
    undefined m_c; // 0x0c
    undefined m_d[3]; // 0x0d
    RHMobileNode005504d0 *m_10; // 0x10
    unsigned m_14; // 0x14
    undefined4 m_18; // 0x18
    bool m_1c; // 0x1c
};

class RHSoundPendingData
{
public:
    void FUN_0052c5a0();
};

// SIZE 0x24
struct RHMobileSoundNode
{
    RHMobileSoundNode *next; // 0x00
    RHMobileSoundNode *previous; // 0x04
    int m_8; // 0x08
    undefined m_c[0x10]; // 0x0c
    void *m_1c; // 0x1c
    int m_20; // 0x20
};

// SIZE 0x254
class RHSound
{
public:
    void FUN_005a7110(RHSoundSource *source);
    void FUN_005a87f0(RHSoundSource *source);
    void FUN_005a8420(int channel);
    void FUN_005a8810(void *value);
    undefined m_0[0x24c]; // 0x00
    RHMobileSoundNode *m_24c; // 0x24c
    unsigned m_250; // 0x250
};

// SIZE 0x14
class SBGeoBoundingBox2D
{
public:
    void Unk00607dc0(const SBGeoPoint2D &point);
    void FUN_00607e90(const SBGeoBoundingBox2D &other);
    SBGeoPoint2D m_0; // 0x00
    SBGeoPoint2D m_8; // 0x08
    undefined m_10; // 0x10
};

class RHElevationLine
{
public:
    char m_0[4];
    SBGeoPoint2D m_4;
    SBGeoPoint2D m_c;
    unsigned m_14;
    char m_18[0xc];
    void *m_24;
    void *m_28;
};

class RHElement
{
public:
    virtual bool Serialize(SBFile &file);
    void CrossElevationLine(RHElevationLine *line);
};

struct RHScriptNode
{
    RHScriptNode *next;
    RHScriptNode *previous;
    RHElevationLine *data;
};

struct RHScriptIter
{
    RHScriptNode *node;
    RHScriptIter(RHScriptNode *value) : node(value) {}
};

class RHUnk0046eb30
{
public:
    RHScriptIter erase(RHScriptIter position);
};

void *FUN_0048f170(void *value);

class RHMobileLineStorage
{
public:
    ~RHMobileLineStorage()
    {
        RHScriptNode *sentinel = head;
        RHScriptNode *current = sentinel->next;
        while (current != sentinel)
        {
            RHScriptNode *node = current;
            current = current->next;
            node->previous->next = node->next;
            node->next->previous = node->previous;
            ::operator delete(node);
            --count;
        }
        ::operator delete(head);
        head = 0;
        count = 0;
    }
    int m_0;
    RHScriptNode *head;
    unsigned count;
};

class RHUnk0040f060 : public RHMobileLineStorage
{
public:
    RHUnk0040f060();
    void GoTo(int index);
    ~RHUnk0040f060()
    {
        RHScriptNode *sentinel = head;
        RHScriptNode *current = sentinel->next;
        while (current != sentinel)
        {
            RHScriptNode *node = current;
            current = current->next;
            FUN_0048f170(node);
            node->previous->next = node->next;
            node->next->previous = node->previous;
            ::operator delete(node);
            --count;
        }
    }
    RHScriptNode *cursor;
    bool dirty;
    char m_11[3];
    int index;
    char m_18[0xc];
};

// SIZE 0x258
class RHElementMobile
{
public:
    bool ExecuteMacroCommand();
    void InitializeFromMissionStream(SBFile &file);
    bool Serialize(SBFile &file);
    void CheckForLineCrossing();
    void FUN_004af0f0(int value);
    void FUN_004af170(void *value);
    unsigned short Size() const { RHMobileElement **first = *(RHMobileElement **volatile *)&m_b0; if (!first) return 0; return (unsigned short)(m_b4 - first); }
    void Emit(SBFile &file);

    undefined m_0[0x50]; // 0x00
    RHUnkTargetSprite *m_50; // 0x50
    undefined m_54[0x5c]; // 0x54
    RHMobileElement **m_b0; // 0xb0
    RHMobileElement **m_b4; // 0xb4
    undefined m_b8[0xd0]; // 0xb8
    RHMobilePath *m_188; // 0x188
    undefined m_18c[4]; // 0x18c
    unsigned char *m_190; // 0x190
    unsigned short m_194; // 0x194
    undefined m_196[2]; // 0x196
    int m_198; // 0x198
    float m_19c; // 0x19c
    float m_1a0; // 0x1a0
    float m_1a4; // 0x1a4
    undefined m_1a8[0x44]; // 0x1a8
    unsigned m_1ec; // 0x1ec
    undefined m_1f0[0x68]; // 0x1f0
};

// SIZE 0x258
class RHUnk004af060 : public RHElementMobile
{
public:
    void Unk(int direction);
};

extern float g_unk0x00677488;
extern float g_unk0x006775d8;
extern bool g_mobileAssertDoubleBond;
extern float g_unk0x0067749c;

#endif
