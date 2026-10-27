#ifndef RHTITBITSCORE_H
#define RHTITBITSCORE_H
#include "RHSectorActorList.h"
#include <string>

class SBFile;
class SBGeoBoundingBox2D;
class SBGeoPoint2D;
class RHElement;
class RHElementActor;
class RHElementActorPC;
struct RHTitbit;
struct RHTitbitNode;

class RHTitbitList
{
public:
    int m_00;                // [0x00]
    RHTitbitNode *m_head;    // [0x04]
    int m_count;             // [0x08]
    RHTitbitNode *m_cur;     // [0x0c]
    char m_valid;            // [0x10]
    int m_index;             // [0x14]

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
        m_valid = 1;
    }
    void Clear(void *out, RHTitbitNode *first, RHTitbitNode *last); // 0x0044e8b0
};

class RHTitbits
{
public:
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
    void SetBlinking(RHElementActorPC *actor, unsigned short action, bool blinking);
    void ResetBlinking();

    void Emit(SBFile &file);

    short m_00;          // [0x00]
    char m_pad0[0x1e];   // [0x02, 0x20): opaque; keeps the list at +0x20
    RHTitbitList m_list; // [0x20]
    char m_pad1[0x6c];   // [0x38, 0xa4): opaque
    unsigned long m_a4;  // [0xa4]
    float m_a8;          // [0xa8]
    int m_ac;            // [0xac]
};

#endif
