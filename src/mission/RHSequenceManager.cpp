#include "SBNullstr.h"
#include "RHSequenceManager.h"

DECOMP_SIZE_ASSERT(RHUnk00582220, 0x3c)
DECOMP_SIZE_ASSERT(RHManagerList<void *>, 0x24)
DECOMP_SIZE_ASSERT(RHManagerSequenceView, 0x2c)
DECOMP_SIZE_ASSERT(RHManagerElementView, 0x3c)
DECOMP_SIZE_ASSERT(RHSequenceManager, 0x1b4)

// FUNCTION: GAME 0x0046eb80
RHScriptIter RHUnk0046eb30::FUN_0046eb80()
{
    return RHScriptIter((RHScriptNode *)((RHManagerList<void *> *)this)->head->next);
}

// Parked: frame 0x10 versus 0x14, plus container/EH differences.
// STUB: GAME 0x0058a9c0
bool RHSequenceManager::Serialize(SBFile &file)
{
    // STRING: GAME 0x006b75f0
    RHSerializeName(file, "RHSequenceManager");
    if (!RHOrder::SerializeStaticStuff(file))
    {
        SBAssert(1,
            // STRING: GAME 0x006b75cc
            "P:\\Robin Hood\\RHsequencemanager.cpp", 367, "Serialization failed");
        return false;
    }
    if (!RHSequence::SerializeStaticStuff(file))
    {
        SBAssert(1, "P:\\Robin Hood\\RHsequencemanager.cpp", 368, "Serialization failed");
        return false;
    }
    if (!RHSequenceElement::SerializeStaticStuff(file))
    {
        SBAssert(1, "P:\\Robin Hood\\RHsequencemanager.cpp", 369, "Serialization failed");
        return false;
    }
    unsigned count;
    if (!file.m_bLoading)
    {
        count = m_4.count;
        if (file.Access(&count, 4) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHsequencemanager.cpp", 374, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
    }
    else
    {
        RHManagerList<RHSequence *> &sequences = m_4;
        ((RHManagerListCalls *)&sequences)->FUN_0058bed0();
        sequences.valid = 1;
        RHManagerList<RHSequenceElement *> &elements = m_28;
        typedef std::list<RHSequenceElement *>::iterator Iterator;
        typedef Iterator (RHTitbitList::*Clear)(Iterator, Iterator);
        (((RHTitbitList *)&elements)->*(Clear)&RHTitbitList::Clear)(((std::list<RHSequenceElement *> *)&elements)->begin(), ((std::list<RHSequenceElement *> *)&elements)->end());
        elements.valid = 1;
        if (file.Access(&count, 4) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHsequencemanager.cpp", 382, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        int size = sequences.count;
        if ((int)count <= size)
        {
            typedef std::list<RHSequence *>::iterator SequenceIterator;
            typedef SequenceIterator (RHUnk0046eb30::*Erase)(SequenceIterator);
            for (int remaining = size - count; remaining > 0; --remaining)
                (((RHUnk0046eb30 *)&sequences)->*(Erase)&RHUnk0046eb30::erase)(--((std::list<RHSequence *> *)&sequences)->end());
        }
        else
        {
            typedef std::list<RHSequence *>::iterator SequenceIterator;
            typedef SequenceIterator (RHUnkList::*Insert)(SequenceIterator, RHSequence *const &);
            for (int remaining = count - size; remaining > 0; --remaining)
                (((RHUnkList *)&sequences)->*(Insert)&RHUnkList::insert)(((std::list<RHSequence *> *)&sequences)->end(), (RHSequence *)0);
        }
        sequences.valid = 1;
    }
    for (unsigned i = 0; i < count; ++i)
    {
        if (!file.m_bLoading)
            m_4[i]->Serialize(file, true);
        else
        {
            RHSequence *sequence = (RHSequence *)new RHUnk00582220;
            sequence->Serialize(file, true);
            m_4[i] = sequence;
        }
    }
    if (!file.m_bLoading)
    {
        count = m_28.count;
        if (file.Access(&count, 4) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHsequencemanager.cpp", 405, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        for (unsigned i = 0; i < count; ++i)
        {
            RHSequenceElement *element = m_28[i];
            SerializeSequenceElementPointer(file, &element);
        }
    }
    else
    {
        RHManagerList<RHSequenceElement *> &elements = m_28;
        elements.clear();
        if (file.Access(&count, 4) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHsequencemanager.cpp", 416, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        for (unsigned i = 0; i < count; ++i)
        {
            RHSequenceElement *element;
            SerializeSequenceElementPointer(file, &element);
            elements.push_back(element);
        }
    }
    return true;
}

// FUNCTION: GAME 0x0058ad80
bool RHSequenceManager::PreSerializePointer(SBFile &file, RHOrder **order)
{
    int id;
    if (!file.m_bLoading)
    {
        if (*order == 0)
        {
            id = -1;
            if (file.Access(&id, 4) < 0)
            {
                SBString *error = file.GetError();
                SBAssert(0,
                    // STRING: GAME 0x006b75a8
                    "P:\\Robin Hood\\RHsequencemanager.cpp", 453, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
                return false;
            }
        }
        else if (file.Access(&(*order)->m_34, 4) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHsequencemanager.cpp", 458, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
    }
    else
    {
        if (file.Access(&id, 4) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHsequencemanager.cpp", 463, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        if (id == -1)
        {
            *order = 0;
            return true;
        }
        m_4c.push_back(order);
        m_70.push_back(id);
    }
    return true;
}

// FUNCTION: GAME 0x0058af00
bool RHSequenceManager::PreSerializePointer(SBFile &file, RHSequenceElement **element, bool launch)
{
    int id;
    if (!file.m_bLoading)
    {
        if (*element == 0)
            id = -1;
        else
            id = *(int *)((char *)*element + 8);
        if (file.Access(&id, 4) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHsequencemanager.cpp", 508, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
    }
    else
    {
        if (file.Access(&id, 4) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHsequencemanager.cpp", 512, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        if (id == -1)
        {
            *element = 0;
        }
        else
        {
            m_94.push_back(element);
            m_dc.push_back(id);
            if (launch)
                m_b8.push_back(1);
            else
                m_b8.push_back(0);
        }
    }
    return true;
}

// FUNCTION: GAME 0x0058b110
bool RHSequenceManager::PreSerializePointer(SBFile &file, RHSequence **sequence)
{
    int id;
    if (!file.m_bLoading)
    {
        if (*sequence == 0)
            id = -1;
        else
            id = *(int *)((char *)*sequence + 4);
        if (file.Access(&id, 4) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHsequencemanager.cpp", 566, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
    }
    else
    {
        if (file.Access(&id, 4) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHsequencemanager.cpp", 570, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        if (id == -1)
        {
            *sequence = 0;
            return true;
        }
        m_100.push_back(sequence);
        m_124.push_back(id);
    }
    return true;
}

// Parked: counted begin callee corrected; iterator/frame reconstruction remains non-exact.
// STUB: GAME 0x0058b280
bool RHSequenceManager::SetAllPreSerializedPointers()
{
    unsigned sequences = m_4.count;
    while (m_4c.count > 0)
    {
        RHOrder **destination = m_4c[0];
        int id = m_70[0];
        m_4c.erase(m_4c.begin());
        m_70.erase(m_70.begin());
        bool found = false;
        for (unsigned short i = 0; !found; ++i)
        {
            if (i >= (unsigned short)sequences)
                break;
            RHManagerSequenceView *sequence = (RHManagerSequenceView *)m_4[i];
            unsigned elements = sequence->m_8.count;
            for (unsigned short j = 0; !found; ++j)
            {
                if (j >= (unsigned short)elements)
                    break;
                RHManagerElementView *element = (RHManagerElementView *)sequence->m_8[j];
                unsigned orders = element->m_18.count;
                for (unsigned short k = 0; !found; ++k)
                {
                    if (k >= (unsigned short)orders)
                        break;
                    RHOrder *order = element->m_18[k];
                    if (order->m_34 == id)
                    {
                        *destination = order;
                        found = true;
                    }
                }
            }
        }
        if (!found)
            SBAssert(0, "P:\\Robin Hood\\RHsequencemanager.cpp", 662,
                // STRING: GAME 0x006b76ac
                "Unable to set pre-serialized order pointer (%d).", id);
    }
    while (m_94.count > 0)
    {
        RHSequenceElement **destination = m_94[0];
        int id = m_dc[0];
        m_b8[0];
        m_94.erase(m_94.begin());
        m_dc.erase(m_dc.begin());
        m_b8.erase(m_b8.begin());
        bool found = false;
        for (unsigned short i = 0; !found; ++i)
        {
            if (i >= (unsigned short)sequences)
                break;
            RHManagerSequenceView *sequence = (RHManagerSequenceView *)m_4[i];
            unsigned elements = sequence->m_8.count;
            for (unsigned short j = 0; !found; ++j)
            {
                if (j >= (unsigned short)elements)
                    break;
                RHSequenceElement *element = sequence->m_8[j];
                if (*(int *)((char *)element + 8) == id)
                {
                    *destination = element;
                    found = true;
                }
            }
        }
        if (!found)
            SBAssert(0, "P:\\Robin Hood\\RHsequencemanager.cpp", 713,
                // STRING: GAME 0x006b7670
                "Unable to set pre-serialized sequence element pointer (%d).", id);
    }
    while (m_100.count > 0)
    {
        RHSequence **destination = m_100[0];
        int id = m_124[0];
        m_100.erase(((std::list<RHSequence **> *)&m_100)->begin());
        m_124.erase(((std::list<int> *)&m_124)->begin());
        bool found = false;
        for (unsigned short i = 0; !found; ++i)
        {
            if (i >= (unsigned short)sequences)
                break;
            RHSequence *sequence = m_4[i];
            if (*(int *)((char *)sequence + 4) == id)
            {
                *destination = sequence;
                found = true;
            }
        }
        if (!found)
            SBAssert(0, "P:\\Robin Hood\\RHsequencemanager.cpp", 748,
                // STRING: GAME 0x006b763c
                "Unable to set pre-serialized sequence pointer (%d).", id);
    }
    for (unsigned short i = 0; i < (unsigned short)m_4.count; ++i)
    {
        RHManagerSequenceView *sequence = (RHManagerSequenceView *)m_4[i];
        unsigned short elements = (unsigned short)sequence->m_8.count;
        if (elements > 0)
        {
            RHSequenceElement *previous = sequence->m_8[0];
            for (unsigned short j = 1; j < elements; ++j)
            {
                RHSequenceElement *element = sequence->m_8[j];
                if (*(RHSequenceElement **)((char *)previous + 0x4c) != element)
                {
                    SBAssert(0, "P:\\Robin Hood\\RHsequencemanager.cpp", 771,
                        // STRING: GAME 0x006b7604
                        "Error when loading: Sequence element linkage incorrect");
                    *(RHSequenceElement **)((char *)previous + 0x4c) = element;
                }
                previous = element;
            }
        }
    }
    m_148.clear();
    m_16c.clear();
    ((std::list<RHSequence *> *)&m_190)->clear();
    m_190.valid = 1;
    return true;
}

// Parked: counted begin callee corrected; index registers and scheduling remain non-exact.
// STUB: GAME 0x0058b7c0
bool RHPathSequenceSerializer::FUN_0058b7c0(SBFile &file, void *&value)
{
    RHSequenceManager *manager = (RHSequenceManager *)this;
    RHSequenceElement **element = (RHSequenceElement **)&value;
    int id;
    if (!file.m_bLoading)
    {
        if (*element == 0)
            id = -1;
        else
            id = *(int *)((char *)*element + 8);
        if (file.Access(&id, 4) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHsequencemanager.cpp", 863, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
    }
    else
    {
        if (file.Access(&id, 4) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHsequencemanager.cpp", 867, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        if (id == -1)
        {
            *element = 0;
            return true;
        }
        bool found = false;
        unsigned sequences = manager->m_4.count;
        for (unsigned short i = 0; !found; ++i)
        {
            if (i >= (unsigned short)sequences)
                break;
            RHManagerSequenceView *sequence = (RHManagerSequenceView *)manager->m_4[i];
            unsigned elements = sequence->m_8.count;
            for (unsigned short j = 0; !found; ++j)
            {
                if (j >= (unsigned short)elements)
                    break;
                RHSequenceElement *current = sequence->m_8.Get(j);
                if (*(int *)((char *)current + 8) == id)
                {
                    *element = current;
                    found = true;
                }
            }
        }
        if (!found)
        {
            *element = 0;
            SBAssert(1, "P:\\Robin Hood\\RHsequencemanager.cpp", 904,
                // STRING: GAME 0x006b76e0
                "GENERALMOBILMACHUNG ! Trying to serialize an unknown sequence element !");
            return false;
        }
    }
    return true;
}

void RHSequenceManager::Emit(SBFile &file)
{
    RHOrder *order = 0;
    RHSequenceElement *element = 0;
    RHSequence *sequence = 0;
    Serialize(file);
    PreSerializePointer(file, &order);
    PreSerializePointer(file, &element, false);
    PreSerializePointer(file, &sequence);
    SetAllPreSerializedPointers();
    SerializeSequenceElementPointer(file, &element);
}
