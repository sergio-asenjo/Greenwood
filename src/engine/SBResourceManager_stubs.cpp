#include "SBNullstr.h"
#include "SBResourceManager.h"
#include "Decomp.h"

DECOMP_SIZE_ASSERT(SBResourceArrayLifecycle84, 0x2c)

void FUN_0064158f(void *) {}

template class SBResourceTreeStorage<0x34, 0x30, 0x44>;
template class SBResourceTreeStorage<0x20, 0x1c, 0x54>;
template class SBResourceTreeStorage<0x20, 0x1c, 0x64>;
template class SBResourceTreeStorage<0x40, 0x3c, 0x74>;
template class SBResourceTreeStorage<0x40, 0x3c, 0x84>;


// FUNCTION: GAME 0x0051d120
void SBResourceArrayLifecycle44::FUN_0051d120()
{
    typedef std::vector<unsigned long> Values;
    Values *values = (Values *)this;
    values->erase(values->begin(), values->end());
    values->~Values();
}
// STUB: GAME 0x0057c820
SBResourceArrayLifecycle84::~SBResourceArrayLifecycle84()
{
    m_values.clear();
}

bool SBResourceManager::FUN_005fdcc0(int, unsigned long) { return false; }
bool SBResourceManager::FUN_005fe000(int, unsigned long) { return false; }
bool SBResourceManager::FUN_005fe380(int, unsigned long) { return false; }
bool SBResourceManager::FUN_005fe970(int, unsigned long) { return false; }
bool SBResourceManager::FUN_005fef60(int, unsigned long) { return false; }



#include <vector>

void ForceWideRangeInsert(std::vector<std::wstring> &values, std::wstring *position,
                          const std::wstring *first, const std::wstring *last)
{
    typedef void (std::vector<std::wstring>::*Insert)(std::wstring *, const std::wstring *, const std::wstring *);
    Insert insert = &std::vector<std::wstring>::insert;
    (values.*insert)(position, first, last);
}

void ForceNarrowRangeInsert(std::vector<std::string> &values, std::string *position,
                           const std::string *first, const std::string *last)
{
    typedef void (std::vector<std::string>::*Insert)(std::string *, const std::string *, const std::string *);
    Insert insert = &std::vector<std::string>::insert;
    (values.*insert)(position, first, last);
}

void ForceResourceWideResize(std::vector<std::wstring> &values, unsigned int count, const std::wstring &value)
{
    void (std::vector<std::wstring>::*resize)(unsigned int, const std::wstring &) = &std::vector<std::wstring>::resize;
    (values.*resize)(count, value);
}

void ForceResourceWideErase(std::vector<std::wstring> &values, std::wstring *first, std::wstring *last)
{
    std::wstring *(std::vector<std::wstring>::*erase)(std::wstring *, std::wstring *) = &std::vector<std::wstring>::erase;
    (values.*erase)(first, last);
}

// Parked: the original reuses the separately owned 16-byte-element vector size entity.
// LIBRARY: GAME 0x00606270
// ?resize@?$vector@V?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@V?$allocator@V?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@@2@@std@@QAEXIABV?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@2@@Z

// LIBRARY: GAME 0x00606470
// ?erase@?$vector@V?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@V?$allocator@V?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@@2@@std@@QAEPAV?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@2@PAV32@0@Z

// FUNCTION: GAME 0x00606780
std::wstring *FUN_00606780(const std::wstring *first, const std::wstring *last, std::wstring *output)
{
    for (; first != last; ++first, ++output)
        *output = *first;
    return output;
}

// Parked: static-CRT npos loads fold to immediate -1 in narrow-string assignment.
// LIBRARY: GAME 0x006073b0
// ?insert@?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@QAEXPAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@PBV32@1@Z

// LIBRARY: GAME 0x00607660
// ?insert@?$vector@V?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@V?$allocator@V?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@@2@@std@@QAEXPAV?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@2@PBV32@1@Z

// FUNCTION: GAME 0x00617690
SBResourceUnkKeyIterator SBResourceUnkTreeEnd::FUN_00617690()
{
    return SBResourceUnkKeyIterator(m_head);
}
