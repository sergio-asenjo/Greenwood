// Stub definitions for the external symbols RHMenuShortcuts.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls are direct `call rel32` in a separate translation unit.

#include "SBNullstr.h"
#include "RHMenuShortcuts.h"
#include <string.h>
#include <stddef.h>
#include "RHPortraitInputField.h"
#include "RHPortraitWidgetInput.h"

// FUNCTION: GAME 0x0051ebf0
RHMenuShortcutsKeys &RHMenuShortcutsKeys::FUN_0051ebf0(const RHKeyConfig &other)
{
    memcpy(m_keys, other.m_keys, 0x3a);
    m_count = other.m_count;
    return *this;
}


// Target 0x0053fdd0, __thiscall.
void RHMenuShortcuts::FUN_0053fdd0()
{
    m_list.FUN_005cf1c0(&m_keys);
}

std::wstring FUN_005e23d0(unsigned long);
int FUN_005fb030(unsigned scanCode, unsigned short *output, int capacity, int mode);

// FUNCTION: GAME 0x005cd010
bool RHMenuShortcutsList::FUN_005cd010(unsigned short key, std::wstring &text)
{
    switch (key)
    {
    case 0x00: text = FUN_005e23d0(0xe9); break;
    case 0xcb: text = FUN_005e23d0(0xb5); break;
    case 0xcd: text = FUN_005e23d0(0xb6); break;
    case 0xc8: text = FUN_005e23d0(0xb3); break;
    case 0xd0: text = FUN_005e23d0(0xb4); break;
    case 0xd2: text = FUN_005e23d0(0xdd); break;
    case 0xc7: text = FUN_005e23d0(0xe4); break;
    case 0xcf: text = FUN_005e23d0(0xe5); break;
    case 0x0e: text = FUN_005e23d0(0xbd); break;
    case 0xd3: text = FUN_005e23d0(0xde); break;
    case 0x01: text = FUN_005e23d0(0xbe); break;
    case 0x1c: text = FUN_005e23d0(0xcb); break;
    case 0x2a: text = FUN_005e23d0(0xb7); break;
    case 0x36: text = FUN_005e23d0(0xb8); break;
    case 0x3a: text = FUN_005e23d0(0xb9); break;
    case 0x1d: text = FUN_005e23d0(0xba); break;
    case 0x9d: text = FUN_005e23d0(0xbb); break;
    case 0x38: text = FUN_005e23d0(0xdf); break;
    case 0xb8: text = FUN_005e23d0(0xe0); break;
    case 0x39: text = FUN_005e23d0(0xbc); break;
    case 0x3b: text = FUN_005e23d0(0xbf); break;
    case 0x3c: text = FUN_005e23d0(0xc0); break;
    case 0x3d: text = FUN_005e23d0(0xc1); break;
    case 0x3e: text = FUN_005e23d0(0xc2); break;
    case 0x3f: text = FUN_005e23d0(0xc3); break;
    case 0x40: text = FUN_005e23d0(0xc4); break;
    case 0x41: text = FUN_005e23d0(0xc5); break;
    case 0x42: text = FUN_005e23d0(0xc6); break;
    case 0x43: text = FUN_005e23d0(0xc7); break;
    case 0x44: text = FUN_005e23d0(0xc8); break;
    case 0x57: text = FUN_005e23d0(0xc9); break;
    case 0x58: text = FUN_005e23d0(0xca); break;
    case 0xb7: text = FUN_005e23d0(0xe6); break;
    case 0x46: text = FUN_005e23d0(0xe7); break;
    case 0x0f: text = FUN_005e23d0(0xe1); break;
    case 0xc5: text = FUN_005e23d0(0xe8); break;
    case 0xc9: text = FUN_005e23d0(0xe2); break;
    case 0xd1: text = FUN_005e23d0(0xe3); break;
    case 0x45: text = FUN_005e23d0(0xcc); break;
    case 0xb5: text = FUN_005e23d0(0xcd); break;
    case 0x37: text = FUN_005e23d0(0xce); break;
    case 0x4a: text = FUN_005e23d0(0xcf); break;
    case 0x4e: text = FUN_005e23d0(0xd0); break;
    case 0x9c: text = FUN_005e23d0(0xd1); break;
    case 0x47: text = FUN_005e23d0(0xd2); break;
    case 0x48: text = FUN_005e23d0(0xd3); break;
    case 0x49: text = FUN_005e23d0(0xd4); break;
    case 0x4b: text = FUN_005e23d0(0xd5); break;
    case 0x4c: text = FUN_005e23d0(0xd6); break;
    case 0x4d: text = FUN_005e23d0(0xd7); break;
    case 0x4f: text = FUN_005e23d0(0xd8); break;
    case 0x50: text = FUN_005e23d0(0xd9); break;
    case 0x51: text = FUN_005e23d0(0xda); break;
    case 0x52: text = FUN_005e23d0(0xdb); break;
    case 0x53: text = FUN_005e23d0(0xdc); break;
    default:
        unsigned short characters[2] = {0, 0};
        FUN_005fb030(key, characters, 2, 2);
        text = (const wchar_t *)characters;
        break;
    }
    return true;
}

