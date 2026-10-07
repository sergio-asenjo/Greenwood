#ifndef SB_UI_RENDERER_INPUT_FIELD_H
#define SB_UI_RENDERER_INPUT_FIELD_H

class SBUIInputFieldUnkObject
{
public:
    virtual void v0() = 0;
    virtual void v1() = 0;
    virtual void v2(unsigned int) = 0;
};

struct SBUIInputFieldUnkResource
{
    char m_00[0x14];
    SBUIInputFieldUnkObject *m_14;
    void *m_18;
};

class SBUIInputFieldUnk00621440
{
public:
    char m_00[0x64];
    SBUIInputFieldUnkObject *m_64;
    void *m_68;
    SBUIInputFieldUnkResource *m_6c;

    void FUN_00621430(unsigned int);
    void FUN_00621440(SBUIInputFieldUnkResource *);
};

#endif
