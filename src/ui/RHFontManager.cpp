#include "SBNullstr.h"
#include "RHFontManager.h"
#include "RHCampaignCommandLine.h"
#include "RHSoundCacheCore.h"
#include "RHTreeDec.h"

extern RHTreeDecNode20 *g_unk0x006c0ae8;

struct RHTreeInc00503420
{
    RHTreeDecNode20 *m_node;
    void FUN_00503420();
};

inline RHFontIterator RHFontIterator::operator++(int)
{
    RHFontIterator previous = *this;
    ((RHTreeInc00503420 *)this)->FUN_00503420();
    return previous;
}

static inline RHTreeDecNode20 *RHFontTreeMinimum(RHTreeDecNode20 *node)
{
    RHUnk00641782Lock lock;
    while (node->m_00 != g_unk0x006c0ae8)
        node = node->m_00;
    return node;
}

struct RHFontInsertNode
{
    RHFontInsertNode *m_00;
    RHFontInsertNode *m_04;
    RHFontInsertNode *m_08;
    std::pair<const std::string, void *> m_0c;
    int m_20;
};

void RHFontConstructValue(std::pair<const std::string, void *> *, const std::pair<const std::string, void *> &);

typedef RHFontIterator RHFontInsertIterator;

class RHFontInsertTree
{
public:
    RHFontInsertIterator FUN_005034d0(RHFontInsertNode *, RHFontInsertNode *, const std::pair<const std::string, void *> &);
    RHFontInsertNode *FUN_005037e0(const std::string &);
    static RHFontInsertNode *&Left(RHFontInsertNode *node) { return node->m_00; }
    inline void RotateLeft(RHFontInsertNode *node)
    {
        RHUnk00641782Lock lock;
        RHFontInsertNode *right = node->m_08;
        node->m_08 = right->m_00;
        if (right->m_00 != (RHFontInsertNode *)g_unk0x006c0ae8) right->m_00->m_04 = node;
        right->m_04 = node->m_04;
        if (node == m_head->m_04) m_head->m_04 = right;
        else if (node == node->m_04->m_00) node->m_04->m_00 = right;
        else node->m_04->m_08 = right;
        right->m_00 = node;
        node->m_04 = right;
    }
    inline void RotateRight(RHFontInsertNode *node)
    {
        RHUnk00641782Lock lock;
        RHFontInsertNode *left = node->m_00;
        node->m_00 = left->m_08;
        if (left->m_08 != (RHFontInsertNode *)g_unk0x006c0ae8) left->m_08->m_04 = node;
        left->m_04 = node->m_04;
        if (node == m_head->m_04) m_head->m_04 = left;
        else if (node == node->m_04->m_08) node->m_04->m_08 = left;
        else node->m_04->m_00 = left;
        left->m_08 = node;
        node->m_04 = left;
    }
    RHFontInsertTree(const undefined &, bool, const undefined &);
    void FUN_00501ca0();
    RHFontInsertIterator FUN_00502a50(RHFontInsertIterator, RHFontInsertIterator);
    RHFontInsertIterator FUN_00502d90(RHFontInsertIterator);
    void FUN_005032c0(RHFontInsertNode *);
    void FUN_00503370();
    static RHFontInsertNode *&Parent(RHFontInsertNode *node) { return node->m_04; }
    static RHFontInsertNode *&Right(RHFontInsertNode *node) { return node->m_08; }
    static int &Color(RHFontInsertNode *node) { return node->m_20; }
    RHFontInsertNode *&Root() { return m_head->m_04; }
    RHFontInsertNode *&Leftmost() { return m_head->m_00; }
    RHFontInsertNode *&Rightmost() { return m_head->m_08; }
    undefined m_00;
    undefined m_01;
    undefined m_02[2];
    RHFontInsertNode *m_head;
    bool m_08;
    undefined m_09[3];
    unsigned m_count;
};

extern unsigned g_unk0x006c0ae4;

static inline RHFontInsertNode *RHFontInsertMinimum(RHFontInsertNode *node)
{
    RHUnk00641782Lock lock;
    while (node->m_00 != (RHFontInsertNode *)g_unk0x006c0ae8)
        node = node->m_00;
    return node;
}

static inline RHFontInsertNode *RHFontInsertMaximum(RHFontInsertNode *node)
{
    RHUnk00641782Lock lock;
    while (node->m_08 != (RHFontInsertNode *)g_unk0x006c0ae8)
        node = node->m_08;
    return node;
}

