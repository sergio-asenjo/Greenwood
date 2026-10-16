#ifndef RHCONSOLE_H
#define RHCONSOLE_H

#include <string>

class RHUnk005ef320;
class RHElementActorPC;

struct RHConsoleEngine
{
    bool FUN_004db7a0();
    unsigned char m_00[0xdc];
    RHUnk005ef320 *m_draw;
    unsigned char m_e0[0x4973];
    char m_4a53;
    char m_4a54;
    char m_4a55;
    unsigned char m_4a56[0xd6];
    char m_4b2c;
    char m_4b2d;
    char m_4b2e;
    char m_4b2f;
    unsigned short m_4b30;
    char m_4b32;
    char m_4b33;
    char m_4b34;
    char m_4b35;
    char m_4b36;
    char m_4b37;
    char m_4b38;
    char m_4b39;
    char m_4b3a;
    char m_4b3b;
    char m_4b3c;
    char m_4b3d;
    char m_4b3e;
    unsigned char m_4b3f[0x9d];
    char m_4bdc;
    unsigned char m_4bdd[7];
    char m_4be4;
};

class RHConsole
{
public:
    static void FUN_0045bc50(char *, const char *);
    char **FUN_0045c360(signed char *, unsigned &);
    void FUN_0045ccc0(const std::string &);
    void FUN_0045cc20(unsigned, char **);
    void FUN_0045cc60(unsigned, char **);
    void FUN_0045d580(unsigned, char **);
    void FUN_0045d5c0(unsigned, char **);
    void FUN_0045d5f0(unsigned, char **);
    void FUN_0045d650(unsigned, char **);
    void FUN_0045d780(unsigned, char **);
    void FUN_0045d7d0(unsigned, char **);
    void FUN_0045d840(unsigned, char **);
    void FUN_0045d8b0(unsigned, char **);
    void FUN_0045d920(unsigned, char **);
    void FUN_0045da50(unsigned, char **);
    void FUN_0045db20(unsigned, char **);
    void FUN_0045db80(unsigned, char **);
    void FUN_0045dc20(unsigned, char **);
    void FUN_0045dc80(unsigned, char **);
    void FUN_0045dce0(unsigned, char **);
    void FUN_0045dd40(unsigned, char **);
    void FUN_0045dd90(unsigned, char **);
    void FUN_0045de60(unsigned, char **);
    void FUN_0045e240(unsigned, char **);
    void FUN_0045e290(unsigned, char **);
    void FUN_0045e2e0(unsigned, char **);
    void FUN_0045e400(unsigned, char **);
    void FUN_0045e450(unsigned, char **);
    void FUN_0045e4b0(unsigned, char **);
    void FUN_0045e530(unsigned, char **);
    void FUN_0045e620(unsigned, char **);
    void FUN_0045e670(unsigned, char **);
    void FUN_0045e6a0(unsigned, char **);
    void FUN_0045e6f0(unsigned, char **);
    void FUN_0045e7e0(unsigned, char **);
    void FUN_0045e8d0(unsigned, char **);
    void FUN_0045eaa0(unsigned, char **);
    void FUN_0045eb50(unsigned, char **);
    void FUN_0045ec90(unsigned, char **);
    void FUN_0045ee70(unsigned, char **);
    void FUN_0045f050(unsigned, char **);
    void FUN_0045f0c0(unsigned, char **);
    void FUN_0045f2a0(unsigned, char **);
    void FUN_0045f310(unsigned, char **);
    void FUN_0045f4e0(unsigned, char **);
    void FUN_0045f500(unsigned, char **);
    void FUN_0045f590(unsigned, char **);
    RHElementActorPC *FUN_0045f670(char *);
    void FUN_004600b0(unsigned, char **);
    void FUN_004600e0(unsigned, char **);
    void FUN_00460140(unsigned, char **);
    void FUN_00460350(unsigned, char **);
    void FUN_00460370(unsigned, char **);
    void FUN_004603b0(unsigned, char **);
    void FUN_004603e0(unsigned, char **);
    void FUN_00460410(unsigned, char **);
    void *FUN_00460600();
    RHConsoleEngine *m_engine;
    unsigned char m_04[0x5b2];
    char m_5b6;
    unsigned char m_5b7;
    unsigned char m_5b8[0x20];
    unsigned char m_5d8[0xb0];
};

void FUN_005ede40(RHUnk005ef320 *, const char *, ...);
void FUN_005edae0(RHUnk005ef320 *, const char *);
void FUN_005edae0(RHUnk005ef320 *, const char *, int);
unsigned FUN_0057aa20();
extern RHUnk005ef320 *g_unk0x6c11d0;
extern char g_unk0x006c07de;

class RHConsoleCampaignCalls
{
public:
    void *FUN_004524b0(unsigned short);
};

class RHConsoleSequenceElement
{
public:
    RHConsoleSequenceElement(unsigned short, int, void *, void *, unsigned short, unsigned short);
    ~RHConsoleSequenceElement();
    char m_data[0x7c];
};

#include "RHConsoleBlockAllocator.h"

#endif
