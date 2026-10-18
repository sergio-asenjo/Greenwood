#include "SBNullstr.h"
#include "RHConsole.h"
#include <string.h>
#include <ctype.h>
#include <new>
#include <stdio.h>
#include <math.h>
#include <iterator>
#include "RHElementActorPC.h"
#include "SBGeoPoint2D.h"

typedef int RHConsole_size_assert[(sizeof(RHConsole) == 0x688) ? 1 : -1];

class RHEngine
{
public:
    void FUN_004e2390(void *actor);
};
class RHMessenger;
class RHUnk00452030
{
public:
    int Get(int);
};
extern RHEngine *g_pEngine;
extern RHUnk00452030 *g_unk0x6c07fc;
RHMessenger *RHUnk00546050();

class RHCampaign
{
public:
    void FUN_00456e60();
};

class RHUnk004a5230
{
public:
    void FUN_004a5230(bool, bool);
};

class RHScriptBatchCalls
{
public:
    void Unk004e3220(int);
    void Unk0050ed40();
    void Unk004520e0(int, int);
    void Unk004d9330(void *, bool);
    void Unk0058a940(void *, int, void *);
    bool Unk00456cb0(int);
};

#include "RHSequenceGenericCalls.h"

#include "RHSequenceTimedCalls.h"

class RHScript
{
public:
    static void AddPCToGang(void *);
};

struct RHConsoleProfile
{
    char m_00[0x14];
    std::string m_name;
    char m_24[0x11];
    char m_35;
};

class RHSectorActorList
{
public:
    void Unk005c8e40(int);
};

struct RHConsoleListNode
{
    RHConsoleListNode *next;
    RHConsoleListNode *previous;
    RHElementActorPC *value;
};

struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &, int, std::bidirectional_iterator_tag);

struct RHConsoleListIterator : std::iterator<std::bidirectional_iterator_tag, RHElementActorPC *>
{
    RHConsoleListNode *node;
    RHConsoleListIterator(RHConsoleListNode *value = 0) : node(value) {}
    RHConsoleListIterator &operator=(const RHConsoleListIterator &other)
    {
        node = other.node;
        return *this;
    }
    RHConsoleListIterator &assign(RHConsoleListNode *value)
    {
        *(RHConsoleListNode *volatile *)&node = value;
        return *this;
    }
    RHConsoleListIterator &operator++() { node = node->next; return *this; }
    RHConsoleListIterator &operator--() { node = node->previous; return *this; }
    RHElementActorPC *&operator*() { return node->value; }
};

struct RHScriptIter
{
    RHConsoleListNode *node;
};

class RHUnk0046eb30
{
public:
    RHScriptIter FUN_0046eb80();
};

struct RHConsolePCList
{
    unsigned m_allocator;
    RHConsoleListNode *m_head;
    unsigned m_count;
    RHConsoleListIterator m_cursor;
    char m_dirty;
    char m_11[3];
    int m_index;
    RHElementActorPC *get(int index)
    {
        ((RHSectorActorList *)this)->Unk005c8e40(index);
        return *m_cursor;
    }
    RHConsoleListIterator begin()
    {
        RHConsoleListNode *sentinel = m_head;
        RHConsoleListNode *first = *(RHConsoleListNode *volatile *)&sentinel->next;
        return RHConsoleListIterator(first);
    }
    RHConsoleListIterator end()
    {
        RHConsoleListNode *sentinel = *(RHConsoleListNode *volatile *)&m_head;
        return RHConsoleListIterator(sentinel);
    }
    RHElementActorPC *getInline(int wanted)
    {
        int size = m_count;
        if (m_dirty)
        {
            if (wanted <= (size + 1) / 2)
            {
                m_cursor = begin();
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)m_cursor, wanted, category);
            }
            else
            {
                m_cursor = end();
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)m_cursor, wanted - size, category);
            }
            m_dirty = 0;
            m_index = wanted;
        }
        else
        {
            int previous = m_index;
            if (wanted != previous)
            {
                if (wanted < previous)
                {
                    if (wanted < (previous + 1) / 2)
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)m_cursor.assign(
                            *(RHConsoleListNode *volatile *)&m_head->next), wanted, category);
                    }
                    else
                    {
                        int distance = wanted - previous;
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)m_cursor, distance, category);
                    }
                }
                else if (wanted < (size + previous) / 2)
                    std::advance(m_cursor, wanted - previous);
                else
                {
                    m_cursor = end();
                    std::advance(m_cursor, wanted - size);
                }
                m_index = wanted;
            }
        }
        return *m_cursor;
    }
    RHElementActorPC *getFirst()
    {
        int size = m_count;
        if (m_dirty)
        {
            if (0 <= (size + 1) / 2)
            {
                RHConsoleListNode *head = m_head;
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)(m_cursor = RHConsoleListIterator(head->next)), 0, category);
            }
            else
            {
                m_cursor = end();
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)m_cursor, -size, category);
            }
            m_dirty = 0;
            m_index = 0;
        }
        else
        {
            int previous = m_index;
            if (previous != 0)
            {
                if (0 < previous)
                {
                    if (0 < (previous + 1) / 2)
                    {
                        typedef RHConsoleListIterator (RHUnk0046eb30::*Begin)();
                        RHConsoleListIterator &cursor = m_cursor;
                        cursor = (((RHUnk0046eb30 *)this)->*(Begin)&RHUnk0046eb30::FUN_0046eb80)();
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)m_cursor, 0, category);
                    }
                    else
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)m_cursor, -previous, category);
                    }
                }
                else if (0 < (previous + size) / 2)
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)m_cursor, -previous, category);
                }
                else
                {
                    m_cursor = end();
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)m_cursor, -size, category);
                }
                m_index = 0;
            }
        }
        return *m_cursor;
    }
};

class RHUnk6c1040;
extern RHUnk6c1040 *g_unk0x6c1040;
extern char g_unk0x6c0560[4];

class RHUnk00450b60
{
public:
    void Unk(int, int);
};

class RHGameActorView
{
public:
    bool FUN_004936e0();
};

class RHUnk0048a970;
extern RHUnk0048a970 *g_unk0x6c0b3c;
int FUN_0064324d(const char *, const char *, ...);
RHElementActorPC *FUN_005e19e0(char *);

class RHActorPCTemplateCalls
{
public:
    void FUN_00493660(int);
};

class RHEngineReinforcementCalls
{
public:
    void FUN_004936a0(int);
};

template<class T>
T &RHConsoleField(void *object, unsigned offset)
{
    return *(T *)((char *)object + offset);
}

class RHConsoleActor
{
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(int);
    virtual void v16(); virtual void v17(int); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
    virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
    virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
    virtual void v52(); virtual void v53(int, bool, bool); virtual void v54();
    virtual void v55(int, bool, bool);
    virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
    virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
    virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
    virtual void v68(); virtual void v69(); virtual void v70(); virtual void v71();
    virtual void v72(); virtual void v73(); virtual void v74(); virtual void v75();
    virtual int v76();
};


