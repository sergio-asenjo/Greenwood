#ifndef RHSEQLIST_H
#define RHSEQLIST_H

#include "RHSectorActorList.h"

class RHSequenceElement;
class RHSeqNode
{
public:
    RHSeqNode *m_next;
    RHSeqNode *m_prev;
    RHSequenceElement *m_data;
};

class RHSeqList
{
public:
    RHSeqList(const char &allocator);
    static void CopyData(RHSequenceElement **destination, RHSequenceElement *const *source);
    __forceinline void GoTo(int index) { ((RHSectorActorList *)this)->Unk005c8e40(index); }
    char m_00[4];
    RHSeqNode *m_head;
    int m_count;
    RHSeqNode *m_current;
    bool m_valid;
    char m_11[3];
    int m_index;
};

#endif
