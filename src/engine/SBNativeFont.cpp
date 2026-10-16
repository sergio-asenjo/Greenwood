#include "SBNativeFont.h"
#include "SB.h"
#include <string.h>

DECOMP_SIZE_ASSERT(SBNativeFont, 0xd8)
DECOMP_SIZE_ASSERT(SBNativeFontCharacterValue, 0x14)
DECOMP_SIZE_ASSERT(SBNativeFontCharacterTree, 0x10)
DECOMP_SIZE_ASSERT(SBNativeFontBase, 0x44)
DECOMP_SIZE_ASSERT(RHUnk006114c0, 0x38)

// GLOBAL: GAME 0x006c18c4
unsigned g_unk0x006c18c4 = 0;

// GLOBAL: GAME 0x006c18c8
SBResourceUnkKeyNode *g_unk0x006c18c8 = 0;

// FUNCTION: GAME 0x00616c70
void *SBNativeFont::FUN_00616c70(unsigned flags)
{
    this->~SBNativeFont();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00616c90
void SBNativeFontCharacterTree::FUN_00616c90()
{
    FUN_006176a0(SBResourceUnkKeyIterator(*(SBResourceUnkKeyNode **)m_head),
        SBResourceUnkKeyIterator(m_head));
    operator delete(m_head);
    m_head = 0;
    m_count = 0;
    {
        SBFontLock lock;
        if (--g_unk0x006c18c4 == 0)
        {
            operator delete(g_unk0x006c18c8);
            g_unk0x006c18c8 = 0;
        }
    }
}

// Parked: picture callback literals and map-cleanup temporary/register scheduling differ.
// STUB: GAME 0x00616d00
SBNativeFont::~SBNativeFont()
{
}

// Parked: picture callback literals and allocator/header store scheduling differ.
// STUB: GAME 0x00616dc0
SBNativeFont::SBNativeFont(const std::string &name)
{
    m_surface = 0;
    m_vptr = 0x0067a96c;
    memset(m_nativeHeader, 0, sizeof(m_nativeHeader));
    m_spacing = 0;
    ((SBFontUnk0061e840 *)this)->FUN_0061ea80(name);
}

// FUNCTION: GAME 0x00616ee0
void SBNativeFont::AttachToRenderContext(SBNativeFontRenderContext *context, unsigned long flags)
{
    ((SBFontUnk0061e840 *)this)->FUN_0061e810((int)context, flags);
    m_surface = context->V0c(&m_pictures[0], &m_pictures[1], (flags & 1) != 0);
}

// FUNCTION: GAME 0x00616f20
void SBNativeFont::DetachFromRenderContext()
{
    m_context->V14(m_surface);
    ((SBFontUnk0061e840 *)this)->FUN_0061e840();
}

// FUNCTION: GAME 0x00616f40
unsigned SBNativeFont::FUN_00616f40() const
{
    return m_nativeHeader[1];
}

// Parked: iterator temporaries add four frame bytes and shift result slots.
// STUB: GAME 0x00616f50
const SBNativeFont::CharacterInfo *SBNativeFont::GetCharacterInfo(unsigned short character) const
{
    SBNativeFontCharacterTree &characters = (SBNativeFontCharacterTree &)m_characters;
    SBResourceUnkKeyIterator candidate = characters.FUN_00617e20(character);
    SBResourceUnkKeyNode *node = candidate.m_node;
    SBResourceUnkKeyIterator value(node);
    SBResourceUnkKeyIterator found = node != characters.FUN_00617690().m_node &&
        character >= *(unsigned short *)&node->m_key ? value : characters.FUN_00617690();
    if (found.m_node != m_characters.m_head)
        return (const CharacterInfo *)((char *)found.m_node + 0x10);
    unsigned short space = 0x20;
    SBResourceUnkKeyIterator fallback(characters.FUN_00618280(space));
    SBResourceUnkKeyNode *fallbackNode = fallback.m_node;
    SBResourceUnkKeyIterator fallbackValue(fallbackNode);
    SBResourceUnkKeyIterator replacement = fallbackNode != characters.FUN_00617690().m_node &&
        space >= *(unsigned short *)&fallbackNode->m_key ? fallbackValue : characters.FUN_00617690();
    const CharacterInfo *result = replacement.m_node == m_characters.m_head ?
        (const CharacterInfo *)((char *)replacement.m_node + 0x10) : 0;
    ((SBFontUnk0061e840 *)this)->FUN_0061ebd0(character);
    return result;
}

// FUNCTION: GAME 0x00617030
unsigned SBNativeFont::FUN_00617030() const
{
    return 0x200;
}

// FUNCTION: GAME 0x00617040
void SBNativeFont::GetImplementationTag(char (&tag)[6]) const
{
    char value[6] = {'S', 'B', 'F', 'O', 'N', 'T'};
    memcpy(tag, value, sizeof(value));
}

// FUNCTION: GAME 0x00617080
unsigned SBNativeFont::FUN_00617080() const
{
    return m_spacing;
}

// Parked: the null-result zero stores use different registers and scheduling.
// STUB: GAME 0x00617090
long SBNativeFont::GetCharacterWidth(unsigned short character, long &left, long &right) const
{
    const CharacterInfo *info = GetCharacterInfo(character);
    if (info)
    {
        long width = info->m_width;
        left = info->m_left;
        right = info->m_right;
        return width;
    }
    return left = right = 0;
}

// Parked: the map insertion frame is twelve bytes short and pair copies differ.
// STUB: GAME 0x006170d0
bool SBNativeFont::LoadFromStream(SBFile &file)
{
    bool loaded = ((SBFontUnk0061e840 *)this)->FUN_0061eb00(file);
    if (!loaded)
        return false;
    if (file.Access(m_nativeHeader, sizeof(m_nativeHeader)))
        return false;
    if (((SBFontUnk0061e840 *)this)->FUN_0061e880() == 0x200 &&
        file.Access(&m_spacing, sizeof(m_spacing)))
        return false;
    for (unsigned i = 0; i < m_nativeHeader[2]; ++i)
    {
        unsigned short character;
        CharacterInfo info;
        if (file.Access(&character, sizeof(character)))
            return false;
        if (file.Access(&info, sizeof(info)))
            return false;
        SBNativeFontCharacterPair inserted = m_characters.FUN_006177d0(
            SBNativeFontCharacterValue(character, info));
        *(CharacterInfo *)((char *)inserted.m_iterator.m_node + 0x10) = info;
    }
    if (!((SBNativeFontPictureCalls *)&m_pictures[0])->V10(file))
        return false;
    return ((SBNativeFontPictureCalls *)&m_pictures[1])->V10(file) != false;
}

class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    ~SBGeoPoint2D();
    SBGeoPoint2D &FUN_005fc1e0(const SBGeoPoint2D &other);
    float x;
    float y;
};

