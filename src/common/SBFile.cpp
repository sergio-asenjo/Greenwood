#include "SBNullstr.h"
#include "SBFile.h"
#include "RHSaveGame.h"
#include "SCSerialize.h"
#include "RHCivilianProfile.h"
#include "RHProfileFileCore.h"
#include "SBFilePosition.h"
#include "RHFontManager.h"

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

struct SBFileTreeCtorNode54
{
    SBFileTreeCtorNode54 *left;
    SBFileTreeCtorNode54 *parent;
    SBFileTreeCtorNode54 *right;
    char value[0x44];
    int color;
};

struct SBFileTreeCtorNode2c
{
    SBFileTreeCtorNode2c *left;
    SBFileTreeCtorNode2c *parent;
    SBFileTreeCtorNode2c *right;
    char value[0x1c];
    int color;
};

struct SBFileTreeInc005f74f0
{
    SBFileTreeCtorNode54 *m_node;
    void Advance();
    SBFileTreeInc005f74f0 operator++(int)
    {
        SBFileTreeInc005f74f0 previous = *this;
        Advance();
        return previous;
    }
};

struct SBFileTreeInc005f7840
{
    SBFileTreeCtorNode2c *m_node;
    void Advance();
    SBFileTreeInc005f7840 operator++(int)
    {
        SBFileTreeInc005f7840 previous = *this;
        Advance();
        return previous;
    }
};

class SBFileTree005f64a0
{
public:
    typedef SBFileTreeCtorNode54 Node;
    typedef SBFileTreeInc005f74f0 Iterator;
    SBFileTree005f64a0(const char &, const char &);
    void FUN_005f4db0();
    Iterator FUN_005f6bb0(Iterator, Iterator);
    void FUN_005f7410(Node *);
    static Node *&Left(Node *node) { return node->left; }
    static Node *&Parent(Node *node) { return node->parent; }
    static Node *&Right(Node *node) { return node->right; }
    static int &Color(Node *node) { return node->color; }
    Node *&Root() { return head->parent; }
    Node *&Leftmost() { return head->left; }
    Node *&Rightmost() { return head->right; }
    Iterator Begin()
    {
        Iterator result;
        result.m_node = Leftmost();
        return result;
    }
    inline void Lrotate(Node *x);
    inline void Rrotate(Node *x);
    char allocator;
    char compare;
    char padding[2];
    SBFileTreeCtorNode54 *head;
    bool multi;
    char padding09[3];
    unsigned size;
};

class SBFileTree005f6570
{
public:
    typedef SBFileTreeCtorNode2c Node;
    typedef SBFileTreeInc005f7840 Iterator;
    SBFileTree005f6570(const char &, const char &);
    void FUN_005f4e80();
    Iterator FUN_005f7220(Iterator, Iterator);
    void FUN_005f75a0(Node *);
    static Node *&Left(Node *node) { return node->left; }
    static Node *&Parent(Node *node) { return node->parent; }
    static Node *&Right(Node *node) { return node->right; }
    static int &Color(Node *node) { return node->color; }
    Node *&Root() { return head->parent; }
    Node *&Leftmost() { return head->left; }
    Node *&Rightmost() { return head->right; }
    Iterator Begin()
    {
        Iterator result;
        result.m_node = Leftmost();
        return result;
    }
    inline void Lrotate(Node *x);
    inline void Rrotate(Node *x);
    char allocator;
    char compare;
    char padding[2];
    SBFileTreeCtorNode2c *head;
    bool multi;
    char padding09[3];
    unsigned size;
};

extern SBFileTreeCtorNode54 *g_unk0x006c1380;
extern unsigned g_unk0x006c1384;
extern SBFileTreeCtorNode2c *g_unk0x006c1388;
extern unsigned g_unk0x006c138c;

extern SBFileTree g_unk0x006c1348;
extern SBFileTree g_unk0x006c1358;

// FUNCTION: GAME 0x005f4d60
void FUN_005f4d60()
{
    char comparison, allocation;
    ((SBFileTree005f64a0 *)&g_unk0x006c1348)->SBFileTree005f64a0::SBFileTree005f64a0(comparison, allocation);
}

