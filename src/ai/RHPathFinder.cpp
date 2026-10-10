#include "SBNullstr.h"
#include "RHPathFinder.h"

DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(SBGeoBoundingBox2D, 0x14)
DECOMP_SIZE_ASSERT(RHScriptNode, 0x0c)
DECOMP_SIZE_ASSERT(RHScriptIter, 0x04)
DECOMP_SIZE_ASSERT(RHUnk004b1520List, 0x18)
DECOMP_SIZE_ASSERT(RHpathRequest, 0x3c)
DECOMP_SIZE_ASSERT(RHPathRequestList, 0x18)
DECOMP_SIZE_ASSERT(RHPathFinder, 0x28)
DECOMP_SIZE_ASSERT(RHPathWorkList, 0x24)
DECOMP_SIZE_ASSERT(RHMalignityQueryList, 0x24)
DECOMP_SIZE_ASSERT(RHUnk005fc3b0, 0x08)
DECOMP_SIZE_ASSERT(RHPathSearchNode, 0x20)
DECOMP_SIZE_ASSERT(RHPathPointList, 0x18)

// GLOBAL: GAME 0x006c0d40
char g_pathStatus;
// GLOBAL: GAME 0x006c0d7c
RHPathSectorConversion *g_pathSectorFirst;
// GLOBAL: GAME 0x006c0d80
RHPathSectorConversion *g_pathSectorLast;
// GLOBAL: GAME 0x006c0d98
RHPathObstacleGrid *g_pathObstacleGrid;
// GLOBAL: GAME 0x006c0da4
char g_pathThreadDone;
// GLOBAL: GAME 0x006c0da8
RHpathRequest *g_currentPathRequest;
// GLOBAL: GAME 0x006c0cb4
RHPathGraphArray **g_pathGraphFirst;
// GLOBAL: GAME 0x006c0cb8
RHPathGraphArray **g_pathGraphLast;
// GLOBAL: GAME 0x006c0dcc
RHPathStateArray *g_pathStates;
// GLOBAL: GAME 0x006c0c78
RHPathPointList g_unk0x006c0c78;
struct RHSpriteGraphEntry;
extern RHSpriteGraphEntry *g_unk0x006c0cd4;
// GLOBAL: GAME 0x006c0d56
undefined2 g_unk0x006c0d56;
// GLOBAL: GAME 0x006c0d70
void *g_unk0x006c0d70;
// GLOBAL: GAME 0x006c0d9c
void *g_unk0x006c0d9c;
// GLOBAL: GAME 0x006c0da0
RHPathGraphArray *g_unk0x006c0da0;
// GLOBAL: GAME 0x006c0db0
RHPathSearchNode *g_unk0x006c0db0;
// GLOBAL: GAME 0x006c0db8
RHUnk005fc3b0 g_unk0x006c0db8;
// GLOBAL: GAME 0x006c0dc0
undefined2 g_unk0x006c0dc0;

// deferred: unannotated pending reccmp #534.
RHScriptIter RHUnk004b1520List::FUN_00424410(RHScriptIter position, void *const &value)
{
    RHScriptNode *next = position.node;
    RHScriptNode *previous = next->previous;
    RHScriptNode *node = (RHScriptNode *)operator new(sizeof(RHScriptNode));
    node->next = next ? next : node;
    node->previous = previous ? previous : node;
    next->previous = node;
    node->previous->next = node;
    new (&node->data) void *(value);
    ++m_08;
    return RHScriptIter(node);
}

// Parked: 68.45%, list frame and cleanup scheduling.
// STUB: GAME 0x004f5750
bool RHPathObstacleGrid::FUN_004f5750(SBGeoBoundingBox2D &box, unsigned short sector)
{
    if (!(unsigned char)((RHUnk00608f10 *)&m_3e84)->FUN_00608f10(&box))
        return false;
    RHPathWorkList list;
    ((RHMalignityGridCalls *)this)->FUN_004ed070((RHMalignityQueryList &)list, sector, box, 2);
    bool result = list.count == 0;
    list.clear();
    return result;
}

