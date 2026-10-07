#ifndef VMCORE_H
#define VMCORE_H

class VMUnk00634bb0
{
public:
    char m_pad0[4];
    unsigned char *m_04;
    int m_08;
    int m_0c;
    void FUN_00634bb0();
};

class VMUnk0063a250
{
public:
    char m_pad0[0x10];
    bool FUN_0063a250(int, int);
    int FUN_0063a320();
    bool FUN_0063a370(void *, int);
    int *FUN_0063a3b0(int);
};

class VMUnk0063a140;

class VMUnk0063a400
{
public:
    VMUnk0063a140 *m_00;
    int m_04;
    int m_08;
    void *m_0c;
    int m_10;
    void *m_14;
    int m_18;
    void FUN_0063a400();
};

class VMUnk0063a140
{
public:
    char m_pad0[8];
    int FUN_0063a140(int, bool);
    int *FUN_0063a1e0(int);
    void FUN_0063a1f0(int, unsigned char *, int);
};

class VMUnk0063a490Result
{
public:
    char m_pad0[0x24];
    int m_24;
};

class VMUnk0063a490
{
public:
    VMUnk0063a490Result *FUN_0063a490(void *);
    void *FUN_0063a510(VMUnk0063a490Result *, void *);
};

class VMCore
{
public:
    VMUnk0063a490 *m_04;
    VMUnk0063a140 *m_08;
    VMUnk0063a250 m_0c;
    VMUnk0063a140 m_1c;
    int m_24;
    int *m_28;
    int m_2c;
    char m_pad30[0x0c];
    char m_3c;
    char m_pad3d[3];
    VMUnk0063a490Result *m_40;
    int *m_44;

    void Empty();
    void FUN_00634c20();
    void FUN_00634c30();
    void FUN_00634d30();
    void EndFunction();
    void FUN_00634db0();
    void FUN_00634dd0();
    void FUN_00635090();
    int *GetSymbolValuePtr(unsigned short &);
    void FUN_00635330();
    void FUN_006353f0();
    void FUN_00635210();
    void FUN_00635320();
    virtual bool FUN_006390a0();
    virtual bool FUN_006390a0_1();
    ~VMCore();
    bool FUN_00639230();
    bool FUN_00639280(void *);
    bool FUN_006392c0();
    bool FUN_006392e0(void *, int);
    bool FUN_00639300(void *);
    int FUN_00639340(void *);
    void FUN_00639360(int &);
    void FUN_00639370();
};

#endif
