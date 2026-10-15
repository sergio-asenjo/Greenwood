#ifndef SBUI_H
#define SBUI_H

#include "Decomp.h"

class RHUnk005ef320;
extern RHUnk005ef320 *g_unk0x6c11d0;

class RHUnk00613e90;

class RHUnkFXDraw
{
public:
    void FUN_005e5260();
    void Unk005e5160(unsigned long surface);
    unsigned long Unk005e4ed0(int width, int height, int, int);
    bool Unk005e5a00(unsigned long surface, RHUnk00613e90 &view, unsigned long flags);
    void Unk005e5ea0(RHUnk00613e90 &view);
    void FUN_005e6440(unsigned long surface, int first, int second, unsigned long third, unsigned long flags);
};

class SBThreadedInput
{
public:
    void FUN_005f1700();
    void PopMouseBackground(bool wait);
};

extern SBThreadedInput *g_unk0x6c1340;

class SBUIWindowView
{
public:
    virtual void V00() = 0;
    virtual void V04() = 0;
    virtual void AttachToDisplay(unsigned long display) = 0;
    virtual void V0c() = 0;
    virtual void V10() = 0;
    virtual void V14() = 0;
    virtual void V18(unsigned long surface) = 0;
    virtual void V1c() = 0;
};

class SBUIFontView
{
public:
    virtual void V00() = 0;
    virtual void V04() = 0;
    virtual void V08() = 0;
    virtual void V0c() = 0;
    virtual void V10() = 0;
    virtual void V14(void *renderer, bool alternate) = 0;
};

class SBUIWindowTooltip
{
public:
    void FUN_00627ee0(unsigned long display);
    void FUN_00628500();
};

class SBInputKeyboardState;

class SBUIUnk0060e1b0
{
public:
    SBUIUnk0060e1b0(int capacity);
    ~SBUIUnk0060e1b0();
    void FUN_0060e460();
    bool FUN_0060e2a0(const SBInputKeyboardState &input);
    bool EmitRefresh(const SBInputKeyboardState &input);
};

class SBUI
{
public:
    ~SBUI();
    void *FUN_006186d0(unsigned flags);
    void FUN_00618910(unsigned long surface);
    void FUN_006189e0(unsigned long frame);
    bool FUN_00619800(SBUIWindowView *window);
    void FUN_00619a00(SBUIWindowView *window);
    bool FUN_00619c20(unsigned long display);
    void FUN_00619c80(SBUIFontView *font, SBUIFontView *alternate);

    unsigned m_vptr;
    unsigned m_allocator;
    SBUIWindowView **m_first;
    SBUIWindowView **m_last;
    SBUIWindowView **m_end;
    SBUIWindowView **m_cursor;
    bool m_dirty;
    bool m_cursorValid;
    undefined m_1a[2];
    int m_index;
    SBUIWindowView *m_current;
    unsigned m_byteAllocator;
    unsigned char *m_flags;
    unsigned char *m_flagsLast;
    unsigned char *m_flagsEnd;
    unsigned char *m_flagsCursor;
    bool m_flagsDirty;
    undefined m_39[0xb];
    SBUIUnk0060e1b0 m_input;
    undefined m_45[0x1713];
    SBUIWindowTooltip *m_tooltip;
    unsigned short m_175c;
    unsigned short m_175e;
    unsigned short m_1760;
    unsigned short m_1762;
    RHUnk005ef320 *m_draw;
    unsigned long m_display;
    undefined m_176c[8];
    SBUIFontView *m_font;
    SBUIFontView *m_alternate;
    undefined m_177c[0x50];
    undefined m_renderer[0x20];
    unsigned long m_surface;
    undefined m_17f0[8];

    int Size() const
    {
        SBUIWindowView **first = *(SBUIWindowView **volatile *)&m_first;
        return first == 0 ? 0 : m_last - first;
    }
    int Find(SBUIWindowView *window)
    {
        m_dirty = false;
        m_current = window;
        int count = m_first == 0 ? 0 : m_last - m_first;
        m_cursor = m_first;
        m_cursorValid = true;
        int index = 0;
        for (; index < count; ++index, ++m_cursor)
            if (*m_cursor == window)
                break;
        return index < count ? index : -1;
    }
};

class RHUnk00641782
{
public:
    RHUnk00641782();
    ~RHUnk00641782();
    unsigned char m_00;
};

struct SBUIUnkTreeNode
{
    SBUIUnkTreeNode *left;
    SBUIUnkTreeNode *parent;
    SBUIUnkTreeNode *right;
    unsigned long key;
    undefined m_10[8];
    int color;
};

extern SBUIUnkTreeNode *g_unk0x006c18dc;
extern unsigned g_unk0x006c18d8;

struct SBUIUnkLess
{
};

struct SBUIUnkAlloc
{
};

class RHUnk00613e90;
void FUN_0059fb20(RHUnk00613e90 *destination, const RHUnk00613e90 &value);