std::wstring FUN_005d0880(const std::wstring &, const std::wstring &);
extern wchar_t g_unk0x006c0b50[1];

// STUB: GAME 0x005ce6b0
RHPortraitWidgetEvent *RHMenuShortcutsList::FUN_005ce6b0(const RHPortraitWidgetInput &input)
{
    RHPortraitInputField &field = *(RHPortraitInputField *)this;
    RHPortraitUnk005d0180 &widget = *(RHPortraitUnk005d0180 *)this;
    RHPortraitWidgetEvent *result;
    bool handled = false;
    RHPortraitWidgetEvent *event = 0;
    if ((unsigned short)field.m_10c > 0 && *(bool *)((char *)this + 0x1f8)
        && *(bool *)((char *)this + 0x1f9))
    {
        int pressed = input.shortcuts->FUN_0060e240(0xd0);
        int repeat = ((int *)((char *)input.shortcuts + 0xa0c))[0xd0];
        if (pressed == 1 && (repeat == 2 || repeat == 0))
        {
            field.FUN_005d1670();
            event = &widget.m_event;
            widget.m_event.widget = this;
            event->type = 15;
            widget.m_event.value = field.m_188;
        }
        else if (field.FUN_005d1630(input, 0xc8))
        {
            field.FUN_005d1700();
            event = &widget.m_event;
            widget.m_event.widget = this;
            event->type = 15;
            widget.m_event.value = field.m_188;
        }
        else if (field.FUN_005d1630(input, 0x1c))
        {
            event = &widget.m_event;
            widget.m_event.widget = this;
            widget.m_event.value = 0;
            event->type = 2;
        }
        if (event)
        {
            widget.m_event.next = 0;
            handled = true;
        }
    }
    if (event)
    {
        result = event;
        result->next = field.FUN_005cf980(input);
    }
    else
    {
        result = field.FUN_005cf980(input);
        if (result)
            handled = true;
    }
    RHGameWidgetAnimatedCalls &animated = *(RHGameWidgetAnimatedCalls *)((char *)this + 0x1dc);
    animated.FUN_005d5790(result, field.m_state, handled);
    if (m_214 == 0xffff)
    {
        (*(RHFocusManager **)((char *)this + 0x1d8))->FUN_00500780(true);
        *(bool *)((char *)this + 0x1f9) = true;
    }
    if (field.m_188 != m_214)
    {
        if (m_214 != 0xffff)
        {
            if ((*m_20c)[m_214] == 0)
            {
                std::wstring binding;
                FUN_005cd010(m_212, binding);
                (*m_20c)[m_214] = m_212;
                FUN_005cf010(m_214, binding);
            }
            m_214 = 0xffff;
            m_212 = 0xffff;
        }
        if (m_214 == 0xffff && field.m_188 != 0xffff)
        {
            if (((input.flags & 1)
                 && ((SBGeoBoundingBox2D *)((char *)this + 0x30))->FUN_006083b0(input.point)
                 && !field.Renderer().FUN_0061d7c0().FUN_00608400(input.point))
                || (input.shortcuts->FUN_0060e240(0x1c) == 0
                    && ((RHPortraitKeyboardCalls *)input.shortcuts)->FUN_0060e270(0x1c)
                    && !m_216 && *(bool *)((char *)this + 0x1f8)))
            {
                m_212 = (*m_20c)[field.m_188];
                m_214 = field.m_188;
                {
                    std::wstring binding(g_unk0x006c0b50);
                    FUN_005cf010(field.m_188, binding);
                }
                (*m_20c)[field.m_188] = 0;
                (*(RHFocusManager **)((char *)this + 0x1d8))->FUN_00500780(false);
                *(bool *)((char *)this + 0x1f9) = false;
            }
            else if (input.shortcuts->FUN_0060e240(0x1c) == 0
                     && ((RHPortraitKeyboardCalls *)input.shortcuts)->FUN_0060e270(0x1c)
                     && m_216)
                m_216 = false;
        }
    }
    if (m_214 != 0xffff)
    {
        std::wstring reserved;
        std::wstring empty;
        reserved = FUN_005e23d0(0xea);
        empty = FUN_005e23d0(0xe9);
        for (unsigned short key = 0; key < 0x100; ++key)
        {
            if (((RHPortraitKeyboardCalls *)input.shortcuts)->FUN_0060e270(key)
                && input.shortcuts->FUN_0060e240(key) == 1)
            {
                std::wstring binding;
                if (FUN_005ce660(key))
                {
                    (*m_20c)[m_214] = 0;
                    FUN_005cf010(m_214, reserved);
                }
                else
                {
                    unsigned short duplicate = m_20c->GetKeyIndex(key);
                    if (duplicate != 0xffff)
                    {
                        (*m_20c)[duplicate] = 0;
                        FUN_005cf010(duplicate, empty);
                    }
                    FUN_005cd010(key, binding);
                    FUN_005cf010(m_214, binding);
                    (*m_20c)[m_214] = key;
                    m_modified = true;
                    m_214 = 0xffff;
                    m_216 = key == 0x1c;
                }
                m_event.type = 9;
                m_event.widget = this;
                m_event.value = 0;
                m_event.next = result;
                result = &m_event;
                animated.FUN_005d5790(result, field.m_state, false);
                break;
            }
        }
    }
    animated.FUN_005d5790(result, field.m_state, false);
    return result;
}