// FUNCTION: GAME 0x005f4db0
void SBFileTree005f64a0::FUN_005f4db0()
{
    Iterator first;
    first.m_node = Leftmost();
    Iterator last;
    last.m_node = head;
    FUN_005f6bb0(first, last);
    operator delete(head);
    head = 0;
    size = 0;
    {
        std::_Lockit lock;
        if (--g_unk0x006c1384 == 0) {
            operator delete(g_unk0x006c1380);
            g_unk0x006c1380 = 0;
        }
    }
}

// FUNCTION: GAME 0x005f4e30
void FUN_005f4e30()
{
    char comparison, allocation;
    ((SBFileTree005f6570 *)&g_unk0x006c1358)->SBFileTree005f6570::SBFileTree005f6570(comparison, allocation);
}

// FUNCTION: GAME 0x005f4e80
void SBFileTree005f6570::FUN_005f4e80()
{
    Iterator first;
    first.m_node = Leftmost();
    Iterator last;
    last.m_node = head;
    FUN_005f7220(first, last);
    operator delete(head);
    head = 0;
    size = 0;
    {
        std::_Lockit lock;
        if (--g_unk0x006c138c == 0) {
            operator delete(g_unk0x006c1388);
            g_unk0x006c1388 = 0;
        }
    }
}

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

