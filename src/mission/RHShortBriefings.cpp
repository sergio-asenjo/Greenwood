#include "SBNullstr.h"
#include "RHShortBriefings.h"

class RHShortBriefingVectorEmission : public std::vector<RHShortBriefings::ShortBriefing>
{
public:
    static void Emit()
    {
        typedef RHShortBriefings::ShortBriefing Value;
        void (std::vector<Value>::*volatile fill)(Value *, unsigned, const Value &) = &RHShortBriefingVectorEmission::_Ufill;
        Value *(std::vector<Value>::*volatile copy)(const Value *, const Value *, Value *) = &RHShortBriefingVectorEmission::_Ucopy;
        Value *(__cdecl *volatile assign)(Value *, Value *, Value *) = &std::copy;
    }
};

// TEMPLATE: GAME 0x0054c320
// ?insert@?$vector@UShortBriefing@RHShortBriefings@@V?$allocator@UShortBriefing@RHShortBriefings@@@std@@@std@@QAEXPAUShortBriefing@RHShortBriefings@@IABU34@@Z

// TEMPLATE: GAME 0x0054c570
// ?_Ufill@?$vector@UShortBriefing@RHShortBriefings@@V?$allocator@UShortBriefing@RHShortBriefings@@@std@@@std@@IAEXPAUShortBriefing@RHShortBriefings@@IABU34@@Z

// TEMPLATE: GAME 0x0054c5a0
// ?copy@std@@YAPAUShortBriefing@RHShortBriefings@@PAU23@00@Z

class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(float x, float y);
    SBGeoPoint2D(const SBGeoPoint2D &other);
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    SBGeoPoint2D Unk005fc190(const SBGeoPoint2D &other) const;
    float x;
    float y;
};

class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D(const SBGeoPoint2D &other);
    SBGeoVector2D(const SBGeoVector2D &other);
    SBGeoVector2D &operator=(const SBGeoVector2D &other);
};

class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D();
    SBGeoBoundingBox2D(const SBGeoPoint2D &point);
    SBGeoBoundingBox2D(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
    SBGeoBoundingBox2D(const SBGeoBoundingBox2D &other);
    SBGeoPoint2D first;
    SBGeoPoint2D second;
    bool active;
    float GetHeight() const { return second.y - first.y; }
    void SetTop(float value) { first.y = value; active = true; }
    void SetBottom(float value) { second.y = value; active = true; }
};

class RHDialogueSet;
class RHEngine
{
public:
    RHDialogueSet *GetDynResources(unsigned long resources);
};
extern RHEngine *g_pEngine;

struct RHDialogueSetView
{
    char m_00[0x3c];
    unsigned long m_3c;
};

// FUNCTION: GAME 0x005a22c0
RHShortBriefings::RHShortBriefings(bool load)
{
    m_fc = 0;
    if (load)
    {
        RHDialogueSetView *resources = (RHDialogueSetView *)g_pEngine->GetDynResources(0);
        for (unsigned long count = resources->m_3c; count; --count)
            ((RHShortBriefingsCalls *)this)->FUN_005a2450((void *)(resources->m_3c - count), (void *)1);
    }
}

// FUNCTION: GAME 0x005a23a0
RHShortBriefings::~RHShortBriefings()
{
}

class RHMobileUnk00607da0
{
public:
    RHMobileUnk00607da0 &FUN_00607da0(const RHMobileUnk00607da0 &other);
};

class RHMapWideText
{
public:
    void Tidy(bool built);
};

class RHBriefingWideText
{
public:
    RHBriefingWideText(const unsigned short *text,
        const std::allocator<unsigned short> &allocator = std::allocator<unsigned short>()) : m_allocator(allocator)
    {
        ((RHMapWideText *)this)->Tidy(false);
        typedef std::basic_string<unsigned short> String;
        String &(String::*assign)(const unsigned short *, unsigned) = &String::assign;
        (((String *)this)->*assign)(text, wcslen(text));
    }
    ~RHBriefingWideText() { ((RHMapWideText *)this)->Tidy(true); }
    std::allocator<unsigned short> m_allocator;
    unsigned short *m_chars;
    unsigned m_size;
    unsigned m_capacity;
};

class RHBriefingReturnedText
{
public:
    ~RHBriefingReturnedText() { ((RHMapWideText *)this)->Tidy(true); }
    std::allocator<unsigned short> m_allocator;
    unsigned short *m_chars;
    unsigned m_size;
    unsigned m_capacity;
};

class RHProfileText
{
public:
    void FUN_00401ee0(bool built);
};

