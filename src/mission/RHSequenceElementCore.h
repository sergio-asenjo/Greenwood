#ifndef RHSEQUENCEELEMENTCORE_H
#define RHSEQUENCEELEMENTCORE_H

class SBFile;

class RHSequenceElement
{
public:
    RHSequenceElement();
    ~RHSequenceElement();
    virtual void Dummy1();
    virtual void Dummy2();
    virtual bool Serialize(SBFile &file, bool pointers);
    bool FUN_00584ef0(SBFile &file, bool pointers);
    char m_04[0x60];
};

#endif
