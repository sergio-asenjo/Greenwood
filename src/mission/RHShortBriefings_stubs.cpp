#include "RHShortBriefings.h"

// Target 0x005a3360: vector range erase.
RHShortBriefings::ShortBriefing *RHShortBriefings::ShortBriefingVector::erase(ShortBriefing *first, ShortBriefing *last)
{
    ShortBriefing *next = first;
    while (last != m_last)
        *next++ = *last++;
    m_last = next;
    return first;
}

// Target 0x0054c320: vector count insert.
void RHShortBriefings::ShortBriefingVector::Insert(ShortBriefing *, unsigned, const ShortBriefing &) {}
