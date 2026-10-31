#ifndef SB_GEO_BOUNDING_BOX_2D_CORE_H
#define SB_GEO_BOUNDING_BOX_2D_CORE_H
#define SBGEO_BOUNDINGBOX2D_VIEW

#ifndef SBGEO_POINT2D_VIEW
#include "SBGeoPoint2D.h"
#endif

class SBGeoVector2D;
class SBGeoSegment2D;
class RHMalignitySegment;
class SBFile;
SBGeoPoint2D operator+(const SBGeoPoint2D &, const SBGeoVector2D &);

// SIZE 0x14
class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D();
    SBGeoBoundingBox2D(float, float, float, float);
    SBGeoBoundingBox2D(const SBGeoPoint2D &);
    SBGeoBoundingBox2D(const SBGeoSegment2D &);
    SBGeoBoundingBox2D(const SBGeoBoundingBox2D &);
    SBGeoBoundingBox2D(const SBGeoPoint2D &, const SBGeoPoint2D &);
    ~SBGeoBoundingBox2D() {}
    SBGeoBoundingBox2D &operator=(const SBGeoBoundingBox2D &);
    void Copy(const SBGeoBoundingBox2D &);
    SBGeoBoundingBox2D FUN_006090d0(const SBGeoVector2D &) const;
    SBGeoBoundingBox2D FUN_006092c0(const SBGeoBoundingBox2D &) const;
    void FUN_00607d90();
    void Unk00607dc0(const SBGeoPoint2D &);
    void FUN_00607e30(const RHMalignitySegment &);
    SBGeoPoint2D FUN_00608f40() const;
    bool FUN_00608400(const SBGeoPoint2D &) const;
    int FUN_00609050(const SBGeoPoint2D &, const SBGeoPoint2D &);
    bool Unk00608f30() const;
    bool FUN_006090a0() const;
    bool Serialize(SBFile &);
    float Value0() const { return m_p0.m_x; }
    float Value4() const { return m_p0.m_y; }
    float Value8() const { return m_p1.m_x; }
    float ValueC() const { return m_p1.m_y; }
    const SBGeoPoint2D &Min() const { return m_p0; }
    const SBGeoPoint2D &Max() const { return m_p1; }
    void SetMin(const SBGeoPoint2D &value) { m_flag = true; m_p0 = value; }
    void SetMax(const SBGeoPoint2D &value) { m_flag = true; m_p1 = value; }
    void SetSize(const SBGeoVector2D &value) { m_flag = true; m_p1 = ::operator+(m_p0, value); }
    void SetValue0(float value) { m_flag = true; m_p0.m_x = value; }
    void SetValue4(float value) { m_flag = true; m_p0.m_y = value; }
    void SetValue8(float value) { m_flag = true; m_p1.m_x = value; }
    void SetValueC(float value) { m_flag = true; m_p1.m_y = value; }
    SBGeoPoint2D m_p0;
    SBGeoPoint2D m_p1;
    bool m_flag;
};

#endif