struct SBUIUnkTreeValue
{
    unsigned long key;
    undefined m_04[8];
};

struct SBUIUnkSurfacePair
{
    unsigned long first;
    unsigned long second;
};

struct SBUIUnkTreeEntry
{
    SBUIUnkTreeEntry(const unsigned long &value, const SBUIUnkSurfacePair &surfaces)
        : key(value), second(surfaces) {}
    unsigned long key;
    SBUIUnkSurfacePair second;
};

class SBUIUnkTreeIterator
{
public:
    SBUIUnkTreeIterator() {}
    SBUIUnkTreeIterator(SBUIUnkTreeNode *value) : node(value) {}
    void FUN_0061bf30();
    void FUN_0061c3c0();
    static SBUIUnkTreeNode *&Left(SBUIUnkTreeNode *node) { return node->left; }
    static SBUIUnkTreeNode *Max(SBUIUnkTreeNode *node)
    {
        RHUnk00641782 lock;
        while (node->right != g_unk0x006c18dc)
            node = node->right;
        return node;
    }
    SBUIUnkTreeIterator &operator++()
    {
        FUN_0061bf30();
        return *this;
    }
    SBUIUnkTreeIterator operator++(int)
    {
        SBUIUnkTreeIterator previous = *this;
        FUN_0061bf30();
        return previous;
    }
    SBUIUnkTreeNode *node;
};

struct SBUIUnkTreeInsertResult
{
    SBUIUnkTreeIterator first;
    bool second;
    SBUIUnkTreeInsertResult() {}
    SBUIUnkTreeInsertResult(const SBUIUnkTreeIterator &position, const bool &inserted)
        : first(position), second(inserted) {}
};

struct SBUIUnkTreeRange
{
    SBUIUnkTreeRange(const SBUIUnkTreeIterator &lower, const SBUIUnkTreeIterator &upper)
        : first(lower), second(upper) {}
    SBUIUnkTreeIterator first;
    SBUIUnkTreeIterator second;
};

class SBUIUnkTree
{
public:
    SBUIUnkTree(const SBUIUnkLess &comp, bool multi, const SBUIUnkAlloc &alloc)
        : m_alloc(alloc), m_comp(comp), m_multi(multi)
    {
        Init();
    }
    static SBUIUnkTreeNode *Buynode(SBUIUnkTreeNode *parent, int color)
    {
        SBUIUnkTreeNode *node = (SBUIUnkTreeNode *)operator new(sizeof(SBUIUnkTreeNode));
        node->parent = parent;
        node->color = color;
        return node;
    }
    void Init()
    {
        RHUnk00641782 lock;
        if (g_unk0x006c18dc == 0) {
            g_unk0x006c18dc = Buynode(0, 1);
            g_unk0x006c18dc->left = 0;
            g_unk0x006c18dc->right = 0;
        }
        ++g_unk0x006c18d8;
        m_head = Buynode(g_unk0x006c18dc, 0);
        m_size = 0;
        Leftmost() = m_head;
        Rightmost() = m_head;
    }
    static SBUIUnkTreeNode *&Left(SBUIUnkTreeNode *node) { return node->left; }
    static SBUIUnkTreeNode *&Parent(SBUIUnkTreeNode *node) { return node->parent; }
    static SBUIUnkTreeNode *&Right(SBUIUnkTreeNode *node) { return node->right; }
    static int &Color(SBUIUnkTreeNode *node) { return node->color; }
    void RotateLeft(SBUIUnkTreeNode *node)
    {
        RHUnk00641782 lock;
        SBUIUnkTreeNode *right = node->right;
        node->right = right->left;
        if (right->left != g_unk0x006c18dc)
            right->left->parent = node;
        right->parent = node->parent;
        if (node == m_head->parent)
            m_head->parent = right;
        else if (node == node->parent->left)
            node->parent->left = right;
        else
            node->parent->right = right;
        right->left = node;
        node->parent = right;
    }
    void RotateRight(SBUIUnkTreeNode *node)
    {
        RHUnk00641782 lock;
        SBUIUnkTreeNode *left = node->left;
        node->left = left->right;
        if (left->right != g_unk0x006c18dc)
            left->right->parent = node;
        left->parent = node->parent;
        if (node == m_head->parent)
            m_head->parent = left;
        else if (node == node->parent->right)
            node->parent->right = left;
        else
            node->parent->left = left;
        left->right = node;
        node->parent = left;
    }
    void FUN_0061b190();
    SBUIUnkTreeIterator FUN_0061b720(SBUIUnkTreeIterator first, SBUIUnkTreeIterator last);
    SBUIUnkTreeInsertResult FUN_0061b850(const SBUIUnkTreeValue &value);
    SBUIUnkTreeIterator FUN_0061b980(SBUIUnkTreeIterator position);
    void FUN_0061bea0(SBUIUnkTreeNode *node);
    SBUIUnkTreeIterator FUN_0061bfe0(SBUIUnkTreeNode *child, SBUIUnkTreeNode *parent, const SBUIUnkTreeValue &value);
    SBUIUnkTreeNode *&Root() { return m_head->parent; }
    SBUIUnkTreeNode *&Leftmost() { return m_head->left; }
    SBUIUnkTreeNode *&Rightmost() { return m_head->right; }
    SBUIUnkTreeIterator begin() { return SBUIUnkTreeIterator(Leftmost()); }
    SBUIUnkTreeIterator lower_bound(const unsigned long &key) { return SBUIUnkTreeIterator(FUN_0061c320(key)); }
    SBUIUnkTreeIterator upper_bound(const unsigned long &key) { return SBUIUnkTreeIterator(FUN_0061c370(key)); }
    SBUIUnkTreeRange equal_range(const unsigned long &key)
    {
        return SBUIUnkTreeRange(lower_bound(key), upper_bound(key));
    }
    static void Distance(SBUIUnkTreeIterator first, SBUIUnkTreeIterator last, unsigned &count)
    {
        for (; first.node != last.node; ++first)
            ++count;
    }
    unsigned erase(const unsigned long &key)
    {
        SBUIUnkTreeRange range = equal_range(key);
        unsigned count = 0;
        Distance(range.first, range.second, count);
        FUN_0061b720(range.first, range.second);
        return count;
    }
    SBUIUnkTreeIterator Begin()
    {
        SBUIUnkTreeIterator first;
        first.node = m_head->left;
        return first;
    }
    void Erase(SBUIUnkTreeNode *node)
    {
        RHUnk00641782 lock;
        SBUIUnkTreeNode *next = node;
        while (next != g_unk0x006c18dc) {
            FUN_0061bea0(next->right);
            next = next->left;
            delete node;
            node = next;
        }
    }
    static SBUIUnkTreeNode *FUN_0061c2e0(SBUIUnkTreeNode *node);
    SBUIUnkTreeNode *FUN_0061c320(const unsigned long &key);
    SBUIUnkTreeNode *FUN_0061c370(const unsigned long &key);

