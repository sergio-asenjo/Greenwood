#ifndef RHMENUFOCUSCLASS_H
#define RHMENUFOCUSCLASS_H

#include "Decomp.h"
#include <string>
#include "RHMenuWindowClass.h"
#include "RHFocusManager.h"

class __declspec(novtable) RHMenuWindowFocus : public RHMenuWindow
{
public:
    RHMenuWindowFocus(RHMenuWindow *parent, void *screen, int orientation, bool wrap);
    RHMenuWindowFocus(RHMenuWindow *parent, void *screen, long resource, int orientation, bool wrap);
    ~RHMenuWindowFocus();
    void *FUN_00544cd0(unsigned flags);
    void *FUN_00545090(const void *input);
    void FUN_005450d0();

    RHFocusManager m_focus;
    SBGeoPoint2D m_138;
};

#include "RHPortraitButton.h"

#endif
