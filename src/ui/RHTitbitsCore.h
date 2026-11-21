#ifndef RHTITBITSCORE_H
#define RHTITBITSCORE_H
#include "RHSectorActorList.h"
#include "RHUnk00613e90.h"
#include "SBList.h"
#include "SBUIUnkSurface.h"
#include <string>

class SBFile;
class SBGeoBoundingBox2D;
class SBGeoPoint2D;
class RHElement;
class RHElementActor;
class RHElementActorPC;
class RHSprite;
class SBDrawManager;
class RHFrameHolder;
class SBFontUnk0061e840;
struct RHTitbit;
struct RHTitbitNode;

enum RHtitbitKind
{
};

struct RHTitbit
{
    int m_00;
    short m_04;
    short m_06;
    short m_08;
    short m_0a;
    RHElement *m_0c;
    int m_10;
    union
    {
        int m_14i;
        short m_14s;
    } m_u14;
    RHUnk00613e90 m_sub;
    int m_24;
    char m_28;
    char m_29;
    char m_2a;
    char m_2b;
    int m_2c;
};

class RHTitbitList : public SBList<RHTitbit>
{
public:
    typedef std::list<RHTitbit>::_Node Node;
    using SBList<RHTitbit>::_Head;
    using SBList<RHTitbit>::_Size;

    __forceinline void At(int index) { ((RHSectorActorList *)this)->Unk005c8e40(index); }
    RHTitbit &Item(int index);

    void Advance(int distance);
    void Seek(int i);

    void Resize(long n);                                   // 0x005c8d30
    void FUN_005c8bf0(RHTitbitList &other);
    void FUN_005c8980();
    void Sort()
    {
        FUN_005c8980();
        m_dirty = true;
    }
    void *Clear(void *out, RHTitbitNode *first, RHTitbitNode *last);
};

class RHTitbits
{
public:
    RHTitbits();
    ~RHTitbits();
    unsigned long LoadFromResource();
    unsigned long AddTitbit(const RHUnk00613e90 &position, unsigned short layer, RHtitbitKind kind,
        RHElement *element, unsigned short subtype, RHElementActorPC *pc, bool shadow, unsigned long id);
    bool Serialize(SBFile &file);
    bool RemoveQuickActionTitbitsFor(RHElementActorPC *actor, unsigned short action);
    bool FUN_005c3680();
    bool RemoveUnconsciousStarsIf(RHElementActor *actor);
    short FUN_005c7fb0(unsigned long id);
    void FUN_005c8120(int kind, RHElement *element);
    bool FUN_005c8340(int kind, RHElement *element);
    bool IsRunningForQA(unsigned long id);
    bool RenderText(const std::wstring &text, const SBGeoPoint2D &point) const;
    bool RenderText(const std::wstring &text, const SBGeoBoundingBox2D &box, unsigned long flags) const;

    void FUN_005c72a0();
    bool RefreshTitbitChain(RHElementActorPC *actor);
    void Update();
    void SetBlinking(RHElementActorPC *actor, unsigned short action, bool blinking);
    void ResetBlinking();

    void Emit(SBFile &file);

    short m_00;          // [0x00]
    char m_pad0[2];
    RHSprite *m_sprite;
    unsigned long m_surface;
    unsigned long m_mask;
    unsigned short m_counts[8];
    RHTitbitList m_list; // [0x20]
    SBDrawManager *m_draw;
    RHFrameHolder *m_bank;
    SBFontUnk0061e840 *m_font;
    SBFontUnk0061e840 *m_outline;
    SBUIUnkSurface m_80;
    unsigned short m_a0;
    char m_a2[2];
    unsigned long m_a4;  // [0xa4]
    float m_a8;          // [0xa8]
    int m_ac;            // [0xac]
};

#endif
