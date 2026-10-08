#ifndef RHFONTMANAGER_H
#define RHFONTMANAGER_H

#include "RHSaveGame.h"
#include "RHCivilianProfile.h"
#include "Decomp.h"
#include <map>
#include <stdio.h>

// SIZE 0x10
class RHFontText
{
public:
    std::allocator<char> m_allocator; // 0x00
    char *m_chars; // 0x04
    unsigned m_size; // 0x08
    unsigned m_capacity; // 0x0c
    RHFontText(const RHFontText &value);
    RHFontText(const std::allocator<char> &allocator = std::allocator<char>()) : m_allocator(allocator)
    {
        ((RHProfileText *)this)->FUN_00401ee0(false);
    }
    ~RHFontText()
    {
        if (m_chars == 0)
            ;
        else if (*((unsigned char *)m_chars - 1) == 0 || *((unsigned char *)m_chars - 1) == 255)
            m_allocator.deallocate(m_chars - 1, m_capacity + 1);
        else
            --*((unsigned char *)m_chars - 1);
        m_chars = 0, m_size = 0, m_capacity = 0;
    }
    void Assign(const std::string &value)
    {
        ((RHProfileText *)this)->FUN_00401ce0(value, 0, std::string::npos);
    }
};

// SIZE 0x04
struct RHFontIterator
{
    struct Node
    {
        undefined m_00[0x1c]; // 0x00
        void *m_1c; // 0x1c
    };
    Node *m_node; // 0x00
};

// SIZE 0x08
struct RHFontInsertResult
{
    RHFontInsertResult(const RHFontIterator &, const bool &);
    RHFontIterator first; // 0x00
    bool second; // 0x04
};

// SIZE 0x0c
class RHFontMap
{
public:
    RHFontInsertResult FUN_00502c20(const std::pair<const std::string, void *> &);
    RHFontInsertResult Insert(const std::pair<const std::string, void *> &value)
    {
        RHFontInsertResult answer = FUN_00502c20(value);
        return RHFontInsertResult(answer.first, answer.second);
    }
    void *&operator[](const std::string &key)
    {
        RHFontIterator position = Insert(std::pair<const std::string, void *>(key, (void *)0)).first;
        return position.m_node->m_1c;
    }
    undefined m_00[0x0c]; // 0x00
};

// SIZE 0x0c
class RHFontManager
{
public:
    // SIZE 0x20
    struct Fonts
    {
        std::string m_00; // +0x00
        std::string m_10; // +0x10; sizeof = 0x20
        ~Fonts();
    };
    void LoadConfiguration(const std::string &name);
    static std::string Get(FILE *file, char delimiter);
    void TrimString(std::string &value);
    void Emit(const std::string &name);
    RHFontMap m_fonts; // +0x00; tree node value +0x0c, Fonts* +0x1c
};

#endif
