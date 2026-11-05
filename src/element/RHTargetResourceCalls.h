#ifndef RHTARGETRESOURCECALLS_H
#define RHTARGETRESOURCECALLS_H

#include "RHBonusInfo.h"
#include <string>

class RHUnkTargetSprite : public RHBonusInfo
{
public:
    bool FUN_005bd050(int kind, const std::string &name, const std::string &profile, int flag);
    bool FUN_005b76e0(unsigned index, unsigned short row);
};

class RHUnkFXDraw
{
public:
    unsigned long Unk005e4ed0(unsigned short width, unsigned short height, unsigned long flags, bool retain);
};

#endif
