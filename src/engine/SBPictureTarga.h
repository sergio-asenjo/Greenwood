// SBPictureTarga — declarations for SBPictureTarga.cpp (decompiled TU).
//
// BINDING: the code run 0x006150d0..0x006157f7 is bracketed by the
// SBUIRendererInputField tail (deleting dtor 0x00614e40) and the per-TU
// <iostream> glue at 0x00615800. Its constructor 0x006150d0 calls the SBPicture
// base constructor 0x00611b90 and stores vptr 0x0067a8fc, whose slots 2..7 are
// 0x00615120, 0x00615220, 0x006152d0, SBPicture::LoadFromSurface 0x00611c80,
// 0x006154b0, 0x00615560 — the Mac oracle's SBPictureTarga GetInfoFromFile,
// LoadFromFile, LoadFromStream, (inherited), SaveToFile, SaveToStream order.
// SerializeHeader 0x00615750 takes two references (SBFile&, SBPictureTGAHeader&),
// unlike SBPictureBitmap's three, and GetInfoFromFile reads the width/height/
// depth at the aligned TGA header offsets 0x0e/0x10/0x12.

#ifndef SBPICTURETARGA_H
#define SBPICTURETARGA_H

#include "SB.h"
#include "SBPicture.h"
#include <string>

#include "RHUnk005f4fc0.h"

// SIZE 0x14
struct SBPictureTGAHeader
{
    unsigned char m_idLength; // 0x00
    unsigned char m_colorMapType; // 0x01
    unsigned char m_imageType; // 0x02
    unsigned short m_colorMapFirst; // 0x04
    unsigned short m_colorMapLength; // 0x06
    unsigned char m_colorMapDepth; // 0x08
    unsigned short m_xOrigin; // 0x0a
    unsigned short m_yOrigin; // 0x0c
    unsigned short m_width; // 0x0e
    unsigned short m_height; // 0x10
    unsigned char m_depth; // 0x12
    unsigned char m_descriptor; // 0x13

    void SetColorMapped()
    {
        m_colorMapDepth = 0;
        m_colorMapLength = 0;
        m_colorMapType = 0;
        m_colorMapFirst = 0;
        m_imageType = 2;
    }
};

// SIZE 0xc
struct SBPictureInfo
{
    unsigned short m_width; // 0x00
    unsigned short m_height; // 0x02
    unsigned short m_depth; // 0x04
    unsigned int m_size; // 0x08
};

class SBPictureTargaVirtuals
{
public:
    virtual void V00();
    virtual void V04();
    virtual void V08();
    virtual void V0c();
    virtual bool LoadFromStream(SBFile &file);
    virtual void V14();
    virtual void V18();
    virtual bool SaveToStream(SBFile &file);
};

#include "SBPictureTargaCore.h"

#endif
