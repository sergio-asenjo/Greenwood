#ifndef RHMOBILEUNK006100E0_H
#define RHMOBILEUNK006100E0_H

class RHUnk0060fbf0;
class RHLineSource00610000;
class SBGeoSegment2D;

class RHMobileUnk006100e0 : public SBGeoPoint2D
{
public:
    RHMobileUnk006100e0() {}
    RHMobileUnk006100e0(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
    RHMobileUnk006100e0(const RHMobileUnk006100e0 &other);
    RHMobileUnk006100e0(const RHLineSource00610000 &other);
    RHMobileUnk006100e0(const SBGeoSegment2D &other);
    ~RHMobileUnk006100e0();
    void FUN_00578c50() throw();
    void FUN_0060ff30(const RHMobileUnk006100e0 &other);
    RHMobileUnk006100e0 &FUN_00610140(const RHMobileUnk006100e0 &other);
    void FUN_00610160(const SBGeoPoint2D &vector);
    RHUnk0060fbf0 FUN_006101c0(const RHMobileUnk006100e0 &other) const;
    float FUN_006104f0(float y);
    float FUN_00610520(float x);
    SBGeoPoint2D &Second() { return m_second; }
    const SBGeoPoint2D &Second() const { return m_second; }
    SBGeoPoint2D m_second;
};

#endif
