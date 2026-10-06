#ifndef RHELEMENTACTORNPC_H
#define RHELEMENTACTORNPC_H

class SBFile;

class RHDetectable
{
public:
    RHDetectable()
    {
        m_04 = 7;
        m_0a = 0;
        m_08 = 0;
        m_09 = 0;
        m_0c = 0;
        m_10 = 0;
    }
    ~RHDetectable() {}
    bool Serialize(SBFile &file);
    void *m_00;
    int m_04;
    char m_08;
    char m_09;
    char m_0a;
    char m_0b;
    char m_0c;
    char m_0d[3];
    int m_10;
};

class RHElementActorNPC
{
public:
    virtual bool Serialize(SBFile &file);
    void Emit(SBFile &file);
    enum
    {
        OffsetAI = 0x49c,
        OffsetRaw4a0 = 0x4a0,
        OffsetWord4c8 = 0x4c8,
        OffsetWord4ca = 0x4ca,
        OffsetWord4d0 = 0x4d0,
        OffsetPoint4d4 = 0x4d4,
        OffsetRaw4dc = 0x4dc,
        OffsetPointer4e4 = 0x4e4,
        OffsetWord4ec = 0x4ec,
        OffsetByte4ee = 0x4ee,
        OffsetInt4f0 = 0x4f0,
        OffsetByte4f4 = 0x4f4,
        OffsetWord4f6 = 0x4f6,
        OffsetWord4f8 = 0x4f8,
        OffsetWord4fa = 0x4fa,
        OffsetInt4fc = 0x4fc,
        OffsetPointer500 = 0x500,
        OffsetDetectableLists = 0x504,
        DetectableListStride = 0x34,
        OffsetDetectableWords = 0x63c,
        OffsetWord648 = 0x648,
        OffsetInt64c = 0x64c,
        OffsetByte652 = 0x652,
        OffsetRaw654 = 0x654,
        OffsetPointer6bc = 0x6bc,
        OffsetByte6e4 = 0x6e4,
        OffsetByte6e5 = 0x6e5,
        ObjectSize = 0x704
    };
    char m_04[0x700];
};

#endif
