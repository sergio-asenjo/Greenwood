#include "SBNullstr.h"
#include "SBFont.h"
#include "SBNativeFontBase.h"
#include "RHSaveGame.h"
#include "RHCampaign.h"
#include <string.h>

DECOMP_SIZE_ASSERT(SBFontTextView, 0x0c)
DECOMP_SIZE_ASSERT(SBFontUnk0061e840, 0x44)
DECOMP_SIZE_ASSERT(SBFontNode0061fcb0, 0x14)
DECOMP_SIZE_ASSERT(SBFontIterator0061fe10, 0x04)
DECOMP_SIZE_ASSERT(SBFontPair0061f2b0, 0x08)
DECOMP_SIZE_ASSERT(SBFontTree0061fcb0, 0x10)
DECOMP_SIZE_ASSERT(SBFontValue0061f120, 0x20)
DECOMP_SIZE_ASSERT(SBFontNode0061f3e0, 0x30)
DECOMP_SIZE_ASSERT(SBFontTree0061f3e0, 0x10)
DECOMP_SIZE_ASSERT(SBFontIterator0061f3e0, 0x04)
DECOMP_SIZE_ASSERT(SBFontPair0061f3e0, 0x08)
DECOMP_SIZE_ASSERT(SBFontLock, 0x01)

template <class Node>
inline Node *&SBFontLeft(Node *node)
{
    return node->m_00;
}

template <class Node>
inline Node *&SBFontRight(Node *node)
{
    return node->m_08;
}

template <class Node>
inline Node *&SBFontParent(Node *node)
{
    return node->m_04;
}

inline int &SBFontColor(SBFontNode0061fcb0 *node)
{
    return node->m_10;
}

inline int &SBFontColor(SBFontNode0061f3e0 *node)
{
    return node->m_2c;
}

inline SBFontNode0061fcb0 *SBFontCopyNodes(SBFontTree0061fcb0 *tree, SBFontNode0061fcb0 *source, SBFontNode0061fcb0 *parent)
{
    SBFontLock lock;
    SBFontNode0061fcb0 *root = source;
    for (; source != g_unk0x006c191c; source = source->m_00) {
        int color = source->m_10;
        SBFontNode0061fcb0 *node = (SBFontNode0061fcb0 *)operator new(sizeof(SBFontNode0061fcb0));
        node->m_04 = parent;
        node->m_10 = color;
        if (root == source) root = node;
        node->m_08 = tree->FUN_00620d60(source->m_08, node);
        void (*construct)(unsigned short *, const unsigned short &) = &std::_Construct;
        construct(&node->m_0c, source->m_0c);
        parent->m_00 = node;
        parent = node;
    }
    parent->m_00 = g_unk0x006c191c;
    return root;
}

template <class Node, class Tree>
inline void SBFontRotateLeft(Tree *tree, Node *node, Node *&nil)
{
    SBFontLock lock;
    Node *right = node->m_08;
    node->m_08 = right->m_00;
    if (right->m_00 != nil) right->m_00->m_04 = node;
    right->m_04 = node->m_04;
    if (node == tree->m_04->m_04) tree->m_04->m_04 = right;
    else if (node == node->m_04->m_00) node->m_04->m_00 = right;
    else node->m_04->m_08 = right;
    right->m_00 = node;
    node->m_04 = right;
}

template <class Node, class Tree>
inline void SBFontRotateRight(Tree *tree, Node *node, Node *&nil)
{
    SBFontLock lock;
    Node *left = node->m_00;
    node->m_00 = left->m_08;
    if (left->m_08 != nil) left->m_08->m_04 = node;
    left->m_04 = node->m_04;
    if (node == tree->m_04->m_04) tree->m_04->m_04 = left;
    else if (node == node->m_04->m_08) node->m_04->m_08 = left;
    else node->m_04->m_00 = left;
    left->m_08 = node;
    node->m_04 = left;
}

template <class Node>
inline Node *SBFontMinimum(Node *node, Node *&nil)
{
    SBFontLock lock;
    while (node->m_00 != nil) node = node->m_00;
    return node;
}

template <class Node>
inline Node *SBFontMaximum(Node *node, Node *&nil)
{
    SBFontLock lock;
    while (node->m_08 != nil) node = node->m_08;
    return node;
}

// GLOBAL: GAME 0x006c191c
SBFontNode0061fcb0 *g_unk0x006c191c = 0;
// GLOBAL: GAME 0x006c1920
unsigned g_unk0x006c1920 = 0;
// GLOBAL: GAME 0x006c1914
SBFontNode0061f3e0 *g_unk0x006c1914 = 0;
// GLOBAL: GAME 0x006c1918
unsigned g_unk0x006c1918 = 0;
// GLOBAL: GAME 0x006c1900
SBFontTree0061f3e0 g_unk0x006c1900;

// STRING: GAME 0x006bb87c
static const char g_sbFontFile[] = "P:\\Robin Hood\\SBLibNG\\SBFont.cpp";
// STRING: GAME 0x006bb8a0
static const char g_sbFontMissing[] = "Warning ! Character 0x%02x is missing in the font '%s'";

void *FUN_0048f170(void *value);

static inline SBFontIterator0061f3e0 SBFontIterator0061f3e0Make(SBFontNode0061f3e0 *node)
{
    SBFontIterator0061f3e0 result;
    result.m_00 = node;
    return result;
}