class RHBriefingNarrowText
{
public:
    RHBriefingNarrowText(const char *text, const std::allocator<char> &allocator = std::allocator<char>()) : m_allocator(allocator)
    {
        ((RHProfileText *)this)->FUN_00401ee0(false);
        typedef std::string String;
        String &(String::*assign)(const char *, unsigned) = &String::assign;
        (((String *)this)->*assign)(text, strlen(text));
    }
    ~RHBriefingNarrowText() { ((RHProfileText *)this)->FUN_00401ee0(true); }
    std::allocator<char> m_allocator;
    char *m_chars;
    unsigned m_size;
    unsigned m_capacity;
};

class RHBriefingSetupCalls
{
public:
    virtual void V00();
    virtual void V04();
    virtual void V08();
    virtual void V0c();
    virtual void V10();
    virtual void V14();
    virtual void V18();
    virtual void V1c(const SBGeoBoundingBox2D &box);
    virtual void V20(const SBGeoPoint2D &point);
    virtual void V24();
    virtual void V28();
    virtual void V2c();
    virtual void V30(const RHMapWideText &text, const SBGeoBoundingBox2D &box, bool enabled, unsigned long id);
    virtual void V34();
    virtual void V38(bool enabled);
};

class RHBriefingParentCalls
{
public:
    virtual void V00();
    virtual void V04();
    virtual void V08();
    virtual void V0c();
    virtual void V10();
    virtual void V14();
    virtual void V18();
    virtual void V1c();
    virtual void V20();
    virtual void V24();
    virtual void V28();
    virtual void V2c();
    virtual void V30(void *widget);
    void *FUN_00544b60(const RHBriefingNarrowText &name);
};

extern wchar_t g_unk0x006c0b50[1];
extern float g_unk0x006774a0;
extern float g_unk0x006775d8;
extern float g_unk0x006774e4;

// Parked: vector temporary slots, x87 operand order and receiver scheduling differ.
// STUB: GAME 0x005a2630
void RHShortBriefings::FUN_005a2630(RHMenuWindow *window, SBGeoBoundingBox2D &box)
{
    if (GetShortBriefingNumber(true) > 0 && GetShortBriefingNumber(false) > 0) {
        SBGeoBoundingBox2D bounds;
        {
            RHBriefingWideText text((const unsigned short *)g_unk0x006c0b50);
            ((RHBriefingSetupCalls *)&m_30)->V30((const RHMapWideText &)text,
                SBGeoBoundingBox2D(box.first, box.first), false, 0x11b);
        }
        ((RHBriefingParentCalls *)window)->V30(&m_30);
        SBGeoPoint2D offset;
        ((RHMobileUnk00607da0 *)&bounds)->FUN_00607da0(*(RHMobileUnk00607da0 *)((char *)&m_30 + 0x30));
        offset = SBGeoPoint2D(((box.second.x - box.first.x) - (bounds.second.x - bounds.first.x)) * g_unk0x006775d8, 10.0f);
        {
            SBGeoVector2D displacement(*(SBGeoVector2D *)&offset);
            ((RHBriefingSetupCalls *)&m_30)->V20(bounds.first.Unk005fc190(displacement));
        }
        box.SetTop(bounds.GetHeight() + box.first.y + g_unk0x006774a0);
    }
}

class RHBriefingTitleBase
{
public:
    RHBriefingTitleBase();
    ~RHBriefingTitleBase();
    unsigned m_vptr;
    char m_04[0xfc];
};

class RHBriefingTitle : public RHBriefingTitleBase
{
public:
    RHBriefingTitle()
    {
        m_vptr = 0x006791a8;
        m_04[0xf8] = true;
        m_04[0xf9] = true;
    }
};

class __declspec(novtable) RHBriefingPicture : public RHGameLifetime00517590
{
public:
    RHBriefingPicture()
    {
        *(unsigned *)this = 0x006775e4;
        m_cc = 0;
    }
    unsigned m_cc;
};

class SBUIUnk0060dd00
{
public:
    bool FUN_0060e0d0(void *first, void *second, void *third, void *fourth);
    int FUN_0060dcd0();
};

class RHSaveGame;
template<class T> class SBArray
{
public:
    void Insert(T *position, unsigned count, const T &value);
};

// GLOBAL: GAME 0x00677480
float g_unk0x00677480 = 3.0f;

// FUNCTION: GAME 0x005a2820
void RHShortBriefings::CreateWidgets(RHMenuWindow *window, const SBGeoBoundingBox2D &box)
{
    SBGeoBoundingBox2D working(box);
    FUN_005a28c0(window, working, true);
    FUN_005a2630(window, working);
    FUN_005a28c0(window, working, false);
}

void EmitRHShortBriefingWidgets(RHShortBriefings *briefings, RHMenuWindow *window, const SBGeoBoundingBox2D &box)
{
    briefings->CreateWidgets(window, box);
}