class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D(float x, float y);
    SBGeoVector2D(const SBGeoPoint2D &other);
};

class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D();
    SBGeoBoundingBox2D(float left, float top, float right, float bottom);
    SBGeoBoundingBox2D operator-(const SBGeoVector2D &other) const;
    SBGeoBoundingBox2D FUN_006090d0(const SBGeoVector2D &other) const;
    SBGeoBoundingBox2D FUN_006092c0(const SBGeoBoundingBox2D &other) const;
    bool FUN_006090a0() const;
    bool Unk00608f30() const;
    SBGeoPoint2D first;
    SBGeoPoint2D second;
    bool active;
};

class RHMapBox
{
public:
    RHMapBox(float left, float top, float right, float bottom);
    ~RHMapBox() {}
    SBGeoPoint2D first;
    SBGeoPoint2D second;
    bool active;
};

class RHMobileUnk00607da0
{
public:
    RHMobileUnk00607da0 &FUN_00607da0(const RHMobileUnk00607da0 &other);
};

class SBUIListboxUnk0061e890
{
public:
    int FUN_0061e890();
};

class SBNativeFontBlitCalls
{
public:
    virtual void V00();
    virtual bool V04(unsigned long surface, const SBGeoBoundingBox2D &source, const SBGeoBoundingBox2D &destination);
};

