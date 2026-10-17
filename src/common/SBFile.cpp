#include "SBNullstr.h"
#include "SBFile.h"
#include "RHSaveGame.h"
#include "SCSerialize.h"
#include "RHCivilianProfile.h"
#include "RHProfileFileCore.h"
#include "SBFilePosition.h"

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

class SBFileArchiveText
{
public:
    explicit SBFileArchiveText(const char *value, const std::allocator<char> &allocator = std::allocator<char>())
    {
        m_allocator = *(const char *)&allocator;
        ((RHProfileText *)this)->FUN_00401ee0(false);
        unsigned int length = strlen(value);
        if (((RHProfileText *)this)->FUN_00402280(length, true)) {
            memcpy(m_chars, value, length);
            m_size = length;
            m_chars[length] = 0;
        }
    }
    ~SBFileArchiveText() { ((RHProfileText *)this)->FUN_00401ee0(true); }
    char m_allocator;
    char *m_chars;
    unsigned int m_size;
    unsigned int m_capacity;
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

#include <windows.h>

// GLOBAL: GAME 0x006c137c
bool (*g_unk0x006c137c)(const std::string &) = 0;

// FUNCTION: GAME 0x005f5090
int RHUnk005f4fc0::FUN_005f5090(const std::string &name, int mode)
{
    for (;;) {
        if (SBFile_stream && *(char *)((char *)this + 0x3c) == 0)
            FUN_005f5290();
        HANDLE file = CreateFileA(name.c_str(), GENERIC_READ, FILE_SHARE_READ, 0,
            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
        if (file != INVALID_HANDLE_VALUE) {
            GetFileTime(file, (FILETIME *)((char *)this + 0x40),
                (FILETIME *)((char *)this + 0x48), (FILETIME *)((char *)this + 0x50));
            CloseHandle(file);
        }
        switch (mode) {
        case 1:
            if ((SBFile_stream = SCSerializeUnk00643c43(name.c_str(), "rb")) == 0 &&
                (SBFile_stream = FUN_005f58c0(name, "rb")) == 0 &&
                ((SBFileUnk005f5280 *)this)->FUN_005f5280((int)&name) == -1) {
                SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBFile.cpp", 0xcb,
                    // STRING: GAME 0x006b9d94
                    "Unable to find the file '%s'", name.c_str());
                if (g_unk0x006c137c && g_unk0x006c137c(name) == true)
                    continue;
                return SBFile_error = -1;
            }
            m_bLoading = true;
            break;
        case 2:
        case 8:
            if ((SBFile_stream = SCSerializeUnk00643c43(name.c_str(),
                // STRING: GAME 0x006b9d6c
                "wb")) == 0 && (SBFile_stream = FUN_005f58c0(name, "wb")) == 0)
                return SBFile_error = -1;
            m_bLoading = false;
            break;
        case 4:
            if ((SBFile_stream = SCSerializeUnk00643c43(name.c_str(),
                // STRING: GAME 0x006b9d68
                "ab")) == 0 && (SBFile_stream = FUN_005f58c0(name, "ab")) == 0)
                return SBFile_error = -1;
            m_bLoading = false;
            break;
        }
        SBFile_position = 0;
        SBFileUnk006439d6(SBFile_stream, 0, 2);
        *(long *)((char *)this + 8) = SBFileUnk00643a8f(SBFile_stream);
        SBFileUnk006439d6(SBFile_stream, 0, 0);
        SBFile_error = 0;
        return 0;
    }
}

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

// Parked: seek branch-local offset loading and register allocation differ.
// STUB: GAME 0x005f5370
int RHProfileFile::FUN_005f5370(int offset, int origin)
{
    int position = offset;
    if (SBFile_embedded) {
        switch (origin) {
        case 2:
            position = SBFile_start + *(int *)((char *)this + 8) - offset;
            origin = 0;
            break;
        case 1:
            position = SBFile_start + SBFile_position + offset;
            origin = 0;
            break;
        case 0:
            position = SBFile_start + offset;
            break;
        }
    }
    if (SBFile_stream == 0 && SBFile_embedded == 0)
        return SBFile_error = -4;
    if (SBFileUnk006439d6(SBFile_stream, position, origin) != 0)
        return SBFile_error = -7;
    if (SBFile_embedded == 1) {
        SBFile_error = 0;
        SBFile_position = position - SBFile_start;
        return 0;
    }
    SBFile_position = SBFileUnk00643a8f(SBFile_stream);
    SBFile_error = 0;
    return 0;
}

// FUNCTION: GAME 0x005f5440
unsigned long ToolboxPositionFile::FUN_005f5440()
{
    if (SBFile_embedded == 0)
        return SBFileUnk00643a8f(SBFile_stream);
    return SBFile_position;
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

// FUNCTION: GAME 0x005f5500
int FUN_005f5500(const void *key)
{
    typedef SBFileTreeIterator &(SBFileTree::*Find)(SBFileTreeIterator &, const std::string &);
    Find findArchive = (Find)&SBFileTree::FUN_005f7360;
    SBFileTreeIterator archiveStorage;
    SBFileTreeIterator archive((g_unk0x006c1358.*findArchive)(archiveStorage, *(const std::string *)key).m_node);
    if (archive.m_node == g_unk0x006c135c)
        return -1;
    unsigned int index = 0;
    unsigned int count = *(unsigned int *)((char *)archive.m_node + 0x20);
    if (count != index) {
        unsigned int offset = 0;
        do {
            char *name = *(char **)((char *)archive.m_node + 0x24) + offset;
            SBFileTreeIterator entry;
            {
                SBFileArchiveText text(name);
                Find findEntry = (Find)&SBFileTree::FUN_005f73f0;
                SBFileTreeIterator candidateStorage;
                SBFileTreeIterator candidate((g_unk0x006c1348.*findEntry)(candidateStorage, *(std::string *)&text).m_node);
                entry = candidate.m_node == g_unk0x006c1348.m_head ||
                    ((RHCampaignCommandLine *)&text)->FUN_0045a010(
                        *(RHProfileText *)((char *)candidate.m_node + 0x0c)) < 0
                    ? SBFileTreeIterator(g_unk0x006c1348.m_head) : candidate;
            }
            if (entry.m_node != g_unk0x006c1348.m_head)
                g_unk0x006c1348.FUN_005f6640(entry);
            else
                SBFileAssert(0, "P:\\Robin Hood\\SBLibNG\\SBFile.cpp", 0x2de,
                    "Warning, unable to find a file entry while closing an archive");
            ++index;
            offset += 0x58;
        } while (index != *(unsigned int *)((char *)archive.m_node + 0x20));
    }
    void *buffer = *(void **)((char *)archive.m_node + 0x24);
    operator delete(buffer);
    g_unk0x006c1358.FUN_005f6cf0(archive);
    return 0;
}

// GLOBAL: GAME 0x006c136c
std::string *g_unk0x006c136c = 0;

// GLOBAL: GAME 0x006c1370
std::string *g_unk0x006c1370 = 0;

// FUNCTION: GAME 0x005f58c0
FILE *RHUnk005f4fc0::FUN_005f58c0(const std::string &name, const char *mode)
{
    for (std::string *path = g_unk0x006c136c; path != g_unk0x006c1370; ++path) {
        FILE *stream;
        if ((stream = SCSerializeUnk00643c43((*path + std::string("\\") + name).c_str(), mode)) != 0)
            return stream;
    }
    return 0;
}

// Parked: VC6 shares the successful string-cleanup return tails.
// STUB: GAME 0x005f5a80
int FUN_005f5a80(std::string &name, bool retry)
{
    while (FUN_005f6400(name) != true) {
        for (std::string *path = g_unk0x006c136c; path != g_unk0x006c1370; ++path) {
            std::string candidate;
            candidate = *path + std::string("\\") + name;
            if (FUN_005f6400(candidate) == true) {
                name = candidate;
                return 0;
            }
        }
        if (g_unk0x006c137c && retry && g_unk0x006c137c(name) == true)
            retry = true;
        else
            return -1;
    }
    return 0;
}

// FUNCTION: GAME 0x005f5d00
bool FUN_005f5d00(const std::string &name)
{
    return DeleteFileA(name.c_str()) > 0;
}

// FUNCTION: GAME 0x005f5d30
bool FUN_005f5d30(const std::string &name)
{
    return CreateDirectoryA(name.c_str(), 0) > 0;
}

// FUNCTION: GAME 0x005f5d60
int RHUnk005f4fc0::FUN_005f5d60(const std::string &name, int mode)
{
    if (SBFile_stream)
        SCSerializeUnk00643c56(SBFile_stream);
    unsigned long access;
    unsigned long protection;
    unsigned long mappingAccess;
    if (mode & 1) {
        access = GENERIC_READ;
        protection = PAGE_READONLY;
        mappingAccess = FILE_MAP_READ;
    }
    if (mode & 2) {
        access = GENERIC_WRITE;
        protection = PAGE_READWRITE;
        mappingAccess = FILE_MAP_ALL_ACCESS;
    }
    HANDLE &file = *(HANDLE *)((char *)this + 0x30);
    HANDLE &mapping = *(HANDLE *)((char *)this + 0x34);
    void *&view = *(void **)((char *)this + 0x38);
    file = CreateFileA(name.c_str(), access, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    char *message;
    if (file == INVALID_HANDLE_VALUE) {
        FormatMessageA(0x1300, 0, GetLastError(), 0x400, (char *)&message, 0, 0);
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBFile.cpp", 0x437,
            // STRING: GAME 0x006b9e48
            "Unable to perform create file, %s", message);
        LocalFree(message);
        return 0;
    }
    mapping = CreateFileMappingA(file, 0, protection, 0, 0,
        // STRING: GAME 0x006b9e40
        "bank");
    if (mapping == INVALID_HANDLE_VALUE) {
        FormatMessageA(0x1300, 0, GetLastError(), 0x400, (char *)&message, 0, 0);
        CloseHandle(file);
        file = INVALID_HANDLE_VALUE;
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBFile.cpp", 0x450,
            // STRING: GAME 0x006b9e14
            "Unable to perform create file mapping, %s", message);
        LocalFree(message);
        return 0;
    }
    view = MapViewOfFile(mapping, mappingAccess, 0, 0, 0);
    if (!view) {
        FormatMessageA(0x1300, 0, GetLastError(), 0x400, (char *)&message, 0, 0);
        CloseHandle(mapping);
        CloseHandle(file);
        mapping = INVALID_HANDLE_VALUE;
        file = INVALID_HANDLE_VALUE;
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBFile.cpp", 0x46d,
            // STRING: GAME 0x006b9df8
            "Unable to map the view (%s)", message);
    }
    return (int)view;
}