// Parked: the frame is twelve bytes larger; receiver colors and wide-string temporaries differ.
// STUB: GAME 0x005a28c0
void RHShortBriefings::FUN_005a28c0(RHMenuWindow *window, SBGeoBoundingBox2D &box, bool mode)
{
    // STRING: GAME 0x006b77e4
    void *active = ((RHBriefingParentCalls *)window)->FUN_00544b60("ActiveShortBriefing");
    // STRING: GAME 0x006b77cc
    void *inactive = ((RHBriefingParentCalls *)window)->FUN_00544b60("InactiveShortBriefing");
    ShortBriefingVector &values = mode ? m_0 : m_10;
    std::vector<RHSaveGame *> created;
    m_fc = window;
    for (ShortBriefing *position = values.begin(); position != values.end(); ++position) {
        ShortBriefing value = *position;
        RHBriefingTitle *title = new RHBriefingTitle;
        void *font = value.m_4 ? inactive : active;
        SBGeoBoundingBox2D bounds;
        ((RHMobileUnk00607da0 *)&bounds)->FUN_00607da0((const RHMobileUnk00607da0 &)box);
        bounds.first.x = g_unk0x006774e4 + bounds.first.x;
        bounds.active = true;
        typedef RHBriefingReturnedText (RHShortBriefings::*GetText)(const ShortBriefing &) const;
        GetText getText = reinterpret_cast<GetText>(&RHShortBriefings::GetShortBriefingText);
        ((RHBriefingSetupCalls *)title)->V30((const RHMapWideText &)(this->*getText)(value), bounds, false, (unsigned long)-1);
        SBUIUnk0060dd00 *renderer = (SBUIUnk0060dd00 *)((char *)title + 0x80);
        renderer->FUN_0060e0d0(font, font, font, font);
        *(unsigned *)((char *)title + 0xe0) = 4;
        float height;
        bounds.SetBottom((height = (unsigned)renderer->FUN_0060dcd0()) + bounds.first.y);
        ((RHBriefingSetupCalls *)title)->V1c(bounds);
        RHSaveGame *widget = (RHSaveGame *)title;
        ((SBArray<RHSaveGame *> *)&created)->Insert(created.end(), 1, widget);
        std::vector<RHSaveGame *> &widgets = *(std::vector<RHSaveGame *> *)&m_20;
        ((SBArray<RHSaveGame *> *)&widgets)->Insert(widgets.end(), 1, widget);
        ((RHBriefingParentCalls *)window)->V30(title);
        if (value.m_4 == 1) {
            SBGeoBoundingBox2D pictureBounds;
            RHBriefingPicture *picture = new RHBriefingPicture;
            ((RHMobileUnk00607da0 *)&pictureBounds)->FUN_00607da0(
                (const RHMobileUnk00607da0 &)SBGeoBoundingBox2D(box.first));
            ((RHBriefingSetupCalls *)picture)->V30((const RHMapWideText &)RHBriefingWideText((const unsigned short *)g_unk0x006c0b50),
                pictureBounds, false, 0x8e);
            ((RHBriefingSetupCalls *)picture)->V38(!value.m_4);
            widget = (RHSaveGame *)picture;
            ((SBArray<RHSaveGame *> *)&widgets)->Insert(widgets.end(), 1, widget);
            ((RHBriefingParentCalls *)window)->V30(picture);
        }
        box.SetTop(height + box.first.y + g_unk0x00677480);
    }
}

class RHBriefingWidgetCalls
{
public:
    virtual ~RHBriefingWidgetCalls();
};

#include "RHBriefingWindowCalls.h"

// FUNCTION: GAME 0x005a2d70
void RHShortBriefings::DestroyWidgets()
{
    std::vector<RHBriefingWidgetCalls *> &widgets = *(std::vector<RHBriefingWidgetCalls *> *)((char *)this + 0x20);
    for (RHBriefingWidgetCalls **position = widgets.begin(); position != widgets.end(); ++position) {
        (*(RHBriefingWindowCalls **)((char *)this + 0xfc))->V34(*position);
        delete *position;
    }
    widgets.erase(widgets.begin(), widgets.end());
    (*(RHBriefingWindowCalls **)((char *)this + 0xfc))->V34((char *)this + 0x30);
    *(void **)((char *)this + 0xfc) = 0;
}