struct RHConsoleActorArray
{
    unsigned m_00;
    RHConsoleActor **m_first;
    RHConsoleActor **m_last;
    unsigned size() const { return m_first == 0 ? 0 : m_last - m_first; }
};

struct RHConsoleActorSearch : RHConsoleActorArray
{
    unsigned m_0c;
    RHConsoleActor **m_cursor;
    char m_14;
    char m_15;
    short m_16;
    int m_index;
    RHConsoleActor *m_value;

    int find(RHConsoleActor *value)
    {
        m_14 = 0;
        m_value = value;
        int count = size();
        m_cursor = m_first;
        m_15 = 1;
        int index = 0;
        for (; index < count; ++index, ++m_cursor)
            if (*m_cursor == value)
                break;
        return m_index = index < count ? index : -1;
    }
};

struct RHConsoleActorActive
{
    char m_00[0x12];
    bool m_active;
    char m_13[0x49c - 0x13];
    int *m_vbtable;
};

inline RHConsoleActor *RHConsoleHumanBase(RHConsoleActor *actor)
{
    return (RHConsoleActor *)((char *)actor + 0x49c + RHConsoleField<int>(RHConsoleField<void *>(actor, 0x49c), 4));
}

struct RHConsoleHumanFlags
{
    char m_00[0x174];
    char m_flags;
    void clear(unsigned char mask) { m_flags &= ~mask; }
};

extern double g_unk0x00677670;

// GLOBAL: GAME 0x00677668
double g_consoleBlockExponent = 5.0;

// GLOBAL: GAME 0x006c080c
RHConsoleActor *g_consoleHonolulu;

// GLOBAL: GAME 0x006c0714
char g_consoleInvisible;
// GLOBAL: GAME 0x006c077c
char g_consoleAttributes;
// GLOBAL: GAME 0x006c07dc
char g_consoleBabylon;
// GLOBAL: GAME 0x006c07dd
char g_consoleFrozen;

// FUNCTION: GAME 0x0045bc50
void RHConsole::FUN_0045bc50(char *destination, const char *source)
{
    for (int index = strlen(source); index >= 0; --index)
        destination[index] = source[index];
}

// FUNCTION: GAME 0x0045c360
char **RHConsole::FUN_0045c360(signed char *line, unsigned &count)
{
    unsigned spaces = 0;
    if (*line)
    {
        signed char *cursor = line;
        do
        {
            if (*cursor == ' ')
            {
                ++spaces;
                *cursor = 0;
            }
            else
                *cursor = toupper(*cursor);
            ++cursor;
        } while (*cursor);
    }
    unsigned remaining = spaces + 1;
    count = remaining;
    char **arguments = (char **)operator new(remaining * sizeof(char *));
    arguments[0] = (char *)line;
    unsigned index = 0;
    if (--remaining)
    {
        char **output = arguments + 1;
        do
        {
            if (!line[index])
            {
                *output++ = (char *)line + index + 1;
                --remaining;
            }
            ++index;
        } while (remaining);
    }
    return arguments;
}

// FUNCTION: GAME 0x0045cc20
void RHConsole::FUN_0045cc20(unsigned, char **)
{
    g_consoleInvisible ^= 1;
    if (g_consoleInvisible)
    {
        // STRING: GAME 0x006acff8
        FUN_005ede40(m_engine->m_draw, "Invisibility On.");
    }
    else
    {
        // STRING: GAME 0x006acfe4
        FUN_005ede40(m_engine->m_draw, "Invisibility Off.");
    }
}

// FUNCTION: GAME 0x0045cc60
void RHConsole::FUN_0045cc60(unsigned, char **)
{
    m_engine->m_4b32 = !m_engine->m_4b32;
    if (m_engine->m_4b32)
    {
        // STRING: GAME 0x006ad028
        FUN_005ede40(m_engine->m_draw, "Elevation display enabled.");
    }
    else
    {
        // STRING: GAME 0x006ad00c
        FUN_005ede40(m_engine->m_draw, "Elevation display disabled.");
    }
}

void RHConsole::FUN_0045bff0() {}

// FUNCTION: GAME 0x0045ccb0
void RHConsole::FUN_0045ccb0(unsigned, char **)
{
    FUN_0045bff0();
}

// FUNCTION: GAME 0x0045ccc0
void RHConsole::FUN_0045ccc0(const std::string &name)
{
    for (unsigned index = 0;
         index < (unsigned char)RHConsoleField<RHConsoleActorArray>(g_pEngine, 0x4938).size();
         ++index)
    {
        RHConsoleActor *actor = RHConsoleField<RHConsoleActorArray>(g_pEngine, 0x4938).m_first[(unsigned char)index];
        RHConsoleProfile *profile = RHConsoleField<RHConsoleProfile *>(actor, 0x5fc);
        if (profile->m_name.compare(name) == 0)
        {
            if (!profile->m_35 || !((RHScriptBatchCalls *)g_unk0x6c07fc)->Unk00456cb0((int)profile))
                RHScript::AddPCToGang(actor);
            break;
        }
    }
}

// FUNCTION: GAME 0x0045d580
void RHConsole::FUN_0045d580(unsigned, char **)
{
    void *mission = RHConsoleField<void *>(g_unk0x6c07fc, 0x178);
    RHConsoleField<char>(RHConsoleField<void *>(mission, 0), 0x60) = 9;
    // STRING: GAME 0x006ad09c
    FUN_005edae0(m_engine->m_draw, "Campaign won !");
    RHScriptBatchCalls *engine = (RHScriptBatchCalls *)m_engine;
    RHConsoleField<char>(this, 0x684) = 1;
    engine->Unk004e3220(1);
}

// FUNCTION: GAME 0x0045d5c0
void RHConsole::FUN_0045d5c0(unsigned, char **)
{
    // STRING: GAME 0x006ad0ac
    FUN_005edae0(m_engine->m_draw, "Mission lost !");
    m_engine->m_4a53 = 1;
}

// FUNCTION: GAME 0x0045d5f0
void RHConsole::FUN_0045d5f0(unsigned, char **)
{
    if (!m_engine->m_4a55)
    {
        // STRING: GAME 0x006ad0d0
        FUN_005edae0(m_engine->m_draw, "Seek points displayed");
        m_engine->m_4a55 = 1;
    }
    else
    {
        // STRING: GAME 0x006ad0bc
        FUN_005edae0(m_engine->m_draw, "Seek points hidden");
        m_engine->m_4a55 = 0;
    }
}

