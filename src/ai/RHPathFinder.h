#ifndef RHPATHFINDER_H
#define RHPATHFINDER_H

#include "SB.h"
#include "RHEngine.h"
#include <windows.h>

class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &point);
    bool Serialize(SBFile &file);
    float x; // +0x00
    float y; // +0x04
};

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
};

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

struct RHpathRequest
{
    unsigned short m_0; // +0x00
    unsigned short m_2; // +0x02
    unsigned short m_4; // +0x04
    char m_pad6[2];
    SBGeoPoint2D m_8; // +0x08
    SBGeoPoint2D m_10; // +0x10
    void *m_18; // +0x18
    void *m_1c; // +0x1c
    RHElement *m_20; // +0x20
    unsigned short m_24; // +0x24
    char m_pad26[2];
    int m_28; // +0x28
    char m_2c; // +0x2c
    unsigned char m_2d; // +0x2d
    char m_pad2e[2];
    int m_30; // +0x30
    char m_34; // +0x34
    char m_pad35[7]; // allocation 0x3c
};

struct RHPathRequestNode
{
    RHPathRequestNode *next; // +0x00
    RHPathRequestNode *previous; // +0x04
    RHpathRequest *request; // +0x08
};

class RHPathRequestList
{
public:
    int allocator; // +0x00
    RHPathRequestNode *head; // +0x04
    int count; // +0x08
    RHPathRequestNode *cursor; // +0x0c
    char valid; // +0x10
    char padding[3];
    int index; // +0x14
    RHUnkIter FUN_0046eb80();
    RHUnkIter begin() { return FUN_0046eb80(); }
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
};

class RHPathSequenceSerializer
{
public:
    bool FUN_0058b7c0(SBFile &file, void *&value);
};

struct RHPathSectorConversion
{
    unsigned short source;
    unsigned short destination;
};

struct RHPathGraphArray
{
    int grow;
    void **first;
    void **last;
    void **end;
    unsigned size() const { return first ? last - first : 0; }
};

struct RHPathStateArray
{
    int grow;
    unsigned *first;
    char padding[0x18]; // array stride 0x20
};

class RHPathFinder
{
public:
    void AddPathRequest(RHpathRequest *request);
    bool TurnOn();
    void FUN_00554750();
    void FUN_00556260();
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
