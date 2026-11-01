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

void RHFontConstructValue(std::pair<const std::string, void *> *, const std::pair<const std::string, void *> &);

inline void RHFontInsertTree::RotateLeft(RHFontInsertNode *node)
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

inline void RHFontInsertTree::RotateRight(RHFontInsertNode *node)
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
    result.m_node = node;
    return result;
}

static inline RHFontInsertNode *RHFontInsertNodeOf(const RHFontInsertIterator &iterator)
{
    return iterator.m_node;
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
#include <string.h>

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
            memmove(m_chars + position, m_chars + position + count, available - count);
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

DECOMP_SIZE_ASSERT(std::string, 0x10)
DECOMP_SIZE_ASSERT(RHFontIterator, 0x04)
DECOMP_SIZE_ASSERT(RHFontInsertNode, 0x24)
DECOMP_SIZE_ASSERT(RHFontInsertResult, 0x08)
DECOMP_SIZE_ASSERT(RHFontInsertTree, 0x10)
DECOMP_SIZE_ASSERT(RHFontManager, 0x14)
DECOMP_SIZE_ASSERT(RHFontManager::Fonts, 0x20)

// TEMPLATE: GAME 0x004577c0
// ??0?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAE@ABV01@@Z

extern "C" __declspec(dllimport) int __stdcall AddFontResourceA(const char *);
extern "C" __declspec(dllimport) int __stdcall RemoveFontResourceA(const char *);

// STUB: GAME 0x00501840
RHFontManager::RHFontManager(const std::string &name)
    : m_family(0)
{
    LoadConfiguration(name);
    // STRING: GAME 0x006aff88
    if (FUN_005f6400(std::string("Data\\Interface\\Fonts\\0051EU__.ttf")))
        AddFontResourceA("Data\\Interface\\Fonts\\0051EU__.ttf");
    // STRING: GAME 0x006aff64
    if (FUN_005f6400(std::string("Data\\Interface\\Fonts\\1141EU__.ttf")))
        AddFontResourceA("Data\\Interface\\Fonts\\1141EU__.ttf");
    // STRING: GAME 0x006aff38
    if (FUN_005f6400(std::string("Data\\Interface\\Fonts\\CloisterBlackEU.ttf")))
        AddFontResourceA("Data\\Interface\\Fonts\\CloisterBlackEU.ttf");
    // STRING: GAME 0x006aff14
    if (FUN_005f6400(std::string("Data\\Interface\\Fonts\\MERLINN.TTF")))
        AddFontResourceA("Data\\Interface\\Fonts\\MERLINN.TTF");
    // STRING: GAME 0x006afef0
    if (FUN_005f6400(std::string("Data\\Interface\\Fonts\\MSGOTHIC.TTF")))
        AddFontResourceA("Data\\Interface\\Fonts\\MSGOTHIC.TTF");
    // STRING: GAME 0x006afecc
    if (FUN_005f6400(std::string("Data\\Interface\\Fonts\\MSMINCHO.TTF")))
        AddFontResourceA("Data\\Interface\\Fonts\\MSMINCHO.TTF");
    // STRING: GAME 0x006afeac
    if (FUN_005f6400(std::string("Data\\Interface\\Fonts\\KAIU.TTF")))
        AddFontResourceA("Data\\Interface\\Fonts\\KAIU.TTF");
    // STRING: GAME 0x006afe88
    if (FUN_005f6400(std::string("Data\\Interface\\Fonts\\MINGLIU.TTF")))
        AddFontResourceA("Data\\Interface\\Fonts\\MINGLIU.TTF");
}

// FUNCTION: GAME 0x00501ca0
inline RHFontInsertTree::~RHFontInsertTree()
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

// STUB: GAME 0x00501d10
RHFontManager::~RHFontManager()
{
    RHFontIterator position;
    position.m_node = m_fonts.m_head->m_00;
    while (position.m_node != m_fonts.m_head)
    {
        delete (Fonts *)position.m_node->m_0c.second;
        position++;
    }
    if (FUN_005f6400(std::string("Data\\Interface\\Fonts\\0051EU__.ttf")))
        RemoveFontResourceA("Data\\Interface\\Fonts\\0051EU__.ttf");
    if (FUN_005f6400(std::string("Data\\Interface\\Fonts\\1141EU__.ttf")))
        RemoveFontResourceA("Data\\Interface\\Fonts\\1141EU__.ttf");
    if (FUN_005f6400(std::string("Data\\Interface\\Fonts\\CloisterBlackEU.ttf")))
        RemoveFontResourceA("Data\\Interface\\Fonts\\CloisterBlackEU.ttf");
    if (FUN_005f6400(std::string("Data\\Interface\\Fonts\\MERLINN.TTF")))
        RemoveFontResourceA("Data\\Interface\\Fonts\\MERLINN.TTF");
    if (FUN_005f6400(std::string("Data\\Interface\\Fonts\\KAIU.TTF")))
        RemoveFontResourceA("Data\\Interface\\Fonts\\KAIU.TTF");
    if (FUN_005f6400(std::string("Data\\Interface\\Fonts\\MINGLIU.TTF")))
        RemoveFontResourceA("Data\\Interface\\Fonts\\MINGLIU.TTF");
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

#include "SBNativeFont.h"
#include "SBTrueTypeFont.h"
#include <stddef.h>

DECOMP_STATIC_ASSERT(offsetof(RHFontInsertTree, m_head) == 4)
DECOMP_STATIC_ASSERT(offsetof(RHFontInsertTree, m_count) == 0xc)
DECOMP_STATIC_ASSERT(offsetof(RHFontInsertNode, m_0c) == 0xc)
DECOMP_STATIC_ASSERT(offsetof(RHFontInsertNode, m_20) == 0x20)
DECOMP_STATIC_ASSERT(offsetof(RHFontManager, m_family) == 0x10)
DECOMP_SIZE_ASSERT(SBNativeFont, 0xd8)
DECOMP_SIZE_ASSERT(SBTrueTypeFont, 0x70)

// STUB: GAME 0x00502270
void *RHFontManager::GetFont(const std::string &name) const
{
    RHFontIterator::Node *node = const_cast<RHFontInsertTree &>(m_fonts).FUN_00502b90(name).m_node;
    if (node != m_fonts.m_head)
    {
        Fonts *fonts = (Fonts *)node->m_0c.second;
        if (m_family > 1)
        {
            if (m_family != 2)
                return 0;
        }
        else
        {
            if (!fonts->m_00.empty())
            {
                // STRING: GAME 0x006afe70
                return new SBNativeFont(std::string("data\\interface\\fonts\\") + fonts->m_00);
            }
        }
        if (!fonts->m_10.empty())
            return new SBTrueTypeFont(std::string("data\\interface\\fonts\\") + fonts->m_10);
    }
    return 0;
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
RHFontInsertTree::RHFontInsertTree(const Compare &compare, bool multi, const Allocator &allocator)
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

// FUNCTION: GAME 0x00502b90
RHFontInsertIterator RHFontInsertTree::FUN_00502b90(const std::string &key)
{
    RHFontInsertIterator result = RHFontInsertMake(FUN_005037e0(key));
    return RHFontInsertNodeOf(result) == m_head || key < RHFontInsertNodeOf(result)->m_0c.first
        ? RHFontInsertMake(m_head) : result;
}

// Parked: pair-construction inlining and frame/register allocation differ.
// STUB: GAME 0x00502c20
RHFontInsertResult RHFontInsertTree::FUN_00502c20(const std::pair<const std::string, void *> &value)
{
    RHFontInsertTree &tree = *this;
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
    previous.m_node = parent;
    if (left) {
        if (previous.m_node == tree.m_head->m_00) {
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

void EmitRHFontInsertTreeLifetime()
{
    RHFontInsertTree::Compare compare;
    RHFontInsertTree::Allocator allocator;
    RHFontInsertTree local(compare, false, allocator);
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
    result.m_node = inserted;
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
    tree.FUN_00502b90(key);
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
    RHFontManager local(name);
    LoadConfiguration(name);
    FUN_005024f0();
    std::string text;
    std::string copy(text);
}