    SBUIUnkAlloc m_alloc;
    SBUIUnkLess m_comp;
    undefined m_02[2];
    SBUIUnkTreeNode *m_head;
    bool m_multi;
    undefined m_09[3];
    unsigned m_size;
};

struct SBUIUnkMap
{
    SBUIUnkTreeInsertResult insert(const SBUIUnkTreeEntry &value)
    {
        SBUIUnkTreeInsertResult answer;
        answer = m_tree.FUN_0061b850((const SBUIUnkTreeValue &)value);
        return SBUIUnkTreeInsertResult(answer.first, answer.second);
    }
    SBUIUnkSurfacePair &operator[](const unsigned long &key)
    {
        SBUIUnkTreeIterator position = insert(SBUIUnkTreeEntry(key, SBUIUnkSurfacePair())).first;
        return *(SBUIUnkSurfacePair *)position.node->m_10;
    }
    unsigned erase(const unsigned long &key) { return m_tree.erase(key); }
    SBUIUnkTree m_tree;
};

class SBUIUnkImage
{
public:
    virtual void V00() = 0;
    virtual void V04() = 0;
    virtual void V08() = 0;
    virtual void V0c() = 0;
    virtual void V10() = 0;
    virtual void V14() = 0;
    virtual void V18() = 0;
    virtual void V1c() = 0;
    virtual void V20(RHUnk005ef320 *draw, unsigned long surface) = 0;
    virtual void V24() = 0;
    virtual void V28() = 0;
    virtual int V2c() = 0;
    virtual int V30() = 0;
};

class SBUIUnkSurfaceBase
{
public:
    SBUIUnkSurfaceBase() { m_vptr = 0x0067ae04; }
    ~SBUIUnkSurfaceBase();
    void *FUN_0061b040(unsigned flags);
    unsigned m_vptr;
};

class SBUIUnkSurface : public SBUIUnkSurfaceBase
{
public:
    SBUIUnkSurface(unsigned long surface);
    ~SBUIUnkSurface();
    void *FUN_0061b020(unsigned flags);
    void *FUN_0061b350();
    bool FUN_0061b640(void *dc);
    unsigned long FUN_0061b380(SBUIUnkImage *image, SBUIUnkImage *mask, bool keyed);
    void FUN_0061b4c0(SBUIUnkSurfacePair &surfaces);
    void FUN_0061b660(unsigned long key);
    RHUnk005ef320 *m_draw;
    unsigned long m_surface;
    SBUIUnkTree m_tree;
    unsigned long m_serial;
};

class RHGameActionCalls : public SBUI
{
public:
    void FUN_00619cc0();
};

class RHMapWindowPart : public SBUI
{
public:
    void FUN_00618850(void *frame);
    bool FUN_00619ad0(void *window);
};

#endif
