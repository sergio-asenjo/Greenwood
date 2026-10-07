#ifndef RHELEMENTMOBILE_H
#define RHELEMENTMOBILE_H

#include "SB.h"
#include <new>

class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(const SBGeoPoint2D &other);
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    SBGeoPoint2D Unk005fc110(const SBGeoPoint2D &other) const;
    bool operator==(const SBGeoPoint2D &other) const;
    bool FUN_005fc0e0(const SBGeoPoint2D &other) const;
    float m_x;
    float m_y;
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

class RHUnk004af060
{
public:
    void Unk(int direction);
    void Unk(unsigned short direction);
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

struct RHMobilePath
{
    int m_0;
    RHMobileWaypoints *m_4;
    unsigned short Size() const { if (!m_4 || !m_4->m_4) return 0; return (unsigned short)(m_4->m_8 - m_4->m_4); }
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
};

class RHUnk0042fde0
{
public:
    SBGeoPoint2D FUN_0042fde0() const;
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

    // Partial offset view for the macro and crossing bodies, not a complete class layout.
    char m_0[0x50];
    RHUnkTargetSprite *m_50;
    char m_54[0x5c];
    RHMobileElement **m_b0;
    RHMobileElement **m_b4;
    char m_b8[0xd0];
    RHMobilePath *m_188;
    char m_18c[4];
    unsigned char *m_190;
    unsigned short m_194;
    char m_196[2];
    int m_198;
    float m_19c;
    float m_1a0;
    float m_1a4;
    char m_1a8[0x44];
    unsigned m_1ec;
    char m_1f0[0x68];
};

extern float g_unk0x00677488;
extern float g_unk0x006775d8;
extern bool g_mobileAssertDoubleBond;

#endif