static inline void SBFontDestroyValue(SBFontValue0061f120 &value)
{
    SBFontTree0061fcb0 &fonts = value.m_10;
    SBFontIterator0061fe10 last;
    ((SBFontUnk00620c90 *)&last)->FUN_00620c90((int)fonts.m_04);
    SBFontIterator0061fe10 first;
    ((SBFontUnk00620c90 *)&first)->FUN_00620c90(*(int *)FUN_0048f170(fonts.m_04));
    fonts.FUN_0061fce0(first, last);
    operator delete(fonts.m_04);
    fonts.m_04 = 0;
    fonts.m_0c = 0;
    {
        SBFontLock lock;
        if (--g_unk0x006c1920 == 0) {
            operator delete(g_unk0x006c191c);
            g_unk0x006c191c = 0;
        }
    }
    value.m_00.~basic_string();
}

// FUNCTION: GAME 0x0061e6f0
void FUN_0061e6f0()
{
    undefined comparison, allocation;
    g_unk0x006c1900.SBFontTree0061f3e0::SBFontTree0061f3e0(comparison, allocation);
}

// FUNCTION: GAME 0x0061e740
void SBFontTree0061f3e0::FUN_0061e740()
{
    FUN_0061efe0(begin(), SBFontIterator0061f3e0Make(m_04));
    operator delete(m_04);
    m_04 = 0;
    m_0c = 0;
    {
        SBFontLock lock;
        if (--g_unk0x006c1918 == 0) {
            operator delete(g_unk0x006c1914);
            g_unk0x006c1914 = 0;
        }
    }
}

// FUNCTION: GAME 0x0061e7b0
SBNativeFontBase::SBNativeFontBase()
{
    m_context = 0;
    m_08[0] = 0;
    *(unsigned *)this = 0x67ae34;
    memset(m_08 + 4, 0, 0xc);
    memset(m_08 + 0x10, 0, 0x2c);
}

