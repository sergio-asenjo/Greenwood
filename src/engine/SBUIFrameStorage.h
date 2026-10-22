#ifndef SB_UI_FRAME_STORAGE_H
#define SB_UI_FRAME_STORAGE_H

#include <vector>
#ifndef SBGEO_POINT2D_VIEW
#define SBGEO_POINT2D_VIEW
class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(float x, float y);
    ~SBGeoPoint2D();
    float m_x;
    float m_y;
};
#endif

#include "SBGeoVector2D.h"

template <class T>
class SBUIFrameArray : public std::vector<T>
{
public:
    SBUIFrameArray() : m_dirty(true) {}
    ~SBUIFrameArray() { clear(); }
    T *m_cursor;
    bool m_dirty;
    bool m_cursorValid;
    int m_index;
};

class RHUnk00627cc0
{
public:
    ~RHUnk00627cc0();
    char m_00[0x10];
    SBUIFrameArray<int> m_values;
    char m_2c[4];
    SBUIFrameArray<int> m_durations;
    char m_4c[4];
    SBGeoVector2D m_point;
};

// FUNCTION: GAME 0x00627cc0
inline RHUnk00627cc0::~RHUnk00627cc0()
{
}

class RHUnk00628480
{
public:
    bool FUN_00628480();
    char m_00[4];
    unsigned short m_frame;
    unsigned short m_value;
    unsigned short m_tick;
    char m_0a[6];
    RHUnk00627cc0 *m_frames;
};

#endif
