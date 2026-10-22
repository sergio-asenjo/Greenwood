#ifndef RHMENUSHORTMISSIONTITLE_H
#define RHMENUSHORTMISSIONTITLE_H

#include "RHGameWidgetLifetime.h"
#include "RHGameTitleLifetimeInline.h"

class __declspec(novtable) RHMenuShortMissionTitle : public RHGameLifetime00525880
{
public:
    RHMenuShortMissionTitle()
    {
        *(unsigned *)this = 0x006791a8;
        m_fc = true;
        m_fd = true;
    }

    ~RHMenuShortMissionTitle()
    {
    }

    bool m_fc;
    bool m_fd;
};

#endif
