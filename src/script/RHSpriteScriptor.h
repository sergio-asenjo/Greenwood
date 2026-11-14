#ifndef RHSPRITESCRIPTOR_H
#define RHSPRITESCRIPTOR_H

#include "RHSaveGame.h"
#include "Decomp.h"
#include <vector>
#include <functional>

#include "SBGeoPoint2D.h"
#include "SBGeoVector2D.h"

// SIZE 0x10
class RHUnkSpriteUshortVector
{
public:
    undefined m_0[4]; // 0x00
    unsigned short *m_first; // 0x04
    unsigned short *m_last; // 0x08
    unsigned short *m_end; // 0x0c
};

#include "RHSpriteRow.h"

// SIZE 0x18
struct RHUnkSpriteScriptInfo
{
    RHUnkSpriteScriptInfo() {}
    RHUnkSpriteScriptInfo(const RHUnkSpriteScriptInfo &other)
        : m_rows(other.m_rows), m_indices(other.m_indices), m_position(other.m_position), m_size(other.m_size) {}
    std::vector<RHUnkSpriteRow> *m_rows; // +0x00
    std::vector<unsigned short> *m_indices; // +0x04
    SBGeoVector2D m_position; // +0x08
    SBGeoVector2D m_size; // +0x10; sizeof = 0x18
};

struct RHSpriteInsertNode;
typedef RHSpriteInsertNode RHUnkSpriteCacheNode;

// SIZE 0x04
struct RHUnkSpriteCacheIterator
{
    RHUnkSpriteCacheNode *m_node; // 0x00
    bool operator==(const RHUnkSpriteCacheIterator &other) const { return m_node == other.m_node; }
};

// SIZE 0x28
struct RHUnkSpriteCacheValue
{
    RHUnkSpriteCacheValue(const std::string &key, const RHUnkSpriteScriptInfo &info);
    const std::string m_key; // +0x00
    RHUnkSpriteScriptInfo m_info; // +0x10; sizeof = 0x28
};

struct RHSpriteInsertNode
{
    RHSpriteInsertNode *m_00;
    RHSpriteInsertNode *m_04;
    RHSpriteInsertNode *m_08;
    RHUnkSpriteCacheValue m_0c;
    int m_34;
};

struct RHSpriteInsertIterator
{
    RHSpriteInsertNode *m_node;
    RHSpriteInsertIterator operator++(int);
    RHUnkSpriteCacheValue &operator*() const { return m_node->m_0c; }
    bool operator!=(const RHSpriteInsertIterator &other) const { return m_node != other.m_node; }
};

class RHSpriteInsertTree
{
public:
    inline RHSpriteInsertTree(const std::less<std::string> &compare, bool multi,
                             const std::allocator<RHUnkSpriteCacheValue> &allocator);
    RHSpriteInsertIterator FUN_005c1290(RHSpriteInsertNode *, RHSpriteInsertNode *, const RHUnkSpriteCacheValue &);
    static RHSpriteInsertNode *&Left(RHSpriteInsertNode *node) { return node->m_00; }
    inline void RotateLeft(RHSpriteInsertNode *node);
    inline void RotateRight(RHSpriteInsertNode *node);
    inline ~RHSpriteInsertTree();
    RHSpriteInsertIterator FUN_005c06c0(RHSpriteInsertIterator, RHSpriteInsertIterator);
    RHSpriteInsertIterator FUN_005c0b50(RHSpriteInsertIterator);
    void FUN_005c10d0(RHSpriteInsertNode *);
    static RHSpriteInsertNode *&Parent(RHSpriteInsertNode *node) { return node->m_04; }
    static RHSpriteInsertNode *&Right(RHSpriteInsertNode *node) { return node->m_08; }
    static int &Color(RHSpriteInsertNode *node) { return node->m_34; }
    RHSpriteInsertNode *&Root() { return m_head->m_04; }
    RHSpriteInsertNode *&Leftmost() { return m_head->m_00; }
    RHSpriteInsertNode *&Rightmost() { return m_head->m_08; }
    RHSpriteInsertIterator Begin()
    {
        RHSpriteInsertIterator result;
        result.m_node = Leftmost();
        return result;
    }
    RHSpriteInsertIterator End()
    {
        RHSpriteInsertIterator result;
        result.m_node = m_head;
        return result;
    }
    std::allocator<RHUnkSpriteCacheValue> m_allocator;
    std::less<std::string> m_compare;
    RHSpriteInsertNode *m_head;
    bool m_multi;
    unsigned m_count;
};

