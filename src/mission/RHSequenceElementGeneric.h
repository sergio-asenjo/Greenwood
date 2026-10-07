#ifndef RHSEQUENCEELEMENTGENERIC_H
#define RHSEQUENCEELEMENTGENERIC_H

#include "RHSequenceElementSerialization.h"

struct RHGenericValue
{
    unsigned int m_0;
    unsigned int m_4;
    unsigned int m_8;
};

struct RHGenericNode
{
    RHGenericNode *left;
    RHGenericNode *parent;
    RHGenericNode *right;
    int key;
    RHGenericValue value;
};

struct RHGenericIterator
{
    RHGenericNode *node;
    RHGenericIterator(RHGenericNode *value) : node(value) {}
    RHGenericIterator(const RHGenericIterator &other) : node(other.node) {}
    RHGenericIterator &FUN_00587ed0();
};

struct RHGenericPair
{
    int key;
    RHGenericValue value;
};

struct RHGenericInsertResult
{
    RHGenericIterator iterator;
    bool inserted;
    RHGenericInsertResult(RHGenericIterator value, bool success) : iterator(value), inserted(success) {}
};

class RHGenericMap
{
public:
    RHGenericInsertResult FUN_005873a0(const RHGenericPair &value);
    RHGenericIterator FUN_005874d0(RHGenericIterator first, RHGenericIterator last);

    char m_00[4];
    RHGenericNode *head;
    bool multi;
    unsigned int count;
};

class RHSequenceElementGeneric : public RHSequenceElement
{
public:
    virtual bool Serialize(SBFile &file, bool pointers);
    void Emit(SBFile &file, bool pointers);

    RHGenericMap m_64;
};

#endif
