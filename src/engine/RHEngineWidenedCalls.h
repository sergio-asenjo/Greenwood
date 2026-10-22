#ifndef RHENGINEWIDENEDCALLS_H
#define RHENGINEWIDENEDCALLS_H

class SBFile;

class RHEngineWidenedCalls
{
public:
    bool FUN_004b2010(char flag, void *description);
    void FUN_004c7f60(const void *point);
    void FUN_005563f0(unsigned value);
    void FUN_004eb120(SBFile &file, void *pathFinder);
    void FUN_00558670(SBFile &file);
    bool FUN_005bd450();
    int FUN_005b7f60(unsigned long value);
    void FUN_0050efd0(void *actor);
    void FUN_004e3660(char flag);
    void FUN_005e5160(unsigned surface);
    unsigned long FUN_005e4ed0(unsigned short width, unsigned short height, unsigned long format, bool system);
};

#endif
