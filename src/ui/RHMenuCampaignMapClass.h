#ifndef RHMENUCAMPAIGNMAPCLASS_H
#define RHMENUCAMPAIGNMAPCLASS_H

#include <vector>

class RHMapTitleText;
class RHMapBox;

struct RHMapByte
{
    signed char value;
};

class RHMenuCampaignMap
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
    virtual void V2c();
    virtual void V30(void *);
    virtual void V34();
    virtual void V38(void *);
    virtual void V3c(void *);
    virtual void V40();
    virtual void V44();
    virtual void V48();
    virtual void V4c();
    virtual void V50();
    virtual void V54();
    bool Create();
    void DisplayPseudoMissionDebriefing();
    bool FUN_00544b40(const RHMapTitleText &, const RHMapBox &, unsigned);
    void FUN_00527a70(RHMapByte);
    void FUN_00527ae0(RHMapByte);
    void FUN_00527c00(const std::vector<void *> &);
    void FUN_005284b0();
    bool FUN_00528520(unsigned, unsigned, unsigned);
    bool FUN_00528550(unsigned, unsigned, unsigned);
    void FUN_00528810();
    void FUN_00528a60();
    void Emit();
    char m_04[0x26fc];
    unsigned m_2700;
};

#endif
