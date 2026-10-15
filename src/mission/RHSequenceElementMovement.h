#ifndef RHSEQUENCEELEMENTMOVEMENT_H
#define RHSEQUENCEELEMENTMOVEMENT_H

#include "RHSequenceElementSerialization.h"

class RHSequence
{
public:
    bool Serialize(SBFile &file, bool pointers);
};

class RHUnk00582220
{
public:
    RHUnk00582220();
    ~RHUnk00582220();
    char data[0x3c];
};

class RHSequenceManager
{
public:
    bool PreSerializePointer(SBFile &file, RHSequenceElement **value, bool launch);
};

class RHUnk6c1040;
extern RHUnk6c1040 *g_unk0x6c1040;

class RHSequenceElementMovement : public RHSequenceElement
{
public:
    virtual bool Serialize(SBFile &file, bool pointers);
    void Emit(SBFile &file, bool pointers);
    void FUN_00588d40(int value);
    bool FUN_005897e0();

    RHSequenceElement *m_64;
    RHSequence *m_68;
    SBGeoPoint2D m_6c;
    unsigned short m_74;
    char m_76[2];
    void *m_78;
    void *m_7c;
    void *m_80;
    void *m_84;
    int m_88;
    int m_8c;
    unsigned short m_90;
    char m_92[2];
    int m_94;
    int m_98;
};

#endif
