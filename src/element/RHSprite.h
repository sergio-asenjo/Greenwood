#ifndef RHSPRITE_H
#define RHSPRITE_H

#include "RHSprite_calls.h"
#include "RHSpriteCore.h"

class RHEngine
{
public:
    bool SerializeElementPointer(SBFile &, class RHElement *&);
    bool FUN_004c4490(SBFile &file, void *&value);
};
extern RHEngine *g_pEngine;

#endif
