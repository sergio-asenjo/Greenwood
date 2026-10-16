#ifndef RH_PATH_REQUEST_H
#define RH_PATH_REQUEST_H

#include "Decomp.h"

class RHElement;

// SIZE 0x3c
struct RHpathRequest
{
    ~RHpathRequest();
    unsigned short m_0; // +0x00
    unsigned short m_2; // +0x02
    unsigned short m_4; // +0x04
    undefined m_pad6[2]; // 0x06
    SBGeoPoint2D m_8; // +0x08
    SBGeoPoint2D m_10; // +0x10
    void *m_18; // +0x18
    void *m_1c; // +0x1c
    RHElement *m_20; // +0x20
    unsigned short m_24; // +0x24
    undefined m_pad26[2]; // 0x26
    int m_28; // +0x28
    char m_2c; // +0x2c
    unsigned char m_2d; // +0x2d
    undefined m_pad2e[2]; // 0x2e
    int m_30; // +0x30
    char m_34; // +0x34
    undefined m_pad35[7]; // 0x35
};

#endif
