// RHElementObject — declarations shared by RHElementObject.cpp (decompiled TU)
// and RHElementObject_stubs.cpp (external-symbol stubs).
//
// BINDING (0x004b2190): RHElementObject::Serialize(SBFile&). See
// src/RHElementObject.cpp for the evidence chain.
//
// Member offsets are derived from the target instructions of
// RHElementObject::Serialize (0x004b2190) and its neighbour
// RHElementObject::Create (0x004b2010, Mac name from
// symbols/mac-RH.txt). Only the offsets the matched function touches are laid
// out; every other byte is opaque padding. The base RHElement is 0xa8 bytes
// (its own vptr + untouched fields), so RHElementObject's members start there.

#include "SB.h"

class SBGeoPoint2D;

class RHElement
{
public:
    virtual bool Serialize(SBFile &file);
    virtual void V04();
    virtual void V08();
    virtual void V0c();
    virtual void V10();
    virtual void V14();
    virtual void V18();
    virtual void V1c();
    virtual void V20();
    virtual void V24();
    virtual void V28();
    virtual void V2c();
    virtual void V30();
    virtual void V34();
    virtual void V38();
    virtual void V3c();
    virtual void V40();
    virtual void V44();
    virtual void V48();
    virtual void V4c();
    virtual void V50();
    virtual void V54();
    virtual void V58();
    virtual void V5c();
    virtual void V60();
    virtual void V64();
    virtual unsigned V68();
    virtual bool V6c(void *actor);

private:
    char m_unkBase[0xa4]; // [0x04, 0xa8): RHElement-owned, not touched here
};

// Nested serialisable sub-object stored at RHElementObject+0xbc. Its
// Serialize is the target 0x00521210; identity unproven, so the type keeps a
// neutral name (see 05-naming.md).
class RHUnk004b2190Member
{
public:
    bool Serialize(SBFile &file);

private:
    char m_unk[0x40]; // [0x00, 0x40): opaque; keeps the following member at +0xfc
};

class RHElementObject : public RHElement
{
public:
    virtual bool Serialize(SBFile &file);

    void Emit(SBFile &file);
    bool FUN_004b2420(void *actor) const;
    bool FUN_004b24d0(const SBGeoPoint2D &point) const;
    void FUN_004b2600(void *points, void *lines, void *actor);
    void *FUN_004b29c0(void *actor);

    int m_a8;                     // [0xa8]
    char m_ac;                    // [0xac]
    char m_ad;                    // [0xad]
    short m_ae;                   // [0xae]
    int m_b0;                     // [0xb0]
    int m_b4;                     // [0xb4]
    int m_b8;                     // [0xb8]
    RHUnk004b2190Member m_member; // [0xbc]
    char m_fc;                    // [0xfc]
    char m_fd;                    // [0xfd]
    short m_fe;                   // [0xfe]
};

// Serialises a type-name tag into the stream; target 0x005e1b70. Free-function
// form is a placeholder calling convention — the target ignores its incoming
// ecx and takes (SBFile&, const char*); see the binding notes.
void RHSerializeName(SBFile &file, const char *name);

class RHUnk00641782
{
public:
    RHUnk00641782();
    ~RHUnk00641782();
};

struct RHObjectMasterNode
{
    RHObjectMasterNode *left;
    RHObjectMasterNode *parent;
    RHObjectMasterNode *right;
    int key;
    void *value;
    int color;
};

struct RHObjectMasterValue
{
    int key;
    void *value;
};

extern RHObjectMasterNode *g_unk0x006c09c0;
extern unsigned g_unk0x006c09c4;

class RHObjectPCQuantity
{
public:
    virtual void V00();
    virtual void V04();
    virtual void V08();
    virtual void V0c();
    virtual void V10();
    virtual void V14();
    virtual void V18();
    virtual void V1c();
    virtual void V20();
    virtual void V24();
    virtual void V28();
    virtual void V2c();
    virtual void V30();
    virtual void V34();
    virtual void V38();
    virtual void V3c();
    virtual void V40();
    virtual void V44();
    virtual void V48();
    virtual void V4c();
    virtual void V50();
    virtual void V54();
    virtual void V58();
    virtual void V5c();
    virtual void V60();
    virtual void V64();
    virtual void V68();
    virtual void V6c();
    virtual void V70();
    virtual void V74();
    virtual void V78();
    virtual void V7c();
    virtual void V80();
    virtual void V84();
    virtual void V88();
    virtual void V8c();
    virtual void V90();
    virtual void V94();
    virtual void V98();
    virtual void V9c();
    virtual void Va0();
    virtual void Va4();
    virtual void Va8();
    virtual void Vac();
    virtual void Vb0();
    virtual void Vb4();
    virtual void Vb8();
    virtual void Vbc();
    virtual void Vc0();
    virtual void Vc4();
    virtual void Vc8();
    virtual void Vcc();
    virtual void Vd0();
    virtual void Vd4();
    virtual void Vd8();
    virtual void Vdc();
    virtual void Ve0();
    virtual unsigned short Ve4(int value);
    unsigned short FUN_0049d5e0(int value);
};