// FUNCTION: GAME 0x005f5f30
SBString *SBFile::GetError()
{
#define message (*(std::string *)((char *)this + 0x18))
    switch (SBFile_error) {
    case 0:
        message =
            // STRING: GAME 0x006b9f34
            "No error reported";
        break;
    case -1:
        message =
            // STRING: GAME 0x006b9f24
            "file not found";
        break;
    case -2:
        message =
            // STRING: GAME 0x006b9f04
            "the file is not an archive file";
        break;
    case -3:
        message =
            // STRING: GAME 0x006b9ee4
            "incoherent archive structure";
        break;
    case -4:
        message =
            // STRING: GAME 0x006b9ecc
            "no file actually opened";
        break;
    case -5:
        message =
            // STRING: GAME 0x006b9ec0
            "read error";
        break;
    case -6:
        message =
            // STRING: GAME 0x006b9eb4
            "write error";
        break;
    case -7:
        message =
            // STRING: GAME 0x006b9ea8
            "seek error";
        break;
    case -8:
        message =
            // STRING: GAME 0x006b9e7c
            "not enough memory to perform the operation";
        break;
    default:
        message =
            // STRING: GAME 0x006b9e6c
            "unknown error";
        break;
    }
    return (SBString *)&message;
#undef message
}

// FUNCTION: GAME 0x005f6200
bool RHUnk005f4fc0::FUN_005f6200(void *value)
{
    FileTimeToSystemTime((const FILETIME *)((char *)this + 0x50), (SYSTEMTIME *)value);
    return true;
}

