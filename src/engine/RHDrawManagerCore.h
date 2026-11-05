#ifndef RHDRAWMANAGERCORE_H
#define RHDRAWMANAGERCORE_H

#ifndef SBGEO_BOUNDINGBOX2D_VIEW
#include "SBGeoBoundingBox2DCore.h"
#endif

class SBGeoSegment2D;
class SBGeoPolyLine2DList;
class SBDrawViewport;
class SBDrawManager;

class RHDrawManager : public SBGeoBoundingBox2D
{
public:
    RHDrawManager(SBDrawManager *drawManager);
    bool CheckPointForDrawing(short x, short y, unsigned short width, unsigned short height);
    void DrawSegment(const SBGeoSegment2D &segment, unsigned short color);
    void DrawPolyLine(const SBGeoPolyLine2DList &list, unsigned short color);
    void FillBox(const SBGeoBoundingBox2D &box, unsigned short color);
    void DrawEllipsePoints(const SBDrawViewport &viewport, const SBGeoPoint2D &center, short x, short y, unsigned short color);
    void DrawDottedLine(const SBGeoPoint2D &from, const SBGeoPoint2D &to, float &phase, float dash, float thickness, unsigned short color);
    unsigned short GetPackedColor(unsigned long color);
    void DrawEllipse(const SBDrawViewport &viewport, const SBGeoPoint2D &center, unsigned short radius, unsigned short color);
    void DrawCircle(const SBDrawViewport &viewport, const SBGeoPoint2D &center, unsigned short radius, unsigned short color);

    static RHDrawManager *mpDrawManager;

    float m_14;
    unsigned long m_18;
    SBDrawManager *m_drawManager;
};

#endif
