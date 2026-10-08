#ifndef SB_FILE_H
#define SB_FILE_H

#include <stdio.h>
#include <string>
#include "Decomp.h"

long SBFileUnk00643a8f(FILE *);
int SBFileUnk006439d6(FILE *, long, int);
unsigned int SBFileUnk00643e0c(void *, unsigned int, unsigned int, FILE *);
unsigned int SBFileUnk00643cd3(const void *, unsigned int, unsigned int, FILE *);
int FUN_005f54d0();
int FUN_005f5500(const void *);

// SIZE 0x01
class SBFileUnk005f5280
{
public:
    int FUN_005f5280(int);
};

// SIZE 0x04
struct SBFileTreeIterator
{
    void *m_node; // 0x00
    explicit SBFileTreeIterator(void *node) : m_node(node) {}
};

// SIZE 0x1c
struct SBFileTreeNode
{
    SBFileTreeNode *m_left; // 0x00
    SBFileTreeNode *m_parent; // 0x04
    SBFileTreeNode *m_right; // 0x08
    std::string m_key; // 0x0c
};

// SIZE 0x10
class SBFileTree
{
public:
    SBFileTreeIterator FUN_005f7360(const std::string &key);
    SBFileTreeIterator FUN_005f73f0(const std::string &key);
    SBFileTreeNode *FUN_005f7650(const std::string &key);
    SBFileTreeNode *FUN_005f7710(const std::string &key);
    SBFileTreeIterator FUN_005f6640(SBFileTreeIterator iterator);
    SBFileTreeIterator FUN_005f6cf0(SBFileTreeIterator iterator);
    undefined m_allocator; // 0x00
    SBFileTreeNode *m_head; // 0x04
    undefined4 m_compare; // 0x08
    unsigned int m_size; // 0x0c
};

#endif
