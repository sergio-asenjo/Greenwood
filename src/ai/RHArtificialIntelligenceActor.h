#ifndef RH_ARTIFICIAL_INTELLIGENCE_ACTOR_H
#define RH_ARTIFICIAL_INTELLIGENCE_ACTOR_H

class RHSprite;

class RHArtificialIntelligenceActor
{
public:
    virtual void V00() = 0;
    virtual void V04() = 0;
    virtual void V08() = 0;
    virtual void V0c() = 0;
    virtual void V10() = 0;
    virtual void V14() = 0;
    virtual void V18() = 0;
    virtual void V1c() = 0;
    virtual void V20() = 0;
    virtual void V24() = 0;
    virtual void V28() = 0;
    virtual void V2c() = 0;
    virtual void V30() = 0;
    virtual void V34() = 0;
    virtual void V38() = 0;
    virtual void V3c() = 0;
    virtual void V40() = 0;
    virtual void V44(int value) = 0;
    virtual bool V48() = 0;
    virtual void V4c() = 0;
    virtual void V50() = 0;
    virtual void V54() = 0;
    virtual void V58() = 0;
    virtual void V5c() = 0;
    virtual void V60() = 0;
    virtual void V64() = 0;
    virtual void V68() = 0;
    virtual void V6c() = 0;
    virtual void V70() = 0;
    virtual void V74() = 0;
    virtual void V78() = 0;
    virtual void V7c() = 0;
    virtual void V80() = 0;
    virtual void V84() = 0;
    virtual void V88() = 0;
    virtual void V8c() = 0;
    virtual void V90() = 0;
    virtual void V94() = 0;
    virtual void V98() = 0;
    virtual void V9c() = 0;
    virtual void Va0() = 0;
    virtual void Va4() = 0;
    virtual void Va8() = 0;
    virtual void Vac() = 0;
    virtual void Vb0() = 0;
    virtual void Vb4() = 0;
    virtual void Vb8() = 0;
    virtual void Vbc() = 0;
    virtual void Vc0() = 0;
    virtual void Vc4(int value) = 0;
    virtual void Vc8() = 0;
    virtual short Vcc() = 0;
    virtual unsigned short Vd0() = 0;
    virtual void Vd4() = 0;
    virtual void Vd8() = 0;
    virtual void Vdc(int value, int first, int second) = 0;
    virtual void Ve0() = 0;
    virtual unsigned short Ve4(unsigned action) = 0;
    virtual void Ve8() = 0;
    virtual void Vec() = 0;
    virtual void Vf0() = 0;
    virtual void Vf4() = 0;
    virtual bool Vf8() = 0;
    virtual void Vfc() = 0;
    virtual void V100() = 0;
    virtual void V104() = 0;
    virtual void V108() = 0;
    virtual void V10c() = 0;
    virtual void V110() = 0;
    virtual void V114() = 0;
    virtual void V118() = 0;
    virtual void V11c() = 0;
    virtual void V120() = 0;
    virtual void V124() = 0;
    virtual void V128() = 0;
    virtual void V12c() = 0;
    virtual int V130() = 0;
    virtual void V134() = 0;
    virtual void V138() = 0;
    virtual void V13c() = 0;
    virtual void V140() = 0;
    virtual void V144() = 0;
    virtual void V148() = 0;
    virtual void V14c() = 0;
    virtual void V150() = 0;
    virtual void V154() = 0;
    virtual void V158() = 0;
    virtual void V15c() = 0;
    virtual void V160() = 0;
    virtual void V164() = 0;
    virtual void V168() = 0;
    virtual void V16c() = 0;
    virtual void V170() = 0;
    virtual void V174() = 0;
    virtual void *V178() = 0;

    union
    {
        unsigned m_flags;
        struct
        {
            unsigned m_kind : 5;
            unsigned m_otherFlags : 27;
        };
    };
    char m_08[0x48];
    RHSprite *m_data;
};

#endif