static inline RHFontInsertIterator RHFontInsertMake(RHFontInsertNode *node)
{
    RHFontInsertIterator result;
    result.m_node = (RHFontIterator::Node *)node;
    return result;
}

static inline RHFontInsertNode *RHFontInsertNodeOf(const RHFontInsertIterator &iterator)
{
    return (RHFontInsertNode *)iterator.m_node;
}

// SIZE 0x10
struct RHSoundCacheString
{
    undefined m_00; // 0x00
    char *m_04; // 0x04
    unsigned m_08; // 0x08
    unsigned m_0c; // 0x0c
    void FUN_00402780();
};

void FUN_006416e6();
void *FUN_00642580(void *, const void *, unsigned int);

// SIZE 0x10
class RHCampaignText
{
public:
    undefined m_allocator; // 0x00
    char *m_chars; // 0x04
    unsigned m_length; // 0x08
    unsigned m_capacity; // 0x0c
    void FUN_004021c0(const char *, unsigned);
};

// SIZE 0x10
struct RHFontTrimText
{
    undefined m_allocator; // 0x00
    char *m_chars; // 0x04
    unsigned m_size; // 0x08
    unsigned m_capacity; // 0x0c

    char *Begin() { return ((std::string *)this)->begin(); }
    char *End() { return ((std::string *)this)->end(); }
    void Split()
    {
        char *storage = m_chars;
        if (storage && (unsigned char)storage[-1] != 0 && (unsigned char)storage[-1] != 255)
        {
            ((RHProfileText *)this)->FUN_00401ee0(true);
            ((RHCampaignText *)this)->FUN_004021c0(storage, strlen(storage));
        }
    }
    void Erase(unsigned position, unsigned count)
    {
        if (m_size < position)
            std::_Xran();
        Split();
        unsigned available = m_size - position;
        if (available < count)
            count = available;
        if (count > 0)
        {
            FUN_00642580(m_chars + position, m_chars + position + count, available - count);
            unsigned length = m_size - count;
            if (((RHProfileText *)this)->FUN_00402280(length, false))
                ((RHProfileText *)this)->FUN_00402260(length);
        }
    }
};

DECOMP_SIZE_ASSERT(RHFontTrimText, 0x10)
DECOMP_SIZE_ASSERT(RHSoundCacheString, 0x10)
DECOMP_SIZE_ASSERT(RHCampaignCommandLine, 0x10)
DECOMP_SIZE_ASSERT(RHCampaignText, 0x10)

DECOMP_SIZE_ASSERT(RHFontText, 0x10)
DECOMP_SIZE_ASSERT(RHFontIterator, 0x04)
DECOMP_SIZE_ASSERT(RHFontInsertResult, 0x08)
DECOMP_SIZE_ASSERT(RHFontMap, 0x0c)
DECOMP_SIZE_ASSERT(RHFontManager, 0x0c)
DECOMP_SIZE_ASSERT(RHFontManager::Fonts, 0x20)

// Parked: copy/zero register allocation and range-error call operand.
// STUB: GAME 0x004577c0
RHFontText::RHFontText(const RHFontText &value)
    : m_allocator(value.m_allocator)
{
    m_chars = 0;
    m_size = 0;
    m_capacity = 0;
    unsigned size = value.m_size;
    unsigned count = std::string::npos;
    if (count < size)
        size = count;
    if (this == &value)
    {
        if (m_size < size)
            FUN_006416e6();
        ((RHSoundCacheString *)this)->FUN_00402780();
        unsigned available = m_size - size;
        if (available < count)
            count = available;
        if (count > 0)
        {
            char *first = m_chars + size;
            FUN_00642580(first, first + count, available - count);
            unsigned length = m_size - count;
            if (((RHProfileText *)this)->FUN_00402280(length, false))
                ((RHProfileText *)this)->FUN_00402260(length);
        }
        ((RHSoundCacheString *)this)->FUN_00402780();
    }
    else if (size > 0 && size == value.m_size && (unsigned char)(value.m_chars ? value.m_chars : "")[-1] < 254)
    {
        m_chars = 0;
        m_size = 0;
        m_capacity = 0;
        m_chars = value.m_chars ? value.m_chars : (char *)"";
        m_size = value.m_size;
        m_capacity = value.m_capacity;
        ++m_chars[-1];
    }
    else if (((RHProfileText *)this)->FUN_00402280(size, true))
    {
        memcpy(m_chars, value.m_chars ? value.m_chars : "", size);
        ((RHProfileText *)this)->FUN_00402260(size);
    }
}

