#ifndef RHSPRITESCRIPTOR_H
#define RHSPRITESCRIPTOR_H

#include "RHSaveGame.h"
#include <vector>

class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(float x, float y);
    SBGeoPoint2D(const SBGeoPoint2D &point);
    ~SBGeoPoint2D();
    float m_x; // +0x00
    float m_y; // +0x04
};

class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D();
    SBGeoVector2D(float x, float y);
    ~SBGeoVector2D() {}
    SBGeoVector2D &operator=(const SBGeoVector2D &other);
};

struct RHUnkSpriteRow
{
    char m_data[0x64]; // LoadRows vector stride, 0x005bdf70
};

struct RHUnkSpriteScriptInfo
{
    RHUnkSpriteScriptInfo() {}
    RHUnkSpriteScriptInfo(const RHUnkSpriteScriptInfo &other)
        : m_rows(other.m_rows), m_indices(other.m_indices), m_position(other.m_position), m_size(other.m_size) {}
    ~RHUnkSpriteScriptInfo();
    std::vector<RHUnkSpriteRow> *m_rows; // +0x00
    std::vector<unsigned short> *m_indices; // +0x04
    SBGeoVector2D m_position; // +0x08
    SBGeoVector2D m_size; // +0x10; sizeof = 0x18
};

struct RHUnkSpriteCacheNode
{
    char m_0[0x1c];
    RHUnkSpriteScriptInfo m_value; // +0x1c
};

struct RHUnkSpriteCacheIterator
{
    RHUnkSpriteCacheNode *m_node;
    bool operator==(const RHUnkSpriteCacheIterator &other) const { return m_node == other.m_node; }
};

struct RHUnkSpriteCacheValue
{
    RHUnkSpriteCacheValue(const std::string &key, const RHUnkSpriteScriptInfo &info);
    std::string m_key; // +0x00
    RHUnkSpriteScriptInfo m_info; // +0x10; sizeof = 0x28
};

struct RHUnkSpriteCacheInsertResult
{
    RHUnkSpriteCacheIterator m_first;
    bool m_second;
};

class RHUnkSpriteCache
{
public:
    RHUnkSpriteCacheIterator FUN_005c0800(const std::string &key);
    RHUnkSpriteCacheInsertResult FUN_005c0690(const RHUnkSpriteCacheValue &value);
    RHUnkSpriteCacheIterator end() const { RHUnkSpriteCacheIterator it; it.m_node = m_head; return it; }
    RHUnkSpriteScriptInfo &operator[](const std::string &key)
    {
        return FUN_005c0690(RHUnkSpriteCacheValue(key, RHUnkSpriteScriptInfo())).m_first.m_node->m_value;
    }
    char m_0[4];
    RHUnkSpriteCacheNode *m_head; // +0x04
    unsigned m_count; // +0x08
};

#pragma pack(push, 1)
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

class RHUnkSpriteBank
{
public:
    bool FUN_00506b10(SBFile &file);
};

class RHEngine;
extern RHEngine *g_pEngine;
extern RHUnkSpriteBank *g_unk0x006c0b1c;
extern std::string g_unk0x006c0620;
extern std::string g_unk0x006c0630;
std::string FUN_004e4b40(const std::string &first, const std::string &second);
std::string FUN_004e4c70(const std::string &first, const char *second);

class RHSpriteScriptor
{
public:
    enum RHframeKind { FRAME_0, FRAME_1, FRAME_2, FRAME_3 };
    RHUnkSpriteScriptInfo LoadSpriteScript(RHframeKind kind, const std::string &name, const std::string &profile);
    bool FUN_005c0490(SBFile &file, const char *profile);
    void FUN_005bfef0(SBFile &file, unsigned short count, std::vector<RHUnkSpriteRow> &rows, std::vector<unsigned short> &indices);
    void Emit(const std::string &name, const std::string &profile);
    char m_0[4]; // +0x00
    RHUnkSpriteCache m_cache; // +0x04, head at +0x08
};

#endif
