#ifndef RHMAPRESOURCES_H
#define RHMAPRESOURCES_H

#include <string>

class RHMapWideText;

class RHMapResources
{
public:
    unsigned int FUN_00600620(unsigned long);
    bool FUN_006009e0(unsigned, unsigned, RHMapWideText &);
    bool FUN_00600bb0(unsigned long, unsigned int, std::string &);
    bool FUN_00600fc0(unsigned);
};

#endif
