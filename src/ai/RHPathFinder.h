#ifndef RHPATHFINDER_H
#define RHPATHFINDER_H

#include "SB.h"
#include "Decomp.h"
#include "RHEngine.h"
#include <windows.h>
#include <new>

// SIZE 0x08
class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(float x, float y);
    SBGeoPoint2D(const SBGeoPoint2D &point);
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &point);
    SBGeoPoint2D Unk005fc110(const SBGeoPoint2D &point) const;
    SBGeoPoint2D Unk005fc190(const SBGeoPoint2D &point) const;
    SBGeoPoint2D FUN_005fc200(const SBGeoPoint2D &point) const;
    bool Serialize(SBFile &file);
    float x; // +0x00
    float y; // +0x04
};

// SIZE 0x14
class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D();
    ~SBGeoBoundingBox2D() {}
    SBGeoBoundingBox2D &operator=(const SBGeoBoundingBox2D &box);
    SBGeoPoint2D FUN_00608f40() const;
    SBGeoPoint2D first; // +0x00
    SBGeoPoint2D last; // +0x08
    char flag; // +0x10
};

class RHElement;
class RHEngine;
class RHUnk6c1040;
class RHOrder;
class RHSequenceElement;
struct RHScriptNode;
struct RHTitbitNode;

// SIZE 0x0c
struct RHScriptNode
{
    RHScriptNode *next; // 0x00
    RHScriptNode *previous; // 0x04
    void *data; // 0x08
};

// SIZE 0x04
struct RHScriptIter
{
    RHScriptNode *node; // 0x00
    RHScriptIter() {}
    RHScriptIter(RHScriptNode *value) : node(value) {}
};

// SIZE 0x18
struct RHUnk004b1520List
{
    undefined m_00[4]; // 0x00
    RHScriptNode *m_04; // 0x04
    int m_08; // 0x08
    RHScriptIter m_0c; // 0x0c
    bool m_10; // 0x10
    int m_14; // 0x14
    RHScriptIter FUN_00424410(RHScriptIter position, void *const &value);
};

class RHUnkIter
{
public:
    void *m_p;
    RHUnkIter() {}
    RHUnkIter(void *p) : m_p(p) {}
};

class RHUnkList
{
public:
    RHUnkIter insert(RHUnkIter position, RHOrder *const &value);
};

class RHTitbitList
{
public:
    void Clear(void *out, RHTitbitNode *first, RHTitbitNode *last);
    void At(int index);
};

class RHUnk0046eb30
{
public:
    RHScriptNode *Unk0059f720(RHScriptNode *next, RHScriptNode *previous);
    RHScriptIter erase(RHScriptIter position);
    RHScriptIter FUN_0046eb80();
};

struct RHSectorActorNode;
class RHSectorActorConstIter
{
public:
    RHSectorActorNode *m_p; // 0x00
    RHSectorActorConstIter(RHSectorActorNode *node) : m_p(node) {}
};
class RHSectorActorIter : public RHSectorActorConstIter
{
public:
    RHSectorActorIter(RHSectorActorNode *node) : RHSectorActorConstIter(node) {}
    RHSectorActorIter operator++(int);
};

// SIZE 0x24
class RHPathWorkList
{
public:
    undefined allocator; // 0x00
    RHScriptNode *head; // 0x04
    int count; // 0x08
    RHScriptNode *cursor; // 0x0c
    bool valid; // 0x10
    int index; // 0x14
    undefined m_18[0x0c]; // 0x18
    RHPathWorkList()
    {
        head = ((RHUnk0046eb30 *)this)->Unk0059f720(0, 0);
        count = 0;
        valid = true;
    }
    ~RHPathWorkList()
    {
        RHScriptNode *last = head;
        RHScriptNode *node = last->next;
        while (node != last)
        {
            RHScriptNode *current = node;
            node = node->next;
            ((RHUnk0046eb30 *)this)->erase(RHScriptIter(current));
        }
        operator delete(head);
    }
    void clear()
    {
        RHScriptNode *last = head;
        RHScriptNode *node = last->next;
        while (node != last)
        {
            RHScriptNode *current = node;
            node = node->next;
            RHSectorActorIter it((RHSectorActorNode *)current);
            RHScriptNode *erased = (RHScriptNode *)(it++).m_p;
            erased->previous->next = erased->next;
            erased->next->previous = erased->previous;
            operator delete(erased);
            --count;
        }
    }
};