// FUNCTION: GAME 0x005ced90
void RHMenuShortcutsList::FUN_005ced90()
{
    RHPortraitUnk005cf570 &list = *(RHPortraitUnk005cf570 *)this;
    list.DeleteAllItems();
    for (int index = 0; index < m_20c->GetKeyCount(); ++index)
    {
        std::wstring label;
        std::wstring binding;
        label = FUN_005e23d0(index + 0x97);
        FUN_005cd010((*m_20c)[index], binding);
        typedef std::wstring (__cdecl *Join)(const std::wstring &, const wchar_t *);
        Join join = &std::operator+;
        list.AddItem(FUN_005d0880(join(label, L"|"), binding), label, 0);
    }
    *(bool *)((char *)this + 0x19a) = true;
    *(bool *)((char *)this + 0x19b) = true;
    m_modified = false;
}

DECOMP_SIZE_ASSERT(RHMenuShortcutsList, 0x228)
DECOMP_SIZE_ASSERT(RHMenuShortcuts, 0x874)
DECOMP_STATIC_ASSERT(offsetof(RHPortraitUnk005d0180, m_event) == 0x1fc)
DECOMP_STATIC_ASSERT(offsetof(RHMenuShortcutsList, m_20c) == 0x20c)
DECOMP_STATIC_ASSERT(offsetof(RHMenuShortcutsList, m_modified) == 0x210)
DECOMP_STATIC_ASSERT(offsetof(RHMenuShortcutsList, m_212) == 0x212)
DECOMP_STATIC_ASSERT(offsetof(RHMenuShortcutsList, m_214) == 0x214)
DECOMP_STATIC_ASSERT(offsetof(RHMenuShortcutsList, m_216) == 0x216)
DECOMP_STATIC_ASSERT(offsetof(RHMenuShortcutsList, m_event) == 0x218)
DECOMP_STATIC_ASSERT(offsetof(RHMenuShortcuts, m_list) == 0x640)
DECOMP_STATIC_ASSERT(offsetof(RHMenuShortcuts, m_keys) == 0x868)

// FUNCTION: GAME 0x005cf1c0
void RHMenuShortcutsList::FUN_005cf1c0(RHMenuShortcutsKeys *keys)
{
    if (keys != m_20c)
    {
        m_20c = keys;
        FUN_005ced90();
    }
}

// GLOBAL: GAME 0x006c069c
bool g_unk0x6c069c;

#include "RHSectorActorList.h"

// STUB: GAME 0x005cf010
void RHMenuShortcutsList::FUN_005cf010(unsigned short index, const std::wstring &binding)
{
    std::wstring text;
    RHPortraitTextLines &original = ((RHPortraitUnk005cf570 *)this)->m_first;
    ((RHSectorActorList *)&original)->Unk005c8e40(index);
    text = *original.m_current;
    text.append(
        // STRING: GAME 0x006b8dd4
        L"|" + binding, 0, std::wstring::npos);
    if (index < (int)((RHPortraitUnk005cf570 *)this)->m_second.size())
    {
        RHPortraitTextLines &display = ((RHPortraitUnk005cf570 *)this)->m_second;
        ((RHSectorActorList *)&display)->Unk005c8e40(index);
        typedef std::wstring &(std::wstring::*Assign)(const std::wstring &, unsigned, unsigned);
        Assign assign = &std::wstring::assign;
        ((*display.m_current).*assign)(text, 0, std::wstring::npos);
        *(bool *)((char *)this + 0x19a) = true;
        *(bool *)((char *)this + 0x19b) = true;
    }
}

void EmitRHMenuShortcutsListBinding(RHMenuShortcutsList *list, const std::wstring &binding,
                                  const RHPortraitWidgetInput &input)
{
    list->FUN_005cf010(0, binding);
    list->FUN_005ce6b0(input);
}
