#include "SBTrueTypeFont.h"
#include <windows.h>
#include "SBUIRendererListbox.h"
#include "SBNativeFont.h"
#include "SBGeoVector2D.h"
#include "SBGeoBoundingBox2D.h"

// FUNCTION: GAME 0x00616790
void SBTrueTypeFont::CreateSystemObjects()
{
    m_font = CreateFontA(((SBUIListboxUnk0061e890 *)this)->FUN_0061e890(), 0, 0, 0,
        ((unsigned char)((SBFontUnk0061e840 *)this)->FUN_0061e970() & 1) ? 700 : 400,
        ((unsigned)((SBFontUnk0061e840 *)this)->FUN_0061e970() >> 1) & 1,
        0, 0, 0, 0, 0, 0, 0, (const char *)m_trueTypeHeader);
    m_deviceContext = CreateCompatibleDC(0);
    SelectObject((HDC)m_deviceContext, (HGDIOBJ)m_font);
}

// FUNCTION: GAME 0x00616800
void SBTrueTypeFont::DestroySystemObjects()
{
    DeleteDC((HDC)m_deviceContext);
    DeleteObject((HGDIOBJ)m_font);
}

// FUNCTION: GAME 0x00616820
long SBTrueTypeFont::GetBaseLine() const
{
    TEXTMETRICA metric;
    GetTextMetricsA((HDC)m_deviceContext, &metric);
    return metric.tmAscent;
}

// FUNCTION: GAME 0x00616870
int SBTrueTypeFont::FUN_00616870(void *context, unsigned long character) const
{
    SIZE size;
    if (GetTextExtentPoint32W((HDC)context, (const WCHAR *)&character, 1, &size) == 1)
    {
        if (size.cx > 255)
        {
            RECT bounds = {0, 0, 0, 0};
            DrawTextW((HDC)context, (const WCHAR *)&character, 1, &bounds, 0x420);
            size.cx = bounds.right - bounds.left;
        }
        return size.cx;
    }
    return 0;
}

static inline HRGN SBTrueTypeFontRegion(float left, float top, float right, float bottom)
{
    return CreateRectRgn((int)left, (int)top, (int)right, (int)bottom);
}

static inline float SBTrueTypeFontOffset(int width, float origin)
{
    return (float)width + origin;
}

static inline float SBTrueTypeFontOffset(unsigned height, float origin)
{
    return (float)height + origin;
}

static inline bool SBTrueTypeFontOverflows(int width, float origin, float limit)
{
    return (float)width + origin > limit;
}

static inline int SBTrueTypeFontText(HDC context, float x, float y, const unsigned short *character)
{
    return TextOutW(context, (int)x, (int)y, character, 1);
}

// Parked at 0.9510: the 0x005fc190 sum temporary keeps a non-throw() destructor state store; x spill slot differs.
// STUB: GAME 0x00616960
bool SBTrueTypeFont::Render(unsigned short character, SBGeoPoint2D &position, const SBGeoBoundingBox2D &bounds, bool measure) const
{
    const float *box = (const float *)&bounds;
    HRGN region = SBTrueTypeFontRegion(box[0], box[1], box[2], box[3]);
    HDC context = (HDC)m_context->V08();
    SelectObject(context, (HGDIOBJ)m_font);
    SetBkMode(context, 1);
    SetMapMode(context, 1);
    SelectClipRgn(context, region);
    SetTextColor(context, *(const COLORREF *)((const char *)this + 0x64));
    if (SBTrueTypeFontOverflows(FUN_00616870(context, character), position.m_x, box[2]))
    {
        position.m_y = SBTrueTypeFontOffset((unsigned)((SBUIListboxUnk0061e890 *)this)->FUN_0061e890(), position.m_y);
        position.m_x = box[0];
        if (bounds.FUN_00608400(position))
        {
            bool outside = !bounds.FUN_00608400(position.Unk005fc190(
                SBGeoVector2D(0, (float)(unsigned)((SBUIListboxUnk0061e890 *)this)->FUN_0061e890())));
            if (!outside)
                goto draw;
        }
        m_context->V10(context);
        return false;
    }
draw:
    int result;
    if (!measure)
        result = SBTrueTypeFontText(context, position.m_x, position.m_y, &character);
    else
        result = 1;
    position.m_x = SBTrueTypeFontOffset(FUN_00616870(context, character), position.m_x);
    m_context->V10(context);
    DeleteObject(region);
    return result == 1;
}