// Parked: the pre-destructor EH-state store is omitted once the state-zero register matches.
// STUB: GAME 0x0045d650
void RHConsole::FUN_0045d650(unsigned, char **)
{
    unsigned soldierCount = 0;
    unsigned index = 0;
    SBGeoPoint2D point;
    RHUnk005ef320 *draw = g_unk0x6c11d0;
    typedef void (__cdecl *Message)(RHUnk005ef320 *, const char *);
    Message output = (Message)(void (__cdecl *)(RHUnk005ef320 *, const char *, int))&FUN_005edae0;
    // STRING: GAME 0x006ad0fc
    output(draw, "Nuking ...");
    for (; index < RHConsoleField<RHConsoleActorArray>(m_engine, 0x48d8).size(); ++index)
    {
        RHConsoleActor *actor = RHConsoleField<RHConsoleActorArray>(m_engine, 0x48d8).m_first[index];
        unsigned flags = RHConsoleField<volatile unsigned>(actor, 4);
        flags &= 0x1f;
        if ((unsigned char)flags == 0x14)
        {
            RHUnk005861c0 *element = new RHUnk005861c0(1, 0x26, actor, 1000, 1000);
            SBGeoPoint2D *position = (SBGeoPoint2D *)((char *)RHConsoleField<void *>(actor, 0x50) + 0x24);
            typedef SBGeoPoint2D &(SBGeoPoint2D::*Assign)(const SBGeoPoint2D &);
            Assign assign = &SBGeoPoint2D::operator=;
            (point.*assign)(*position);
            ++soldierCount;
            ((RHScriptBatchCalls *)((char *)m_engine + 0x43f8))->Unk0058a940(g_unk0x6c0560, 0, element);
        }
    }
    // STRING: GAME 0x006ad0e8
    FUN_005edae0(draw, "Nuked %i soldiers", (unsigned short)soldierCount);
}

// FUNCTION: GAME 0x0045d780
void RHConsole::FUN_0045d780(unsigned, char **)
{
    RHUnk005ef320 *draw = g_unk0x6c11d0;
    m_engine->m_4b3b = !m_engine->m_4b3b;
    if (m_engine->m_4b3b)
    {
        // STRING: GAME 0x006ad128
        FUN_005edae0(draw, "Free shadow polygon enabled");
    }
    else
    {
        // STRING: GAME 0x006ad108
        FUN_005edae0(draw, "Free shadow polygon disabled");
    }
}

// FUNCTION: GAME 0x0045d7d0
void RHConsole::FUN_0045d7d0(unsigned, char **)
{
    // STRING: GAME 0x006ad144
    FUN_005edae0(g_unk0x6c11d0, "Wake up !");
    for (unsigned index = 0;
         index < RHConsoleField<RHConsoleActorArray>(m_engine, 0x48d8).size();
         ++index)
    {
        RHConsoleActor *actor = RHConsoleField<RHConsoleActorArray>(m_engine, 0x48d8).m_first[index];
        if ((RHConsoleField<volatile unsigned>(actor, 4) & 0xf) == 4 && RHConsoleField<char>(actor, 0x1ce))
            actor->v55(31, false, false);
    }
}

// FUNCTION: GAME 0x0045d840
void RHConsole::FUN_0045d840(unsigned, char **)
{
    RHEngine *engine = g_pEngine;
    for (unsigned index = 0;
         index < (unsigned short)RHConsoleField<RHConsoleActorArray>(engine, 0x4cc8).size();
         ++index)
        RHConsoleField<char>(RHConsoleField<RHConsoleActorArray>(engine, 0x4cc8).m_first[(unsigned short)index], 0x496) = 1;
    // STRING: GAME 0x006ad150
    FUN_005edae0(m_engine->m_draw, "Friends invulnerable");
}

// FUNCTION: GAME 0x0045d8b0
void RHConsole::FUN_0045d8b0(unsigned, char **)
{
    RHEngine *engine = g_pEngine;
    for (unsigned index = 0;
         index < (unsigned short)RHConsoleField<RHConsoleActorArray>(engine, 0x4ce8).size();
         ++index)
        RHConsoleField<char>(RHConsoleField<RHConsoleActorArray>(engine, 0x4ce8).m_first[(unsigned short)index], 0x496) = 1;
    // STRING: GAME 0x006ad168
    FUN_005edae0(m_engine->m_draw, "Foes invulnerable");
}

// Parked: redundant null guard is eliminated and the activity load moves before cleanup.
// STUB: GAME 0x0045d920
void RHConsole::FUN_0045d920(unsigned, char **)
{
    RHConsoleActor *actor = RHConsoleField<RHConsoleActor *>(m_engine, 0xd4);
    if (actor && (RHConsoleField<volatile unsigned>(actor, 4) & 0xf) == 4)
    {
        // STRING: GAME 0x006ad298
        FUN_005edae0(m_engine->m_draw, "Honolulu");
        if (actor && RHConsoleField<char>(actor, 0x12))
        {
            g_consoleHonolulu = RHConsoleField<RHConsoleActor *>(m_engine, 0xd4);
            RHConsoleField<char>(g_consoleHonolulu, 0x12) = 0;
            RHConsoleHumanBase(g_consoleHonolulu)->v15(4);
            ((RHScriptBatchCalls *)m_engine)->Unk004d9330(0, false);
            // STRING: GAME 0x006ad280
            FUN_005edae0(m_engine->m_draw, "Bye, I'm on holiday.");
        }
        else if (g_consoleHonolulu && !RHConsoleField<char>(g_consoleHonolulu, 0x12))
        {
            RHConsoleField<char>(g_consoleHonolulu, 0x12) = 1;
            ((RHConsoleHumanFlags *)RHConsoleHumanBase(g_consoleHonolulu))->clear(4);
            // STRING: GAME 0x006ad274
            FUN_005edae0(m_engine->m_draw, "I'm back!");
        }
        else
        {
            // STRING: GAME 0x006ad228
            FUN_005edae0(m_engine->m_draw, "Cheat couldn't be performed. There are two possibilities to do this cheat:");
            // STRING: GAME 0x006ad1dc
            FUN_005edae0(m_engine->m_draw, "(1) Enable a view cone, then use this cheat to send this guy to Honolulu");
            // STRING: GAME 0x006ad17c
            FUN_005edae0(m_engine->m_draw, "(2) If (1) already done: Disable view cone, use this cheat to get last guy back from Honolulu.");
        }
    }
}

// FUNCTION: GAME 0x0045da50
void RHConsole::FUN_0045da50(unsigned, char **)
{
    // STRING: GAME 0x006ad2f0
    FUN_005edae0(m_engine->m_draw, "Last man standing");
    if (RHConsoleField<RHConsoleActor *>(m_engine, 0xd4))
    {
        unsigned short count = RHConsoleField<RHConsoleActorArray>(g_pEngine, 0x4958).size();
        for (unsigned short index = 0; index < count; ++index)
        {
            RHConsoleActor *actor = RHConsoleField<RHConsoleActorArray>(g_pEngine, 0x4958).m_first[index];
            if (actor != RHConsoleField<RHConsoleActor *>(m_engine, 0xd4))
            {
                RHConsoleActorActive *view = (RHConsoleActorActive *)actor;
                view->m_active = false;
                ((RHConsoleActor *)((char *)&view->m_vbtable + view->m_vbtable[1]))->v15(4);
            }
        }
        // STRING: GAME 0x006ad2e0
        FUN_005edae0(m_engine->m_draw, "Lonely hero...");
    }
    else
    {
        // STRING: GAME 0x006ad2a4
        FUN_005edae0(m_engine->m_draw, "Please enable view cone of a NPC before using this command.");
    }
}

