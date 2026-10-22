#ifndef SB_NATIVE_FONT_H
#define SB_NATIVE_FONT_H

#include "SBFont.h"
#include "SBResourceManager.h"
#include <functional>

struct SBNativeFontCharacterInfo
{
    unsigned long m_position;
    long m_width;
    long m_left;
    long m_right;
};

struct SBNativeFontCharacterValue
{
    SBNativeFontCharacterValue() {}
    SBNativeFontCharacterValue(const unsigned short &character, const SBNativeFontCharacterInfo &info)
        : m_character(character), m_info(info) {}
    unsigned short m_character;
    SBNativeFontCharacterInfo m_info;
};

struct SBNativeFontCharacterPair
{
    SBNativeFontCharacterPair(const SBResourceUnkKeyIterator &iterator, const bool &inserted)
        : m_iterator(iterator), m_inserted(inserted) {}
    SBResourceUnkKeyIterator m_iterator;
    bool m_inserted;
};

extern unsigned g_unk0x006c18c4;
extern SBResourceUnkKeyNode *g_unk0x006c18c8;

struct SBNativeFontDecNode
{
    SBNativeFontDecNode *m_00;
    SBNativeFontDecNode *m_04;
    SBNativeFontDecNode *m_08;
    unsigned short m_0c;
    SBNativeFontCharacterInfo m_info;
    int m_20;
    static SBNativeFontDecNode *&Left(SBNativeFontDecNode *node) { return node->m_00; }
};

class SBNativeFontCharacterTree : public SBResourceUnkTreeEnd
{
public:
    SBNativeFontCharacterTree()
    {
        std::less<unsigned short> comparison;
        std::allocator<unsigned char> allocator;
        m_00[0] = *(unsigned char *)&allocator;
        m_00[1] = *(unsigned char *)&comparison;
        *(bool *)&m_08 = false;
        SBFontLock lock;
        if (!g_unk0x006c18c8) {
            SBResourceUnkKeyNode *node = (SBResourceUnkKeyNode *)operator new(0x24);
            *(void **)((char *)node + 4) = 0;
            *(unsigned *)((char *)node + 0x20) = 1;
            g_unk0x006c18c8 = node;
            *(void **)node = 0;
            *(void **)((char *)g_unk0x006c18c8 + 8) = 0;
        }
        unsigned references = g_unk0x006c18c4;
        SBResourceUnkKeyNode *parent = g_unk0x006c18c8;
        g_unk0x006c18c4 = references + 1;
        SBResourceUnkKeyNode *node = (SBResourceUnkKeyNode *)operator new(0x24);
        *(SBResourceUnkKeyNode **)((char *)node + 4) = parent;
        *(unsigned *)((char *)node + 0x20) = 0;
        m_head = node;
        m_count = 0;
        *(SBResourceUnkKeyNode **)node = node;
        *(SBResourceUnkKeyNode **)((char *)m_head + 8) = m_head;
    }
    ~SBNativeFontCharacterTree()
    {
        SBResourceUnkKeyIterator first;
        first.m_node = *(SBResourceUnkKeyNode **)m_head;
        SBResourceUnkKeyIterator last;
        last.m_node = m_head;
        FUN_006176a0(first, last);
        std::allocator<SBNativeFontDecNode> allocator;
        allocator.deallocate((SBNativeFontDecNode *)m_head, 1);
        m_head = 0;
        m_count = 0;
        {
            SBFontLock lock;
            if (--g_unk0x006c18c4 == 0) {
                allocator.deallocate((SBNativeFontDecNode *)g_unk0x006c18c8, 1);
                g_unk0x006c18c8 = 0;
            }
        }
    }
    SBResourceUnkKeyIterator FUN_00617e20(const unsigned short &);
    SBResourceUnkKeyIterator Find(const unsigned short &character)
    {
        SBResourceUnkKeyIterator value(FUN_00617e20(character).m_node);
        SBResourceUnkKeyNode *node = value.m_node;
        return node == FUN_00617690().m_node || character < *(unsigned short *)&node->m_key ? FUN_00617690() : value;
    }
    SBResourceUnkKeyNode *FUN_00618280(const unsigned short &);
    SBNativeFontCharacterPair FUN_006177d0(const SBNativeFontCharacterValue &);
    SBResourceUnkKeyIterator FUN_00617f80(SBNativeFontDecNode *, SBNativeFontDecNode *, const SBNativeFontCharacterValue &);
    void Lrotate(SBNativeFontDecNode *);
    void Rrotate(SBNativeFontDecNode *);
    SBNativeFontDecNode *&InsertRoot() { return *(SBNativeFontDecNode **)((char *)m_head + 4); }
    SBResourceUnkKeyIterator FUN_006176a0(SBResourceUnkKeyIterator, SBResourceUnkKeyIterator);
    void FUN_00617e40(SBResourceUnkKeyNode *);
    SBResourceUnkKeyIterator FUN_00617900(SBResourceUnkKeyIterator);
    typedef SBNativeFontDecNode Node;
    static Node *&Left(Node *node) { return node->m_00; }
    static Node *&Parent(Node *node) { return node->m_04; }
    static Node *&Right(Node *node) { return node->m_08; }
    static int &Color(Node *node) { return node->m_20; }
    Node *&EraseLeftmost() { return *(Node **)m_head; }
    Node *&EraseRightmost() { return *(Node **)((char *)m_head + 8); }
    SBResourceUnkKeyNode *&Root() { return *(SBResourceUnkKeyNode **)((char *)m_head + 4); }
    SBResourceUnkKeyNode *&Leftmost() { return *(SBResourceUnkKeyNode **)m_head; }
    SBResourceUnkKeyNode *&Rightmost() { return *(SBResourceUnkKeyNode **)((char *)m_head + 8); }
    SBResourceUnkKeyIterator begin() { return SBResourceUnkKeyIterator(Leftmost()); }
    void FUN_00616c90();
    unsigned m_08;
    unsigned m_count;
};