// FUNCTION: GAME 0x00501ca0
void RHFontInsertTree::FUN_00501ca0()
{
    RHFontInsertIterator first = RHFontInsertMake(Leftmost());
    RHFontInsertIterator last = RHFontInsertMake(m_head);
    FUN_00502a50(first, last);
    operator delete(m_head);
    m_head = 0;
    m_count = 0;
    {
        RHUnk00641782Lock lock;
        if (--g_unk0x006c0ae4 == 0) {
            operator delete(g_unk0x006c0ae8);
            g_unk0x006c0ae8 = 0;
        }
    }
}

// GLOBAL: GAME 0x006c0ae4
unsigned g_unk0x006c0ae4;

// FUNCTION: GAME 0x00502110
std::string RHFontManager::Get(FILE *file, char delimiter)
{
    std::string value;
    char character = fgetc(file);
    while (character != delimiter)
    {
        if (character == (char)-1)
            break;
        if (character == '\r' || character == '\n')
        {
            do
            {
                character = fgetc(file);
            } while (character == '\r' || character == '\n');
            ungetc(character, file);
            break;
        }
        value.append(1, character);
        character = fgetc(file);
    }
    if (character == delimiter)
        ungetc(character, file);
    return value;
}

// Parked: frame 0xcc versus 0xd8 and map-result temporary layout.
// STUB: GAME 0x00502500
void RHFontManager::LoadConfiguration(const std::string &name)
{
    RHUnk005f4fc0 file;
    if (file.FUN_005f5090(name, 1) != 0)
    {
        SBAssert(0,
                 // STRING: GAME 0x006affac
                 "P:\\Robin Hood\\RHFontManager.cpp", 0x134,
                 // STRING: GAME 0x006affcc
                 "RHFontManager : unable to open the specified file : '%s'\n", ((SBString *)&name)->m_chars ? ((SBString *)&name)->m_chars : "");
        return;
    }
    FILE *stream = *(FILE **)&file;
    while (!feof(stream) && !ferror(stream))
    {
        std::string key;
        Fonts *fonts = new Fonts;
        key = Get(stream, ':');
        TrimString((std::string &)key);
        fgetc(stream);
        fonts->m_00 = Get(stream, ',');
        TrimString((std::string &)fonts->m_00);
        fgetc(stream);
        fonts->m_10 = Get(stream, 0);
        TrimString((std::string &)fonts->m_10);
        m_fonts[(const std::string &)key] = fonts;
    }
}

// Parked: iterator arithmetic and split/erase scheduling.
// STUB: GAME 0x00502840
void RHFontManager::TrimString(std::string &value)
{
    RHFontTrimText &text = (RHFontTrimText &)value;
    if (value.empty())
        return;
    if (*text.Begin() == ' ' || *text.Begin() == '\t')
    {
        char *first = text.Begin();
        while (*first == ' ' || *first == '\t')
            ++first;
        char *begin = text.Begin();
        char *base = text.Begin();
        unsigned position = begin == 0 ? 0 : begin - base;
        typedef std::string &(std::string::*Erase)(unsigned, unsigned);
        Erase erase = &std::string::erase;
        (value.*erase)(position, first == 0 ? 0 : first - begin);
    }
    if (*(text.End() - 1) == ' ' || *(text.End() - 1) == '\t')
    {
        std::string::iterator last = value.end();
        do
        {
            --last;
        } while (*last == ' ' || *last == '\t');
        char *end = value.end();
        ++last;
        char *begin = text.Begin();
        text.Erase(last == 0 ? 0 : last - begin, end == 0 ? 0 : end - last);
    }
}

// FUNCTION: GAME 0x00502a20
RHFontInsertTree::RHFontInsertTree(const undefined &compare, bool multi, const undefined &allocator)
    : m_00(allocator), m_01(compare), m_08(multi)
{
    FUN_00503370();
}