// Parked: 34.49%, geometry temporaries and cleanup scheduling.
// STUB: GAME 0x004f5890
bool RHPathObstacleGrid::FUN_004f5890(SBGeoBoundingBox2D &box, unsigned short sector)
{
    RHMalignityQueryList list;
    if (!(unsigned char)((RHUnk00608f10 *)&m_3e84)->FUN_00608f10(&box))
    {
        float x;
        float y;
        if (box.last.x < g_unk0x00677488)
            x = -box.first.x;
        else if (m_3e84.last.x < box.first.x)
            x = -(box.last.x - m_3e84.last.x);
        else
            x = 0.0f;
        if (box.last.y < g_unk0x00677488)
            y = -box.first.y;
        else if (m_3e84.last.y < box.first.y)
            y = -(box.last.y - m_3e84.last.y);
        else
            y = 0.0f;
        ((RHMobileUnk006091b0 *)&box)->FUN_006091b0(SBGeoPoint2D(x, y));
    }
    unsigned short iteration = 0;
    do
    {
        ((RHMalignityGridCalls *)this)->FUN_004ed070(list, sector, box, 2);
        unsigned short count = (unsigned short)list.count;
        if (count == 0)
            return true;
        int index = 0;
        while (count != 0)
        {
            ((RHPathQueryCalls *)&list)->FUN_005c8e40(index);
            char *line = (char *)list.cursor->data;
            SBGeoPoint2D *origin = (SBGeoPoint2D *)(line + 4);
            SBGeoVector2D *normal = (SBGeoVector2D *)(line + 0x34);
            if (normal->FUN_005fc660(box.FUN_00608f40().Unk005fc110(*origin)) > g_unk0x00677488)
            {
                float distance = normal->FUN_005fc660(origin->Unk005fc110(box.first));
                if (distance > g_unk0x006787f8)
                    ((RHMobileUnk006091b0 *)&box)->FUN_006091b0(operator*(distance + g_unk0x0067749c, *(SBGeoVector2D *)normal));
                distance = normal->FUN_005fc660(origin->Unk005fc110(box.last));
                if (distance > g_unk0x006787f8)
                    ((RHMobileUnk006091b0 *)&box)->FUN_006091b0(operator*(distance + g_unk0x0067749c, *(SBGeoVector2D *)normal));
                distance = normal->FUN_005fc660(origin->Unk005fc110(SBGeoPoint2D(box.last.x, box.first.y)));
                if (distance > g_unk0x006787f8)
                    ((RHMobileUnk006091b0 *)&box)->FUN_006091b0(operator*(distance + g_unk0x0067749c, *(SBGeoVector2D *)normal));
                distance = normal->FUN_005fc660(origin->Unk005fc110(SBGeoPoint2D(box.first.x, box.last.y)));
                if (distance > g_unk0x006787f8)
                    ((RHMobileUnk006091b0 *)&box)->FUN_006091b0(operator*(distance + g_unk0x0067749c, *(SBGeoVector2D *)normal));
            }
            ++index;
            --count;
        }
        RHScriptNode *node = list.head->next;
        while (node != list.head)
        {
            RHScriptNode *current = node;
            node = node->next;
            current->previous->next = current->next;
            current->next->previous = current->previous;
            operator delete(current);
            --list.count;
        }
        list.valid = true;
        ++iteration;
    } while (iteration < 50);
    return false;
}

// Parked: 48.73%, frame/register scheduling.
// STUB: GAME 0x00552e00
void RHPathFinder::AddPathRequest(RHpathRequest *request)
{
    SBGeoBoundingBox2D box;
    box = ((RHPathActorInfo *)(*(char **)((char *)request->m_1c + 0x50) + 4))->FUN_00560450();
    if (!g_pathObstacleGrid->FUN_004f5750(box, request->m_0))
    {
        request->m_34 = 1;
        if (!g_pathObstacleGrid->FUN_004f5890(box, request->m_0))
        {
            ((RHUnk0046bcb0 *)request->m_1c)->Unk(8);
            ((RHScriptBatchCalls *)request->m_1c)->Unk00464630();
            SBGeoPoint2D *position = (SBGeoPoint2D *)(*(char **)((char *)request->m_1c + 0x50) + 0x24);
            SBAssert(0,
                     // STRING: GAME 0x006b15b0
                     "P:\\Robin Hood\\RHpathfinder.cpp", 468,
                     // STRING: GAME 0x006b15d8
                     "UNERH\xd6RT : Path request impossible, character cannot be extracted from its obstacle (%f,%f) !",
                     position->x, position->y);
            return;
        }
        request->m_8 = box.FUN_00608f40();
    }
    else
        request->m_34 = 0;
    RHPathRequestList &requests = m_10;
    int count = requests.count;
    if ((unsigned short)count < 2)
        requests.insert(requests.end(), request);
    else
    {
        unsigned short i = (unsigned short)(count - 1);
        for (; (short)i > 0; --i)
        {
            if (requests[(unsigned short)i]->m_2d <= request->m_2d)
            {
                unsigned next = (unsigned short)i + 1;
                if (next == requests.count)
                    requests.insert(requests.end(), request);
                else
                {
                    requests[next];
                    requests.InsertInline(requests.cursor, request);
                }
                break;
            }
        }
        if (i == 0)
        {
            if (g_pathStatus != 4 && g_pathStatus != 3)
                requests.InsertInline(requests.head->next, request);
            else
            {
                if (requests.count == 1)
                    requests.insert(requests.end(), request);
                else
                {
                    requests[1];
                    requests.insert(RHUnkIter(requests.cursor), request);
                }
                if (request->m_2d < m_c)
                    FUN_00552d50(request->m_2d);
            }
        }
    }
}