// FUNCTION: GAME 0x005a2df0
void RHShortBriefings::DoneShortBriefing(unsigned long id)
{
    ulCurID = id;
    ShortBriefing *last = m_0.m_last;
    ShortBriefing *position = m_0.m_first;
    while (position != last) {
        if (IsSearchedShortBriefing(*position))
            break;
        ++position;
    }
    if (position == m_0.m_last) {
        last = m_10.m_last;
        position = m_10.m_first;
        while (position != last) {
            if (IsSearchedShortBriefing(*position))
                break;
            ++position;
        }
        if (position == m_10.m_last)
            return;
    }
    position->m_4 = 1;
}

void EmitRHShortBriefingDestroy(RHShortBriefings *briefings)
{
    briefings->DestroyWidgets();
    briefings->DoneShortBriefing(0);
}

// GLOBAL: GAME 0x006c104c
unsigned long RHShortBriefings::ulCurID = 0;

// FUNCTION: GAME 0x005a2e50
unsigned RHShortBriefings::GetShortBriefingNumber(bool first) const
{
    const ShortBriefingVector &values = first ? m_0 : m_10;
    return values.m_first == 0 ? 0 : values.m_last - values.m_first;
}

void EmitRHShortBriefingCount(const RHShortBriefings *briefings, bool first)
{
    briefings->GetShortBriefingNumber(first);
}

#include "RHMapResources.h"
extern RHMapResources *g_unk0x006c1840;

// Parked: resource manager loads at the call instead of hoisting into ESI before the null test.
// STUB: GAME 0x005a2e80
std::basic_string<unsigned short> RHShortBriefings::GetShortBriefingText(const ShortBriefing &value) const
{
    RHDialogueSet *resources = g_pEngine->GetDynResources(0);
    std::basic_string<unsigned short> text;
    if (!resources || !g_unk0x006c1840->FUN_006009e0(*(unsigned *)((char *)resources + 0x40), value.m_0, (RHMapWideText &)text)) {
        // STRING: GAME 0x006b77f8
        text = (const unsigned short *)L"Invalid short briefing ID...";
    }
    return text;
}

void EmitRHShortBriefingText(const RHShortBriefings *briefings, const RHShortBriefings::ShortBriefing &value)
{
    briefings->GetShortBriefingText(value);
}

// FUNCTION: GAME 0x005a2fa0
bool RHShortBriefings::HasShortBriefing(unsigned long id) const
{
    ulCurID = id;
    ShortBriefing *last = m_0.m_last;
    ShortBriefing *position = m_0.m_first;
    while (position != last) {
        if (IsSearchedShortBriefing(*position))
            break;
        ++position;
    }
    if (position != m_0.m_last)
        return true;
    last = m_10.m_last;
    position = m_10.m_first;
    while (position != last) {
        if (IsSearchedShortBriefing(*position))
            break;
        ++position;
    }
    if (position != m_10.m_last)
        return true;
    return false;
}

// FUNCTION: GAME 0x005a3010
bool RHShortBriefings::IsSearchedShortBriefing(const ShortBriefing &value)
{
    return value.m_0 == ulCurID;
}

void EmitRHShortBriefingSearch(const RHShortBriefings *briefings, unsigned long id)
{
    briefings->HasShortBriefing(id);
}

// FUNCTION: GAME 0x005a3030
bool RHShortBriefings::Serialize(SBFile &file)
{
    // STRING: GAME 0x006b7834
    RHSerializeName(file, "RHShortBriefings");
    SerializeContainer(file, m_0, SerializeShortBriefing);
    SerializeContainer(file, m_10, SerializeShortBriefing);
    return true;
}

// FUNCTION: GAME 0x005a32a0
bool RHShortBriefings::SerializeShortBriefing(SBFile &file, ShortBriefing &value)
{
    if (file.Access(&value.m_0, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        // STRING: GAME 0x006b77a8
        SBAssert(0, "P:\\Robin Hood\\RHShortBriefings.cpp", 399, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&value.m_4, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHShortBriefings.cpp", 400, "Serialize failed reason is %s", reason);
        return false;
    }
    return true;
}

void RHShortBriefings::Emit(SBFile &file)
{
    RHShortBriefings local(false);
    RHShortBriefingVectorEmission::Emit();
    Serialize(file);
    ShortBriefing value;
    SerializeShortBriefing(file, value);
}

// TEMPLATE: GAME 0x005a3320
// ?_Ucopy@?$vector@UShortBriefing@RHShortBriefings@@V?$allocator@UShortBriefing@RHShortBriefings@@@std@@@std@@IAEPAUShortBriefing@RHShortBriefings@@PBU34@0PAU34@@Z

// TEMPLATE: GAME 0x005a3360
// ?erase@?$vector@UShortBriefing@RHShortBriefings@@V?$allocator@UShortBriefing@RHShortBriefings@@@std@@@std@@QAEPAUShortBriefing@RHShortBriefings@@PAU34@0@Z
