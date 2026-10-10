#include "SBNullstr.h"
#include "SBFile.h"
#include "RHSaveGame.h"
#include "SCSerialize.h"
#include "RHCivilianProfile.h"

// SIZE 0x10
class RHCampaignCommandLine
{
public:
    int FUN_0045a010(const RHProfileText &value);
    undefined4 m_allocator; // 0x00
    char *m_chars; // 0x04
    unsigned int m_size; // 0x08
    unsigned int m_capacity; // 0x0c
};

extern void SBFileAssert(int, const char *, int, const char *, ...);

DECOMP_SIZE_ASSERT(SBFileUnk005f5280, 0x01)
DECOMP_SIZE_ASSERT(SBFileTreeIterator, 0x04)
DECOMP_SIZE_ASSERT(SBFileTreeNode, 0x1c)
DECOMP_SIZE_ASSERT(SBFileTree, 0x10)
DECOMP_SIZE_ASSERT(RHCampaignCommandLine, 0x10)
DECOMP_SIZE_ASSERT(RHProfileText, 0x10)

#define SBFile_stream (*(FILE **)((char *)this))
#define SBFile_position (*(int *)((char *)this + 0xc))
#define SBFile_error (*(int *)((char *)this + 0x14))
#define SBFile_embedded (*(char *)((char *)this + 0x28))
#define SBFile_start (*(int *)((char *)this + 0x2c))

// FUNCTION: GAME 0x005f5280
int SBFileUnk005f5280::FUN_005f5280(int)
{
    return -1;
}

// FUNCTION: GAME 0x005f5290
void RHUnk005f4fc0::FUN_005f5290()
{
    if (SBFile_embedded != 1) {
        SCSerializeUnk00643c56(SBFile_stream);
        SBFile_stream = 0;
    }
}

// FUNCTION: GAME 0x005f52b0
int SBFile::Access(void *buffer, int size)
{
    if (SBFile_stream == 0 && SBFile_embedded == 0)
        return SBFile_error = -4;
    if (SBFile_embedded == 1) {
        if (SBFileUnk00643a8f(SBFile_stream) != SBFile_start + SBFile_position)
            SBFileUnk006439d6(SBFile_stream, SBFile_start + SBFile_position, 0);
    }
    if (m_bLoading != 0) {
        if (SBFileUnk00643e0c(buffer, 1, size, SBFile_stream) != size)
            return SBFile_error = -5;
    } else {
        if (SBFileUnk00643cd3(buffer, 1, size, SBFile_stream) != size)
            return SBFile_error = -6;
    }
    SBFile_error = 0;
    SBFile_position += size;
    return 0;
}

void SBFileEmit(SBFileUnk005f5280 *file)
{
    file->FUN_005f5280(0);
}

// GLOBAL: GAME 0x006c135c
void **g_unk0x006c135c = 0;

// GLOBAL: GAME 0x006c1364
unsigned int g_unk0x006c1364 = 0;

// GLOBAL: GAME 0x006c1348
SBFileTree g_unk0x006c1348 = {0};

// GLOBAL: GAME 0x006c1358
SBFileTree g_unk0x006c1358 = {0};

// STRING: GAME 0x006b9d70
static const char *const g_sbFileName = "P:\\Robin Hood\\SBLibNG\\SBFile.cpp";

// STRING: GAME 0x006b9db8
static const char *const g_sbFileArchiveWarning = "Warning, unable to find a file entry while closing an archive";

// FUNCTION: GAME 0x005f54d0
int FUN_005f54d0()
{
    int result = 0;
    while (g_unk0x006c1364 != 0 && result == 0) {
        result = (int)*g_unk0x006c135c + 12;
        result = FUN_005f5500((void *)result);
    }
    return result;
}

// Unannotated: coupled caller; iterator temporaries and EH frame differ.
int FUN_005f5500(const void *key)
{
    SBFileTreeIterator archive = g_unk0x006c1358.FUN_005f7360(*(const std::string *)key);
    if (archive.m_node == g_unk0x006c1358.m_head)
        return -1;
    unsigned int count = *(unsigned int *)((char *)archive.m_node + 0x20);
    unsigned int index = 0;
    unsigned int offset = 0;
    if (count != 0) {
        do {
            char *name = *(char **)((char *)archive.m_node + 0x24) + offset;
            SBFileTreeIterator entry(0);
            {
                RHProfileText text;
                unsigned int size = strlen(name);
                if (text.FUN_00402280(size, true)) {
                    memcpy(text.m_chars, name, size);
                    text.m_size = size;
                    text.m_chars[size] = 0;
                }
                SBFileTreeIterator candidate = g_unk0x006c1348.FUN_005f73f0(*(std::string *)&text);
                entry = candidate.m_node == g_unk0x006c1348.m_head ||
                    ((RHCampaignCommandLine *)&text)->FUN_0045a010(
                        *(RHProfileText *)((char *)candidate.m_node + 0x0c)) < 0
                    ? SBFileTreeIterator(g_unk0x006c1348.m_head) : candidate;
            }
            if (entry.m_node != g_unk0x006c1348.m_head)
                g_unk0x006c1348.FUN_005f6640(entry);
            else
                SBFileAssert(0, g_sbFileName, 0x2de, g_sbFileArchiveWarning);
            ++index;
            offset += 0x58;
        } while (index != *(unsigned int *)((char *)archive.m_node + 0x20));
    }
    operator delete(*(void **)((char *)archive.m_node + 0x24));
    g_unk0x006c1358.FUN_005f6cf0(archive);
    return 0;
}

// FUNCTION: GAME 0x005f63c0
// wmemset

// FUNCTION: GAME 0x005f7360
SBFileTreeIterator SBFileTree::FUN_005f7360(const std::string &key)
{
    SBFileTreeIterator iterator(FUN_005f7710(key));
    return iterator.m_node == m_head || key < ((SBFileTreeNode *)iterator.m_node)->m_key
        ? SBFileTreeIterator(m_head) : iterator;
}

// FUNCTION: GAME 0x005f73f0
SBFileTreeIterator SBFileTree::FUN_005f73f0(const std::string &key)
{
    return SBFileTreeIterator(FUN_005f7650(key));
}

void SBFileTreeEmit(SBFileTree *tree, const std::string &key)
{
    tree->FUN_005f7360(key);
    tree->FUN_005f73f0(key);
}
