#ifndef VMCORE_H
#define VMCORE_H

#include <string>

class SBFile;

struct VMUnk00634ab0Text
{
    std::allocator<char> m_allocator;
    char *m_pointer;
    unsigned int m_length;
    unsigned int m_capacity;
    VMUnk00634ab0Text() : m_allocator(std::allocator<char>()), m_pointer(0), m_length(0), m_capacity(0) {}
    ~VMUnk00634ab0Text() { ((std::string *)this)->~basic_string(); }
};

struct VMUnk00634ab0Record
{
    VMUnk00634ab0Text m_name;
    void (__cdecl *m_serializer)(SBFile &, void *&);
    VMUnk00634ab0Record() {}
    VMUnk00634ab0Record(const VMUnk00634ab0Record &);
};

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

struct VMQuad;

class VMUnk0063a490Result
{
public:
    char m_pad0[0x24];
    int m_24;
    char m_pad28[0x28];
    VMQuad *m_50;
};

class VMUnk0063a490
{
public:
    VMUnk0063a490Result *FUN_0063a490(void *);
    void *FUN_0063a510(VMUnk0063a490Result *, void *);
};

// VTABLE: GAME 0x0067bbc4
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

    void RegisterSerializerForType(const std::string &, void (__cdecl *)(SBFile &, void *&));
    void Empty();
    void FUN_00634c20();
    void FUN_00634c30();
    void FUN_00634d30();
    void EndFunction();
    void FUN_00634db0();
    void FUN_00634dd0();
    void FUN_00634de0();
    void FUN_00634eb0();
    void FUN_00634fa0();
    void FUN_00635090();
    void FUN_00635150();
    int *GetSymbolValuePtr(unsigned short &);
    void FUN_00635330();
    void FUN_006353f0();
    void FUN_00635210();
    void FUN_00635240();
    void FUN_00635320();
    void FUN_006354b0();
    void FUN_00635630();
    void FUN_006357b0();
    void FUN_006358a0();
    void FUN_00635990();
    void FUN_00635b20();
    void FUN_00635cb0();
    void FUN_00635e50();
    void FUN_00635fd0();
    void FUN_00636210();
    void FUN_00636450();
    void FUN_00636680();
    void FUN_006368c0();
    void FUN_00636b00();
    void FUN_00636d40();
    void FUN_00636f80();
    void FUN_006371b0();
    void FUN_006373e0();
    void FUN_00637610();
    void FUN_00637840();
    void FUN_00637a40();
    void FUN_00637c40();
    void FUN_00637e40();
    void FUN_00638040();
    void FUN_00638240();
    void FUN_00638440();
    void FUN_00638650();
    void FUN_00638860();
    void FUN_00638a70();
    void FUN_00638c80();
    void FUN_00638e90();
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
