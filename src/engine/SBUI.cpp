#include "SBUI.h"
#include <vector>

DECOMP_SIZE_ASSERT(SBUI, 0x17f8)

class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    ~SBGeoPoint2D();
    float m_x;
    float m_y;
};

class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D();
    ~SBGeoBoundingBox2D();
    SBGeoPoint2D m_0;
    SBGeoPoint2D m_8;
    undefined m_10[4];
};

template <class T>
class SBUIArrayLifetime : public std::vector<T>
{
public:
    SBUIArrayLifetime() : m_dirty(true) {}
    T *m_cursor;
    bool m_dirty;
    bool m_cursorValid;
    int m_index;
    void *m_current;
};

class SBUILifetime
{
public:
    SBUILifetime();
    unsigned m_vptr;
    SBUIArrayLifetime<SBUIWindowView *> m_windows;
    SBUIArrayLifetime<char> m_flags;
    SBUIUnk0060e1b0 m_input;
    undefined m_45[0x170f];
    bool m_1754;
    SBUIWindowTooltip *m_tooltip;
    unsigned short m_175c;
    unsigned short m_175e;
    unsigned short m_1760;
    unsigned short m_1762;
    RHUnk005ef320 *m_draw;
    unsigned long m_display;
    SBGeoPoint2D m_176c;
    SBUIFontView *m_font;
    SBUIFontView *m_alternate;
    unsigned long m_177c;
    unsigned long m_1780;
    unsigned long m_1784;
    bool m_1788;
    std::vector<unsigned long> m_178c;
    SBGeoBoundingBox2D m_179c[2];
    bool m_17c4;
    bool m_17c5;
    unsigned long m_17c8;
    SBUIUnkSurface m_17cc;
    unsigned long m_surface;
    unsigned long m_17f0;
    unsigned long m_17f4;
};

DECOMP_SIZE_ASSERT(SBUILifetime, 0x17f8)

// Parked: the box-array ctor/dtor pointers are the unannotated 0x6079c0 ctor and the folded 0x40ee30 dtor.
// STUB: GAME 0x00618580
SBUILifetime::SBUILifetime()
    : m_input(0x1f4), m_1754(true), m_tooltip(0), m_175c(0), m_175e(0), m_1760(0), m_1762(0),
      m_font(0), m_alternate(0), m_177c(0), m_1780(0), m_1784(0x4b), m_1788(false),
      m_17c8(0), m_17cc(0), m_surface(0), m_17f0(0), m_17f4(0)
{
    m_vptr = 0x0067ad98;
    m_17c4 = false;
    m_17c5 = false;
}