// FUNCTION: GAME 0x0045db20
void RHConsole::FUN_0045db20(unsigned, char **)
{
    // STRING: GAME 0x006ad340
    FUN_005edae0(m_engine->m_draw, "Dies irae");
    if (m_engine->FUN_004db7a0())
    {
        // STRING: GAME 0x006ad318
        FUN_005ede40(m_engine->m_draw, "Mine is the vengeance, says the Lord !");
    }
    else
    {
        // STRING: GAME 0x006ad304
        FUN_005ede40(m_engine->m_draw, "The Lord pardons...");
    }
}

// FUNCTION: GAME 0x0045db80
void RHConsole::FUN_0045db80(unsigned, char **)
{
    // STRING: GAME 0x006ad438
    FUN_005edae0(m_engine->m_draw, "noise");
    RHConsoleEngine *engine = m_engine;
    engine->m_4b34 ^= 1;
    if (engine->m_4b34)
    {
        // STRING: GAME 0x006ad420
        FUN_005edae0(m_engine->m_draw, "Noise display enabled.");
        // STRING: GAME 0x006ad408
        FUN_005edae0(m_engine->m_draw, "  White circles: Noises");
        // STRING: GAME 0x006ad3c0
        FUN_005edae0(m_engine->m_draw, "  Black circles: Deafness because of covering noises, explosions etc...");
        // STRING: GAME 0x006ad364
        FUN_005edae0(m_engine->m_draw, "  A NPC can hear a nois when he resp. his black circle is entirely within a white circle.");
    }
    else
    {
        // STRING: GAME 0x006ad34c
        FUN_005edae0(m_engine->m_draw, "Noise display disabled.");
    }
}

// FUNCTION: GAME 0x0045dc20
void RHConsole::FUN_0045dc20(unsigned, char **)
{
    // STRING: GAME 0x006ad480
    FUN_005edae0(m_engine->m_draw, "Zone");
    RHConsoleEngine *engine = m_engine;
    engine->m_4be4 ^= 1;
    if (engine->m_4be4)
    {
        // STRING: GAME 0x006ad460
        FUN_005edae0(m_engine->m_draw, "Script zone display enabled.");
    }
    else
    {
        // STRING: GAME 0x006ad440
        FUN_005edae0(m_engine->m_draw, "Script zone display disabled.");
    }
}

// FUNCTION: GAME 0x0045dc80
void RHConsole::FUN_0045dc80(unsigned, char **)
{
    // STRING: GAME 0x006ad4ac
    FUN_005edae0(m_engine->m_draw, "freeze");
    g_consoleFrozen ^= 1;
    if (g_consoleFrozen)
    {
        // STRING: GAME 0x006ad49c
        FUN_005edae0(m_engine->m_draw, "Enemies frozen.");
    }
    else
    {
        // STRING: GAME 0x006ad488
        FUN_005edae0(m_engine->m_draw, "Enemies defrosted.");
    }
}

// FUNCTION: GAME 0x0045dce0
void RHConsole::FUN_0045dce0(unsigned, char **)
{
    // STRING: GAME 0x006ad4e4
    FUN_005edae0(m_engine->m_draw, "Pamela Anderson");
    g_unk0x006c07de ^= 1;
    if (g_unk0x006c07de)
    {
        // STRING: GAME 0x006ad4cc
        FUN_005edae0(m_engine->m_draw, "Soldiers are stupid !");
    }
    else
    {
        // STRING: GAME 0x006ad4b4
        FUN_005edae0(m_engine->m_draw, "Soldiers are smart !");
    }
}

// FUNCTION: GAME 0x0045dd40
void RHConsole::FUN_0045dd40(unsigned, char **)
{
    for (unsigned index = 0;
         index < RHConsoleField<RHConsoleActorArray>(m_engine, 0x48d8).size();
         ++index)
    {
        RHConsoleActor *actor = RHConsoleField<RHConsoleActorArray>(m_engine, 0x48d8).m_first[index];
        if ((RHConsoleField<volatile unsigned>(actor, 4) & 0x1f) == 0x14)
            ((RHUnk004a5230 *)actor)->FUN_004a5230(true, false);
    }
}

// Parked: actor/flag registers and final message receiver differ.
// STUB: GAME 0x0045dd90
void RHConsole::FUN_0045dd90(unsigned, char **)
{
    for (unsigned index = 0;
         index < RHConsoleField<RHConsoleActorArray>(m_engine, 0x48d8).size();
         ++index)
    {
        RHConsoleActor *actor = RHConsoleField<RHConsoleActorArray>(m_engine, 0x48d8).m_first[index];
        if ((RHConsoleField<volatile unsigned>(actor, 4) & 0xf) == 0xc)
        {
            RHConsoleSequenceElement *element = new RHConsoleSequenceElement(1, 0x26, actor, 0, 100, 0);
            ((RHScriptBatchCalls *)g_unk0x6c1040)->Unk0058a940(g_unk0x6c0560, 0, element);
        }
    }
    // STRING: GAME 0x006ad4f4
    FUN_005ede40(m_engine->m_draw, "Sweet dreams !");
}

// FUNCTION: GAME 0x0045de60
void RHConsole::FUN_0045de60(unsigned, char **)
{
    RHConsoleBlockMap before;
    RHConsoleBlockMap after;
    char buffer[128];
    RHConsoleField<RHConsoleBlockAllocator *>(m_engine, 0x42f0)->FUN_00506070(&before);
    int merges = ((RHConsoleBlockAllocator *)((char *)RHConsoleField<void *>(m_engine, 0x42f0) + 0xc0))->FUN_00506620();
    RHConsoleField<RHConsoleBlockAllocator *>(m_engine, 0x42f0)->FUN_00506070(&after);
    // STRING: GAME 0x006ad510
    FUN_005ede40(m_engine->m_draw, "Free Blocks map after optimisation (%d merge)", merges);
    int size = (int)pow(g_unk0x00677670, g_consoleBlockExponent);
    typedef void (__cdecl *Message)(RHUnk005ef320 *, const char *);
    Message output = (Message)&FUN_005ede40;
    for (int index = 0; index < 17; ++index)
    {
        // STRING: GAME 0x006ad504
        sprintf(buffer, "%05d: %d", size, after.m_counts[index] - before.m_counts[index]);
        output(m_engine->m_draw, buffer);
        size += size;
    }
}

