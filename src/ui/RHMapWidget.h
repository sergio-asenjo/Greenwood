#ifndef RHMAPWIDGET_H
#define RHMAPWIDGET_H

#include <string>

class SBGeoBoundingBox2D;
class RHMapTitleText;
#include "RHMapBox.h"

class RHMapWidget
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
    virtual const SBGeoBoundingBox2D &V24();
    virtual void V28();
    virtual void V2c(const RHMapTitleText &);
    virtual bool V30(const std::wstring &, const RHMapBox &, unsigned, unsigned);
    virtual void V34();
    virtual void V38();
    virtual void V3c();
    virtual void V40();
    virtual void V44();
    virtual void V48();
    virtual void V4c();
    virtual void V50();
    virtual void V54(bool);
    char m_04[0xc8];
};

#endif