// Parked: switch default is placed before the origin-2 case instead of after origin-0.
// STUB: GAME 0x005f5370
int RHProfileFile::FUN_005f5370(int offset, int origin)
{
    int position;
    if (!SBFile_embedded)
        position = offset;
    else {
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
        default:
            position = offset;
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

// GLOBAL: GAME 0x006c1380
SBFileTreeCtorNode54 *g_unk0x006c1380 = 0;
// GLOBAL: GAME 0x006c1384
unsigned g_unk0x006c1384 = 0;
// GLOBAL: GAME 0x006c1388
SBFileTreeCtorNode2c *g_unk0x006c1388 = 0;
// GLOBAL: GAME 0x006c138c
unsigned g_unk0x006c138c = 0;

// FUNCTION: GAME 0x005f64a0
SBFileTree005f64a0::SBFileTree005f64a0(const char &comparison, const char &allocation)
{
    allocator = allocation;
    compare = comparison;
    multi = false;
    std::_Lockit lock;
    if (g_unk0x006c1380 == 0) {
        SBFileTreeCtorNode54 *node = (SBFileTreeCtorNode54 *)operator new(0x54);
        node->parent = 0;
        node->color = 1;
        g_unk0x006c1380 = node;
        g_unk0x006c1380->left = 0;
        g_unk0x006c1380->right = 0;
    }
    ++g_unk0x006c1384;
    SBFileTreeCtorNode54 *sentinel = g_unk0x006c1380;
    SBFileTreeCtorNode54 *node = (SBFileTreeCtorNode54 *)operator new(0x54);
    node->parent = sentinel;
    node->color = 0;
    head = node;
    size = 0;
    head->left = head;
    head->right = head;
}

// FUNCTION: GAME 0x005f6570
SBFileTree005f6570::SBFileTree005f6570(const char &comparison, const char &allocation)
{
    allocator = allocation;
    compare = comparison;
    multi = false;
    std::_Lockit lock;
    if (g_unk0x006c1388 == 0) {
        SBFileTreeCtorNode2c *node = (SBFileTreeCtorNode2c *)operator new(0x2c);
        node->parent = 0;
        node->color = 1;
        g_unk0x006c1388 = node;
        g_unk0x006c1388->left = 0;
        g_unk0x006c1388->right = 0;
    }
    ++g_unk0x006c138c;
    SBFileTreeCtorNode2c *sentinel = g_unk0x006c1388;
    SBFileTreeCtorNode2c *node = (SBFileTreeCtorNode2c *)operator new(0x2c);
    node->parent = sentinel;
    node->color = 0;
    head = node;
    size = 0;
    head->left = head;
    head->right = head;
}

void EmitSBFileTreeCtors()
{
    char value = 0;
    SBFileTree005f64a0 archives(value, value);
    archives.FUN_005f4db0();
    SBFileTree005f6570 entries(value, value);
    entries.FUN_005f4e80();
}

static inline SBFileTreeCtorNode54 *SBFileTreeMin54(SBFileTreeCtorNode54 *node)
{
    std::_Lockit lock;
    while (node->left != g_unk0x006c1380)
        node = node->left;
    return node;
}

static inline SBFileTreeCtorNode54 *SBFileTreeMax54(SBFileTreeCtorNode54 *node)
{
    std::_Lockit lock;
    while (node->right != g_unk0x006c1380)
        node = node->right;
    return node;
}

inline void SBFileTree005f64a0::Lrotate(Node *x)
{
    std::_Lockit lock;
    Node *y = x->right;
    x->right = y->left;
    if (y->left != g_unk0x006c1380)
        y->left->parent = x;
    y->parent = x->parent;
    if (x == Root())
        Root() = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

inline void SBFileTree005f64a0::Rrotate(Node *x)
{
    std::_Lockit lock;
    Node *y = x->left;
    x->left = y->right;
    if (y->right != g_unk0x006c1380)
        y->right->parent = x;
    y->parent = x->parent;
    if (x == Root())
        Root() = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

// FUNCTION: GAME 0x005f6640
SBFileTreeIterator SBFileTree::FUN_005f6640(SBFileTreeIterator iterator)
{
    typedef SBFileTreeCtorNode54 Node;
    typedef SBFileTree005f64a0 Tree;
    Tree &tree = *(Tree *)this;
    Node *x;
    Node *y = (*(SBFileTreeInc005f74f0 *)&iterator)++.m_node;
    Node *z = y;
    std::_Lockit lock;
    if (Tree::Left(y) == g_unk0x006c1380)
        x = Tree::Right(y);
    else if (Tree::Right(y) == g_unk0x006c1380)
        x = Tree::Left(y);
    else
    {
        y = SBFileTreeMin54(Tree::Right(y));
        x = Tree::Right(y);
    }
    {
        if (y != z)
        {
            Tree::Parent(Tree::Left(z)) = y;
            Tree::Left(y) = Tree::Left(z);
            if (y == Tree::Right(z))
                Tree::Parent(x) = y;
            else
            {
                Tree::Parent(x) = Tree::Parent(y);
                Tree::Left(Tree::Parent(y)) = x;
                Tree::Right(y) = Tree::Right(z);
                Tree::Parent(Tree::Right(z)) = y;
            }
            if (tree.Root() == z)
                tree.Root() = y;
            else if (Tree::Left(Tree::Parent(z)) == z)
                Tree::Left(Tree::Parent(z)) = y;
            else
                Tree::Right(Tree::Parent(z)) = y;
            Tree::Parent(y) = Tree::Parent(z);
            std::swap(Tree::Color(y), Tree::Color(z));
            y = z;
        }
        else
        {
            Tree::Parent(x) = Tree::Parent(y);
            if (tree.Root() == z)
                tree.Root() = x;
            else if (Tree::Left(Tree::Parent(z)) == z)
                Tree::Left(Tree::Parent(z)) = x;
            else
                Tree::Right(Tree::Parent(z)) = x;
            if (tree.Leftmost() == z)
            {
                if (Tree::Right(z) == g_unk0x006c1380)
                    tree.Leftmost() = Tree::Parent(z);
                else
                {
                    tree.Leftmost() = SBFileTreeMin54(x);
                }
            }
            if (tree.Rightmost() == z)
            {
                if (Tree::Left(z) == g_unk0x006c1380)
                    tree.Rightmost() = Tree::Parent(z);
                else
                {
                    tree.Rightmost() = SBFileTreeMax54(x);
                }
            }
        }
        if (Tree::Color(y) == 1)
        {
            while (x != tree.Root() && Tree::Color(x) == 1)
            {
                if (x == Tree::Left(Tree::Parent(x)))
                {
                    Node *w = Tree::Right(Tree::Parent(x));
                    if (Tree::Color(w) == 0)
                    {
                        Tree::Color(w) = 1;
                        Tree::Color(Tree::Parent(x)) = 0;
                        tree.Lrotate(Tree::Parent(x));
                        w = Tree::Right(Tree::Parent(x));
                    }
                    if (Tree::Color(Tree::Left(w)) == 1 && Tree::Color(Tree::Right(w)) == 1)
                    {
                        Tree::Color(w) = 0;
                        x = Tree::Parent(x);
                    }
                    else
                    {
                        if (Tree::Color(Tree::Right(w)) == 1)
                        {
                            Tree::Color(Tree::Left(w)) = 1;
                            Tree::Color(w) = 0;
                            tree.Rrotate(w);
                            w = Tree::Right(Tree::Parent(x));
                        }
                        Tree::Color(w) = Tree::Color(Tree::Parent(x));
                        Tree::Color(Tree::Parent(x)) = 1;
                        Tree::Color(Tree::Right(w)) = 1;
                        tree.Lrotate(Tree::Parent(x));
                        break;
                    }
                }
                else
                {
                    Node *w = Tree::Left(Tree::Parent(x));
                    if (Tree::Color(w) == 0)
                    {
                        Tree::Color(w) = 1;
                        Tree::Color(Tree::Parent(x)) = 0;
                        tree.Rrotate(Tree::Parent(x));
                        w = Tree::Left(Tree::Parent(x));
                    }
                    if (Tree::Color(Tree::Right(w)) == 1 && Tree::Color(Tree::Left(w)) == 1)
                    {
                        Tree::Color(w) = 0;
                        x = Tree::Parent(x);
                    }
                    else
                    {
                        if (Tree::Color(Tree::Left(w)) == 1)
                        {
                            Tree::Color(Tree::Right(w)) = 1;
                            Tree::Color(w) = 0;
                            tree.Lrotate(w);
                            w = Tree::Left(Tree::Parent(x));
                        }
                        Tree::Color(w) = Tree::Color(Tree::Parent(x));
                        Tree::Color(Tree::Parent(x)) = 1;
                        Tree::Color(Tree::Left(w)) = 1;
                        tree.Rrotate(Tree::Parent(x));
                        break;
                    }
                }
            }
            Tree::Color(x) = 1;
        }
    }
    ((std::string *)(y->value + 0x10))->~basic_string();
    ((std::string *)y->value)->~basic_string();
    operator delete(y);
    --tree.size;
    return iterator;
}

// FUNCTION: GAME 0x005f6bb0
SBFileTree005f64a0::Iterator SBFileTree005f64a0::FUN_005f6bb0(Iterator first, Iterator last)
{
    if (size != 0 && first.m_node == head->left && last.m_node == head) {
        std::_Lockit lock;
        Node *node = Root();
        {
            std::_Lockit inner;
            for (Node *next = node; next != g_unk0x006c1380; node = next) {
                FUN_005f7410(next->right);
                next = next->left;
                ((RHFontManager::Fonts *)node->value)->~Fonts();
                operator delete(node);
            }
        }
        Root() = g_unk0x006c1380;
        size = 0;
        Leftmost() = head;
        Rightmost() = head;
        return Begin();
    }
    while (first.m_node != last.m_node)
        ((SBFileTree *)this)->FUN_005f6640(SBFileTreeIterator((first++).m_node));
    return first;
}

static inline SBFileTreeCtorNode2c *SBFileTreeMin2c(SBFileTreeCtorNode2c *node)
{
    std::_Lockit lock;
    while (node->left != g_unk0x006c1388)
        node = node->left;
    return node;
}

static inline SBFileTreeCtorNode2c *SBFileTreeMax2c(SBFileTreeCtorNode2c *node)
{
    std::_Lockit lock;
    while (node->right != g_unk0x006c1388)
        node = node->right;
    return node;
}

inline void SBFileTree005f6570::Lrotate(Node *x)
{
    std::_Lockit lock;
    Node *y = x->right;
    x->right = y->left;
    if (y->left != g_unk0x006c1388)
        y->left->parent = x;
    y->parent = x->parent;
    if (x == Root())
        Root() = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

inline void SBFileTree005f6570::Rrotate(Node *x)
{
    std::_Lockit lock;
    Node *y = x->left;
    x->left = y->right;
    if (y->right != g_unk0x006c1388)
        y->right->parent = x;
    y->parent = x->parent;
    if (x == Root())
        Root() = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

// FUNCTION: GAME 0x005f6cf0
SBFileTreeIterator SBFileTree::FUN_005f6cf0(SBFileTreeIterator iterator)
{
    typedef SBFileTreeCtorNode2c Node;
    typedef SBFileTree005f6570 Tree;
    Tree &tree = *(Tree *)this;
    Node *x;
    Node *y = (*(SBFileTreeInc005f7840 *)&iterator)++.m_node;
    Node *z = y;
    std::_Lockit lock;
    if (Tree::Left(y) == g_unk0x006c1388)
        x = Tree::Right(y);
    else if (Tree::Right(y) == g_unk0x006c1388)
        x = Tree::Left(y);
    else
    {
        y = SBFileTreeMin2c(Tree::Right(y));
        x = Tree::Right(y);
    }
    {
        if (y != z)
        {
            Tree::Parent(Tree::Left(z)) = y;
            Tree::Left(y) = Tree::Left(z);
            if (y == Tree::Right(z))
                Tree::Parent(x) = y;
            else
            {
                Tree::Parent(x) = Tree::Parent(y);
                Tree::Left(Tree::Parent(y)) = x;
                Tree::Right(y) = Tree::Right(z);
                Tree::Parent(Tree::Right(z)) = y;
            }
            if (tree.Root() == z)
                tree.Root() = y;
            else if (Tree::Left(Tree::Parent(z)) == z)
                Tree::Left(Tree::Parent(z)) = y;
            else
                Tree::Right(Tree::Parent(z)) = y;
            Tree::Parent(y) = Tree::Parent(z);
            std::swap(Tree::Color(y), Tree::Color(z));
            y = z;
        }
        else
        {
            Tree::Parent(x) = Tree::Parent(y);
            if (tree.Root() == z)
                tree.Root() = x;
            else if (Tree::Left(Tree::Parent(z)) == z)
                Tree::Left(Tree::Parent(z)) = x;
            else
                Tree::Right(Tree::Parent(z)) = x;
            if (tree.Leftmost() == z)
            {
                if (Tree::Right(z) == g_unk0x006c1388)
                    tree.Leftmost() = Tree::Parent(z);
                else
                {
                    tree.Leftmost() = SBFileTreeMin2c(x);
                }
            }
            if (tree.Rightmost() == z)
            {
                if (Tree::Left(z) == g_unk0x006c1388)
                    tree.Rightmost() = Tree::Parent(z);
                else
                {
                    tree.Rightmost() = SBFileTreeMax2c(x);
                }
            }
        }
        if (Tree::Color(y) == 1)
        {
            while (x != tree.Root() && Tree::Color(x) == 1)
            {
                if (x == Tree::Left(Tree::Parent(x)))
                {
                    Node *w = Tree::Right(Tree::Parent(x));
                    if (Tree::Color(w) == 0)
                    {
                        Tree::Color(w) = 1;
                        Tree::Color(Tree::Parent(x)) = 0;
                        tree.Lrotate(Tree::Parent(x));
                        w = Tree::Right(Tree::Parent(x));
                    }
                    if (Tree::Color(Tree::Left(w)) == 1 && Tree::Color(Tree::Right(w)) == 1)
                    {
                        Tree::Color(w) = 0;
                        x = Tree::Parent(x);
                    }
                    else
                    {
                        if (Tree::Color(Tree::Right(w)) == 1)
                        {
                            Tree::Color(Tree::Left(w)) = 1;
                            Tree::Color(w) = 0;
                            tree.Rrotate(w);
                            w = Tree::Right(Tree::Parent(x));
                        }
                        Tree::Color(w) = Tree::Color(Tree::Parent(x));
                        Tree::Color(Tree::Parent(x)) = 1;
                        Tree::Color(Tree::Right(w)) = 1;
                        tree.Lrotate(Tree::Parent(x));
                        break;
                    }
                }
                else
                {
                    Node *w = Tree::Left(Tree::Parent(x));
                    if (Tree::Color(w) == 0)
                    {
                        Tree::Color(w) = 1;
                        Tree::Color(Tree::Parent(x)) = 0;
                        tree.Rrotate(Tree::Parent(x));
                        w = Tree::Left(Tree::Parent(x));
                    }
                    if (Tree::Color(Tree::Right(w)) == 1 && Tree::Color(Tree::Left(w)) == 1)
                    {
                        Tree::Color(w) = 0;
                        x = Tree::Parent(x);
                    }
                    else
                    {
                        if (Tree::Color(Tree::Left(w)) == 1)
                        {
                            Tree::Color(Tree::Right(w)) = 1;
                            Tree::Color(w) = 0;
                            tree.Lrotate(w);
                            w = Tree::Left(Tree::Parent(x));
                        }
                        Tree::Color(w) = Tree::Color(Tree::Parent(x));
                        Tree::Color(Tree::Parent(x)) = 1;
                        Tree::Color(Tree::Left(w)) = 1;
                        tree.Rrotate(Tree::Parent(x));
                        break;
                    }
                }
            }
            Tree::Color(x) = 1;
        }
    }
    ((std::string *)y->value)->~basic_string();
    operator delete(y);
    --tree.size;
    return iterator;
}

// FUNCTION: GAME 0x005f7220
SBFileTree005f6570::Iterator SBFileTree005f6570::FUN_005f7220(Iterator first, Iterator last)
{
    if (size != 0 && first.m_node == head->left && last.m_node == head) {
        std::_Lockit lock;
        Node *node = Root();
        {
            std::_Lockit inner;
            for (Node *next = node; next != g_unk0x006c1388; node = next) {
                FUN_005f75a0(next->right);
                next = next->left;
                ((RHProfileText *)node->value)->~RHProfileText();
                operator delete(node);
            }
        }
        Root() = g_unk0x006c1388;
        size = 0;
        Leftmost() = head;
        Rightmost() = head;
        return Begin();
    }
    while (first.m_node != last.m_node)
        ((SBFileTree *)this)->FUN_005f6cf0(SBFileTreeIterator((first++).m_node));
    return first;
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

// FUNCTION: GAME 0x005f7410
void SBFileTree005f64a0::FUN_005f7410(Node *node)
{
    std::_Lockit lock;
    for (Node *next = node; next != g_unk0x006c1380; node = next) {
        FUN_005f7410(next->right);
        next = next->left;
        ((std::string *)(node->value + 0x10))->~basic_string();
        ((std::string *)node->value)->~basic_string();
        operator delete(node);
    }
}

// FUNCTION: GAME 0x005f74f0
void SBFileTreeInc005f74f0::Advance()
{
    std::_Lockit lock;
    if (m_node->right != g_unk0x006c1380)
        m_node = SBFileTreeMin54(m_node->right);
    else {
        SBFileTreeCtorNode54 *parent;
        while (m_node == (parent = m_node->parent)->right)
            m_node = parent;
        if (m_node->right != parent)
            m_node = parent;
    }
}

// FUNCTION: GAME 0x005f75a0
void SBFileTree005f6570::FUN_005f75a0(Node *node)
{
    std::_Lockit lock;
    for (Node *next = node; next != g_unk0x006c1388; node = next) {
        FUN_005f75a0(next->right);
        next = next->left;
        ((std::string *)node->value)->~basic_string();
        operator delete(node);
    }
}

// FUNCTION: GAME 0x005f7650
SBFileTreeNode *SBFileTree::FUN_005f7650(const std::string &key)
{
    std::_Lockit lock;
    SBFileTreeNode *node = m_head->m_parent;
    SBFileTreeNode *candidate = m_head;
    while (node != (SBFileTreeNode *)g_unk0x006c1380) {
        if (node->m_key.compare(key) < 0)
            node = node->m_right;
        else {
            candidate = node;
            node = node->m_left;
        }
    }
    return candidate;
}

// FUNCTION: GAME 0x005f7710
SBFileTreeNode *SBFileTree::FUN_005f7710(const std::string &key)
{
    std::_Lockit lock;
    SBFileTreeNode *node = m_head->m_parent;
    SBFileTreeNode *candidate = m_head;
    while (node != (SBFileTreeNode *)g_unk0x006c1388) {
        if (node->m_key.compare(key) < 0)
            node = node->m_right;
        else {
            candidate = node;
            node = node->m_left;
        }
    }
    return candidate;
}

// FUNCTION: GAME 0x005f7840
void SBFileTreeInc005f7840::Advance()
{
    std::_Lockit lock;
    if (m_node->right != g_unk0x006c1388)
        m_node = SBFileTreeMin2c(m_node->right);
    else {
        SBFileTreeCtorNode2c *parent;
        while (m_node == (parent = m_node->parent)->right)
            m_node = parent;
        if (m_node->right != parent)
            m_node = parent;
    }
}

void EmitSBFileTreeIncrement(SBFileTreeInc005f74f0 &archives, SBFileTreeInc005f7840 &entries)
{
    archives.Advance();
    entries.Advance();
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