// SIZE 0x24
class RHMalignityQueryList
{
public:
    RHMalignityQueryList();
    ~RHMalignityQueryList() { FUN_004e6c10(); FUN_004e52a0(); }
    void FUN_004e6c10();
    void FUN_004e52a0();
    undefined4 allocator; // 0x00
    RHScriptNode *head; // 0x04
    int count; // 0x08
    RHScriptNode *cursor; // 0x0c
    bool valid; // 0x10
    int index; // 0x14
    undefined m_18[0x0c]; // 0x18
};

class RHMalignityGridCalls
{
public:
    void FUN_004ed070(RHMalignityQueryList &list, unsigned short layer, const SBGeoBoundingBox2D &box, unsigned mask);
};

class RHUnk00608f10
{
public:
    int FUN_00608f10(void *value);
};

// SIZE 0x08
class RHUnk005fc3b0 : public SBGeoPoint2D
{
public:
    RHUnk005fc3b0();
    ~RHUnk005fc3b0() {}
    RHUnk005fc3b0 &FUN_005fc430(const SBGeoPoint2D &point);
};

class RHMobileUnk006091b0
{
public:
    RHMobileUnk006091b0 &FUN_006091b0(const SBGeoPoint2D &point);
};

class SBGeoVector2D : public SBGeoPoint2D
{
public:
    ~SBGeoVector2D() {}
    float FUN_005fc660(const SBGeoPoint2D &point) const;
};

class RHPathQueryCalls
{
public:
    void FUN_005c8e40(int index);
};

SBGeoVector2D operator*(float factor, const SBGeoVector2D &point);
extern float g_unk0x00677488;
extern float g_unk0x0067749c;
extern float g_unk0x006787f8;

class RHSeqList
{
public:
    static void CopyData(RHSequenceElement **destination, RHSequenceElement *const *source);
};

class RHUnk0046bcb0
{
public:
    void Unk(int value);
};

class RHScriptBatchCalls
{
public:
    void Unk00464630();
};

class RHPathActorInfo
{
public:
    const SBGeoBoundingBox2D &FUN_00560450();
};

// SIZE 0x3c
struct RHpathRequest
{
    unsigned short m_0; // +0x00
    unsigned short m_2; // +0x02
    unsigned short m_4; // +0x04
    undefined m_pad6[2]; // 0x06
    SBGeoPoint2D m_8; // +0x08
    SBGeoPoint2D m_10; // +0x10
    void *m_18; // +0x18
    void *m_1c; // +0x1c
    RHElement *m_20; // +0x20
    unsigned short m_24; // +0x24
    undefined m_pad26[2]; // 0x26
    int m_28; // +0x28
    char m_2c; // +0x2c
    unsigned char m_2d; // +0x2d
    undefined m_pad2e[2]; // 0x2e
    int m_30; // +0x30
    char m_34; // +0x34
    undefined m_pad35[7]; // 0x35
};

struct RHPathRequestNode
{
    RHPathRequestNode *next; // +0x00
    RHPathRequestNode *previous; // +0x04
    RHpathRequest *request; // +0x08
};

// SIZE 0x18
class RHPathRequestList
{
public:
    int allocator; // +0x00
    RHPathRequestNode *head; // +0x04
    int count; // +0x08
    RHPathRequestNode *cursor; // +0x0c
    char valid; // +0x10
    undefined padding[3]; // 0x11
    int index; // +0x14
    RHUnkIter FUN_0046eb80();
    RHUnkIter begin()
    {
        return RHUnkIter(((RHUnk0046eb30 *)this)->FUN_0046eb80().node);
    }
    RHUnkIter end() { return RHUnkIter(head); }
    RHUnkIter insert(RHUnkIter position, RHpathRequest *const &request)
    {
        RHUnkIter result = ((RHUnkList *)this)->insert(position, (RHOrder *const &)request);
        valid = 1;
        return result;
    }
    void clear()
    {
        RHUnkIter result;
        ((RHTitbitList *)this)->Clear(&result, (RHTitbitNode *)begin().m_p, (RHTitbitNode *)end().m_p);
        valid = 1;
    }
    RHpathRequest *&operator[](int wanted)
    {
        ((RHTitbitList *)this)->At(wanted);
        return cursor->request;
    }
    void InsertInline(RHPathRequestNode *node, RHpathRequest *const &request)
    {
        node->previous = (RHPathRequestNode *)((RHUnk0046eb30 *)this)->Unk0059f720((RHScriptNode *)node, (RHScriptNode *)node->previous);
        RHPathRequestNode *created = node->previous;
        created->previous->next = created;
        RHSeqList::CopyData((RHSequenceElement **)&created->request, (RHSequenceElement *const *)&request);
        ++count;
        valid = 1;
    }
};