// FUNCTION: GAME 0x005546e0
bool RHPathFinder::TurnOn()
{
    if (m_10.count == 0)
        g_pathStatus = 1;
    else
    {
        g_pathStatus = 2;
        RHPathRequestNode *node = *(RHPathRequestNode *volatile *)&m_10.head;
        node = node->next;
        g_currentPathRequest = node->request;
    }
    g_pathThreadDone = 0;
    m_8 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)0x005545c0, 0, 0, &m_4);
    if (!m_8)
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHpathfinder.cpp", 1676,
                 // STRING: GAME 0x006b1660
                 "Pathfinder error : Cannot create thread.");
        return false;
    }
    return true;
}

// Parked: 66.54%, receiver scheduling, return cleanup and annotated callees.
// STUB: GAME 0x005547c0
bool FUN_005547c0(unsigned short graph, unsigned short sector, unsigned short direction, const SBGeoPoint2D &first, const SBGeoPoint2D &last)
{
    SBGeoPoint2D previous;
    SBGeoPoint2D middle;
    SBGeoPoint2D current;
    RHUnk005fc3b0 vector;
    g_unk0x006c0dc0 = graph;
    unsigned short converted = RHPathFinder::ConvertSector(sector);
    g_unk0x006c0d9c = g_pathGraphFirst[graph]->first[converted];
    g_unk0x006c0d70 = ((RHPathGraphArray *)g_unk0x006c0da0->first[graph])->first[converted];
    g_unk0x006c0d56 = direction;
    g_unk0x006c0db8.FUN_005fc430(((SBGeoPoint2D *)g_unk0x006c0cd4)[direction]);
    FUN_005557c0();
    g_unk0x006c0c78.FUN_00610ac0();
    if (!FUN_00558210(last))
        return false;
    if (g_currentPathRequest->m_34 && FUN_00557e70(first, last) && FUN_00556990(first, last))
        g_unk0x006c0c78.FUN_00610a60(last);
    else
    {
        FUN_00553e60(first, last);
        RHPathSearchNode *node = FUN_00556490(last);
        g_unk0x006c0db0 = node;
        if (!node)
            return false;
        g_unk0x006c0c78.FUN_00610a00(last);
        unsigned char value = node->m_1c;
        RHPathSearchNode *link = node->m_18;
        while (link)
        {
            value = FUN_00554b80(link, value, g_unk0x006c0c78);
            node = link->m_04;
            link = node->m_18;
        }
        FUN_005553d0(node, node->m_1d, value, g_unk0x006c0c78);
        g_unk0x006c0c78.FUN_00610a00(first);
        unsigned short count = (unsigned short)(unsigned)((RHUnk0053bf20 *)&g_unk0x006c0c78)->FUN_0053bf20();
        if (count > 3)
        {
            previous = g_unk0x006c0c78.FUN_00610cb0(0);
            middle = g_unk0x006c0c78.FUN_00610cb0(1);
            for (unsigned short index = 2; index < count; ++index)
            {
                current = g_unk0x006c0c78.FUN_00610cb0(index);
                vector.FUN_005fc430(operator*(0.00005f, (const SBGeoVector2D &)current.Unk005fc110(previous)));
                if (FUN_00556990(previous.Unk005fc190(vector), current.FUN_005fc200(vector)))
                {
                    g_unk0x006c0c78.FUN_00610b50(index - 1);
                    --count;
                    --index;
                }
                else
                    previous = middle;
                middle = current;
            }
        }
    }
    return true;
}

// Parked: 43.31%, list frame/cursor scheduling; unannotated for rule 28.
void RHPathFinder::FUN_00556260()
{
    RHPathWorkList list;
    unsigned short graphs = g_pathGraphFirst ? g_pathGraphLast - g_pathGraphFirst : 0;
    for (unsigned short graph = 0; graph < graphs; ++graph)
    {
        unsigned short count = g_pathGraphFirst[graph]->size();
        for (unsigned short node = 0; node < count; ++node)
            FUN_00555a10(graph, node, g_pathStates[graph].first[node], list);
    }
    list.clear();
}

// FUNCTION: GAME 0x00559660
unsigned short RHPathFinder::ConvertSector(unsigned short sector)
{
    unsigned short size = g_pathSectorFirst == 0 ? 0 : g_pathSectorLast - g_pathSectorFirst;
    for (unsigned short i = 0; i < size; ++i)
        if (g_pathSectorFirst[i].source == sector)
            return g_pathSectorFirst[i].destination;
    SBAssert(0, "P:\\Robin Hood\\RHpathfinder.cpp", 5049,
             // STRING: GAME 0x006b168c
             "ConvertSector failed (sector %d)", sector);
    return 0;
}

