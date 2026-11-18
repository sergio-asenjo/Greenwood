#ifndef RHMAPRESOURCES_H
#define RHMAPRESOURCES_H

#include <string>

class RHMapWideText;
class RHUnk005fc3b0;

class RHMapResources
{
public:
    bool FUN_006006f0(long, RHUnk005fc3b0 &);
    unsigned int FUN_00600620(unsigned long);
    bool FUN_006009e0(unsigned, unsigned, std::wstring &);
    bool FUN_00600bb0(unsigned long, unsigned int, std::string &);
    bool FUN_00600fc0(unsigned);
};

#endif