class RHPathObstacleGrid
{
public:
    bool FUN_004f5750(SBGeoBoundingBox2D &box, unsigned short sector);
    bool FUN_004f5890(SBGeoBoundingBox2D &box, unsigned short sector);
    undefined m_00[0x3e84]; // 0x00
    SBGeoBoundingBox2D m_3e84; // 0x3e84
};

class RHPathSequenceSerializer
{
public:
    bool FUN_0058b7c0(SBFile &file, void *&value);
};

struct RHPathSectorConversion
{
    unsigned short source; // 0x00
    unsigned short destination; // 0x02
};

struct RHPathGraphArray
{
    int grow; // 0x00
    void **first; // 0x04
    void **last; // 0x08
    void **end; // 0x0c
    unsigned size() const { return first ? last - first : 0; }
};

struct RHPathStateArray
{
    int grow; // 0x00
    unsigned *first; // 0x04
    undefined padding[0x18]; // 0x08
};

// SIZE 0x20
struct RHPathSearchNode
{
    undefined m_00[4]; // 0x00
    RHPathSearchNode *m_04; // 0x04
    undefined m_08[0x10]; // 0x08
    RHPathSearchNode *m_18; // 0x18
    unsigned char m_1c; // 0x1c
    unsigned char m_1d; // 0x1d
    undefined m_1e[2]; // 0x1e
};

// SIZE 0x18
class RHPathPointList
{
public:
    void FUN_00610ac0();
    void FUN_00610a00(const SBGeoPoint2D &point);
    void FUN_00610a60(const SBGeoPoint2D &point);
    void FUN_00610b50(int index);
    const SBGeoPoint2D &FUN_00610cb0(int index);
    undefined m_00[0x18]; // 0x00
};

class RHUnk0053bf20
{
public:
    void *FUN_0053bf20() const;
};

bool FUN_005547c0(unsigned short graph, unsigned short sector, unsigned short direction, const SBGeoPoint2D &first, const SBGeoPoint2D &last);
void FUN_005557c0();
bool FUN_00558210(const SBGeoPoint2D &point);
bool FUN_00557e70(const SBGeoPoint2D &first, const SBGeoPoint2D &last);
bool FUN_00556990(SBGeoPoint2D first, SBGeoPoint2D last);
void FUN_00553e60(const SBGeoPoint2D &first, const SBGeoPoint2D &last);
RHPathSearchNode *FUN_00556490(const SBGeoPoint2D &point);
unsigned char FUN_00554b80(RHPathSearchNode *node, unsigned char value, RHPathPointList &list);
void FUN_005553d0(RHPathSearchNode *node, unsigned char first, unsigned char last, RHPathPointList &list);

// SIZE 0x28
class RHPathFinder
{
public:
    void AddPathRequest(RHpathRequest *request);
    bool TurnOn();
    void FUN_00554750();
    void FUN_00556260();
    void FUN_00555a10(unsigned short graph, unsigned short node, unsigned state, RHPathWorkList &list);
    void FUN_00552d50(unsigned char speed);
    static unsigned short ConvertSector(unsigned short sector);
    bool Serialize(SBFile &file);
    void Emit(SBFile &file, RHpathRequest *request);

    int m_0; // +0x00
    DWORD m_4; // +0x04: thread id
    HANDLE m_8; // +0x08: thread handle
    int m_c; // +0x0c
    RHPathRequestList m_10; // +0x10, head +0x14, count +0x18
};

extern char g_pathStatus;
extern char g_pathThreadDone;
extern RHpathRequest *g_currentPathRequest;
extern RHPathObstacleGrid *g_pathObstacleGrid;
extern RHPathSectorConversion *g_pathSectorFirst;
extern RHPathSectorConversion *g_pathSectorLast;
extern RHPathGraphArray **g_pathGraphFirst;
extern RHPathGraphArray **g_pathGraphLast;
extern RHPathStateArray *g_pathStates;
extern RHEngine *g_pEngine;
extern RHUnk6c1040 *g_unk0x6c1040;
void RHSerializeName(SBFile &file, const char *name);

#endif