// FUNCTION: GAME 0x00502a50
RHFontInsertIterator RHFontInsertTree::FUN_00502a50(RHFontInsertIterator first, RHFontInsertIterator last)
{
    if (m_count != 0 && RHFontInsertNodeOf(first) == m_head->m_00 && RHFontInsertNodeOf(last) == m_head) {
        RHUnk00641782Lock lock;
        RHFontInsertNode *node = Root();
        {
            RHUnk00641782Lock inner;
            for (RHFontInsertNode *next = node; next != (RHFontInsertNode *)g_unk0x006c0ae8; node = next) {
                FUN_005032c0(next->m_08);
                next = next->m_00;
                ((RHProfileText *)&node->m_0c.first)->~RHProfileText();
                operator delete(node);
            }
        }
        Root() = (RHFontInsertNode *)g_unk0x006c0ae8;
        m_count = 0;
        Leftmost() = m_head;
        Rightmost() = m_head;
        return RHFontInsertMake(Leftmost());
    }
    while (first.m_node != last.m_node)
        FUN_00502d90(first++);
    return first;
}

// Parked: pair-construction inlining and frame/register allocation differ.
// STUB: GAME 0x00502c20
RHFontInsertResult RHFontMap::FUN_00502c20(const std::pair<const std::string, void *> &value)
{
    RHFontInsertTree &tree = *(RHFontInsertTree *)this;
    RHFontInsertNode *node = tree.m_head->m_04;
    RHFontInsertNode *parent = tree.m_head;
    bool left = true;
    {
        RHUnk00641782Lock lock;
        while (node != (RHFontInsertNode *)g_unk0x006c0ae8) {
            parent = node;
            const RHProfileText &key = *(const RHProfileText *)&value.first;
            const RHProfileText &other = *(const RHProfileText *)&node->m_0c.first;
            left = key.FUN_00460900(0, key.m_size, other.c_str(), other.m_size) < 0;
            node = left ? node->m_00 : node->m_08;
        }
    }
    if (*(bool *)&tree.m_08) {
        RHFontInsertResult result(tree.FUN_005034d0(node, parent, value), true);
        return result;
    }
    RHFontIterator previous;
    previous.m_node = (RHFontIterator::Node *)parent;
    if (left) {
        if (previous.m_node == (RHFontIterator::Node *)tree.m_head->m_00) {
            RHFontInsertResult result(tree.FUN_005034d0(node, parent, value), true);
            return result;
        }
        ((RHTreeDec005038a0 *)&previous)->FUN_005038a0();
    }
    if (((RHCampaignCommandLine *)&((RHFontInsertNode *)previous.m_node)->m_0c.first)->FUN_0045a010(*(const RHProfileText *)&value.first) < 0) {
        RHFontInsertResult result(tree.FUN_005034d0(node, parent, value), true);
        return result;
    }
    RHFontInsertResult result(previous, false);
    return result;
}