// FUNCTION: GAME 0x0045e240
void RHConsole::FUN_0045e240(unsigned, char **)
{
    m_engine->m_4b38 = !m_engine->m_4b38;
    if (m_engine->m_4b38)
    {
        // STRING: GAME 0x006ad77c
        FUN_005ede40(m_engine->m_draw, "Railroads displayed.");
    }
    else
    {
        // STRING: GAME 0x006ad768
        FUN_005ede40(m_engine->m_draw, "Railroads hidden.");
    }
}

// FUNCTION: GAME 0x0045e290
void RHConsole::FUN_0045e290(unsigned, char **)
{
    m_engine->m_4b36 = !m_engine->m_4b36;
    if (m_engine->m_4b36)
    {
        // STRING: GAME 0x006ad7ac
        FUN_005ede40(m_engine->m_draw, "3D-obstacles displayed.");
    }
    else
    {
        // STRING: GAME 0x006ad794
        FUN_005ede40(m_engine->m_draw, "3D-obstacles hidden.");
    }
}

// FUNCTION: GAME 0x0045e2e0
void RHConsole::FUN_0045e2e0(unsigned, char **)
{
    unsigned count = (unsigned short)RHConsoleField<RHConsoleActorArray>(g_pEngine, 0x4958).size();
    for (unsigned index = 0; index < count; ++index)
    {
        RHConsoleActor **actors = RHConsoleField<RHConsoleActorArray>(g_pEngine, 0x4958).m_first;
        RHConsoleActor *actor = actors[(unsigned short)index];
        if ((RHConsoleField<volatile unsigned>(actor, 4) & 0x1f) == 0x14 && actor->v76() == 1)
        {
            actor->v55(100, false, false);
            actor->v17(3);
            RHUnk00584d60 *element = new RHUnk00584d60(1, 0xa1, actor);
            ((RHScriptBatchCalls *)g_unk0x6c1040)->Unk0058a940(g_unk0x6c0560, 0, element);
        }
    }
    // STRING: GAME 0x006ad7c4
    FUN_005ede40(m_engine->m_draw, "NPCs knocked out !");
}

// FUNCTION: GAME 0x0045e400
void RHConsole::FUN_0045e400(unsigned, char **)
{
    m_engine->m_4b37 = !m_engine->m_4b37;
    if (m_engine->m_4b37)
    {
        // STRING: GAME 0x006ad7f4
        FUN_005ede40(m_engine->m_draw, "Projection areas displayed.");
    }
    else
    {
        // STRING: GAME 0x006ad7d8
        FUN_005ede40(m_engine->m_draw, "Projection areas hidden.");
    }
}

// FUNCTION: GAME 0x0045e450
void RHConsole::FUN_0045e450(unsigned, char **)
{
    RHConsoleEngine *engine = m_engine;
    char enabled = engine->m_4b2e;
    engine->m_4b30 = 0;
    engine->m_4b2e = !enabled;
    if (m_engine->m_4b2e)
    {
        // STRING: GAME 0x006ad820
        FUN_005ede40(m_engine->m_draw, "The seven bridges of Koenigsberg.");
    }
    else
    {
        // STRING: GAME 0x006ad810
        FUN_005ede40(m_engine->m_draw, "Graph hidden.");
    }
}

// FUNCTION: GAME 0x0045e4b0
void RHConsole::FUN_0045e4b0(unsigned, char **)
{
    m_engine->m_4b2d = !m_engine->m_4b2d;
    m_engine->m_4b2c = !m_engine->m_4b2c;
    if (m_engine->m_4b2d)
    {
        // STRING: GAME 0x006ad860
        FUN_005ede40(m_engine->m_draw, "Motion obstacles displayed.");
    }
    else
    {
        // STRING: GAME 0x006ad844
        FUN_005ede40(m_engine->m_draw, "Motion obstacles hidden.");
    }
}

// FUNCTION: GAME 0x0045e527
void RHConsole::FUN_0045e527(unsigned, char **)
{
}

// FUNCTION: GAME 0x0045e530
void RHConsole::FUN_0045e530(unsigned count, char **arguments)
{
    // STRING: GAME 0x006ad8c0
    if (count > 1 && strcmp(arguments[1], "BROTHER") == 0)
    {
        m_engine->m_4b33 = !m_engine->m_4b33;
        if (m_engine->m_4b33)
        {
            // STRING: GAME 0x006ad8a8
            FUN_005ede40(m_engine->m_draw, "Actor infos displayed !");
        }
        else
        {
            // STRING: GAME 0x006ad890
            FUN_005ede40(m_engine->m_draw, "Actors infos hidden !");
        }
    }
}

// FUNCTION: GAME 0x0045e620
void RHConsole::FUN_0045e620(unsigned, char **)
{
    g_consoleAttributes ^= 1;
    if (g_consoleAttributes == 1)
    {
        // STRING: GAME 0x006ad910
        FUN_005ede40(m_engine->m_draw, "Attributes displayed");
    }
    else
    {
        // STRING: GAME 0x006ad8fc
        FUN_005ede40(m_engine->m_draw, "Attributes hidden");
    }
}

// FUNCTION: GAME 0x0045e670
void RHConsole::FUN_0045e670(unsigned, char **)
{
    RHConsoleField<char>(RHUnk00546050(), 0x1d) = 1;
    // STRING: GAME 0x006ad928
    FUN_005ede40(m_engine->m_draw, "FPS displayed.");
}

// FUNCTION: GAME 0x0045e6a0
void RHConsole::FUN_0045e6a0(unsigned, char **)
{
    g_consoleBabylon ^= 1;
    if (g_consoleBabylon == 1)
    {
        // STRING: GAME 0x006ad940
        FUN_005ede40(m_engine->m_draw, "Patati Patata Bla Bla Laber Rhabarber Patatitata...");
    }
    else
    {
        // STRING: GAME 0x006ad938
        FUN_005ede40(m_engine->m_draw, "Shht !");
    }
}

// FUNCTION: GAME 0x0045e6f0
void RHConsole::FUN_0045e6f0(unsigned, char **)
{
    // STRING: GAME 0x006ac37c
    FUN_005edae0(m_engine->m_draw, "MORPHEUS");
    RHConsoleActor *actor = RHConsoleField<RHConsoleActor *>(m_engine, 0xd4);
    if (actor && (RHConsoleField<volatile unsigned>(actor, 4) & 0xf) == 4)
    {
        actor->v55(100, false, false);
        actor->v17(3);
        RHUnk00584d60 *element = new RHUnk00584d60(1, 0xa1, actor);
        ((RHScriptBatchCalls *)g_unk0x6c1040)->Unk0058a940(g_unk0x6c0560, 0, element);
        ((RHScriptBatchCalls *)m_engine)->Unk004d9330(0, false);
        // STRING: GAME 0x006ad974
        FUN_005edae0(m_engine->m_draw, "Sleep well...");
    }
    else
        FUN_005edae0(m_engine->m_draw, "Please enable view cone of a NPC before using this command.");
}

