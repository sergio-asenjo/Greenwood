#include "SBNullstr.h"
#include "RHElementMobile.h"

class RHSprite
{
public:
    bool FUN_005b9e30(void *first, void *second, bool third);
};

RHMobileBase004a8130::RHMobileBase004a8130(int) throw() {}
// SYNTHETIC: GAME 0x004a81d0
// RHMobileBase004a8130::`scalar deleting destructor'

RHMobileBase004a8130::~RHMobileBase004a8130() {}
void RHMobileBase004a8130::v1() {}
void RHMobileBase004a8130::v2() {}
void RHMobileBase004a8130::v3() {}
void RHMobileBase004a8130::v4() {}
void RHMobileBase004a8130::v5() {}
void RHMobileBase004a8130::v6() {}
void RHMobileBase004a8130::v7() {}
void RHMobileBase004a8130::v8() {}
void RHMobileBase004a8130::v9() {}
void RHMobileBase004a8130::v10() {}
void RHMobileBase004a8130::v11() {}
void RHMobileBase004a8130::v12() {}
void RHMobileBase004a8130::v13() {}
void RHMobileBase004a8130::v14(SBFile &) {}
void RHMobileBase004a8130::v15() {}
bool RHMobileBase004a8130::v16(SBFile &) { return false; }
void RHMobileBase004a8130::v17(bool) {}
void RHMobileBase004a8130::v18() {}
void RHMobileBase004a8130::v19() {}
void RHMobileBase004a8130::v20() {}
void RHMobileBase004a8130::v21() {}
void RHMobileBase004a8130::v22() {}
void RHMobileBase004a8130::v23() {}
void RHMobileBase004a8130::v24() {}
void RHMobileBase004a8130::v25() {}
// SYNTHETIC: GAME 0x004aac80
// RHUnk004aac40::`scalar deleting destructor'
// FUNCTION: GAME 0x004aaca0
RHUnk004aac40::~RHUnk004aac40() {}
void RHUnk004aac40::v9() {}
void RHUnk004aac40::v10() {}
bool RHUnk004aac40::v16(SBFile &) { return false; }

RHMobileSegment::RHMobileSegment(const SBGeoPoint2D &, const SBGeoPoint2D &) {}
RHMobileSegment::~RHMobileSegment() {}
void RHMobileGrid::FUN_004ed370(void *, unsigned short, const RHMobileSegment &, unsigned) {}
// FUNCTION: GAME 0x006158b0
RHMobileUnk0060a820 &RHMobileUnk0060a820::FUN_006158b0(const SBGeoPoint2D &first, const SBGeoPoint2D &second)
{
    ((RHMobileUnk006100e0 *)this)->RHMobileUnk006100e0::RHMobileUnk006100e0(first, second);
    return *this;
}

// FUNCTION: GAME 0x006158d0
RHMobileUnk0060a820 &RHMobileUnk0060a820::FUN_006158d0(const SBGeoPoint2D &point)
{
    ((RHMobileUnk006100e0 *)this)->RHMobileUnk006100e0::RHMobileUnk006100e0(point, *(const SBGeoPoint2D *)((const char *)&point + 8));
    return *this;
}

// FUNCTION: GAME 0x006158f0
RHMobileUnk0060a820 &RHMobileUnk0060a820::FUN_006158f0(const RHMobileUnk006100e0 &other)
{
    ((RHMobileUnk006100e0 *)this)->FUN_00610140(other);
    return *this;
}
// FUNCTION: GAME 0x00607990
void RHMobileUnk00607da0::FUN_00607990(const RHMobileUnk00607da0 &other)
{
    bool value = *(const bool *)((const char *)&other + 0x10);
    *(bool *)((char *)this + 0x10) = value;
    if (value)
    {
        *(SBGeoPoint2D *)this = *(const SBGeoPoint2D *)&other;
        *(SBGeoPoint2D *)((char *)this + 8) = *(const SBGeoPoint2D *)((const char *)&other + 8);
    }
}
void RHMobileUnk006100e0::FUN_00578c50() {}

