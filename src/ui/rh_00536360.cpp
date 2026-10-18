// Anonymous cluster at 0x00536360.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Member offsets are exact from Game.exe: the receiver holds a polymorphic
// sub-object at +0x2ac and forwards its first argument to vtable slot +0x2c.

class RHUnk00536360Sub
{
public:
    virtual void V00();
    virtual void V04();
    virtual void V08();
    virtual void V0c();
    virtual void V10();
    virtual void V14();
    virtual void V18();
    virtual void V1c();
    virtual void V20();
    virtual void V24();
    virtual void V28();
    virtual void V2c(int arg);
};

class RHUnk00536360
{
public:
    void FUN_00536360(int arg);

private:
    char m_00[0x2ac];
    RHUnk00536360Sub m_2ac;
};

// FUNCTION: GAME 0x00536360
void RHUnk00536360::FUN_00536360(int arg)
{
    m_2ac.V2c(arg);
}