class SBNativeFontSpacingCalls
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
    virtual unsigned long V20();
};

// Parked: vector temporary slots and signed-width x87 conversion scheduling differ.
// STUB: GAME 0x00617220
bool SBNativeFont::Render(unsigned short character, SBGeoPoint2D &position, const SBGeoBoundingBox2D &clip, bool measure) const
{
    bool rendered = false;
    const CharacterInfo *info = GetCharacterInfo(character);
    if (info) {
        unsigned long atlasPosition = info->m_position;
        RHMapBox image((float)atlasPosition, 0.0f,
            (float)(atlasPosition + info->m_width), (float)(unsigned)((SBUIListboxUnk0061e890 *)this)->FUN_0061e890());
        SBGeoBoundingBox2D &source = *(SBGeoBoundingBox2D *)&image;
        SBGeoBoundingBox2D destination;
        position.FUN_005fc1e0(SBGeoVector2D((float)info->m_left, 0.0f));
        destination.first.x = position.x;
        destination.first.y = position.y;
        destination.second.x = position.x + info->m_width;
        destination.active = true;
        destination.second.y = (float)(unsigned)((SBUIListboxUnk0061e890 *)this)->FUN_0061e890() + position.y;
        destination.active = true;
        ((RHMobileUnk00607da0 *)&destination)->FUN_00607da0((const RHMobileUnk00607da0 &)destination.FUN_006092c0(clip));
        {
            SBGeoVector2D origin(destination.first);
            SBGeoVector2D atlas((float)info->m_position, 0.0f);
            ((RHMobileUnk00607da0 *)&source)->FUN_00607da0((const RHMobileUnk00607da0 &)(destination - origin).FUN_006090d0(atlas));
        }
        if (destination.FUN_006090a0() && destination.Unk00608f30()) {
            if (!measure)
                rendered = ((SBNativeFontBlitCalls *)m_context)->V04(m_surface, source, destination);
            else
                rendered = true;
            position.FUN_005fc1e0(SBGeoVector2D((float)(((SBNativeFontSpacingCalls *)this)->V20() + info->m_right + info->m_width), 0.0f));
        }
    }
    return rendered;
}

// Parked: file and receiver registers swap and failure tails merge differently.
// STUB: GAME 0x00617590
bool SBNativeFont::SaveToStream(SBFile &file)
{
    if (!((SBFontUnk0061e840 *)this)->FUN_0061ed70(file))
        return false;
    if (file.Access(m_nativeHeader, sizeof(m_nativeHeader)))
        return false;
    if (file.Access(&m_spacing, sizeof(m_spacing)))
        return false;
    SBNativeFontCharacterIterator it;
    it.m_node = *(SBResourceUnkKeyNode **)m_characters.m_head;
    for (; it.m_node != m_characters.m_head; it.FUN_00617ed0())
    {
        unsigned short character = *(unsigned short *)&it.m_node->m_key;
        CharacterInfo info = *(CharacterInfo *)((char *)it.m_node + 0x10);
        if (file.Access(&character, sizeof(character)))
            return false;
        if (file.Access(&info, sizeof(info)))
            return false;
    }
    if (!((SBNativeFontPictureCalls *)&m_pictures[0])->V1c(file))
        return false;
    return ((SBNativeFontPictureCalls *)&m_pictures[1])->V1c(file) != false;
}

void EmitSBNativeFont(SBNativeFont *font, SBNativeFontRenderContext *context,
                      char (&tag)[6], long &spacing, SBFile &file)
{
    SBNativeFont local(std::string(""));
    font->FUN_00616c70(0);
    font->AttachToRenderContext(context, 0);
    font->DetachFromRenderContext();
    font->FUN_00616f40();
    font->FUN_00617030();
    font->FUN_00617080();
    font->GetImplementationTag(tag);
    font->GetCharacterWidth(0, spacing, spacing);
    font->LoadFromStream(file);
    font->Render(0, *(SBGeoPoint2D *)font, *(SBGeoBoundingBox2D *)font, true);
    font->SaveToStream(file);
    font->m_characters.FUN_00616c90();
}