class SBNativeFontPictureCalls
{
public:
    virtual void V00();
    virtual void V04();
    virtual void V08();
    virtual void V0c();
    virtual bool V10(SBFile &);
    virtual void V14();
    virtual void V18();
    virtual bool V1c(SBFile &);
};

class SBNativeFontRenderContext
{
public:
    virtual void V00();
    virtual void V04();
    virtual void *V08();
    virtual unsigned long V0c(void *, void *, bool);
    virtual void V10(void *context);
    virtual void V14(unsigned long);
};

class SBGeoPoint2D;
class SBGeoBoundingBox2D;

#include "RHUnk006114c0.h"

#include "SBNativeFontBase.h"

class __declspec(novtable) SBNativeFont : public SBNativeFontBase
{
public:
    typedef SBNativeFontCharacterInfo CharacterInfo;

    SBNativeFont(const std::string &name);
    ~SBNativeFont();
    void *FUN_00616c70(unsigned flags);
    void AttachToRenderContext(SBNativeFontRenderContext *, unsigned long);
    void DetachFromRenderContext();
    unsigned FUN_00616f40() const;
    virtual unsigned GetImplementationVersion() const;
    unsigned FUN_00617080() const;
    const CharacterInfo *GetCharacterInfo(unsigned short) const;
    void GetImplementationTag(char (&tag)[6]) const;
    long GetCharacterWidth(unsigned short character, long &left, long &right) const;
    bool LoadFromStream(SBFile &);
    bool Render(unsigned short character, SBGeoPoint2D &position, const SBGeoBoundingBox2D &clip, bool measure) const;
    bool SaveToStream(SBFile &);
    unsigned m_nativeHeader[3];
    unsigned m_spacing;
    SBNativeFontCharacterTree m_characters;
    RHUnk006114c0 m_pictures[2];
    unsigned long m_surface;
};

#endif