struct RHObjectMasterIterator
{
    RHObjectMasterIterator() {}
    RHObjectMasterIterator(RHObjectMasterNode *value) : node(value) {}
    bool operator!=(const RHObjectMasterIterator &other) const { return node != other.node; }
    void FUN_004b3ab0();
    void FUN_004b3eb0();
    static RHObjectMasterNode *&Left(RHObjectMasterNode *value) { return value->left; }
    RHObjectMasterIterator operator++(int)
    {
        RHObjectMasterIterator previous = *this;
        FUN_004b3ab0();
        return previous;
    }
    RHObjectMasterNode *node;
};

struct RHObjectMasterInsertResult
{
    RHObjectMasterInsertResult() {}
    RHObjectMasterInsertResult(const RHObjectMasterIterator &value, const bool &added)
        : position(value), inserted(added) {}
    RHObjectMasterIterator position;
    bool inserted;
};

class RHObjectMasterTree
{
public:
    RHObjectMasterTree(const char &compare, const char &allocator);
    void FUN_004b2ea0();
    RHObjectMasterIterator FUN_004b32a0(RHObjectMasterIterator first, RHObjectMasterIterator last);
    RHObjectMasterInsertResult FUN_004b33d0(const RHObjectMasterValue &value);
    RHObjectMasterIterator FUN_004b3500(RHObjectMasterIterator entry);
    void FUN_004b3a20(RHObjectMasterNode *node);
    RHObjectMasterIterator FUN_004b3b60(RHObjectMasterNode *node, RHObjectMasterNode *parent, const RHObjectMasterValue &value);
    RHObjectMasterNode *FUN_004b3e60(const int &key);
    RHObjectMasterNode *&Root() { return head->parent; }
    RHObjectMasterNode *&Leftmost() { return head->left; }
    RHObjectMasterNode *&Rightmost() { return head->right; }
    RHObjectMasterIterator Begin() { return RHObjectMasterIterator(Leftmost()); }
    RHObjectMasterIterator End() { return RHObjectMasterIterator(head); }
    static RHObjectMasterNode *&Left(RHObjectMasterNode *node) { return node->left; }
    static RHObjectMasterNode *&Right(RHObjectMasterNode *node) { return node->right; }
    static RHObjectMasterNode *&Parent(RHObjectMasterNode *node) { return node->parent; }
    static int &Color(RHObjectMasterNode *node) { return node->color; }
    void RotateLeft(RHObjectMasterNode *node)
    {
        RHUnk00641782 lock;
        RHObjectMasterNode *right = node->right;
        node->right = right->left;
        if (right->left != g_unk0x006c09c0)
            right->left->parent = node;
        right->parent = node->parent;
        if (node == head->parent)
            head->parent = right;
        else if (node == node->parent->left)
            node->parent->left = right;
        else
            node->parent->right = right;
        right->left = node;
        node->parent = right;
    }
    void RotateRight(RHObjectMasterNode *node)
    {
        RHUnk00641782 lock;
        RHObjectMasterNode *left = node->left;
        node->left = left->right;
        if (left->right != g_unk0x006c09c0)
            left->right->parent = node;
        left->parent = node->parent;
        if (node == head->parent)
            head->parent = left;
        else if (node == node->parent->right)
            node->parent->right = left;
        else
            node->parent->left = left;
        left->right = node;
        node->parent = left;
    }
    char allocator;
    char compare;
    RHObjectMasterNode *head;
    bool multi;
    unsigned size;
};

extern RHObjectMasterNode *g_unk0x006c09c0;
extern unsigned g_unk0x006c09c4;

class RHElementObjectMaster
{
public:
    virtual ~RHElementObjectMaster();
    static void AddMasterObject(int key, RHElementObjectMaster *master);
    static void DeleteMasters();
    void FUN_004b3170(const std::string &first, const std::string &second, bool flag);
};