// FUNCTION: GAME 0x00502d90
RHFontInsertIterator RHFontInsertTree::FUN_00502d90(RHFontInsertIterator position)
{
    RHFontInsertNode *x;
    RHFontInsertNode *y = RHFontInsertNodeOf(position++);
    RHFontInsertNode *z = y;
    RHUnk00641782Lock lock;
    if (Left(y) == (RHFontInsertNode *)g_unk0x006c0ae8)
        x = Right(y);
    else if (Right(y) == (RHFontInsertNode *)g_unk0x006c0ae8)
        x = Left(y);
    else
    {
        y = RHFontInsertMinimum(Right(y));
        x = Right(y);
    }
    {
        if (y != z)
        {
            Parent(Left(z)) = y;
            Left(y) = Left(z);
            if (y == Right(z))
                Parent(x) = y;
            else
            {
                Parent(x) = Parent(y);
                Left(Parent(y)) = x;
                Right(y) = Right(z);
                Parent(Right(z)) = y;
            }
            if (Root() == z)
                Root() = y;
            else if (Left(Parent(z)) == z)
                Left(Parent(z)) = y;
            else
                Right(Parent(z)) = y;
            Parent(y) = Parent(z);
            std::swap(Color(y), Color(z));
            y = z;
        }
        else
        {
            Parent(x) = Parent(y);
            if (Root() == z)
                Root() = x;
            else if (Left(Parent(z)) == z)
                Left(Parent(z)) = x;
            else
                Right(Parent(z)) = x;
            if (Leftmost() == z)
            {
                if (Right(z) == (RHFontInsertNode *)g_unk0x006c0ae8)
                    Leftmost() = Parent(z);
                else
                {
                    Leftmost() = RHFontInsertMinimum(x);
                }
            }
            if (Rightmost() == z)
            {
                if (Left(z) == (RHFontInsertNode *)g_unk0x006c0ae8)
                    Rightmost() = Parent(z);
                else
                {
                    Rightmost() = RHFontInsertMaximum(x);
                }
            }
        }
        if (Color(y) == 1)
        {
            while (x != Root() && Color(x) == 1)
            {
                if (x == Left(Parent(x)))
                {
                    RHFontInsertNode *w = Right(Parent(x));
                    if (Color(w) == 0)
                    {
                        Color(w) = 1;
                        Color(Parent(x)) = 0;
                        RotateLeft(Parent(x));
                        w = Right(Parent(x));
                    }
                    if (Color(Left(w)) == 1 && Color(Right(w)) == 1)
                    {
                        Color(w) = 0;
                        x = Parent(x);
                    }
                    else
                    {
                        if (Color(Right(w)) == 1)
                        {
                            Color(Left(w)) = 1;
                            Color(w) = 0;
                            RotateRight(w);
                            w = Right(Parent(x));
                        }
                        Color(w) = Color(Parent(x));
                        Color(Parent(x)) = 1;
                        Color(Right(w)) = 1;
                        RotateLeft(Parent(x));
                        break;
                    }
                }
                else
                {
                    RHFontInsertNode *w = Left(Parent(x));
                    if (Color(w) == 0)
                    {
                        Color(w) = 1;
                        Color(Parent(x)) = 0;
                        RotateRight(Parent(x));
                        w = Left(Parent(x));
                    }
                    if (Color(Right(w)) == 1 && Color(Left(w)) == 1)
                    {
                        Color(w) = 0;
                        x = Parent(x);
                    }
                    else
                    {
                        if (Color(Left(w)) == 1)
                        {
                            Color(Right(w)) = 1;
                            Color(w) = 0;
                            RotateLeft(w);
                            w = Left(Parent(x));
                        }
                        Color(w) = Color(Parent(x));
                        Color(Parent(x)) = 1;
                        Color(Left(w)) = 1;
                        RotateRight(Parent(x));
                        break;
                    }
                }
            }
            Color(x) = 1;
        }
    }
    ((std::string &)y->m_0c.first).~basic_string();
    operator delete(y);
    --m_count;
    return position;
}

// FUNCTION: GAME 0x005032c0
void RHFontInsertTree::FUN_005032c0(RHFontInsertNode *node)
{
    RHUnk00641782Lock lock;
    for (RHFontInsertNode *next = node; next != (RHFontInsertNode *)g_unk0x006c0ae8; node = next) {
        FUN_005032c0(next->m_08);
        next = next->m_00;
        ((std::string &)node->m_0c.first).~basic_string();
        operator delete(node);
    }
}

// FUNCTION: GAME 0x00503370
void RHFontInsertTree::FUN_00503370()
{
    RHUnk00641782Lock lock;
    if (g_unk0x006c0ae8 == 0) {
        RHFontInsertNode *node = (RHFontInsertNode *)operator new(sizeof(RHFontInsertNode));
        node->m_04 = 0;
        node->m_20 = 1;
        g_unk0x006c0ae8 = (RHTreeDecNode20 *)node;
        ((RHFontInsertNode *)g_unk0x006c0ae8)->m_00 = 0;
        ((RHFontInsertNode *)g_unk0x006c0ae8)->m_08 = 0;
    }
    ++g_unk0x006c0ae4;
    RHFontInsertNode *sentinel = (RHFontInsertNode *)g_unk0x006c0ae8;
    RHFontInsertNode *head = (RHFontInsertNode *)operator new(sizeof(RHFontInsertNode));
    head->m_04 = sentinel;
    head->m_20 = 0;
    m_head = head;
    m_count = 0;
    m_head->m_00 = m_head;
    m_head->m_08 = m_head;
}

void EmitRHFontInsertTreeLifetime(RHFontInsertTree &tree)
{
    tree.FUN_00501ca0();
    undefined compare;
    RHFontInsertTree local(compare, false, compare);
}

// FUNCTION: GAME 0x00503420
void RHTreeInc00503420::FUN_00503420()
{
    RHUnk00641782Lock lock;
    if (m_node->m_08 != g_unk0x006c0ae8)
        m_node = RHFontTreeMinimum(m_node->m_08);
    else {
        RHTreeDecNode20 *parent;
        while (m_node == (parent = m_node->m_04)->m_08)
            m_node = parent;
        if (m_node->m_08 != parent)
            m_node = parent;
    }
}

