#ifndef RHSTIMULUS_H
#define RHSTIMULUS_H

class SBFile;
struct RHMalignityPosition;

class RHStimulus
{
public:
    bool Serialize(SBFile &file);
    RHStimulus() : m_type(0), m_24(0), m_28(0) {}
    ~RHStimulus() {}
    void Unk004188d0(int value);
    void FUN_0041a930(int event, const RHMalignityPosition &position);
    char m_00[0x1c];
    unsigned m_type;
    unsigned m_20;
    void *m_24;
    char m_28;
};

#endif
