#ifndef RHPLAYERPROFILEMANAGER_H
#define RHPLAYERPROFILEMANAGER_H

#include "Decomp.h"
#include "SBListCursor.h"
#include <string>

// SIZE 0x24
class RHPlayerProfileList : public RHProfileListCursor
{
public:
    undefined m_18[0xc]; // [0x18, 0x24)

    __forceinline std::list<RHPlayerProfile *>::iterator &SetCurrent(std::list<RHPlayerProfile *>::iterator position)
    {
        m_current = position;
        return m_current;
    }
    void RemoveAll();
    void DeleteAt(int index);
    __forceinline RHPlayerProfile *Current() const { return *m_current; }
    RHPlayerProfile *At(int index)
    {
        int count = size();
        if (m_dirty)
        {
            if (index <= (count + 1) / 2)
            {
                m_current = begin();
                std::bidirectional_iterator_tag category;
                RHAdvanceProfileCursor(m_current, index, category);
            }
            else
            {
                m_current = end();
                std::bidirectional_iterator_tag category;
                RHAdvanceProfileCursor(m_current, index - count, category);
            }
            m_dirty = false;
            m_index = index;
        }
        else
        {
            int previous = m_index;
            if (index != previous)
            {
                if (index < previous)
                {
                    if (index < (previous + 1) / 2)
                    {
                        m_current = begin();
                        std::bidirectional_iterator_tag category;
                        RHAdvanceProfileCursor(m_current, index, category);
                    }
                    else
                    {
                        int distance = index - previous;
                        std::bidirectional_iterator_tag category;
                        RHAdvanceProfileCursor(m_current, distance, category);
                    }
                }
                else
                {
                    if (index < (previous + count) / 2)
                    {
                        int distance = index;
                        RHProfilePointerList::iterator &current = m_current;
                        distance -= previous;
                        std::bidirectional_iterator_tag category;
                        RHAdvanceProfileCursor(current, distance, category);
                    }
                    else
                    {
                        m_current = end();
                        std::advance(m_current, index - count);
                    }
                }
                m_index = index;
            }
        }
        return Current();
    }
    __forceinline RHPlayerProfile *&GetProfile(int index)
    {
        GoTo(index);
        return *m_current;
    }
    RHPlayerProfile *Lookup(int index)
    {
        bool dirty = m_dirty;
        int count = size();
        if (dirty)
        {
            if (index <= (count + 1) / 2)
            {
                std::bidirectional_iterator_tag category;
                {
                    std::list<RHPlayerProfile *>::iterator first = begin();
                    RHAdvanceProfileCursor(SetCurrent(first), index, category);
                }
            }
            else
            {
                std::bidirectional_iterator_tag category;
                {
                    std::list<RHPlayerProfile *>::iterator last = end();
                    RHAdvanceProfileCursor(SetCurrent(last), index - count, category);
                }
            }
            m_dirty = false;
            m_index = index;
        }
        else
        {
            int previous = m_index;
            if (index != previous)
            {
                if (index < previous)
                {
                    if (index < (previous + 1) / 2)
                    {
                        std::bidirectional_iterator_tag category;
                        {
                            std::list<RHPlayerProfile *>::iterator first = begin();
                            RHAdvanceProfileCursor(SetCurrent(first), index, category);
                        }
                    }
                    else
                    {
                        int distance = index - previous;
                        std::bidirectional_iterator_tag category;
                        RHAdvanceProfileCursor(m_current, distance, category);
                    }
                }
                else
                {
                    if (index < (previous + count) / 2)
                    {
                        std::advance(m_current, index - previous);
                    }
                    else
                    {
                        m_current = end();
                        std::advance(m_current, index - count);
                    }
                }
                m_index = index;
            }
        }
        return Current();
    }
    __forceinline RHPlayerProfile *operator[](int index) { return Lookup(index); }
};

// SIZE 0x30
class RHPlayerProfileManager
{
public:
    RHPlayerProfileManager();
    RHPlayerProfile *AddProfile(const std::wstring &name, unsigned long difficulty);
    bool Load();
    bool Save() const;
    bool FUN_0055d830();
    static const std::string &GetProfilesDirectory();
    static RHPlayerProfileManager *FUN_0052ef90();
    void FUN_0055d930(unsigned long index);
    bool FUN_0055da70(RHPlayerProfile *profile);
    int FUN_0055dbc0(RHPlayerProfile *profile);
    RHPlayerProfile *FUN_0055dd10(unsigned long index);
    void FUN_0055e410(unsigned long index);
    void FUN_0055e550(RHPlayerProfile *profile);
    void Emit();

    unsigned long m_00; // +0x00: four-byte archive field
    mutable RHPlayerProfileList m_profiles; // +0x04: head +0x08, count +0x0c, cursor +0x10
    RHPlayerProfile *m_active; // +0x28
    bool m_2c; // 0x2c
};

#endif
