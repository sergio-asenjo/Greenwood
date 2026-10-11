#include "RHFontManager.h"

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
class RHCampaignCommandLine
{
public:
    undefined m_allocator[4]; // 0x00
    char *m_chars; // 0x04
    unsigned m_length; // 0x08
    unsigned m_capacity; // 0x0c
    void FUN_00457be0() { ((std::string *)this)->begin(); }
};

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

// FUNCTION: GAME 0x005c1270
RHFontInsertResult::RHFontInsertResult(const RHFontIterator &iterator, const bool &inserted)
    : first(iterator), second(inserted)
{
}

void RHFontManager::Emit(const std::string &name)
{
    LoadConfiguration(name);
    RHFontText text;
    RHFontText copy(text);
}
