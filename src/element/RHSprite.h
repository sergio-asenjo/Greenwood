#ifndef RHSPRITE_H
#define RHSPRITE_H

#include "RHSprite_calls.h"
#include <list>

struct RHSpriteListNode
{
    RHSpriteListNode *next;
    RHSpriteListNode *previous;
    int value;
};

struct RHSpriteListIterator
{
    RHSpriteListNode *node;
    RHSpriteListIterator(RHSpriteListNode *value) : node(value) {}
    RHSpriteListIterator(const RHSpriteListIterator &value) : node(value.node) {}
    RHSpriteListIterator &operator=(const RHSpriteListIterator &value) { node = value.node; return *this; }
    RHSpriteListIterator &operator++() { node = node->next; return *this; }
    RHSpriteListIterator operator++(int);
    int &operator*() { return node->value; }
};

struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &, int, std::bidirectional_iterator_tag);

class RHSpriteList
{
public:
    RHSpriteListIterator erase(RHSpriteListIterator);
    RHSpriteListIterator begin();
    void FUN_005c8e40(int);
    void Find(const int &value, int &found, RHSpriteListNode *sentinel, int size)
    {
        int i;
        current = RHSpriteListIterator(sentinel->next);
        for (i = 0; i < size; ++i, ++current)
        {
            if (*current == value)
                break;
        }
        if (i < size)
        {
            found = i;
            dirty = false;
            index = i;
            return;
        }
        dirty = true;
        found = -1;
    }
    int Value(int wanted)
    {
        FUN_005c8e40(wanted);
        return current.node->value;
    }
    void Clear()
    {
        RHSpriteListNode *last = head;
        RHSpriteListNode *node = last->next;
        while (node != last)
        {
            RHSpriteListNode *removed = node;
            node = node->next;
            erase(RHSpriteListIterator(removed));
        }
        dirty = true;
    }
    RHSpriteListIterator insert(RHSpriteListIterator position, const int &value)
    {
        RHSpriteListNode *next = position.node;
        RHSpriteListNode *previous = next->previous;
        RHSpriteListNode *node = (RHSpriteListNode *)operator new(sizeof(RHSpriteListNode));
        node->next = next ? next : node;
        node->previous = previous ? previous : node;
        next->previous = node;
        node->previous->next = node;
        int *destination = &node->value;
        if (destination)
            *destination = value;
        ++count;
        dirty = true;
        return RHSpriteListIterator(node);
    }
    void Append(const int &value)
    {
        insert(RHSpriteListIterator(head), value);
    }
    void GoTo(int wanted)
    {
        int size = count;
        std::bidirectional_iterator_tag category;
        if (dirty)
        {
            if (wanted <= (size + 1) / 2)
            {
                current = RHSpriteListIterator(head->next);
                FUN_005c9010((RHUnk005c9010Iterator &)current, wanted, category);
            }
            else
            {
                current = RHSpriteListIterator(head);
                FUN_005c9010((RHUnk005c9010Iterator &)current, wanted - size, category);
            }
            dirty = false;
            index = wanted;
        }
        else
        {
            int previous = index;
            if (wanted != previous)
            {
                if (wanted < previous)
                {
                    if (wanted < (previous + 1) / 2)
                    {
                        current = begin();
                        FUN_005c9010((RHUnk005c9010Iterator &)current, wanted, category);
                    }
                    else
                        FUN_005c9010((RHUnk005c9010Iterator &)current, wanted - previous, category);
                }
                else if (wanted < (previous + size) / 2)
                    FUN_005c9010((RHUnk005c9010Iterator &)current, wanted - previous, category);
                else
                {
                    current = RHSpriteListIterator(head);
                    FUN_005c9010((RHUnk005c9010Iterator &)current, wanted - size, category);
                }
                index = wanted;
            }
        }
    }
    char m_00[4];
    RHSpriteListNode *head; // +0x04
    int count; // +0x08
    RHSpriteListIterator current; // +0x0c
    bool dirty; // +0x10
    int index; // +0x14
};

class RHUnk005b5e00
{
public:
    void *Unk();
};

struct RHSpriteFrameTable
{
    char m_00[4];
    unsigned short *m_04; // +0x04, pointer to WORD entries
    unsigned short Frame(int animation) const
    {
        unsigned short *entries = *(unsigned short *const volatile *)&m_04;
        return entries[animation];
    }
};

class RHUnk005bd5b0
{
public:
    bool Unk(bool);
};

class RHPositionInterface
{
public:
    bool Serialize(SBFile &);
};

class RHEngine
{
public:
    bool SerializeElementPointer(SBFile &, class RHElement *&);
};
extern RHEngine *g_pEngine;

class RHUnk005b5ed0
{
public:
    bool FUN_005b5ed0(SBFile &);
    void FUN_005bd8b0();
    char m_00[0xd8];
    unsigned short m_d8; // +0xd8
    char m_da[0x76];
    int m_150; // +0x150
    char m_154[0x14];
    char *m_168; // +0x168
    char m_16c[0x18];
    unsigned short m_184; // +0x184, WORD
    unsigned short m_186; // +0x186, WORD
    unsigned short m_188; // +0x188, WORD
    unsigned short m_18a; // +0x18a, WORD
    unsigned short m_18c; // +0x18c, WORD
    unsigned short m_18e; // +0x18e, WORD
    unsigned short m_190; // +0x190, WORD
    char m_192; // +0x192, BYTE
    char m_193; // +0x193, BYTE
    char m_194; // +0x194, BYTE
    char m_195[5];
    unsigned short m_19a; // +0x19a, WORD
    unsigned short m_19c; // +0x19c, WORD
    char m_19e[2];
    SBGeoBoundingBox2D m_1a0; // +0x1a0
    char m_1b4[0x10];
    int m_1c4; // +0x1c4, DWORD
    class RHElement *m_1c8; // +0x1c8, pointer
    char m_1cc; // +0x1cc, BYTE
    char m_1cd[0xf];
    int m_1dc; // +0x1dc, DWORD
    RHSpriteList m_1e0; // +0x1e0
    bool m_1f8; // +0x1f8, BYTE
    int m_1fc; // +0x1fc, DWORD
    int m_200; // +0x200, DWORD
    RHSpriteList m_204; // +0x204
    char m_21c[0xc];
    unsigned char m_228; // +0x228, BYTE
};

class RHSprite : public RHUnk005b5ed0
{
public:
    int PerformAction(RHOrder *, int, int, bool);
    void LoadPositionInfoFromFile(SBFile &, int);
    int PerformMotion(RHOrder *, RHOrder *, int, int, float, int, bool);
    void FUN_005b7720(int);
    void FUN_005b7300(int, int);
    bool FUN_005b7820(int);
    void FUN_005bd450();
    unsigned short FUN_005bdbf0(unsigned short, unsigned short);
    short FUN_005bdc20(unsigned short, unsigned short);
    void Emit(SBFile &);
};

void RHSerializeName(SBFile &, const char *);

#endif