#define PATH_ACCESS(pointer, size, line) \
    if (file.Access(pointer, size) < 0) \
    { \
        SBString *err = file.GetError(); \
        SBAssert(0, "P:\\Robin Hood\\RHpathfinder.cpp", line, \
                 "Serialize failed reason is %s", err->m_chars ? err->m_chars : ""); \
        return false; \
    }

#define PATH_REQUEST_FIELDS(request, line) \
    PATH_ACCESS(&(request)->m_28, 4, line) \
    PATH_ACCESS(&(request)->m_2c, 1, line + 1) \
    PATH_ACCESS(&(request)->m_34, 1, line + 2) \
    PATH_ACCESS(&(request)->m_30, 4, line + 3) \
    PATH_ACCESS(&(request)->m_2d, 1, line + 4) \
    PATH_ACCESS(&(request)->m_4, 2, line + 5) \
    PATH_ACCESS(&(request)->m_24, 2, line + 6) \
    PATH_ACCESS(&(request)->m_0, 2, line + 7) \
    PATH_ACCESS(&(request)->m_2, 2, line + 8) \
    (request)->m_10.Serialize(file); \
    (request)->m_8.Serialize(file); \
    g_pEngine->FUN_004c3af0(file, (request)->m_1c); \
    g_pEngine->SerializeElementPointer(file, (request)->m_20); \
    ((RHPathSequenceSerializer *)g_unk0x6c1040)->FUN_0058b7c0(file, (request)->m_18);

// Parked: counted begin callee corrected; iterator-result/local scheduling and engine-call residuals remain.
// STUB: GAME 0x0055aa60
bool RHPathFinder::Serialize(SBFile &file)
{
    RHSerializeName(file,
                    // STRING: GAME 0x006b16b0
                    "RHPathFinder");
    unsigned short graphCount = g_pathGraphFirst == 0 ? 0 : g_pathGraphLast - g_pathGraphFirst;
    RHpathRequest *request;
    if (file.m_bLoading)
    {
        FUN_00554750();
        PATH_ACCESS(&g_pathThreadDone, 1, 5485)
        RHPathRequestList &requests = m_10;
        requests.clear();
        unsigned short count;
        PATH_ACCESS(&count, 2, 5490)
        for (unsigned short i = 0; i < count; ++i)
        {
            request = new RHpathRequest;
            PATH_REQUEST_FIELDS(request, 5495)
            requests.insert(requests.end(), request);
        }
        for (unsigned short graph = 0; graph < graphCount; ++graph)
        {
            unsigned short size = g_pathGraphFirst[graph]->size();
            for (unsigned short node = 0; node < size; ++node)
            {
                unsigned value;
                PATH_ACCESS(&value, 4, 5523)
                g_pathStates[graph].first[node] = value;
            }
        }
        FUN_00556260();
        TurnOn();
    }
    else
    {
        unsigned short count = m_10.count;
        unsigned short i = 0;
        if (g_pathThreadDone)
        {
            i = 1;
            --count;
        }
        bool done = false;
        PATH_ACCESS(&done, 1, 5544)
        PATH_ACCESS(&count, 2, 5546)
        for (; i < m_10.count; ++i)
        {
            RHpathRequest *current = m_10[i];
            PATH_ACCESS(&current->m_28, 4, 5552)
            PATH_ACCESS(&request->m_2c, 1, 5553)
            PATH_ACCESS(&request->m_34, 1, 5554)
            PATH_ACCESS(&request->m_30, 4, 5555)
            PATH_ACCESS(&request->m_2d, 1, 5556)
            PATH_ACCESS(&request->m_4, 2, 5557)
            PATH_ACCESS(&request->m_24, 2, 5558)
            PATH_ACCESS(&request->m_0, 2, 5559)
            PATH_ACCESS(&request->m_2, 2, 5560)
            request->m_10.Serialize(file);
            request->m_8.Serialize(file);
            g_pEngine->FUN_004c3af0(file, request->m_1c);
            g_pEngine->SerializeElementPointer(file, request->m_20);
            ((RHPathSequenceSerializer *)g_unk0x6c1040)->FUN_0058b7c0(file, request->m_18);
        }
        for (unsigned short graph = 0; graph < graphCount; ++graph)
        {
            unsigned short size = g_pathGraphFirst[graph]->size();
            for (unsigned short node = 0; node < size; ++node)
            {
                unsigned value = g_pathStates[graph].first[node];
                PATH_ACCESS(&value, 4, 5579)
            }
        }
    }
    return true;
}

#undef PATH_REQUEST_FIELDS
#undef PATH_ACCESS

void RHPathFinder::Emit(SBFile &file, RHpathRequest *request)
{
    AddPathRequest(request);
    TurnOn();
    ConvertSector(0);
    Serialize(file);
}