// FUNCTION: GAME 0x0045e7e0
void RHConsole::FUN_0045e7e0(unsigned, char **)
{
    // STRING: GAME 0x006ac534
    FUN_005edae0(m_engine->m_draw, "HADES");
    RHConsoleActor *actor = RHConsoleField<RHConsoleActor *>(m_engine, 0xd4);
    if (actor && (RHConsoleField<volatile unsigned>(actor, 4) & 0xf) == 4)
    {
        actor->v53(0, false, true);
        actor->v17(12);
        RHUnk00584d60 *element = new RHUnk00584d60(1, 0xa1, actor);
        ((RHScriptBatchCalls *)g_unk0x6c1040)->Unk0058a940(g_unk0x6c0560, 0, element);
        ((RHScriptBatchCalls *)m_engine)->Unk004d9330(0, false);
        // STRING: GAME 0x006ad984
        FUN_005edae0(m_engine->m_draw, "Sleep well... forever!");
    }
    else
        FUN_005edae0(m_engine->m_draw, "Please enable view cone of a NPC before using this command.");
}

// FUNCTION: GAME 0x0045e8d0
void RHConsole::FUN_0045e8d0(unsigned, char **)
{
    // STRING: GAME 0x006ada08
    FUN_005edae0(m_engine->m_draw, "Coma !");
    unsigned count = RHConsoleField<volatile unsigned>(m_engine, 0x4a00);
    if (count >= 1)
    {
        if (g_unk0x6c07fc->Get(0) >= 1)
        {
            RHElementActorPC *actor = RHConsoleField<RHConsolePCList>(m_engine, 0x49f8).getFirst();
            RHUnk005861c0 *element = new RHUnk005861c0(1, 0x26, actor, 10000, 0);
            ((RHScriptBatchCalls *)g_unk0x6c1040)->Unk0058a940(g_unk0x6c0560, 0, element);
        }
        else
        {
            // STRING: GAME 0x006ad9c4
            FUN_005edae0(m_engine->m_draw, "There not enough amulets left to put the selected PC in the coma.");
        }
    }
    else
    {
        // STRING: GAME 0x006ad99c
        FUN_005edae0(m_engine->m_draw, "Please, select the PC to make sleep.");
    }
}

// FUNCTION: GAME 0x0045eaa0
void RHConsole::FUN_0045eaa0(unsigned count, char **arguments)
{
    unsigned amount = 100;
    char buffer[1024];
    // STRING: GAME 0x006ada38
    FUN_005edae0(m_engine->m_draw, "Amulets [amount]");
    if (count >= 2)
        FUN_0064324d(arguments[1], "%u", &amount);
    // STRING: GAME 0x006ada10
    sprintf(buffer, "%u amulets added to the campaign.", amount);
    FUN_005edae0(m_engine->m_draw, buffer);
    ((RHScriptBatchCalls *)g_unk0x6c07fc)->Unk004520e0(0, amount);
}

// FUNCTION: GAME 0x0045eb40
void RHConsole::FUN_0045eb40(unsigned, char **)
{
    ((RHEngine *)m_engine)->FUN_004e2390(0);
}

// FUNCTION: GAME 0x0045eb50
void RHConsole::FUN_0045eb50(unsigned, char **)
{
    char buffer[1024];
    // STRING: GAME 0x006ada94
    FUN_005edae0(m_engine->m_draw, "San Petrus");
    unsigned count = RHConsoleField<volatile unsigned>(m_engine, 0x4a00);
    if (count == 0)
    {
        // STRING: GAME 0x006ada70
        FUN_005edae0(m_engine->m_draw, "You must select at least one PC.");
    }
    else
    {
        for (unsigned index = 0; index < RHConsoleField<RHConsolePCList>(m_engine, 0x49f8).m_count; ++index)
        {
            RHElementActorPC *actor = RHConsoleField<RHConsolePCList>(m_engine, 0x49f8).get((unsigned short)index);
            RHUnk005861c0 *element = new RHUnk005861c0(1, 0x26, actor, 10000, 0);
            ((RHScriptBatchCalls *)g_unk0x6c1040)->Unk0058a940(g_unk0x6c0560, 0, element);
            // STRING: GAME 0x006ada4c
            sprintf(buffer, "%s has been recalled by San Petrus.", RHConsoleField<RHConsoleProfile *>(actor, 0x5fc)->m_name.c_str());
            FUN_005edae0(m_engine->m_draw, buffer);
        }
    }
}

// FUNCTION: GAME 0x0045ec90
void RHConsole::FUN_0045ec90(unsigned, char **)
{
    // STRING: GAME 0x006adae0
    FUN_005edae0(m_engine->m_draw, "Wasps");
    RHConsoleEngine *engine = m_engine;
    if (RHConsoleField<RHConsolePCList>(engine, 0x49f8).m_count == 0)
    {
        // STRING: GAME 0x006adaa0
        FUN_005edae0(engine->m_draw, "You must selected at meast one PC which must go to paradise.");
    }
    else
    {
        typedef void (RHElementActorPC::*SetAmount)(unsigned, unsigned short);
        SetAmount setAmount = (SetAmount)&RHElementActorPC::FUN_0049f640;
        for (unsigned index = 0; index < RHConsoleField<RHConsolePCList>(engine, 0x49f8).m_count; ++index, engine = m_engine)
            (RHConsoleField<RHConsolePCList>(engine, 0x49f8).getInline((unsigned short)index)->*setAmount)(0x13, 0xffff);
    }
}

// FUNCTION: GAME 0x0045ee70
void RHConsole::FUN_0045ee70(unsigned, char **)
{
    // STRING: GAME 0x006adb0c
    FUN_005edae0(m_engine->m_draw, "Arrows");
    RHConsoleEngine *engine = m_engine;
    if (RHConsoleField<RHConsolePCList>(engine, 0x49f8).m_count == 0)
    {
        // STRING: GAME 0x006adae8
        FUN_005edae0(engine->m_draw, "You must selected at meast one PC.");
    }
    else
    {
        typedef void (RHElementActorPC::*SetAmount)(unsigned, unsigned short);
        SetAmount setAmount = (SetAmount)&RHElementActorPC::FUN_0049f640;
        for (unsigned index = 0; index < RHConsoleField<RHConsolePCList>(engine, 0x49f8).m_count; ++index, engine = m_engine)
            (RHConsoleField<RHConsolePCList>(engine, 0x49f8).getInline((unsigned short)index)->*setAmount)(1, 0xffff);
    }
}