bool RHMobilePath::FUN_00550660(unsigned char) { return false; }
void RHMobilePath::FUN_005505c0() {}
RHUnk005fc3b0::RHUnk005fc3b0(float x, float y) : SBGeoVector2D(x, y) {}
float RHUnk005fc3b0::FUN_005fc7c0(float) { return 0.0f; }
// FUNCTION: GAME 0x004e6a10
void FUN_004b0620(RHUnk005fc3b0 *destination, const RHUnk005fc3b0 &value) { new (destination) RHUnk005fc3b0(value); }
void FUN_004b05b0(RHUnk005fc3b0 *first, RHUnk005fc3b0 *last, const RHUnk005fc3b0 &value)
{
    for (; first != last; ++first)
        first->FUN_005fc430(value);
}
void FUN_004b05e0(RHUnk005fc3b0 *first, RHUnk005fc3b0 *last, RHUnk005fc3b0 *destination)
{
    while (last != first)
        (--destination)->FUN_005fc430(*--last);
}
RHUnk005fc3b0 *RHMobileUnk004b06f0::FUN_004b04d0(RHUnk005fc3b0 *first, RHUnk005fc3b0 *last, RHUnk005fc3b0 *destination)
{
    for (; first != last; ++first, ++destination)
        FUN_004b0620(destination, *first);
    return destination;
}
void RHMobileUnk004b06f0::FUN_004b0510(RHUnk005fc3b0 *first, unsigned count, const RHUnk005fc3b0 &value)
{
    for (; count; --count, ++first)
        FUN_004b0620(first, value);
}
void RHMobileUnk004b06f0::FUN_004aff00(RHUnk005fc3b0 *first, RHUnk005fc3b0 *last)
{
    for (; first != last; ++first)
        first->~RHUnk005fc3b0();
}

void RHMobilePointList::FUN_005c8e40(int index) { GoToInline(index, (unsigned short)m_8); }
RHMobilePointIterator RHMobilePointList::FUN_0046eb80()
{
    RHMobilePointIterator result;
    result.node = m_4->next;
    return result;
}
void RHMobilePointList::FUN_005c9010(RHMobilePointNode *&node, int distance, unsigned)
{
    while (distance > 0) { node = node->next; --distance; }
    while (distance < 0) { node = node->previous; ++distance; }
}

unsigned short RHMobilePolygonPoints::FUN_0060ce80() const { return 0; }
RHMobileUnk0051fd10::RHMobileUnk0051fd10(float, float) {}
RHMobileUnk0051fd10::~RHMobileUnk0051fd10() {}
void RHMobileUnk0051fd10::FUN_0051fdc0() {}
RHMobileUnk00520b60::RHMobileUnk00520b60(const SBGeoPoint2D &, float, float) {}
RHMobileUnk00520b60::~RHMobileUnk00520b60() {}
void RHMobileUnk00520b60::FUN_00520c80(const SBGeoPoint2D &, const SBGeoPoint2D &) {}
RHMobilePointerList::RHMobilePointerList()
{
    m_4 = (RHMobilePointerNode *)::operator new(12);
    m_4->next = m_4;
    m_4->previous = m_4;
    m_8 = 0;
    m_10 = true;
}
RHMobilePointerList::~RHMobilePointerList()
{
    RHMobilePointerNode *node = m_4->next;
    while (node != m_4)
    {
        RHMobilePointerNode *next = node->next;
        ::operator delete(node);
        node = next;
    }
    ::operator delete(m_4);
}
void RHMobilePointerList::FUN_005c8e40(int index)
{
    m_c = m_4->next;
    for (int i = 0; i < index; ++i)
        m_c = m_c->next;
    m_14 = index;
    m_10 = false;
}

SBGeoPoint2D RHUnk005fc3b0::FUN_005fc450() const { return *this; }

RHMobilePointerArray::RHMobilePointerArray() : m_4(0), m_8(0), m_c(0), m_14(true) {}
RHMobilePointerArray::~RHMobilePointerArray() { ::operator delete(m_4); }
void RHMobilePointerArray::Append(void *value)
{
    if (m_8 == m_c)
    {
        unsigned count = m_4 ? m_8 - m_4 : 0;
        unsigned capacity = count ? count * 2 : 1;
        void **storage = (void **)::operator new(capacity * sizeof(void *));
        for (unsigned i = 0; i < count; ++i)
            storage[i] = m_4[i];
        ::operator delete(m_4);
        m_4 = storage;
        m_8 = storage + count;
        m_c = storage + capacity;
    }
    *m_8++ = value;
    m_14 = true;
}
RHMobileAreaLoad::RHMobileAreaLoad() {}
void RHMobileAreaLoad::FUN_005a3810(SBFile &, RHMobilePointerArray &) {}
SBGeoBoundingBox2D::SBGeoBoundingBox2D(float left, float top, float right, float bottom) : m_0(left, top), m_8(right, bottom), m_10(1) {}
// FUNCTION: GAME 0x004aafc0
bool RHMobilePartCalls::FUN_004aafc0(void *value)
{
    return ((RHSprite *)m_50)->FUN_005b9e30(value, m_54, false);
}