// FUNCTION: GAME 0x006186d0
void *SBUI::FUN_006186d0(unsigned flags)
{
    this->~SBUI();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00618850
void RHMapWindowPart::FUN_00618850(void *frame)
{
    unsigned count = m_first == 0 ? 0 : m_last - m_first;
    unsigned long *counter = (unsigned long *)frame;
    unsigned long value = counter != 0 ? *counter : 0;
    for (unsigned index = 0; index < count; ++index)
        m_first[index]->V1c();
    ((RHUnkFXDraw *)m_draw)->FUN_005e6440(m_surface, 0, 0, 0, 0);
    FUN_006189e0(value++);
    g_unk0x6c1340->FUN_005f1700();
    ((RHUnkFXDraw *)g_unk0x6c11d0)->FUN_005e5260();
    g_unk0x6c1340->PopMouseBackground(false);
    ((RHUnkFXDraw *)m_draw)->FUN_005e6440(m_surface, 0, 0, 0, 0);
    FUN_006189e0(value);
    if (counter != 0)
        *counter = value + 1;
}

// FUNCTION: GAME 0x00618910
void SBUI::FUN_00618910(unsigned long surface)
{
    unsigned count = m_first == 0 ? 0 : m_last - m_first;
    ((RHUnkFXDraw *)m_draw)->FUN_005e6440(m_surface, surface, 0, surface, 0);
    for (unsigned index = 0; index < count; ++index)
        m_first[index]->V18(surface);
    g_unk0x6c1340->FUN_005f1700();
    ((RHUnkFXDraw *)g_unk0x6c11d0)->FUN_005e5260();
    g_unk0x6c1340->PopMouseBackground(false);
    ((RHUnkFXDraw *)m_draw)->FUN_005e6440(m_surface, surface, 0, surface, 0);
    for (index = 0; index < count; ++index)
        m_first[index]->V18(surface);
    g_unk0x6c1340->FUN_005f1700();
    ((RHUnkFXDraw *)g_unk0x6c11d0)->FUN_005e5260();
    g_unk0x6c1340->PopMouseBackground(false);
}

#include <vector>

class RHSaveGame;

template <class T>
class SBArray
{
public:
    void Insert(T *position, unsigned count, const T &value);
};

struct SBUIWindowArray
{
    unsigned allocator;
    SBUIWindowView **first;
    SBUIWindowView **last;
    SBUIWindowView **end;
    SBUIWindowView **cursor;
    bool dirty;
    bool cursorValid;
    undefined m_16[2];
    int index;
    SBUIWindowView *current;

    int Size() const { return first == 0 ? 0 : last - first; }
    int Find(SBUIWindowView *window)
    {
        dirty = false;
        current = window;
        int count = first == 0 ? 0 : last - first;
        cursor = first;
        cursorValid = true;
        int position = 0;
        for (; position < count; ++position, ++cursor)
            if (*cursor == window)
                break;
        return position < count ? position : -1;
    }
};

class SBUIFlagArray : public std::vector<char>
{
public:
    char *cursor;
    bool dirty;
    void FUN_00619d00();
    inline void Clear();

    void Insert(char *position, unsigned count, const char &value)
    {
        typedef char *(std::vector<char>::*Copy)(const char *, const char *, char *);
        typedef void (std::vector<char>::*Fill)(char *, unsigned, const char &);
        typedef void (std::vector<char>::*Destroy)(char *, char *);
        Copy copy = &SBUIFlagArray::_Ucopy;
        Fill fill = &SBUIFlagArray::_Ufill;
        Destroy destroy = &SBUIFlagArray::_Destroy;
        if ((unsigned)(_End - _Last) < count) {
            unsigned capacity = size() + (count < size() ? size() : count);
            char *storage = allocator.allocate(capacity, 0);
            char *destination = storage;
            for (char *source = _First; source != position; ++destination, ++source) {
                void (*construct)(char *, const char &) = &std::_Construct;
                construct(destination, *source);
            }
            (this->*fill)(destination, count, value);
            (this->*copy)(position, _Last, destination + count);
            (this->*destroy)(_First, _Last);
            allocator.deallocate(_First, _End - _First);
            _End = storage + capacity;
            _Last = storage + size() + count;
            _First = storage;
        } else if ((unsigned)(_Last - position) < count) {
            (this->*copy)(position, _Last, position + count);
            (this->*fill)(_Last, count - (_Last - position), value);
            std::fill(position, _Last, value);
            _Last += count;
        } else if (count > 0) {
            (this->*copy)(_Last - count, _Last, _Last);
            std::copy_backward(position, _Last - count, _Last);
            std::fill(position, position + count, value);
            _Last += count;
        }
    }
};

// FUNCTION: GAME 0x00619800
bool SBUI::FUN_00619800(SBUIWindowView *window)
{
    SBUIWindowArray &windows = *(SBUIWindowArray *)((char *)this + 4);
    windows.index = windows.Find(window);
    if (windows.index == -1) {
        ((SBArray<RHSaveGame *> *)&windows)->Insert(
            (RHSaveGame **)windows.last, 1, (RHSaveGame *const &)window);
        windows.dirty = true;
        char flag = 1;
        SBUIFlagArray &flags = *(SBUIFlagArray *)((char *)this + 0x24);
        flags.Insert(flags.end(), 1, flag);
        flags.dirty = true;
        window->AttachToDisplay(m_display);
        return true;
    }
    return false;
}

// FUNCTION: GAME 0x00619a00
void SBUI::FUN_00619a00(SBUIWindowView *window)
{
    m_index = Find(window);
    if (m_index != -1) {
        int index = m_index;
        unsigned char flag = m_flags[index];
        for (; index < Size() - 1; ++index) {
            m_first[index] = m_first[index + 1];
            m_flags[index] = m_flags[index + 1];
        }
        m_first[Size() - 1] = window;
        m_flags[Size() - 1] = flag;
    }
}

class RHScriptFXArray
{
public:
    void Unk005008e0(void **first, void **last);
};

inline void SBUIFlagArray::Clear()
{
    char *destination = std::copy(_Last, _Last, _First);
    ((RHScriptFXArray *)this)->Unk005008e0((void **)destination, (void **)_Last);
    _Last = destination;
    dirty = true;
}

// Parked: the clear path loads the first window through the frame base, not the array base.
// STUB: GAME 0x00619ad0
bool RHMapWindowPart::FUN_00619ad0(void *item)
{
    SBUIWindowView *window = (SBUIWindowView *)item;
    if (window == 0) {
        SBUIWindowArray &windows = *(SBUIWindowArray *)((char *)this + 4);
        SBUIWindowView **destination = std::copy(m_last, m_last, windows.first);
        ((RHScriptFXArray *)&windows)->Unk005008e0((void **)destination, (void **)windows.last);
        windows.last = destination;
        windows.dirty = true;
        ((SBUIFlagArray *)((char *)this + 0x24))->Clear();
        return true;
    }
    SBUIWindowView **first = *(SBUIWindowView **volatile *)&m_first;
    SBUIWindowArray &windows = *(SBUIWindowArray *)((char *)this + 4);
    for (unsigned short index = 0; index < (first == 0 ? 0 : windows.last - first); ++index) {
        if (m_first[index] == window) {
            std::vector<SBUIWindowView *> &all = *(std::vector<SBUIWindowView *> *)&windows;
            all.erase(&all.at(index));
            windows.dirty = true;
            SBUIFlagArray &flags = *(SBUIFlagArray *)((char *)this + 0x24);
            flags.erase(&flags.at(index));
            flags.dirty = true;
            return true;
        }
    }
    return false;
}

// FUNCTION: GAME 0x00619c20
bool SBUI::FUN_00619c20(unsigned long display)
{
    m_draw = g_unk0x6c11d0;
    m_display = display;
    unsigned count = Size();
    for (unsigned index = 0; index < count; ++index)
        m_first[index]->AttachToDisplay(display);
    if (m_tooltip != 0)
        m_tooltip->FUN_00627ee0(display);
    return true;
}

// FUNCTION: GAME 0x00619c80
void SBUI::FUN_00619c80(SBUIFontView *font, SBUIFontView *alternate)
{
    m_font = font;
    font->V14(m_renderer, false);
    m_alternate = alternate;
    if (alternate != 0)
        alternate->V14(m_renderer, false);
}

// FUNCTION: GAME 0x00619cc0
void RHGameActionCalls::FUN_00619cc0()
{
    m_input.FUN_0060e460();
    if (m_tooltip != 0)
        m_tooltip->FUN_00628500();
    m_175c = 0;
    m_175e = 0;
    m_1760 = 0;
    m_1762 = 0;
}

// FUNCTION: GAME 0x00619d00
void SBUIFlagArray::FUN_00619d00()
{
    erase(begin(), end());
    ((std::vector<char> *)this)->~vector();
}

// LIBRARY: GAME 0x00619f10
// ?_Ucopy@?$vector@DV?$allocator@D@std@@@std@@IAEPADPBD0PAD@Z

// LIBRARY: GAME 0x00619f40
// ?_Ufill@?$vector@DV?$allocator@D@std@@@std@@IAEXPADIABD@Z

// GLOBAL: GAME 0x006c18d8
unsigned g_unk0x006c18d8 = 0;

// GLOBAL: GAME 0x006c18dc
SBUIUnkTreeNode *g_unk0x006c18dc = 0;

#include "SBDrawManager.h"

DECOMP_SIZE_ASSERT(SBUIUnkSurface, 0x20)

// FUNCTION: GAME 0x0061af30
SBUIUnkSurface::SBUIUnkSurface(unsigned long surface)
    : m_draw(g_unk0x6c11d0), m_surface(surface), m_tree(SBUIUnkLess(), false, SBUIUnkAlloc())
{
    m_serial = 0;
    m_vptr = 0x0067adec;
}

// FUNCTION: GAME 0x0061b020
void *SBUIUnkSurface::FUN_0061b020(unsigned flags)
{
    this->~SBUIUnkSurface();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x0061b040
void *SBUIUnkSurfaceBase::FUN_0061b040(unsigned flags)
{
    this->~SBUIUnkSurfaceBase();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x0061b190
void SBUIUnkTree::FUN_0061b190()
{
    SBUIUnkTreeIterator first;
    first.node = m_head->left;
    SBUIUnkTreeIterator last;
    last.node = m_head;
    FUN_0061b720(first, last);
    delete m_head;
    m_head = 0;
    m_size = 0;
    {
        RHUnk00641782 lock;
        if (--g_unk0x006c18d8 == 0) {
            delete g_unk0x006c18dc;
            g_unk0x006c18dc = 0;
        }
    }
}

// FUNCTION: GAME 0x0061b350
void *SBUIUnkSurface::FUN_0061b350()
{
    void *dc = 0;
    m_draw->FUN_005e5890(m_surface, &dc, 0);
    return dc;
}

// FUNCTION: GAME 0x0061b380
unsigned long SBUIUnkSurface::FUN_0061b380(SBUIUnkImage *image, SBUIUnkImage *mask, bool keyed)
{
    SBUIUnkSurfacePair surfaces;
    surfaces.first = ((RHUnkFXDraw *)m_draw)->Unk005e4ed0(image->V2c(), image->V30(), 0, 0);
    image->V20(m_draw, surfaces.first);
    surfaces.second = ((RHUnkFXDraw *)m_draw)->Unk005e4ed0(mask->V2c(), mask->V30(), 0, 0);
    mask->V20(m_draw, surfaces.second);
    if (keyed == true) {
        FUN_0061b4c0(surfaces);
        ((RHUnkFXDraw *)m_draw)->Unk005e5160(surfaces.second);
        surfaces.second = 0;
    }
    ((SBUIUnkMap &)m_tree)[++m_serial] = surfaces;
    return m_serial;
}

// FUNCTION: GAME 0x0061b460
unsigned long FUN_0061b460(unsigned long red, unsigned long green, unsigned long blue)
{
    return ((((red & 0xf8) << 5) | (green & 0xf8)) << 2) | ((blue >> 3) & 0x1f);
}

// FUNCTION: GAME 0x0061b490
unsigned long FUN_0061b490(unsigned long red, unsigned long green, unsigned long blue)
{
    return ((((red & 0xf8) << 5) | (green & 0xfc)) << 3) | ((blue >> 3) & 0x1f);
}

class SBPictureUnkView
{
public:
    SBPictureUnkView();
    ~SBPictureUnkView();
    char m_00[4];
    unsigned short m_width;
    unsigned short m_height;
    unsigned long m_pitch;
    unsigned short m_depth;
    char m_0e[2];
    unsigned short *m_data;
    char m_14[4];
};

typedef unsigned long (*SBUIUnkPack)(unsigned long, unsigned long, unsigned long);

// Parked: this/surface registers swap (esi/edi) and the inner-loop prologue schedules differently.
// STUB: GAME 0x0061b4c0
void SBUIUnkSurface::FUN_0061b4c0(SBUIUnkSurfacePair &surfaces)
{
    SBPictureUnkView image;
    SBPictureUnkView mask;
    ((RHUnkFXDraw *)m_draw)->Unk005e5a00(surfaces.first, (RHUnk00613e90 &)image, 0);
    ((RHUnkFXDraw *)m_draw)->Unk005e5a00(surfaces.second, (RHUnk00613e90 &)mask, 0);
    unsigned width = image.m_width;
    unsigned height = image.m_height;
    unsigned long pitch = image.m_pitch >> 1;
    SBUIUnkPack pack = image.m_depth == 15 ? FUN_0061b460 : FUN_0061b490;
    unsigned short *destination = image.m_data;
    unsigned short *source = mask.m_data;
    for (unsigned y = 0; y != height; ++y) {
        for (unsigned x = 0; x != width; ++x)
            destination[x] = source[x] == 0 ? (unsigned short)pack(0, 0xff, 0) : destination[x];
        destination += pitch;
        source += pitch;
    }
    ((RHUnkFXDraw *)m_draw)->Unk005e5ea0((RHUnk00613e90 &)image);
    ((RHUnkFXDraw *)m_draw)->Unk005e5ea0((RHUnk00613e90 &)mask);
    ((SBDrawUnk005e5ec0 *)m_draw)->FUN_005e5ec0(surfaces.first, pack(0, 0xff, 0));
}

// FUNCTION: GAME 0x0061b640
bool SBUIUnkSurface::FUN_0061b640(void *dc)
{
    return m_draw->FUN_005e5bd0(m_surface, dc);
}

// FUNCTION: GAME 0x0061b660
void SBUIUnkSurface::FUN_0061b660(unsigned long key)
{
    SBUIUnkMap &surfaceMap = (SBUIUnkMap &)m_tree;
    SBUIUnkSurfacePair surfaces = surfaceMap[key];
    ((RHUnkFXDraw *)m_draw)->Unk005e5160(surfaces.first);
    if (surfaces.second != 0)
        ((RHUnkFXDraw *)m_draw)->Unk005e5160(surfaces.second);
    surfaceMap.erase(key);
}

// FUNCTION: GAME 0x0061b720
SBUIUnkTreeIterator SBUIUnkTree::FUN_0061b720(SBUIUnkTreeIterator first, SBUIUnkTreeIterator last)
{
    if (m_size != 0 && first.node == m_head->left && last.node == m_head) {
        RHUnk00641782 lock;
        Erase(m_head->parent);
        Root() = g_unk0x006c18dc;
        m_size = 0;
        Leftmost() = m_head;
        Rightmost() = m_head;
        return begin();
    }
    while (first.node != last.node)
        FUN_0061b980(first++);
    return first;
}

// FUNCTION: GAME 0x0061b850
SBUIUnkTreeInsertResult SBUIUnkTree::FUN_0061b850(const SBUIUnkTreeValue &value)
{
    SBUIUnkTreeNode *parent = m_head;
    bool before = true;
    SBUIUnkTreeNode *child = parent->parent;
    {
        RHUnk00641782 lock;
        while (child != g_unk0x006c18dc) {
            parent = child;
            before = value.key < child->key;
            child = before ? child->left : child->right;
        }
    }
    typedef SBUIUnkTreeIterator (SBUIUnkTree::*Insert)(SBUIUnkTreeNode *, SBUIUnkTreeNode *, const SBUIUnkTreeValue &);
    Insert insert = &SBUIUnkTree::FUN_0061bfe0;
    if (m_multi)
    {
        SBUIUnkTreeInsertResult result((this->*insert)(child, parent, value), true);
        return result;
    }
    SBUIUnkTreeIterator position(parent);
    if (before) {
        if (position.node == m_head->left) {
            SBUIUnkTreeInsertResult result((this->*insert)(child, parent, value), true);
            return result;
        }
        typedef void (SBUIUnkTreeIterator::*Previous)();
        Previous previous = &SBUIUnkTreeIterator::FUN_0061c3c0;
        (position.*previous)();
    }
    if (position.node->key < value.key) {
        SBUIUnkTreeInsertResult result((this->*insert)(child, parent, value), true);
        return result;
    }
    SBUIUnkTreeInsertResult result(position, false);
    return result;
}

static inline SBUIUnkTreeNode *SBUITreeMax(SBUIUnkTreeNode *node);
static inline SBUIUnkTreeNode *SBUITreeMin(SBUIUnkTreeNode *node);

// FUNCTION: GAME 0x0061b980
SBUIUnkTreeIterator SBUIUnkTree::FUN_0061b980(SBUIUnkTreeIterator entry)
{
    SBUIUnkTreeNode *removed = (entry++).node;
    SBUIUnkTreeNode *original = removed;
    SBUIUnkTreeNode *replacement;
    RHUnk00641782 lock;
    if (Left(removed) == g_unk0x006c18dc)
        replacement = Right(removed);
    else if (Right(removed) == g_unk0x006c18dc)
        replacement = Left(removed);
    else
    {
        removed = SBUITreeMin(Right(removed));
        replacement = Right(removed);
    }
    if (removed != original)
    {
        Parent(Left(original)) = removed;
        Left(removed) = Left(original);
        if (removed == Right(original))
            Parent(replacement) = removed;
        else
        {
            Parent(replacement) = Parent(removed);
            Left(Parent(removed)) = replacement;
            Right(removed) = Right(original);
            Parent(Right(original)) = removed;
        }
        if (Root() == original)
            Root() = removed;
        else if (Left(Parent(original)) == original)
            Left(Parent(original)) = removed;
        else
            Right(Parent(original)) = removed;
        Parent(removed) = Parent(original);
        std::swap(Color(removed), Color(original));
        removed = original;
    }
    else
    {
        Parent(replacement) = Parent(removed);
        if (Root() == original)
            Root() = replacement;
        else if (Left(Parent(original)) == original)
            Left(Parent(original)) = replacement;
        else
            Right(Parent(original)) = replacement;
        if (Leftmost() == original)
        {
            if (Right(original) == g_unk0x006c18dc)
                Leftmost() = Parent(original);
            else
                Leftmost() = SBUITreeMin(replacement);
        }
        if (Rightmost() == original)
        {
            if (Left(original) == g_unk0x006c18dc)
                Rightmost() = Parent(original);
            else
                Rightmost() = SBUITreeMax(replacement);
        }
    }
    if (Color(removed) == 1)
    {
        while (replacement != Root() && Color(replacement) == 1)
        {
            if (replacement == Left(Parent(replacement)))
            {
                SBUIUnkTreeNode *sibling = Right(Parent(replacement));
                if (Color(sibling) == 0)
                {
                    Color(sibling) = 1;
                    Color(Parent(replacement)) = 0;
                    RotateLeft(Parent(replacement));
                    sibling = Right(Parent(replacement));
                }
                if (Color(Left(sibling)) == 1 && Color(Right(sibling)) == 1)
                {
                    Color(sibling) = 0;
                    replacement = Parent(replacement);
                }
                else
                {
                    if (Color(Right(sibling)) == 1)
                    {
                        Color(Left(sibling)) = 1;
                        Color(sibling) = 0;
                        RotateRight(sibling);
                        sibling = Right(Parent(replacement));
                    }
                    Color(sibling) = Color(Parent(replacement));
                    Color(Parent(replacement)) = 1;
                    Color(Right(sibling)) = 1;
                    RotateLeft(Parent(replacement));
                    break;
                }
            }
            else
            {
                SBUIUnkTreeNode *sibling = Left(Parent(replacement));
                if (Color(sibling) == 0)
                {
                    Color(sibling) = 1;
                    Color(Parent(replacement)) = 0;
                    RotateRight(Parent(replacement));
                    sibling = Left(Parent(replacement));
                }
                if (Color(Right(sibling)) == 1 && Color(Left(sibling)) == 1)
                {
                    Color(sibling) = 0;
                    replacement = Parent(replacement);
                }
                else
                {
                    if (Color(Left(sibling)) == 1)
                    {
                        Color(Right(sibling)) = 1;
                        Color(sibling) = 0;
                        RotateLeft(sibling);
                        sibling = Left(Parent(replacement));
                    }
                    Color(sibling) = Color(Parent(replacement));
                    Color(Parent(replacement)) = 1;
                    Color(Left(sibling)) = 1;
                    RotateRight(Parent(replacement));
                    break;
                }
            }
        }
        Color(replacement) = 1;
    }
    operator delete(removed);
    --m_size;
    return entry;
}

// FUNCTION: GAME 0x0061bea0
void SBUIUnkTree::FUN_0061bea0(SBUIUnkTreeNode *node)
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

// FUNCTION: GAME 0x0061bf30
void SBUIUnkTreeIterator::FUN_0061bf30()
{
    RHUnk00641782 lock;
    if (node->right != g_unk0x006c18dc) {
        SBUIUnkTreeNode *minimum = node->right;
        {
            RHUnk00641782 inner;
            while (minimum->left != g_unk0x006c18dc)
                minimum = minimum->left;
        }
        node = minimum;
    }
    else {
        SBUIUnkTreeNode *parent;
        while (node == (parent = node->parent)->right)
            node = parent;
        if (node->right != parent)
            node = parent;
    }
}

// FUNCTION: GAME 0x0061bfe0
SBUIUnkTreeIterator SBUIUnkTree::FUN_0061bfe0(SBUIUnkTreeNode *child, SBUIUnkTreeNode *parent, const SBUIUnkTreeValue &value)
{
    RHUnk00641782 lock;
    SBUIUnkTreeNode *inserted = (SBUIUnkTreeNode *)operator new(sizeof(SBUIUnkTreeNode));
    inserted->parent = parent;
    inserted->color = 0;
    inserted->left = g_unk0x006c18dc;
    inserted->right = g_unk0x006c18dc;
    FUN_0059fb20((RHUnk00613e90 *)&inserted->key, (const RHUnk00613e90 &)value);
    ++m_size;
    if (parent == m_head || child != g_unk0x006c18dc || value.key < parent->key) {
        parent->left = inserted;
        if (parent == m_head) {
            m_head->parent = inserted;
            m_head->right = inserted;
        }
        else if (parent == m_head->left)
            m_head->left = inserted;
    }
    else {
        parent->right = inserted;
        if (parent == m_head->right)
            m_head->right = inserted;
    }
    for (child = inserted; child != m_head->parent && child->parent->color == 0;) {
        if (Parent(child) == Left(Parent(Parent(child)))) {
            parent = child->parent->parent->right;
            if (parent->color == 0) {
                child->parent->color = 1;
                parent->color = 1;
                child->parent->parent->color = 0;
                child = child->parent->parent;
            }
            else {
                if (child == child->parent->right) {
                    child = child->parent;
                    RotateLeft(child);
                }
                child->parent->color = 1;
                child->parent->parent->color = 0;
                RotateRight(child->parent->parent);
            }
        }
        else {
            parent = Left(Parent(Parent(child)));
            if (parent->color == 0) {
                child->parent->color = 1;
                parent->color = 1;
                child->parent->parent->color = 0;
                child = child->parent->parent;
            }
            else {
                if (child == child->parent->left) {
                    child = child->parent;
                    RotateRight(child);
                }
                child->parent->color = 1;
                child->parent->parent->color = 0;
                RotateLeft(child->parent->parent);
            }
        }
    }
    m_head->parent->color = 1;
    return SBUIUnkTreeIterator(inserted);
}

// FUNCTION: GAME 0x0061c2e0
SBUIUnkTreeNode *SBUIUnkTree::FUN_0061c2e0(SBUIUnkTreeNode *node)
{
    RHUnk00641782 lock;
    while (node->left != g_unk0x006c18dc)
        node = node->left;
    return node;
}

// FUNCTION: GAME 0x0061c320
SBUIUnkTreeNode *SBUIUnkTree::FUN_0061c320(const unsigned long &key)
{
    RHUnk00641782 lock;
    SBUIUnkTreeNode *node = m_head->parent;
    SBUIUnkTreeNode *result = m_head;
    while (node != g_unk0x006c18dc) {
        if (node->key < key)
            node = node->right;
        else {
            result = node;
            node = node->left;
        }
    }
    return result;
}

// FUNCTION: GAME 0x0061c370
SBUIUnkTreeNode *SBUIUnkTree::FUN_0061c370(const unsigned long &key)
{
    RHUnk00641782 lock;
    SBUIUnkTreeNode *node = m_head->parent;
    SBUIUnkTreeNode *result = m_head;
    while (node != g_unk0x006c18dc) {
        if (key < node->key) {
            result = node;
            node = node->left;
        } else
            node = node->right;
    }
    return result;
}

// FUNCTION: GAME 0x0061c3c0
void SBUIUnkTreeIterator::FUN_0061c3c0()
{
    RHUnk00641782 lock;
    if (node->color == 0 && node->parent->parent == node)
        node = node->right;
    else if (Left(node) != g_unk0x006c18dc)
        node = Max(Left(node));
    else {
        SBUIUnkTreeNode *parent;
        while (node == (parent = node->parent)->left)
            node = parent;
        node = parent;
    }
}

static inline SBUIUnkTreeNode *SBUITreeMax(SBUIUnkTreeNode *node)
{
    RHUnk00641782 lock;
    while (node->right != g_unk0x006c18dc)
        node = node->right;
    return node;
}

static inline SBUIUnkTreeNode *SBUITreeMin(SBUIUnkTreeNode *node)
{
    RHUnk00641782 lock;
    while (node->left != g_unk0x006c18dc)
        node = node->left;
    return node;
}

void EmitSBUI(SBUI *ui, SBUIWindowView *window, SBUIFontView *font)
{
    ui->FUN_006186d0(0);
    ((SBUIUnkSurface *)ui)->FUN_0061b020(0);
    ((SBUIUnkSurfaceBase *)ui)->FUN_0061b040(0);
    ui->FUN_00618910(0);
    ui->FUN_00619800(window);
    ui->FUN_00619a00(window);
    ui->FUN_00619c20(0);
    ((RHMapWindowPart *)ui)->FUN_00618850(0);
    ((RHGameActionCalls *)ui)->FUN_00619cc0();
    ((RHMapWindowPart *)ui)->FUN_00619ad0(window);
    ui->FUN_00619c80(font, font);
    ((SBUIFlagArray *)((char *)ui + 0x24))->FUN_00619d00();
    ((SBUIUnkTree *)ui)->FUN_0061b190();
    ((SBUIUnkSurface *)ui)->FUN_0061b350();
    FUN_0061b490(0, 0, 0);
    ((SBUIUnkSurface *)ui)->FUN_0061b640(0);
    ((SBUIUnkSurface *)ui)->FUN_0061b380((SBUIUnkImage *)window, (SBUIUnkImage *)window, false);
    ((SBUIUnkSurface *)ui)->FUN_0061b660(0);
    ((SBUIUnkTree *)ui)->FUN_0061b850(*(SBUIUnkTreeValue *)window);
    ((SBUIUnkTree *)ui)->FUN_0061b720(*(SBUIUnkTreeIterator *)window, *(SBUIUnkTreeIterator *)window);
    ((SBUIUnkTreeIterator *)ui)->FUN_0061c3c0();
    ((SBUIUnkTree *)ui)->FUN_0061bea0((SBUIUnkTreeNode *)window);
    SBUIUnkTree::FUN_0061c2e0((SBUIUnkTreeNode *)window);
    ((SBUIUnkTree *)ui)->FUN_0061c320(0);
    ((SBUIUnkTree *)ui)->FUN_0061c370(0);
    ((SBUIUnkTreeIterator *)ui)->FUN_0061bf30();
}