void EmitRHFontTreeInc(RHTreeInc00503420 &iterator)
{
    iterator.FUN_00503420();
}

// FUNCTION: GAME 0x005034d0
RHFontInsertIterator RHFontInsertTree::FUN_005034d0(RHFontInsertNode *node, RHFontInsertNode *parent, const std::pair<const std::string, void *> &value)
{
    RHUnk00641782Lock lock;
    RHFontInsertNode *inserted = (RHFontInsertNode *)operator new(sizeof(RHFontInsertNode));
    inserted->m_04 = parent;
    inserted->m_20 = 0;
    inserted->m_00 = (RHFontInsertNode *)g_unk0x006c0ae8;
    inserted->m_08 = (RHFontInsertNode *)g_unk0x006c0ae8;
    RHFontConstructValue(&inserted->m_0c, value);
    ++m_count;
    if (parent == m_head || node != (RHFontInsertNode *)g_unk0x006c0ae8 ||
        ((RHCampaignCommandLine *)&value.first)->FUN_0045a010(*(const RHProfileText *)&parent->m_0c.first) < 0) {
        parent->m_00 = inserted;
        if (parent == m_head) {
            m_head->m_04 = inserted;
            m_head->m_08 = inserted;
        } else if (parent == m_head->m_00) m_head->m_00 = inserted;
    } else {
        parent->m_08 = inserted;
        if (parent == m_head->m_08) m_head->m_08 = inserted;
    }
    for (node = inserted; node != m_head->m_04 && node->m_04->m_20 == 0;) {
        if (node->m_04 == Left(node->m_04->m_04)) {
            parent = node->m_04->m_04->m_08;
            if (parent->m_20 == 0) {
                node->m_04->m_20 = 1;
                parent->m_20 = 1;
                node->m_04->m_04->m_20 = 0;
                node = node->m_04->m_04;
            } else {
                if (node == node->m_04->m_08) {
                    node = node->m_04;
                    RotateLeft(node);
                }
                node->m_04->m_20 = 1;
                node->m_04->m_04->m_20 = 0;
                RotateRight(node->m_04->m_04);
            }
        } else {
            parent = node->m_04->m_04->m_00;
            if (parent->m_20 == 0) {
                node->m_04->m_20 = 1;
                parent->m_20 = 1;
                node->m_04->m_04->m_20 = 0;
                node = node->m_04->m_04;
            } else {
                if (node == node->m_04->m_00) {
                    node = node->m_04;
                    RotateRight(node);
                }
                node->m_04->m_20 = 1;
                node->m_04->m_04->m_20 = 0;
                RotateLeft(node->m_04->m_04);
            }
        }
    }
    m_head->m_04->m_20 = 1;
    RHFontInsertIterator result;
    result.m_node = (RHFontIterator::Node *)inserted;
    return result;
}

void EmitRHFontInsertTree(RHFontInsertTree &tree, const std::pair<const std::string, void *> &value)
{
    tree.FUN_005034d0(0, 0, value);
}

// FUNCTION: GAME 0x005037e0
RHFontInsertNode *RHFontInsertTree::FUN_005037e0(const std::string &key)
{
    RHUnk00641782Lock lock;
    RHFontInsertNode *node = m_head->m_04;
    RHFontInsertNode *candidate = m_head;
    while (node != (RHFontInsertNode *)g_unk0x006c0ae8) {
        if (node->m_0c.first.compare(key) < 0)
            node = node->m_08;
        else {
            candidate = node;
            node = node->m_00;
        }
    }
    return candidate;
}

void EmitRHFontLowerBound(RHFontInsertTree &tree, const std::string &key)
{
    tree.FUN_005037e0(key);
}

// FUNCTION: GAME 0x005c1270
RHFontInsertResult::RHFontInsertResult(const RHFontIterator &iterator, const bool &inserted)
    : first(iterator), second(inserted)
{
}

// FUNCTION: GAME 0x005024f0
void *RHFontManager::FUN_005024f0()
{
    return (void *)0x6c0ad0;
}

void RHFontManager::Emit(const std::string &name)
{
    LoadConfiguration(name);
    FUN_005024f0();
    RHFontText text;
    RHFontText copy(text);
}
