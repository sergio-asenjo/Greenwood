// Anonymous cluster at 0x004b23axx.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// The virtual slot is exact from Game.exe (vtable +0xc).

class RHUnk004b2300
{
public:
    virtual void V0();
    virtual void V1();
    virtual void V2();
    virtual void V3(int a, int b);
};

// FUNCTION: GAME 0x004b23a0
bool __stdcall FUN_004b23a0(RHUnk004b2300 *object)
{
    object->V3(5, 1);
    return false;
}

void EmitFUN_004b23a0(RHUnk004b2300 *object)
{
    FUN_004b23a0(object);
}
