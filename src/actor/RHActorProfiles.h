#ifndef RHACTORPROFILES_H
#define RHACTORPROFILES_H

#include "RHCivilianProfile.h"

class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    ~SBGeoPoint2D();
    bool Serialize(SBFile &file);
    float m_x;
    float m_y;
};

class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D();
    ~SBGeoBoundingBox2D() {}
    bool Serialize(SBFile &file);
    SBGeoPoint2D m_p0;
    SBGeoPoint2D m_p1;
    bool m_flag;
};

class RHCharacterProfile
{
public:
    int m_00;
    RHProfileText m_04;
    RHProfileText m_14;
    RHProfileString m_24;
    char m_34;
    char m_35;
    short m_36;
    short m_38;
    short m_3a;
    int m_3c;
    int m_40;
    int m_44;
    int m_48;
    int m_4c;
    int m_50;
    short m_54;
    short m_56;
    short m_58;
    short m_5a;
    int m_5c;
    int m_60;
    int m_64;
    int m_68;
    char m_6c[4];
    SBGeoBoundingBox2D m_70;
    SBGeoPoint2D m_84;
    short m_8c;
    short m_8e;
    short m_90;
    short m_92;
    int m_94;
    int m_98;
};

class RHSoldierProfile
{
public:
    RHProfileText m_00;
    RHProfileText m_10;
    RHProfileString m_20;
    short m_30;
    short m_32;
    short m_34;
    short m_36;
    short m_38;
    char m_3a[2];
    short m_3c;
    short m_3e;
    short m_40;
    short m_42;
    int m_44;
    int m_48;
    int m_4c;
    short m_50;
    short m_52;
    short m_54;
    short m_56;
    int m_58;
    char m_5c[4];
    SBGeoBoundingBox2D m_60;
    SBGeoPoint2D m_74;
    short m_7c;
    short m_7e;
    int m_80;
    int m_84;
};

#endif
