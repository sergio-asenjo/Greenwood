#ifndef RHFONTMANAGER_H
#define RHFONTMANAGER_H

#include "RHSaveGame.h"
#include "RHCivilianProfile.h"
#include "Decomp.h"
#include <map>
#include <stdio.h>

struct RHFontInsertNode
{
    RHFontInsertNode *m_00;
    RHFontInsertNode *m_04;
    RHFontInsertNode *m_08;
    std::pair<const std::string, void *> m_0c;
    int m_20;
};

// SIZE 0x04
struct RHFontIterator
{
    typedef RHFontInsertNode Node;
    Node *m_node; // 0x00
    RHFontIterator operator++(int);
};

// SIZE 0x08
struct RHFontInsertResult
{
    RHFontInsertResult(const RHFontIterator &, const bool &);
    RHFontIterator first; // 0x00
    bool second; // 0x04
};

typedef RHFontIterator RHFontInsertIterator;

// SIZE 0x10
class RHFontInsertTree
{
public:
    typedef std::less<std::string> Compare;
    typedef std::allocator<void *> Allocator;
    RHFontInsertTree(const Compare &compare = Compare(), bool multi = false,
                     const Allocator &allocator = Allocator());
    ~RHFontInsertTree();
    RHFontInsertIterator FUN_005034d0(RHFontInsertNode *, RHFontInsertNode *, const std::pair<const std::string, void *> &);
    RHFontInsertIterator FUN_00502b90(const std::string &key);
    RHFontInsertNode *FUN_005037e0(const std::string &);
    RHFontInsertIterator FUN_00502a50(RHFontInsertIterator, RHFontInsertIterator);
    RHFontInsertIterator FUN_00502d90(RHFontInsertIterator);
    void FUN_005032c0(RHFontInsertNode *);
    void FUN_00503370();
    static RHFontInsertNode *&Left(RHFontInsertNode *node) { return node->m_00; }
    static RHFontInsertNode *&Parent(RHFontInsertNode *node) { return node->m_04; }
    static RHFontInsertNode *&Right(RHFontInsertNode *node) { return node->m_08; }
    static int &Color(RHFontInsertNode *node) { return node->m_20; }
    RHFontInsertNode *&Root() { return m_head->m_04; }
    RHFontInsertNode *&Leftmost() { return m_head->m_00; }
    RHFontInsertNode *&Rightmost() { return m_head->m_08; }
    inline void RotateLeft(RHFontInsertNode *);
    inline void RotateRight(RHFontInsertNode *);
    RHFontInsertResult FUN_00502c20(const std::pair<const std::string, void *> &);
    RHFontInsertResult Insert(const std::pair<const std::string, void *> &value)
    {
        RHFontInsertResult answer = FUN_00502c20(value);
        return RHFontInsertResult(answer.first, answer.second);
    }
    void *&operator[](const std::string &key)
    {
        RHFontIterator position = Insert(std::pair<const std::string, void *>(key, (void *)0)).first;
        return position.m_node->m_0c.second;
    }
    Allocator m_00;
    Compare m_01;
    undefined m_02[2];
    RHFontInsertNode *m_head;
    bool m_08;
    undefined m_09[3];
    unsigned m_count;
};

// SIZE 0x14
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
    RHFontManager(const std::string &name);
    ~RHFontManager();
    void LoadConfiguration(const std::string &name);
    static void *FUN_005024f0();
    void *GetFont(const std::string &name) const;
    static std::string Get(FILE *file, char delimiter);
    void TrimString(std::string &value);
    void Emit(const std::string &name);
    RHFontInsertTree m_fonts; // +0x00; tree node value +0x0c, Fonts* +0x1c
    unsigned m_family;
    static RHFontManager mInstance;
};

#endif
