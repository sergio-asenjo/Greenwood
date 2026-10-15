#ifndef RHPOSITIONINTERFACE_H
#define RHPOSITIONINTERFACE_H

#include "RHOrder.h"

class RHUnkPathGeometry
{
public:
    bool Unk004fbec0(SBFile &file, void *&value);
    bool Unk004fc030(SBFile &file, void *&value);
    bool Unk004fc180(SBFile &file, void *&value);
    bool Unk004fc2d0(SBFile &file, void *&value);
};

struct RHUnkSectorGlobal;
extern RHUnkSectorGlobal *g_unk0x6c0a9c;

class SBGeoBoundingBox2D
{
public:
    bool Serialize(SBFile &file);
    char m_bytes[0x14];
};

class RHPositionInterface
{
public:
    bool Turn();
    bool TurnFast();
    bool TurnSlow(unsigned char delay);
    bool TurnAntiVibration();
    bool Serialize(SBFile &file);
    void Emit(SBFile &file);

    char m_pad0[4]; // +0x00
    int m_4; // +0x04
    int m_8; // +0x08
    RHUnk005df510 m_c; // +0x0c
    SBGeoPoint2D m_18; // +0x18
    SBGeoPoint2D m_20; // +0x20
    RHUnk005df510 m_28; // +0x28
    SBGeoPoint2D m_34; // +0x34
    SBGeoPoint2D m_3c; // +0x3c
    SBGeoPoint2D m_44; // +0x44
    SBGeoPoint2D m_4c; // +0x4c
    RHUnk005df510 m_54; // +0x54
    RHUnk005df510 m_60; // +0x60
    SBGeoPoint2D m_6c; // +0x6c
    char m_74; // +0x74
    char m_pad75[3];
    int m_78; // +0x78
    char m_7c; // +0x7c
    char m_pad7d[0xb];
    int m_88; // +0x88
    int m_8c; // +0x8c
    char m_pad90[0x2c];
    char m_bc; // +0xbc
    char m_padbd[3];
    SBGeoBoundingBox2D m_c0; // +0xc0
    unsigned short m_d4; // +0xd4
    unsigned short m_d6; // +0xd6
    char m_d8; // +0xd8
    char m_d9; // +0xd9
    unsigned short m_da; // +0xda
    void *m_dc; // +0xdc
    unsigned short m_e0; // +0xe0
    char m_pade2[2];
    void *m_e4; // +0xe4
    void *m_e8; // +0xe8
    void *m_ec; // +0xec
    void *m_f0; // +0xf0
    char m_f4; // +0xf4
    char m_padf5[3];
    int m_f8; // +0xf8
    char m_fc; // +0xfc
    char m_fd; // +0xfd
    char m_fe; // +0xfe
    char m_padff;
    unsigned short m_100; // +0x100
    char m_pad102[2];
    SBGeoBoundingBox2D m_104; // +0x104
    int m_118; // +0x118
    char m_pad11c[4];
    RHElement *m_120; // +0x120
    char m_124; // +0x124
    char m_pad125[3];
    SBGeoPoint2D m_128; // +0x128
    char m_pad130[4];
    RHUnk005df510 m_134; // +0x134
};

#endif