// Parked: string helper bindings and iterator-insertion inlining differ.
// STUB: GAME 0x005f6220
int RHUnk005f4fc0::FUN_005f6220(std::string &value)
{
    char character = 0;
    value.erase();
    while (character != '\n' && (unsigned int)SBFile_position < *(unsigned int *)((char *)this + 8)) {
        Access(&character, 1);
        if (character != '\n' && character != '\r')
            value.insert(value.end(), character);
    }
    return (unsigned int)SBFile_position < *(unsigned int *)((char *)this + 8);
}

// LIBRARY: GAME 0x005f63c0
// wmemset

// FUNCTION: GAME 0x005f6400
bool FUN_005f6400(const std::string &name)
{
    WIN32_FIND_DATAA data;
    HANDLE file = CreateFileA(name.c_str(), GENERIC_READ, FILE_SHARE_READ, 0,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (file != INVALID_HANDLE_VALUE) {
        CloseHandle(file);
        return true;
    }
    HANDLE search = FindFirstFileA(name.c_str(), &data);
    if (search != INVALID_HANDLE_VALUE) {
        FindClose(search);
        return true;
    }
    return false;
}

// FUNCTION: GAME 0x005f6490
bool FUN_005f6490(bool (*callback)(const std::string &))
{
    g_unk0x006c137c = callback;
    return true;
}

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

void SBFileLineEmit(RHUnk005f4fc0 *file, std::string &value)
{
    file->FUN_005f6220(value);
}
