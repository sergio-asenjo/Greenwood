#ifndef RH_LAUNCHER_H
#define RH_LAUNCHER_H

#include <windows.h>
#include <string>

#define RH_LAUNCHER_CALL(address, result, arguments) \
    class RHUnk##address { public: result FUN_##address arguments; }

RH_LAUNCHER_CALL(005f4fc0, void, ());
RH_LAUNCHER_CALL(005f4ff0, void, ());
RH_LAUNCHER_CALL(005f9760, void, ());
RH_LAUNCHER_CALL(00578c50, void, ());
RH_LAUNCHER_CALL(0040bc00, void, (const char &allocator));
RH_LAUNCHER_CALL(0040bcc0, void, ());
RH_LAUNCHER_CALL(0040bc30, void, ());
RH_LAUNCHER_CALL(00503ba0, void, ());
RH_LAUNCHER_CALL(00503e20, void, ());
RH_LAUNCHER_CALL(005f9b80, void, (HINSTANCE instance));
RH_LAUNCHER_CALL(005f9d00, void, ());
RH_LAUNCHER_CALL(005e3c20, void, (HINSTANCE instance, HICON icon, int show, bool flag, unsigned callback, int value));
RH_LAUNCHER_CALL(005e4ca0, void, ());
RH_LAUNCHER_CALL(005fa240, void, (int value, HWND window));
RH_LAUNCHER_CALL(0055dea0, void, ());
RH_LAUNCHER_CALL(0055dbb0, char *, ());
RH_LAUNCHER_CALL(005fced0, void, ());
RH_LAUNCHER_CALL(005f0750, void, ());
RH_LAUNCHER_CALL(005e41d0, void, (int width, int height, bool flag));
RH_LAUNCHER_CALL(005e4810, void, (int width, int height, int depth));
RH_LAUNCHER_CALL(005e3f40, void, (const std::string &value));
RH_LAUNCHER_CALL(00504040, void, ());
RH_LAUNCHER_CALL(005fd5c0, bool, (const std::string &value));
RH_LAUNCHER_CALL(004505a0, void, ());
RH_LAUNCHER_CALL(00450790, void, ());
RH_LAUNCHER_CALL(004509c0, void, ());
RH_LAUNCHER_CALL(00453bd0, void, (const std::string &first, const std::string &second, bool flag));
RH_LAUNCHER_CALL(005a5f90, void, (HWND window));
RH_LAUNCHER_CALL(005a62b0, void, ());
RH_LAUNCHER_CALL(005a7800, bool, (std::string &error));
RH_LAUNCHER_CALL(005a7d40, void, ());
RH_LAUNCHER_CALL(005a7b40, void, (int value));
RH_LAUNCHER_CALL(005f9ea0, char, (bool flag));
RH_LAUNCHER_CALL(005fc3c0, void *, (int first, int second));
RH_LAUNCHER_CALL(005fc060, void *, (int first, int second, const void *value));
RH_LAUNCHER_CALL(005fc080, void, ());
RH_LAUNCHER_CALL(005fc090, void, (const void *value));
RH_LAUNCHER_CALL(005fc030, void, ());
RH_LAUNCHER_CALL(005f13c0, void, ());
RH_LAUNCHER_CALL(005f4900, void, (bool flag));
RH_LAUNCHER_CALL(005f4840, void, ());
RH_LAUNCHER_CALL(005f4850, void, ());
RH_LAUNCHER_CALL(0053adc0, void, (int first, int second, int third, int fourth));
RH_LAUNCHER_CALL(0053af80, void, ());
RH_LAUNCHER_CALL(0052e1b0, void, (void *value));
RH_LAUNCHER_CALL(0052e4b0, void, ());
RH_LAUNCHER_CALL(0052e320, void, ());
RH_LAUNCHER_CALL(00544b80, void, (bool first, bool second));
class RHMenuIntro;
typedef RHMenuIntro RHUnk0052ec40;
typedef RHMenuIntro RHUnk0052ec50;
RH_LAUNCHER_CALL(0056fb70, void *, (const void *value));
RH_LAUNCHER_CALL(0056ee20, bool, (const void *value));
RH_LAUNCHER_CALL(0063a1d0, unsigned, ());
RH_LAUNCHER_CALL(00451ff0, void *, (unsigned value));
RH_LAUNCHER_CALL(00457330, void, (void *value));
RH_LAUNCHER_CALL(0050b640, void, (void *first, void *second, void *third));
RH_LAUNCHER_CALL(005185b0, void, ());
RH_LAUNCHER_CALL(0050f710, int, ());
RH_LAUNCHER_CALL(00456e40, void, (int value));
RH_LAUNCHER_CALL(005cb6f0, char *, ());
RH_LAUNCHER_CALL(00455810, void, ());
RH_LAUNCHER_CALL(004539f0, void *, ());

#undef RH_LAUNCHER_CALL

class RHUnkLauncherVirtual0
{
public:
    virtual void FUN_00000000(unsigned value);
};

class RHUnkLauncherVirtual4
{
public:
    virtual void FUN_00000000(unsigned value);
    virtual void FUN_00000004(unsigned value);
};

void FUN_004090d0();
char **FUN_00409d10(const char *command, unsigned *counts);
bool FUN_00409d70(char **arguments, unsigned *index, unsigned count);
void FUN_0040a0d0();
unsigned FUN_005e1440();
bool FUN_005f6400(const std::string &name);
bool FUN_005f5d30(const std::string &name);
void FUN_005f1580(int value);
void FUN_005f4930(bool flag);
void FUN_005f1490(const void *first, const void *second);
void FUN_005f14c0(int first, bool second);
bool FUN_005f6490(bool (*callback)(const std::string &));
void *FUN_005fc580(void *result, const void *value, float factor);
void FUN_004013a0(const std::string &name);
void FUN_005e24f0(const char *name, void *value);
void FUN_005e27e0(const std::string &name, int value);
void FUN_005f8030(int severity, const char *file, int line, const char *message, ...);

int __stdcall FUN_0040a230(HINSTANCE instance, HINSTANCE previous, char *command, int show);
void EmitLauncher(HINSTANCE instance, HINSTANCE previous, char *command, int show);

#endif
