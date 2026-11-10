#ifndef RHELEMENTMOBILEBASE_VIEW
#define RHELEMENTMOBILEBASE_VIEW

#include "Decomp.h"
#include "SBGeoBoundingBox2DCore.h"
#include "SBFile.h"

class RHMobileElementBase
{
public:
    RHMobileElementBase(int type, int value);
    virtual ~RHMobileElementBase();
    undefined m_04[0xb0];
};

class RHMobileBase004a8130 : public RHMobileElementBase
{
public:
    RHMobileBase004a8130(int type);
    virtual ~RHMobileBase004a8130();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14(SBFile &file);
    virtual void v15();
    virtual bool v16(SBFile &file);
    virtual void v17(bool value);
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    SBGeoBoundingBox2D m_b4;
    char m_c8;
    int m_cc;
    char m_d0;
    undefined m_d4[0x24];
    undefined m_f8[4];
};

#endif
