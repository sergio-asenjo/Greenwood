#ifndef RHELEMENTAREASHAPE_H
#define RHELEMENTAREASHAPE_H

#include "RHUnkSectorPoints.h"

class RHElementAreaShape
{
public:
    bool FUN_0060c660(const SBGeoPoint2D &point) const;
    unsigned FUN_0060ce80() const;
    const SBGeoPoint2D &FUN_0060cef0(unsigned index) const
    {
        return ((RHUnkSectorPoints *)this)->Unk0060cef0(index);
    }
    undefined m_00[0x24];
    undefined2 m_24;
};

#endif
