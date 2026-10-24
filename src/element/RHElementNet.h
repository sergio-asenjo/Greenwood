#ifndef RHELEMENTNET_H
#define RHELEMENTNET_H

#include "SB.h"
#include "RHEngine.h"
#include "RHProjectileLifetime.h"
#include "RHFastFindGeometry.h"
#include "RHRepulsivePoint.h"
#include <memory>

struct RHNetListStorage
{
    RHNetListStorage(const std::allocator<void *> &allocator = std::allocator<void *>())
        : m_00(allocator), m_04(BuyHead()), m_08(0), m_10(true)
    {
    }
    ~RHNetListStorage()
    {
        FUN_0044e8b0(RHScriptIter(m_04->next), end());
        operator delete(m_04);
        m_04 = 0;
        m_08 = 0;
    }
    static RHScriptNode *BuyHead()
    {
        RHScriptNode *head = (RHScriptNode *)operator new(sizeof(RHScriptNode));
        head->next = head;
        head->previous = head;
        return head;
    }

    std::allocator<void *> m_00;
    RHScriptNode *m_04;
    int m_08;
    RHScriptNode *m_0c;
    bool m_10;
    int m_14;

    RHScriptIter end() { return RHScriptIter(m_04); }
    RHScriptIter FUN_0044e8b0(RHScriptIter first, RHScriptIter last);
    RHScriptIter FUN_00424410(RHScriptIter position, void *const &value);
};

class __declspec(novtable) RHElementNet : public RHProjectileLifetime
{
public:
    RHElementNet(void *victim);
    ~RHElementNet();
    void *FUN_004b0860(unsigned flags);
    void FUN_004b1270();
    void FUN_004b1380(RHNetListStorage &points, RHNetListStorage &lines, void *actor);
    void FUN_004b1730();
    bool FUN_004b19d0();
    bool FUN_004b14a0(void *point, void *pc, int focus) const;
    virtual bool Serialize(SBFile &file);
    void Emit(SBFile &file);

    RHUnk00520ae0 m_15c;
    RHNetListStorage m_19c;
    char m_1b4[0x0c];
    int m_1c0;
    char m_1c4;
    char m_1c5;
};

#endif
