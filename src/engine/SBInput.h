#ifndef SB_INPUT_H
#define SB_INPUT_H

#include <string>
#include <list>

struct SBInputUnkDevice;
struct SBInputJoystickState;
struct SBInputJoystickNameNode;
struct SBInputInterface;
struct SBInputDataFormat;
class RHUnk0051a4e0;

struct SBInputDeviceGuid
{
    unsigned long m_data[4];
};

struct SBInputJoystickNames
{
    std::list<std::string> values;
    std::list<std::string>::iterator cursor;
    bool dirty;
    int cursorIndex;
    bool searching;
    int foundIndex;
    std::string needle;
    ~SBInputJoystickNames() { values.clear(); }
    int Find(const std::string &);
};

struct SBInputPropertyHeader
{
    unsigned long size;
    unsigned long headerSize;
    unsigned long object;
    unsigned long how;
};

struct SBInputPropertyRange
{
    SBInputPropertyHeader header;
    long minimum;
    long maximum;
};

struct SBInputPropertyValue
{
    SBInputPropertyHeader header;
    unsigned long value;
};

struct SBInputDeviceData
{
    unsigned long offset;
    unsigned long data;
    unsigned long timestamp;
    unsigned long sequence;
};

struct SBInputUnkDeviceTable
{
    void *m_00[2];
    unsigned long (__stdcall *m_08)(SBInputUnkDevice *);
    void *m_0c[3];
    long (__stdcall *m_18)(SBInputUnkDevice *, const void *, const SBInputPropertyHeader *);
    long (__stdcall *m_1c)(SBInputUnkDevice *);
    long (__stdcall *m_20)(SBInputUnkDevice *);
    long (__stdcall *m_24)(SBInputUnkDevice *, unsigned long, void *);
    long (__stdcall *m_28)(SBInputUnkDevice *, unsigned long, SBInputDeviceData *, unsigned long *, unsigned long);
    long (__stdcall *m_2c)(SBInputUnkDevice *, const SBInputDataFormat *);
    long (__stdcall *m_30)(SBInputUnkDevice *, void *);
    long (__stdcall *m_34)(SBInputUnkDevice *, void *, unsigned long);
    void *m_38[11];
    long (__stdcall *m_64)(SBInputUnkDevice *);
};

struct SBInputUnkDevice
{
    SBInputUnkDeviceTable *m_table;
};

struct SBInputInterfaceTable
{
    void *m_00[2];
    unsigned long (__stdcall *m_08)(SBInputInterface *);
    long (__stdcall *m_0c)(SBInputInterface *, const SBInputDeviceGuid *, SBInputUnkDevice **, void *);
    void *m_10[5];
    long (__stdcall *m_24)(SBInputInterface *, const SBInputDeviceGuid *, const SBInputDeviceGuid *, SBInputUnkDevice **, void *);
};

struct SBInputInterface
{
    SBInputInterfaceTable *m_table;
};

class SBInputUnk005fb730
{
public:
    void *m_00;
    SBInputInterface *m_04;
    SBInputUnkDevice *m_08;
    SBInputUnkDevice *m_0c;
    int m_10;
    SBInputJoystickNames m_14;
    SBInputDeviceGuid m_44[16];
    SBInputUnkDevice *m_144[16];
    char m_184[0x120];
    unsigned char m_2a4;
    unsigned char m_2a5;
    unsigned char m_2a6;
    unsigned char m_2a7;
    unsigned char m_2a8;
    unsigned char m_2a9;
    unsigned char m_2aa;
    char m_2ab;
    std::string m_2ac;

    ~SBInputUnk005fb730();
    bool FUN_005f9ea0(unsigned char);
    bool FUN_005fa240(unsigned short, void *);
    void FUN_005fae70(void *);
    RHUnk0051a4e0 *FUN_005fafc0();
    bool FUN_005fb210(unsigned char, unsigned long, long, long, unsigned long);
    unsigned char FUN_005fb410(std::string name, unsigned short, void *window);
    bool FUN_005fb730(unsigned char);
    bool FUN_005fb770(unsigned char, void *, bool *);
    bool FUN_005fb980(void *);
    bool FUN_005fba70(void *);
    bool FUN_005fbb70(SBInputDeviceData *);
    bool FUN_005fbdb0(SBInputDeviceData *);
    bool FUN_005fbfc0();
    static SBInputUnk005fb730 *mpInput;
};

int __stdcall FUN_005fae50(void *, SBInputUnk005fb730 *);
std::string FUN_005f81d0(long);

#endif