// FUNCTION: GAME 0x0061e7e0
void *SBNativeFontBase::FUN_0061e7e0(unsigned flags)
{
    this->~SBNativeFontBase();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x0061e800
SBNativeFontBase::~SBNativeFontBase()
{
    *(unsigned *)this = 0x67ae34;
}

void EmitSBFontUnk0061e800(SBNativeFontBase *a)
{
    a->~SBNativeFontBase();
}

// FUNCTION: GAME 0x0061e810
void SBFontUnk0061e840::FUN_0061e810(int value, int)
{
    if (m_04) {
        v6();
    }
    m_04 = value;
}

// FUNCTION: GAME 0x0061e840
void SBFontUnk0061e840::FUN_0061e840()
{
    m_04 = 0;
}

// FUNCTION: GAME 0x0061e850
int SBFontUnk0061e840::FUN_0061e850(unsigned short value)
{
    int first;
    int second;
    int result = v3(value, first, second);
    return first + second + result;
}

// FUNCTION: GAME 0x0061e880
int SBFontUnk0061e840::FUN_0061e880()
{
    return m_14;
}

// FUNCTION: GAME 0x0061e8a0
std::string SBFontUnk0061e840::FUN_0061e8a0()
{
    return std::string(m_18);
}

// FUNCTION: GAME 0x0061e970
int SBFontUnk0061e840::FUN_0061e970()
{
    return m_3c;
}

// Parked at 0.4645: unannotated park from the asymmetric-comparator era; residual scheduling/registers.
// STUB: GAME 0x0061e980
int SBFontUnk0061e840::FUN_0061e980(void *value, int &first, int &second)
{
    SBFontTextView &text = *(SBFontTextView *)value;
    first = 0;
    second = 0;
    int width = 0;
    for (unsigned short *it = text.m_04, *next = it + 1;
         it != text.end(); ++it, ++next) {
        int left;
        int right;
        int result = v3(*it, left, right);
        width += v8();
        width += result;
        if (it == text.m_04) {
            first = left;
        } else {
            width += left;
        }
        if (next == text.end()) {
            second = right;
        } else {
            width += right;
        }
    }
    return width;
}

// FUNCTION: GAME 0x0061ea50
int SBFontUnk0061e840::FUN_0061ea50(void *value)
{
    int first;
    int second;
    int result = FUN_0061e980(value, first, second);
    return first + second + result;
}

// FUNCTION: GAME 0x0061ea80
bool SBFontUnk0061e840::FUN_0061ea80(const std::string &name)
{
    RHUnk005f4fc0 file;
    bool result = false;
    if (file.FUN_005f5090(name, 1) == 0) {
        result = v9(file);
    }
    m_08[0] = result;
    return result;
}

// FUNCTION: GAME 0x0061eb00
bool SBFontUnk0061e840::FUN_0061eb00(SBFile &file)
{
    char tag[6];
    file.Access(m_08 + 4, 6);
    if (file.Access(&m_14, 4)) {
        return false;
    }
    v1(tag);
    if (memcmp(m_08 + 4, tag, 6)) {
        return false;
    }
    if (file.Access(m_18, 0x2c)) {
        return false;
    }
    return true;
}

// FUNCTION: GAME 0x0061eb80
int SBFontUnk0061e840::FUN_0061eb80(SBFontTextView *text, void *a, const void *b, bool c)
{
    int count = 0;
    for (unsigned short *it = text->m_04; it != text->end(); ++count, ++it) {
        v4(*it, a, b, c);
    }
    return count;
}

// Parked: font-name return ABI and pair-copy materialization remain unmatched.
// STUB: GAME 0x0061ebd0
void SBFontUnk0061e840::FUN_0061ebd0(unsigned short value)
{
    std::string name = FUN_0061e8a0();
    undefined compare;
    undefined allocator;
    SBFontPair0061f3e0 result = g_unk0x006c1900.FUN_0061f3e0(
        SBFontValue0061f120(name, SBFontTree0061fcb0(compare, false, allocator)));
    SBFontTree0061fcb0 &characters = result.m_00.m_00->m_0c.m_10;
    SBFontIterator0061fe10 it = characters.FUN_0061fe10(value);
    if (it.m_00 == characters.m_04 || value < it.m_00->m_0c) {
        it = characters.end();
    }
    if (it.m_00 == characters.m_04) {
        characters.FUN_0061f2b0(value);
        FUN_005f8030(0, g_sbFontFile, 0x17d, g_sbFontMissing, (unsigned)value, name.c_str());
    }
}

// FUNCTION: GAME 0x0061ed70
bool SBFontUnk0061e840::FUN_0061ed70(SBFile &file)
{
    v1(m_08 + 4);
    m_14 = v0();
    file.Access(m_08 + 4, 6);
    if (file.Access(&m_14, 4)) {
        return false;
    }
    if (file.Access(m_18, 0x2c)) {
        return false;
    }
    return true;
}

// FUNCTION: GAME 0x0061edd0
SBFontTree0061f3e0::SBFontTree0061f3e0(const undefined &comparison, const undefined &allocation)
{
    m_00[0] = allocation;
    m_00[1] = comparison;
    m_08 = false;
    SBFontLock lock;
    if (g_unk0x006c1914 == 0) {
        SBFontNode0061f3e0 *node = (SBFontNode0061f3e0 *)operator new(0x30);
        node->m_04 = 0;
        node->m_2c = 1;
        g_unk0x006c1914 = node;
        g_unk0x006c1914->m_00 = 0;
        g_unk0x006c1914->m_08 = 0;
    }
    ++g_unk0x006c1918;
    SBFontNode0061f3e0 *sentinel = g_unk0x006c1914;
    SBFontNode0061f3e0 *node = (SBFontNode0061f3e0 *)operator new(0x30);
    node->m_04 = sentinel;
    node->m_2c = 0;
    m_04 = node;
    m_0c = 0;
    m_04->m_00 = m_04;
    m_04->m_08 = m_04;
}

// FUNCTION: GAME 0x0061eea0
void SBFontTree0061fcb0::FUN_0061eea0()
{
    FUN_0061fce0(begin(), end());
    operator delete(m_04);
    m_04 = 0;
    m_0c = 0;
    {
        SBFontLock lock;
        if (--g_unk0x006c1920 == 0) {
            operator delete(g_unk0x006c191c);
            g_unk0x006c191c = 0;
        }
    }
}

// FUNCTION: GAME 0x0061ef10
SBFontValue0061f120::~SBFontValue0061f120()
{
}

// FUNCTION: GAME 0x0061efe0
SBFontIterator0061f3e0 SBFontTree0061f3e0::FUN_0061efe0(SBFontIterator0061f3e0 first, SBFontIterator0061f3e0 last)
{
    if (m_0c != 0 && first.m_00 == m_04->m_00 && last.m_00 == m_04) {
        SBFontLock lock;
        SBFontNode0061f3e0 *node = root();
        {
            SBFontLock inner;
            for (SBFontNode0061f3e0 *next = node; next != g_unk0x006c1914; node = next) {
                FUN_0061fb40(next->m_08);
                next = next->m_00;
                node->m_0c.~SBFontValue0061f120();
                operator delete(node);
            }
        }
        root() = g_unk0x006c1914;
        m_0c = 0;
        leftmost() = m_04;
        rightmost() = m_04;
        return begin();
    }
    while (first.m_00 != last.m_00)
        FUN_0061f550(first++);
    return first;
}

// FUNCTION: GAME 0x0061f120
SBFontValue0061f120::SBFontValue0061f120(const std::string &name, const SBFontTree0061fcb0 &tree)
    : m_00(name), m_10(tree)
{
}

// FUNCTION: GAME 0x0061f2b0
SBFontPair0061f2b0 SBFontTree0061fcb0::FUN_0061f2b0(const unsigned short &value)
{
    SBFontNode0061fcb0 *node = m_04->m_04;
    SBFontNode0061fcb0 *parent = m_04;
    bool left = true;
    {
        SBFontLock lock;
        while (node != g_unk0x006c191c) {
            parent = node;
            left = value < node->m_0c;
            node = left ? node->m_00 : node->m_08;
        }
    }
    if (m_08) {
        SBFontPair0061f2b0 result(FUN_0061fe30(node, parent, value), true);
        return result;
    }
    SBFontIterator0061fe10 it;
    it.m_00 = parent;
    if (left) {
        if (it.m_00 == m_04->m_00) {
            SBFontPair0061f2b0 result(FUN_0061fe30(node, parent, value), true);
            return result;
        }
        it.FUN_00620ca0();
    }
    if (it.m_00->m_0c < value) {
        SBFontPair0061f2b0 result(FUN_0061fe30(node, parent, value), true);
        return result;
    }
    SBFontPair0061f2b0 result(it, false);
    return result;
}

// Parked: pair-construction calls and frame slots differ from the target.
// STUB: GAME 0x0061f3e0
SBFontPair0061f3e0 SBFontTree0061f3e0::FUN_0061f3e0(const SBFontValue0061f120 &value)
{
    SBFontNode0061f3e0 *node = m_04->m_04;
    SBFontNode0061f3e0 *parent = m_04;
    bool left = true;
    {
        SBFontLock lock;
        while (node != g_unk0x006c1914) {
            parent = node;
            const RHProfileText &key = *(const RHProfileText *)&value.m_00;
            const RHProfileText &other = *(const RHProfileText *)&node->m_0c.m_00;
            left = key.FUN_00460900(0, key.m_size, other.c_str(), other.m_size) < 0;
            node = left ? node->m_00 : node->m_08;
        }
    }
    if (m_08) {
        SBFontPair0061f3e0 result(FUN_00620130(node, parent, value), true);
        return result;
    }
    SBFontIterator0061f3e0 it;
    it.m_00 = parent;
    if (left) {
        if (it.m_00 == m_04->m_00) {
            SBFontPair0061f3e0 result(FUN_00620130(node, parent, value), true);
            return result;
        }
        it.FUN_00620e30();
    }
    if (((RHCampaignCommandLine *)&it.m_00->m_0c.m_00)->FUN_0045a010(*(const RHProfileText *)&value.m_00) < 0) {
        SBFontPair0061f3e0 result(FUN_00620130(node, parent, value), true);
        return result;
    }
    SBFontPair0061f3e0 result(it, false);
    return result;
}

// Parked: the original inlines the value destructor with out-of-line iterator construction; this layer cannot reproduce that inline depth.
// STUB: GAME 0x0061f550
SBFontIterator0061f3e0 SBFontTree0061f3e0::FUN_0061f550(SBFontIterator0061f3e0 position)
{
    SBFontNode0061f3e0 *replacement;
    SBFontNode0061f3e0 *removed = (position++).m_00;
    SBFontNode0061f3e0 *original = removed;
    SBFontLock lock;
    if (SBFontLeft(removed) == g_unk0x006c1914) replacement = SBFontRight(removed);
    else if (SBFontRight(removed) == g_unk0x006c1914) replacement = SBFontLeft(removed);
    else {
        removed = SBFontMinimum(SBFontRight(removed), g_unk0x006c1914);
        replacement = SBFontRight(removed);
    }
    if (removed != original) {
        SBFontParent(SBFontLeft(original)) = removed;
        SBFontLeft(removed) = SBFontLeft(original);
        if (removed == SBFontRight(original)) SBFontParent(replacement) = removed;
        else {
            SBFontParent(replacement) = SBFontParent(removed);
            SBFontLeft(SBFontParent(removed)) = replacement;
            SBFontRight(removed) = SBFontRight(original);
            SBFontParent(SBFontRight(original)) = removed;
        }
        if (root() == original) root() = removed;
        else if (SBFontLeft(SBFontParent(original)) == original) SBFontLeft(SBFontParent(original)) = removed;
        else SBFontRight(SBFontParent(original)) = removed;
        SBFontParent(removed) = SBFontParent(original);
        std::swap(SBFontColor(removed), SBFontColor(original));
        removed = original;
    } else {
        SBFontParent(replacement) = SBFontParent(removed);
        if (root() == original) root() = replacement;
        else if (SBFontLeft(SBFontParent(original)) == original) SBFontLeft(SBFontParent(original)) = replacement;
        else SBFontRight(SBFontParent(original)) = replacement;
        if (leftmost() == original) {
            if (SBFontRight(original) == g_unk0x006c1914) leftmost() = SBFontParent(original);
            else leftmost() = SBFontMinimum(replacement, g_unk0x006c1914);
        }
        if (rightmost() == original) {
            if (SBFontLeft(original) == g_unk0x006c1914) rightmost() = SBFontParent(original);
            else rightmost() = SBFontMaximum(replacement, g_unk0x006c1914);
        }
    }
    if (SBFontColor(removed) == 1) {
        while (replacement != root() && SBFontColor(replacement) == 1) {
            if (replacement == SBFontLeft(SBFontParent(replacement))) {
                SBFontNode0061f3e0 *sibling = SBFontRight(SBFontParent(replacement));
                if (SBFontColor(sibling) == 0) {
                    SBFontColor(sibling) = 1;
                    SBFontColor(SBFontParent(replacement)) = 0;
                    SBFontRotateLeft(this, SBFontParent(replacement), g_unk0x006c1914);
                    sibling = SBFontRight(SBFontParent(replacement));
                }
                if (SBFontColor(SBFontLeft(sibling)) == 1 && SBFontColor(SBFontRight(sibling)) == 1) {
                    SBFontColor(sibling) = 0;
                    replacement = SBFontParent(replacement);
                } else {
                    if (SBFontColor(SBFontRight(sibling)) == 1) {
                        SBFontColor(SBFontLeft(sibling)) = 1;
                        SBFontColor(sibling) = 0;
                        SBFontRotateRight(this, sibling, g_unk0x006c1914);
                        sibling = SBFontRight(SBFontParent(replacement));
                    }
                    SBFontColor(sibling) = SBFontColor(SBFontParent(replacement));
                    SBFontColor(SBFontParent(replacement)) = 1;
                    SBFontColor(SBFontRight(sibling)) = 1;
                    SBFontRotateLeft(this, SBFontParent(replacement), g_unk0x006c1914);
                    break;
                }
            } else {
                SBFontNode0061f3e0 *sibling = SBFontLeft(SBFontParent(replacement));
                if (SBFontColor(sibling) == 0) {
                    SBFontColor(sibling) = 1;
                    SBFontColor(SBFontParent(replacement)) = 0;
                    SBFontRotateRight(this, SBFontParent(replacement), g_unk0x006c1914);
                    sibling = SBFontLeft(SBFontParent(replacement));
                }
                if (SBFontColor(SBFontRight(sibling)) == 1 && SBFontColor(SBFontLeft(sibling)) == 1) {
                    SBFontColor(sibling) = 0;
                    replacement = SBFontParent(replacement);
                } else {
                    if (SBFontColor(SBFontLeft(sibling)) == 1) {
                        SBFontColor(SBFontRight(sibling)) = 1;
                        SBFontColor(sibling) = 0;
                        SBFontRotateLeft(this, sibling, g_unk0x006c1914);
                        sibling = SBFontLeft(SBFontParent(replacement));
                    }
                    SBFontColor(sibling) = SBFontColor(SBFontParent(replacement));
                    SBFontColor(SBFontParent(replacement)) = 1;
                    SBFontColor(SBFontLeft(sibling)) = 1;
                    SBFontRotateRight(this, SBFontParent(replacement), g_unk0x006c1914);
                    break;
                }
            }
        }
        SBFontColor(replacement) = 1;
    }
    removed->m_0c.~SBFontValue0061f120();
    operator delete(removed);
    --m_0c;
    return position;
}

// Parked: the original inlines the value destructor (with its unwind state) but keeps iterator construction out of line.
// STUB: GAME 0x0061fb40
void SBFontTree0061f3e0::FUN_0061fb40(SBFontNode0061f3e0 *node)
{
    SBFontLock lock;
    for (SBFontNode0061f3e0 *next = node; next != g_unk0x006c1914; node = next) {
        FUN_0061fb40(next->m_08);
        next = next->m_00;
        SBFontDestroyValue(node->m_0c);
        operator delete(node);
    }
}

// FUNCTION: GAME 0x0061fcb0
SBFontTree0061fcb0::SBFontTree0061fcb0(const undefined &compare, bool multi, const undefined &allocator)
    : m_00(allocator), m_01(compare), m_08(multi)
{
    FUN_00620b70();
}

// FUNCTION: GAME 0x0061fce0
SBFontIterator0061fe10 SBFontTree0061fcb0::FUN_0061fce0(SBFontIterator0061fe10 first, SBFontIterator0061fe10 last)
{
    if (m_0c != 0 && first.m_00 == m_04->m_00 && last.m_00 == m_04) {
        SBFontLock lock;
        SBFontNode0061fcb0 *node = m_04->m_04;
        {
            SBFontLock inner;
            for (SBFontNode0061fcb0 *next = node; next != g_unk0x006c191c; node = next) {
                FUN_00620ae0(next->m_08);
                next = next->m_00;
                operator delete(node);
            }
        }
        root() = g_unk0x006c191c;
        m_0c = 0;
        leftmost() = m_04;
        rightmost() = m_04;
        return begin();
    }
    while (first != last)
        FUN_00620440(first++);
    return first;
}

// FUNCTION: GAME 0x0061fe10
SBFontIterator0061fe10 SBFontTree0061fcb0::FUN_0061fe10(const unsigned short &value)
{
    SBFontIterator0061fe10 result;
    result.m_00 = FUN_00620c20(value);
    return result;
}

// FUNCTION: GAME 0x0061fe30
SBFontIterator0061fe10 SBFontTree0061fcb0::FUN_0061fe30(SBFontNode0061fcb0 *node, SBFontNode0061fcb0 *parent, const unsigned short &value)
{
    SBFontLock lock;
    SBFontNode0061fcb0 *inserted = (SBFontNode0061fcb0 *)operator new(sizeof(SBFontNode0061fcb0));
    inserted->m_04 = parent;
    inserted->m_10 = 0;
    inserted->m_00 = g_unk0x006c191c;
    inserted->m_08 = g_unk0x006c191c;
    void (*construct)(unsigned short *, const unsigned short &) = &std::_Construct;
    construct(&inserted->m_0c, value);
    ++m_0c;
    if (parent == m_04 || node != g_unk0x006c191c || value < parent->m_0c) {
        parent->m_00 = inserted;
        if (parent == m_04) {
            m_04->m_04 = inserted;
            m_04->m_08 = inserted;
        } else if (parent == m_04->m_00) m_04->m_00 = inserted;
    } else {
        parent->m_08 = inserted;
        if (parent == m_04->m_08) m_04->m_08 = inserted;
    }
    for (node = inserted; node != m_04->m_04 && node->m_04->m_10 == 0;) {
        if (node->m_04 == SBFontLeft(node->m_04->m_04)) {
            parent = node->m_04->m_04->m_08;
            if (parent->m_10 == 0) {
                node->m_04->m_10 = 1;
                parent->m_10 = 1;
                node->m_04->m_04->m_10 = 0;
                node = node->m_04->m_04;
            } else {
                if (node == node->m_04->m_08) {
                    node = node->m_04;
                    SBFontRotateLeft(this, node, g_unk0x006c191c);
                }
                node->m_04->m_10 = 1;
                node->m_04->m_04->m_10 = 0;
                SBFontRotateRight(this, node->m_04->m_04, g_unk0x006c191c);
            }
        } else {
            parent = node->m_04->m_04->m_00;
            if (parent->m_10 == 0) {
                node->m_04->m_10 = 1;
                parent->m_10 = 1;
                node->m_04->m_04->m_10 = 0;
                node = node->m_04->m_04;
            } else {
                if (node == node->m_04->m_00) {
                    node = node->m_04;
                    SBFontRotateRight(this, node, g_unk0x006c191c);
                }
                node->m_04->m_10 = 1;
                node->m_04->m_04->m_10 = 0;
                SBFontRotateLeft(this, node->m_04->m_04, g_unk0x006c191c);
            }
        }
    }
    m_04->m_04->m_10 = 1;
    SBFontIterator0061fe10 result;
    result.m_00 = inserted;
    return result;
}

// FUNCTION: GAME 0x00620130
SBFontIterator0061f3e0 SBFontTree0061f3e0::FUN_00620130(SBFontNode0061f3e0 *node, SBFontNode0061f3e0 *parent, const SBFontValue0061f120 &value)
{
    SBFontLock lock;
    SBFontNode0061f3e0 *inserted = (SBFontNode0061f3e0 *)operator new(sizeof(SBFontNode0061f3e0));
    inserted->m_04 = parent;
    inserted->m_2c = 0;
    inserted->m_00 = g_unk0x006c1914;
    inserted->m_08 = g_unk0x006c1914;
    SBFontConstructValue(&inserted->m_0c, value);
    ++m_0c;
    if (parent == m_04 || node != g_unk0x006c1914 ||
        ((RHCampaignCommandLine *)&value.m_00)->FUN_0045a010(*(const RHProfileText *)&parent->m_0c.m_00) < 0) {
        parent->m_00 = inserted;
        if (parent == m_04) {
            m_04->m_04 = inserted;
            m_04->m_08 = inserted;
        } else if (parent == m_04->m_00) m_04->m_00 = inserted;
    } else {
        parent->m_08 = inserted;
        if (parent == m_04->m_08) m_04->m_08 = inserted;
    }
    for (node = inserted; node != m_04->m_04 && node->m_04->m_2c == 0;) {
        if (node->m_04 == SBFontLeft(node->m_04->m_04)) {
            parent = node->m_04->m_04->m_08;
            if (parent->m_2c == 0) {
                node->m_04->m_2c = 1;
                parent->m_2c = 1;
                node->m_04->m_04->m_2c = 0;
                node = node->m_04->m_04;
            } else {
                if (node == node->m_04->m_08) {
                    node = node->m_04;
                    SBFontRotateLeft(this, node, g_unk0x006c1914);
                }
                node->m_04->m_2c = 1;
                node->m_04->m_04->m_2c = 0;
                SBFontRotateRight(this, node->m_04->m_04, g_unk0x006c1914);
            }
        } else {
            parent = node->m_04->m_04->m_00;
            if (parent->m_2c == 0) {
                node->m_04->m_2c = 1;
                parent->m_2c = 1;
                node->m_04->m_04->m_2c = 0;
                node = node->m_04->m_04;
            } else {
                if (node == node->m_04->m_00) {
                    node = node->m_04;
                    SBFontRotateRight(this, node, g_unk0x006c1914);
                }
                node->m_04->m_2c = 1;
                node->m_04->m_04->m_2c = 0;
                SBFontRotateLeft(this, node->m_04->m_04, g_unk0x006c1914);
            }
        }
    }
    m_04->m_04->m_2c = 1;
    SBFontIterator0061f3e0 result;
    result.m_00 = inserted;
    return result;
}

// FUNCTION: GAME 0x00620440
SBFontIterator0061fe10 SBFontTree0061fcb0::FUN_00620440(SBFontIterator0061fe10 position)
{
    SBFontNode0061fcb0 *replacement;
    SBFontNode0061fcb0 *removed = (position++).m_00;
    SBFontNode0061fcb0 *original = removed;
    SBFontLock lock;
    if (SBFontLeft(removed) == g_unk0x006c191c) replacement = SBFontRight(removed);
    else if (SBFontRight(removed) == g_unk0x006c191c) replacement = SBFontLeft(removed);
    else {
        removed = SBFontMinimum(SBFontRight(removed), g_unk0x006c191c);
        replacement = SBFontRight(removed);
    }
    if (removed != original) {
        SBFontParent(SBFontLeft(original)) = removed;
        SBFontLeft(removed) = SBFontLeft(original);
        if (removed == SBFontRight(original)) SBFontParent(replacement) = removed;
        else {
            SBFontParent(replacement) = SBFontParent(removed);
            SBFontLeft(SBFontParent(removed)) = replacement;
            SBFontRight(removed) = SBFontRight(original);
            SBFontParent(SBFontRight(original)) = removed;
        }
        if (root() == original) root() = removed;
        else if (SBFontLeft(SBFontParent(original)) == original) SBFontLeft(SBFontParent(original)) = removed;
        else SBFontRight(SBFontParent(original)) = removed;
        SBFontParent(removed) = SBFontParent(original);
        std::swap(SBFontColor(removed), SBFontColor(original));
        removed = original;
    } else {
        SBFontParent(replacement) = SBFontParent(removed);
        if (root() == original) root() = replacement;
        else if (SBFontLeft(SBFontParent(original)) == original) SBFontLeft(SBFontParent(original)) = replacement;
        else SBFontRight(SBFontParent(original)) = replacement;
        if (leftmost() == original) {
            if (SBFontRight(original) == g_unk0x006c191c) leftmost() = SBFontParent(original);
            else leftmost() = SBFontMinimum(replacement, g_unk0x006c191c);
        }
        if (rightmost() == original) {
            if (SBFontLeft(original) == g_unk0x006c191c) rightmost() = SBFontParent(original);
            else rightmost() = SBFontMaximum(replacement, g_unk0x006c191c);
        }
    }
    if (SBFontColor(removed) == 1) {
        while (replacement != root() && SBFontColor(replacement) == 1) {
            if (replacement == SBFontLeft(SBFontParent(replacement))) {
                SBFontNode0061fcb0 *sibling = SBFontRight(SBFontParent(replacement));
                if (SBFontColor(sibling) == 0) {
                    SBFontColor(sibling) = 1;
                    SBFontColor(SBFontParent(replacement)) = 0;
                    SBFontRotateLeft(this, SBFontParent(replacement), g_unk0x006c191c);
                    sibling = SBFontRight(SBFontParent(replacement));
                }
                if (SBFontColor(SBFontLeft(sibling)) == 1 && SBFontColor(SBFontRight(sibling)) == 1) {
                    SBFontColor(sibling) = 0;
                    replacement = SBFontParent(replacement);
                } else {
                    if (SBFontColor(SBFontRight(sibling)) == 1) {
                        SBFontColor(SBFontLeft(sibling)) = 1;
                        SBFontColor(sibling) = 0;
                        SBFontRotateRight(this, sibling, g_unk0x006c191c);
                        sibling = SBFontRight(SBFontParent(replacement));
                    }
                    SBFontColor(sibling) = SBFontColor(SBFontParent(replacement));
                    SBFontColor(SBFontParent(replacement)) = 1;
                    SBFontColor(SBFontRight(sibling)) = 1;
                    SBFontRotateLeft(this, SBFontParent(replacement), g_unk0x006c191c);
                    break;
                }
            } else {
                SBFontNode0061fcb0 *sibling = SBFontLeft(SBFontParent(replacement));
                if (SBFontColor(sibling) == 0) {
                    SBFontColor(sibling) = 1;
                    SBFontColor(SBFontParent(replacement)) = 0;
                    SBFontRotateRight(this, SBFontParent(replacement), g_unk0x006c191c);
                    sibling = SBFontLeft(SBFontParent(replacement));
                }
                if (SBFontColor(SBFontRight(sibling)) == 1 && SBFontColor(SBFontLeft(sibling)) == 1) {
                    SBFontColor(sibling) = 0;
                    replacement = SBFontParent(replacement);
                } else {
                    if (SBFontColor(SBFontLeft(sibling)) == 1) {
                        SBFontColor(SBFontRight(sibling)) = 1;
                        SBFontColor(sibling) = 0;
                        SBFontRotateLeft(this, sibling, g_unk0x006c191c);
                        sibling = SBFontLeft(SBFontParent(replacement));
                    }
                    SBFontColor(sibling) = SBFontColor(SBFontParent(replacement));
                    SBFontColor(SBFontParent(replacement)) = 1;
                    SBFontColor(SBFontLeft(sibling)) = 1;
                    SBFontRotateRight(this, SBFontParent(replacement), g_unk0x006c191c);
                    break;
                }
            }
        }
        SBFontColor(replacement) = 1;
    }
    operator delete(removed);
    --m_0c;
    return position;
}

// FUNCTION: GAME 0x00620960
void SBFontTree0061fcb0::FUN_00620960(const SBFontTree0061fcb0 &other)
{
    SBFontLock lock;
    root() = SBFontCopyNodes(this, other.m_04->m_04, m_04);
    m_0c = other.size();
    if (root() != g_unk0x006c191c) {
        leftmost() = SBFontMinimum(root(), g_unk0x006c191c);
        rightmost() = SBFontMaximum(root(), g_unk0x006c191c);
    } else {
        leftmost() = m_04;
        rightmost() = m_04;
    }
}

// FUNCTION: GAME 0x00620ae0
void SBFontTree0061fcb0::FUN_00620ae0(SBFontNode0061fcb0 *node)
{
    SBFontLock lock;
    SBFontNode0061fcb0 *current = node;
    while (current != g_unk0x006c191c)
    {
        FUN_00620ae0(current->m_08);
        current = current->m_00;
        operator delete(node);
        node = current;
    }
}

// FUNCTION: GAME 0x00620b70
void SBFontTree0061fcb0::FUN_00620b70()
{
    SBFontLock lock;
    if (!g_unk0x006c191c)
    {
        SBFontNode0061fcb0 *node = (SBFontNode0061fcb0 *)operator new(sizeof(SBFontNode0061fcb0));
        node->m_04 = 0;
        node->m_10 = 1;
        g_unk0x006c191c = node;
        g_unk0x006c191c->m_00 = 0;
        g_unk0x006c191c->m_08 = 0;
    }
    ++g_unk0x006c1920;
    SBFontNode0061fcb0 *parent = g_unk0x006c191c;
    SBFontNode0061fcb0 *node = (SBFontNode0061fcb0 *)operator new(sizeof(SBFontNode0061fcb0));
    node->m_04 = parent;
    node->m_10 = 0;
    m_04 = node;
    m_0c = 0;
    m_04->m_00 = m_04;
    m_04->m_08 = m_04;
}

// FUNCTION: GAME 0x00620c20
SBFontNode0061fcb0 *SBFontTree0061fcb0::FUN_00620c20(const unsigned short &key)
{
    SBFontLock lock;
    SBFontNode0061fcb0 *head = m_04;
    SBFontNode0061fcb0 *node = head->m_04;
    SBFontNode0061fcb0 *result = head;
    while (node != g_unk0x006c191c)
    {
        if (node->m_0c < key)
            node = node->m_08;
        else
        {
            result = node;
            node = node->m_00;
        }
    }
    return result;
}

static inline SBFontNode0061fcb0 *SBFontMax0061fcb0(SBFontNode0061fcb0 *node)
{
    SBFontLock lock;
    while (node->m_08 != g_unk0x006c191c)
        node = node->m_08;
    return node;
}

// FUNCTION: GAME 0x00620ca0
void SBFontIterator0061fe10::FUN_00620ca0()
{
    SBFontLock lock;
    if (m_00->m_10 == 0 && m_00->m_04->m_04 == m_00)
        m_00 = m_00->m_08;
    else if (Left(m_00) != g_unk0x006c191c)
        m_00 = SBFontMax0061fcb0(Left(m_00));
    else
    {
        SBFontNode0061fcb0 *parent;
        while (m_00 == (parent = m_00->m_04)->m_00)
            m_00 = parent;
        m_00 = parent;
    }
}

static inline SBFontNode0061f3e0 *SBFontMax0061f3e0(SBFontNode0061f3e0 *node)
{
    SBFontLock lock;
    while (node->m_08 != g_unk0x006c1914)
        node = node->m_08;
    return node;
}

// FUNCTION: GAME 0x00620e30
void SBFontIterator0061f3e0::FUN_00620e30()
{
    SBFontLock lock;
    if (m_00->m_2c == 0 && m_00->m_04->m_04 == m_00)
        m_00 = m_00->m_08;
    else if (Left(m_00) != g_unk0x006c1914)
        m_00 = SBFontMax0061f3e0(Left(m_00));
    else
    {
        SBFontNode0061f3e0 *parent;
        while (m_00 == (parent = m_00->m_04)->m_00)
            m_00 = parent;
        m_00 = parent;
    }
}

static inline SBFontNode0061f3e0 *SBFontMin0061f3e0(SBFontNode0061f3e0 *node)
{
    SBFontLock lock;
    while (node->m_00 != g_unk0x006c1914)
        node = node->m_00;
    return node;
}

// FUNCTION: GAME 0x00620ef0
void SBFontIterator0061f3e0::FUN_00620ef0()
{
    SBFontLock lock;
    if (m_00->m_08 != g_unk0x006c1914)
        m_00 = SBFontMin0061f3e0(m_00->m_08);
    else {
        SBFontNode0061f3e0 *parent;
        while (m_00 == (parent = m_00->m_04)->m_08)
            m_00 = parent;
        if (m_00->m_08 != parent)
            m_00 = parent;
    }
}

void EmitSBFontIncrement(SBFontIterator0061f3e0 &iterator)
{
    iterator.FUN_00620ef0();
    g_unk0x006c1900.FUN_0061e740();
}

static inline SBFontNode0061fcb0 *SBFontMin0061fcb0(SBFontNode0061fcb0 *node)
{
    SBFontLock lock;
    while (node->m_00 != g_unk0x006c191c)
        node = node->m_00;
    return node;
}

// FUNCTION: GAME 0x00620fa0
void SBFontIterator0061fe10::FUN_00620fa0()
{
    SBFontLock lock;
    if (m_00->m_08 != g_unk0x006c191c)
        m_00 = SBFontMin0061fcb0(m_00->m_08);
    else
    {
        SBFontNode0061fcb0 *parent;
        while (m_00 == (parent = m_00->m_04)->m_08)
            m_00 = parent;
        if (m_00->m_08 != parent)
            m_00 = parent;
    }
}

void SBFontEmit(SBFontUnk0061e840 *font, unsigned short value)
{
    undefined comparison = 0;
    SBFontTree0061f3e0 fonts(comparison, comparison);
    font->FUN_0061e810(value, 0);
    font->FUN_0061e840();
    font->FUN_0061e850(value);
    font->FUN_0061e880();
    font->FUN_0061e8a0();
    font->FUN_0061e970();
    font->FUN_0061ea50(0);
    font->FUN_0061ea80(std::string());
    font->FUN_0061eb80(0, 0, 0, 0);
    font->FUN_0061eb00(*(SBFile *)0);
    font->FUN_0061ed70(*(SBFile *)0);
    font->FUN_0061ebd0(value);
    undefined byte;
    SBFontTree0061fcb0 tree(byte, false, byte);
    tree.FUN_0061fe10(value);
    tree.FUN_0061eea0();
    tree.FUN_0061f2b0(value);
    tree.FUN_00620ae0(g_unk0x006c191c);
    tree.FUN_00620440(tree.begin());
    SBFontValue0061f120 pair(std::string(), tree);
    g_unk0x006c1900.FUN_0061f3e0(pair);
}
