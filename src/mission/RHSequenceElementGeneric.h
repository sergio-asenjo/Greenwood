#ifndef RHSEQUENCEELEMENTGENERIC_H
#define RHSEQUENCEELEMENTGENERIC_H

#include "RHSequenceElementSerialization.h"
#include "RHGenericMap.h"

class RHUnk00613e90;

class RHSequenceElementGeneric : public RHSequenceElement
{
public:
    RHSequenceElementGeneric *FUN_00586840();
    virtual bool Serialize(SBFile &file, bool pointers);
    void Emit(SBFile &file, bool pointers);
    void FUN_00586e50(int key, unsigned char value);
    void FUN_00586f10(int key, unsigned long value);
    void FUN_00587060(int key, const RHGenericValue &value);
    float FUN_00587110(int key);
    RHUnk00613e90 FUN_00587290(int key);
    void EmitProperties(int key, const RHGenericValue &value);

    RHGenericMap m_64;
};

#endif
