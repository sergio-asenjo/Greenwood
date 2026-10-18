#ifndef RHGAMEACTIONCALLS_H
#define RHGAMEACTIONCALLS_H

class SBGeoPoint2D;
class SBGeoVector2D;

class RHGameActionCalls
{
public:
    void FUN_005110e0(unsigned);
    void FUN_00510fc0(unsigned short);
    void FUN_00511210(unsigned);
    void FUN_005140b0();
    void FUN_0050eff0();
    void FUN_005f4900(char);
    void FUN_005e5260();
    void FUN_005104c0();
    bool FUN_005104d0(SBGeoPoint2D point);
    bool FUN_00510550(SBGeoVector2D point);
    void FUN_00619cc0();
    bool FUN_004d2300(void *, unsigned);
    bool FUN_004da2f0();
    void FUN_005a7b40(int);
};

#endif
