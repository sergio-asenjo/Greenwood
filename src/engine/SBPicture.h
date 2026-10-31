#ifndef SBPICTURE_H
#define SBPICTURE_H

#include <string>

class SBFile;
struct SBPictureInfo
{
    unsigned short m_width;
    unsigned short m_height;
    unsigned short m_depth;
    unsigned int m_size;
};
class RHUnkFXDraw;
class SBPictureUnkDrawManager;
class SBGeoVector2D;
class SBGeoPoint2D;

// VTABLE: GAME 0x0067a8bc
class SBPicture
{
public:
    SBPicture();
    ~SBPicture();
    virtual void *FUN_00611be0(unsigned flags);
    virtual void FUN_00611c50();
    virtual const SBPictureInfo &GetInfoFromFile(const std::string &name);
    virtual bool LoadFromFile(const std::string &name);
    virtual bool LoadFromStream(SBFile &file);
    virtual bool FUN_00611c80(SBPictureUnkDrawManager *, unsigned long);
    virtual bool SaveToFile(const std::string &name);
    virtual bool SaveToStream(SBFile &file);
    virtual bool Unk00613530(RHUnkFXDraw *, unsigned long);
    virtual void *FUN_006114e0();
    virtual unsigned int FUN_006114f0();
    virtual unsigned short FUN_00611500();
    virtual unsigned short FUN_00611510();
    virtual unsigned short FUN_00611520();
    virtual int FUN_00611530();
    int m_04;
    char m_pad08[0x0c];
    unsigned char *m_14;
    void *m_18;
    unsigned int m_1c;
    unsigned short m_20;
    unsigned short m_22;
    unsigned short m_24;
    char m_26[2];
#ifdef SBGEO_VECTOR2D_VIEW
    SBGeoVector2D m_28;
#else
    float m_28[2];
#endif

    bool FUN_00611ea0(int);
    bool FUN_00611f70(int);
    bool FUN_00612040(int);
    bool FUN_00612150(int);
    bool FUN_00612260(int);
    bool FUN_006122b0(int);
    bool FUN_00612300(const SBGeoVector2D &, int);
    bool FUN_00612350(const SBGeoVector2D &);
    unsigned short FUN_006124f0(unsigned short *, unsigned short, unsigned short, unsigned short);
    unsigned short FUN_006125c0(unsigned short *, unsigned short, unsigned short, unsigned short);
    bool FUN_00612690(const SBGeoVector2D &);
    bool FUN_006128b0(const SBGeoVector2D &);
    SBPicture *Unk00612ad0(const SBGeoPoint2D &, const SBGeoVector2D &);
    bool FUN_00612d80(unsigned short, unsigned short);
    bool FUN_00612e30(unsigned short, unsigned short);
    bool FUN_006131a0(unsigned short, unsigned short);
};

#endif