// FUNCTION: GAME 0x0045f050
void RHConsole::FUN_0045f050(unsigned, char **)
{
    // STRING: GAME 0x006adb14
    FUN_005edae0(m_engine->m_draw, "Ammunition !");
    for (unsigned index = 0; index < FUN_0057aa20(); ++index)
    {
        RHElementActorPC *actor = (RHElementActorPC *)RHConsoleField<RHConsoleActorArray>(g_pEngine, 0x4938).m_first[(unsigned char)index];
        for (unsigned action = 0; action < 3; ++action)
            actor->FUN_0049f640(actor->FUN_0049d5c0(action), 999);
    }
}

// FUNCTION: GAME 0x0045f0c0
void RHConsole::FUN_0045f0c0(unsigned count, char **arguments)
{
    unsigned amount = 0;
    // STRING: GAME 0x006adbb8
    FUN_005edae0(m_engine->m_draw, "Money !");
    if (count >= 2)
    {
        char *argument = arguments[1];
        // STRING: GAME 0x006adbb0
        if (strcmp(argument, "HUNDRED") == 0)
            amount = 100;
        // STRING: GAME 0x006adba4
        else if (strcmp(argument, "THOUSAND") == 0)
            amount = 1000;
        // STRING: GAME 0x006adb98
        else if (strcmp(argument, "TENTHOUSAND") == 0)
            amount = 10000;
        // STRING: GAME 0x006adb88
        else if (strcmp(argument, "HUNDREDTHOUSAND") == 0)
            amount = 100000;
        else
            FUN_0064324d(argument, "%u", &amount);
    }
    else
    {
        // STRING: GAME 0x006adb6c
        FUN_005edae0(m_engine->m_draw, "Try also the following :");
        // STRING: GAME 0x006adb60
        FUN_005edae0(m_engine->m_draw, "CASH CENT");
        // STRING: GAME 0x006adb50
        FUN_005edae0(m_engine->m_draw, "CASH THOUSAND");
        // STRING: GAME 0x006adb3c
        FUN_005edae0(m_engine->m_draw, "CASH TENTHOUSAND");
        // STRING: GAME 0x006adb24
        FUN_005edae0(m_engine->m_draw, "CASH HUNDREDTHOUSAND");
        amount = 1000;
    }
    ((RHUnk00450b60 *)g_unk0x6c07fc)->Unk(1, amount);
}

// FUNCTION: GAME 0x0045f2a0
void RHConsole::FUN_0045f2a0(unsigned count, char **arguments)
{
    // STRING: GAME 0x006adbc0
    FUN_005edae0(m_engine->m_draw, "Blazons !");
    unsigned amount;
    if (count >= 2)
    {
        // STRING: GAME 0x006ada34
        FUN_0064324d(arguments[1], "%u", &amount);
    }
    else
        amount = 1;
    ((RHUnk00450b60 *)g_unk0x6c07fc)->Unk(3, amount);
    ((RHScriptBatchCalls *)g_unk0x6c0b3c)->Unk0050ed40();
}

// FUNCTION: GAME 0x0045f310
void RHConsole::FUN_0045f310(unsigned, char **)
{
    m_engine->m_4b3c = !m_engine->m_4b3c;
}

// FUNCTION: GAME 0x0045f4e0
void RHConsole::FUN_0045f4e0(unsigned, char **)
{
    // STRING: GAME 0x006adbe0
    FUN_005ede40(m_engine->m_draw, "Checking Memory result is %d", 1);
}

// FUNCTION: GAME 0x0045f500
void RHConsole::FUN_0045f500(unsigned, char **)
{
    RHConsoleActorArray &actors = RHConsoleField<RHConsoleActorArray>(m_engine, 0x4938);
    for (int index = 0; (unsigned short)index < (int)actors.size(); ++index)
    {
        RHGameActorView *actor = (RHGameActorView *)actors.m_first[(unsigned short)index];
        // STRING: GAME 0x006adc68
        FUN_005ede40(m_engine->m_draw, "Actor ptr ....................... <COLOR=FF0000>%x", actor);
        if (actor->FUN_004936e0())
        {
            // STRING: GAME 0x006adc34
            FUN_005ede40(m_engine->m_draw, "Interface Displayed ............. <COLOR=FF0000>YES");
        }
        else
        {
            // STRING: GAME 0x006adc00
            FUN_005ede40(m_engine->m_draw, "Interface Displayed ............. <COLOR=FF0000>NO");
        }
    }
}

// FUNCTION: GAME 0x0045f590
void RHConsole::FUN_0045f590(unsigned count, char **arguments)
{
    if (count >= 3)
    {
        RHElementActorPC *actor = FUN_0045f670(arguments[1]);
        if (actor)
        {
            // STRING: GAME 0x006add34
            if (strcmp("HIDEINTERFACE", arguments[2]) == 0)
            {
                ((RHEngineReinforcementCalls *)actor)->FUN_004936a0(1);
                // STRING: GAME 0x006adcf4
                FUN_005ede40(m_engine->m_draw, "Hiding interface for ActorPC(<COLOR=FF0000>%x<COLOR=FFFFFF>)");
            }
            // STRING: GAME 0x006adce0
            if (strcmp("DISPLAYINTERFACE", arguments[2]) == 0)
            {
                ((RHActorPCTemplateCalls *)actor)->FUN_00493660(1);
                // STRING: GAME 0x006adc9c
                FUN_005ede40(m_engine->m_draw, "Displaying interface for ActorPC(<COLOR=FF0000>%x<COLOR=FFFFFF>)");
            }
        }
    }
}

// FUNCTION: GAME 0x0045f670
RHElementActorPC *RHConsole::FUN_0045f670(char *name)
{
    RHElementActorPC *actor = FUN_005e19e0(name);
    return RHConsoleField<RHConsoleActorSearch>(m_engine, 0x4938).find((RHConsoleActor *)actor) == -1 ? 0 : actor;
}

// FUNCTION: GAME 0x004600b0
void RHConsole::FUN_004600b0(unsigned, char **)
{
    // STRING: GAME 0x006add8c
    FUN_005ede40(m_engine->m_draw, "New member !");
    ((RHConsoleCampaignCalls *)g_unk0x6c07fc)->FUN_004524b0(0xffff);
}

// FUNCTION: GAME 0x004600e0
void RHConsole::FUN_004600e0(unsigned, char **)
{
    // STRING: GAME 0x006add9c
    FUN_005ede40(m_engine->m_draw, "Unblip !");
    for (unsigned index = 0;
         index < RHConsoleField<RHConsoleActorArray>(m_engine, 0x48d8).size();
         ++index)
    {
        RHConsoleActor *actor = RHConsoleField<RHConsoleActorArray>(m_engine, 0x48d8).m_first[index];
        if (actor && (RHConsoleField<volatile unsigned>(actor, 4) & 0xf) == 4 && RHConsoleField<char>(actor, 8))
            actor->v13();
    }
}