// SIZE 0x08
struct RHUnkSpriteCacheInsertResult
{
    RHUnkSpriteCacheInsertResult() {}
    RHUnkSpriteCacheInsertResult(const std::pair<RHUnkSpriteCacheIterator, bool> &other)
        : m_first(other.first), m_second(other.second) {}
    RHUnkSpriteCacheInsertResult(const RHUnkSpriteCacheIterator &first, const bool &second)
        : m_first(first), m_second(second) {}
    RHUnkSpriteCacheIterator m_first; // 0x00
    undefined m_second; // 0x04
};

// SIZE 0x10
class RHUnkSpriteCache : public RHSpriteInsertTree
{
public:
    inline RHUnkSpriteCache(const std::less<std::string> &compare = std::less<std::string>(),
                           const std::allocator<RHUnkSpriteCacheValue> &allocator = std::allocator<RHUnkSpriteCacheValue>());
    RHUnkSpriteCacheIterator FUN_005c0800(const std::string &key);
    RHUnkSpriteCacheInsertResult FUN_005c0690(const RHUnkSpriteCacheValue &value);
    std::pair<RHUnkSpriteCacheIterator, bool> FUN_005c09c0(const RHUnkSpriteCacheValue &value);
    RHUnkSpriteCacheNode *FUN_005c15a0(const std::string &key);
    RHUnkSpriteCacheIterator end() const { RHUnkSpriteCacheIterator it; it.m_node = m_head; return it; }
    RHUnkSpriteScriptInfo &operator[](const std::string &key)
    {
        RHUnkSpriteScriptInfo info;
        RHUnkSpriteCacheIterator position = FUN_005c0690(RHUnkSpriteCacheValue(key, info)).m_first;
        return position.m_node->m_0c.m_info;
    }
};

#pragma pack(push, 1)
// SIZE 0x2e
struct RHUnkSpriteFileHeader
{
    char m_name[0x20]; // +0x00
    unsigned short m_rows; // +0x20
    unsigned short m_x; // +0x22
    unsigned short m_y; // +0x24
    int m_26; // +0x26
    int m_size; // +0x2a; sizeof = 0x2e
};
#pragma pack(pop)

class RHFrameHolder;

#pragma pack(push, 1)
// SIZE 0x0e
struct RHUnkSpriteRowHeader
{
    unsigned short m_count; // 0x00
    unsigned short m_kind; // 0x02
    int m_x; // 0x04
    int m_y; // 0x08
    unsigned short m_index; // 0x0c
};

// SIZE 0x0e
struct RHUnkSpriteFrameHeader
{
    int m_resource; // 0x00
    unsigned short m_frames; // 0x04
    short m_rate; // 0x06
    short m_x; // 0x08
    short m_y; // 0x0a
    unsigned short m_flags; // 0x0c
};
#pragma pack(pop)

class RHEngine;
extern RHEngine *g_pEngine;
extern RHFrameHolder *g_unk0x006c0b1c;
extern std::string g_unk0x006c0620;
extern std::string g_unk0x006c0630;
std::string FUN_004e4b40(const std::string &first, const std::string &second);

// SIZE 0x14
// VTABLE: GAME 0x00679e44
class RHSpriteScriptor
{
public:
    enum RHframeKind { FRAME_0, FRAME_1, FRAME_2, FRAME_3 };
    RHSpriteScriptor();
    virtual ~RHSpriteScriptor();
    static RHSpriteScriptor *GetInstance();
    RHUnkSpriteScriptInfo LoadSpriteScript(RHframeKind kind, const std::string &name, const std::string &profile);
    bool FUN_005c0490(SBFile &file, const char *profile);
    void FUN_005bfef0(SBFile &file, unsigned short count, std::vector<RHUnkSpriteRow> &rows, std::vector<unsigned short> &indices);
    void Emit(const std::string &name, const std::string &profile);
    RHUnkSpriteCache m_cache; // +0x04, head at +0x08
};

#endif
