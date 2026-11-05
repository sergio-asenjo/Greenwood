#ifndef RHMENUSHORTCUTSLIST_H
#define RHMENUSHORTCUTSLIST_H

#include "RHWidgetPortrait.h"

class RHMenuShortcutsKeys;

// SIZE 0x228
// VTABLE: GAME 0x00679f5c RHPortraitUnk005cf570
// VTABLE: GAME 0x00679f54 RHPortraitUnk005d06d0
class RHMenuShortcutsList : public RHPortraitUnk005d0180
{
public:
    RHMenuShortcutsList();
    ~RHMenuShortcutsList();
    virtual void *FUN_005dee10(unsigned flags);
    bool FUN_005cd010(unsigned short key, std::wstring &text);
    char FUN_005ce660(unsigned short key) const;
    RHPortraitWidgetEvent *FUN_005ce6b0(const RHPortraitWidgetInput &input);
    void FUN_005ced90();
    void FUN_005cf010(unsigned short index, const std::wstring &binding);
    void FUN_005cf1c0(RHMenuShortcutsKeys *keys);

    RHMenuShortcutsKeys *m_20c;
    bool m_modified;
    undefined m_211;
    unsigned short m_212;
    unsigned short m_214;
    bool m_216;
    RHPortraitWidgetEvent m_event;
};

#endif