// FUNCTION: GAME 0x00460140
void RHConsole::FUN_00460140(unsigned count, char **arguments)
{
    typedef void (__cdecl *Message)(RHUnk005ef320 *, const char *);
    Message output = (Message)&FUN_005ede40;
    if (count == 2)
    {
        // STRING: GAME 0x006ade90
        output(m_engine->m_draw, "Displayes all texts of the current level. Possible options are:");
        // STRING: GAME 0x006ade7c
        output(m_engine->m_draw, " DG for dialogues");
        // STRING: GAME 0x006ade68
        output(m_engine->m_draw, " DB for debriefings");
        // STRING: GAME 0x006ade54
        output(m_engine->m_draw, " PT for popup texts");
        // STRING: GAME 0x006ade38
        output(m_engine->m_draw, " SB for short berinfings");
    }
    else
    {
        char *option = arguments[2];
        // STRING: GAME 0x006ade34
        if (strcmp(option, "DG") == 0)
        {
            // STRING: GAME 0x006ade18
            output(m_engine->m_draw, "Displaying all dialogues...");
            RHConsoleField<char>(m_engine, 0x4be5) = 1;
        }
        // STRING: GAME 0x006ade14
        else if (strcmp(option, "DB") == 0)
        {
            // STRING: GAME 0x006addf4
            output(m_engine->m_draw, "Displaying all debriefings...");
            RHConsoleField<char>(m_engine, 0x4be6) = 1;
        }
        // STRING: GAME 0x006addf0
        else if (strcmp(option, "PT") == 0)
        {
            // STRING: GAME 0x006addd0
            output(m_engine->m_draw, "Displaying all popup texts...");
            RHConsoleField<char>(m_engine, 0x4be7) = 1;
        }
        // STRING: GAME 0x006addcc
        else if (strcmp(option, "SB") == 0)
        {
            // STRING: GAME 0x006adda8
            output(m_engine->m_draw, "Displaying all short briefings...");
            RHConsoleField<char>(m_engine, 0x4be8) = 1;
        }
    }
}

// FUNCTION: GAME 0x00460350
void RHConsole::FUN_00460350(unsigned, char **)
{
    m_engine->m_4b3d = !m_engine->m_4b3d;
}

// FUNCTION: GAME 0x00460370
void RHConsole::FUN_00460370(unsigned count, char **)
{
    // STRING: GAME 0x006adef0
    FUN_005ede40(m_engine->m_draw, "Valid");
    if (count > 2)
    {
        // STRING: GAME 0x006aded0
        FUN_005ede40(m_engine->m_draw, "Calling the memory police...");
    }
}

// FUNCTION: GAME 0x004603b0
void RHConsole::FUN_004603b0(unsigned, char **)
{
    // STRING: GAME 0x006adef8
    FUN_005ede40(m_engine->m_draw, "Reporting...\n");
    ((RHCampaign *)g_unk0x6c07fc)->FUN_00456e60();
}

// FUNCTION: GAME 0x004603e0
void RHConsole::FUN_004603e0(unsigned, char **)
{
    // STRING: GAME 0x006adf08
    FUN_005ede40(m_engine->m_draw, "Light zones\n");
    m_engine->m_4b3e = !m_engine->m_4b3e;
}

// FUNCTION: GAME 0x00460410
void RHConsole::FUN_00460410(unsigned, char **)
{
    if (m_engine->m_4bdc)
    {
        // STRING: GAME 0x006adf28
        FUN_005ede40(m_engine->m_draw, "PCs can't see\n");
    }
    else
    {
        // STRING: GAME 0x006adf18
        FUN_005ede40(m_engine->m_draw, "PCs can see\n");
    }
    m_engine->m_4bdc = !m_engine->m_4bdc;
}

// FUNCTION: GAME 0x00460600
void *RHConsole::FUN_00460600()
{
    return m_5b6 ? m_5d8 : m_5b8;
}

void EmitRHConsole(RHConsole *console, signed char *line, unsigned &count, char **arguments)
{
    RHConsole::FUN_0045bc50((char *)line, (char *)line);
    console->FUN_0045e527(count, arguments);
    console->FUN_0045c360(line, count);
    console->FUN_0045cc20(count, arguments);
    console->FUN_0045cc60(count, arguments);
    console->FUN_0045ccc0(*(std::string *)line);
    console->FUN_0045d580(count, arguments);
    console->FUN_0045d5c0(count, arguments);
    console->FUN_0045d5f0(count, arguments);
    console->FUN_0045d650(count, arguments);
    console->FUN_0045d780(count, arguments);
    console->FUN_0045d7d0(count, arguments);
    console->FUN_0045d840(count, arguments);
    console->FUN_0045d8b0(count, arguments);
    console->FUN_0045d920(count, arguments);
    console->FUN_0045da50(count, arguments);
    console->FUN_0045db20(count, arguments);
    console->FUN_0045db80(count, arguments);
    console->FUN_0045dc20(count, arguments);
    console->FUN_0045dc80(count, arguments);
    console->FUN_0045dce0(count, arguments);
    console->FUN_0045dd40(count, arguments);
    console->FUN_0045dd90(count, arguments);
    console->FUN_0045de60(count, arguments);
    console->FUN_0045e240(count, arguments);
    console->FUN_0045e290(count, arguments);
    console->FUN_0045e2e0(count, arguments);
    console->FUN_0045e400(count, arguments);
    console->FUN_0045e450(count, arguments);
    console->FUN_0045e4b0(count, arguments);
    console->FUN_0045e530(count, arguments);
    console->FUN_0045e620(count, arguments);
    console->FUN_0045e670(count, arguments);
    console->FUN_0045e6a0(count, arguments);
    console->FUN_0045e6f0(count, arguments);
    console->FUN_0045e7e0(count, arguments);
    console->FUN_0045e8d0(count, arguments);
    console->FUN_0045eaa0(count, arguments);
    console->FUN_0045eb40(count, arguments);
    console->FUN_0045eb50(count, arguments);
    console->FUN_0045ec90(count, arguments);
    console->FUN_0045ee70(count, arguments);
    console->FUN_0045f050(count, arguments);
    console->FUN_0045f0c0(count, arguments);
    console->FUN_0045f2a0(count, arguments);
    console->FUN_0045f310(count, arguments);
    console->FUN_0045f4e0(count, arguments);
    console->FUN_0045f500(count, arguments);
    console->FUN_0045f590(count, arguments);
    console->FUN_0045f670((char *)line);
    console->FUN_004600b0(count, arguments);
    console->FUN_004600e0(count, arguments);
    console->FUN_00460140(count, arguments);
    console->FUN_00460350(count, arguments);
    console->FUN_00460370(count, arguments);
    console->FUN_004603b0(count, arguments);
    console->FUN_004603e0(count, arguments);
    console->FUN_00460410(count, arguments);
    console->FUN_00460600();
}
