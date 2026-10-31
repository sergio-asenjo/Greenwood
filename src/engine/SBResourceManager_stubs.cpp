#include "SBNullstr.h"
#include "SBResourceManager.h"
#include "Decomp.h"

extern template class std::basic_string<char>;

// TEMPLATE: GAME 0x00634bb0 FOLDED
// ??1?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAE@XZ

DECOMP_SIZE_ASSERT(SBResourceArrayLifecycle84, 0x2c)
DECOMP_SIZE_ASSERT(SBResourceArrayLifecycle74, 0x2c)
DECOMP_SIZE_ASSERT(SBResourceUnk005fe790, 0x30)
DECOMP_SIZE_ASSERT(SBResourceUnk005fe880, 0x30)
DECOMP_SIZE_ASSERT(SBResourceUnk005fed80, 0x30)
DECOMP_SIZE_ASSERT(SBResourceUnk005fee70, 0x30)
DECOMP_STATIC_ASSERT(offsetof(SBResourceUnk005fe790, m_value) == 4)
DECOMP_STATIC_ASSERT(offsetof(SBResourceUnk005fe880, m_value) == 4)

template class SBResourceTreeStorage<0x34, 0x30, 0x44>;
template class SBResourceTreeStorage<0x20, 0x1c, 0x54>;
template class SBResourceTreeStorage<0x20, 0x1c, 0x64>;
template class SBResourceTreeStorage<0x40, 0x3c, 0x74>;
template class SBResourceTreeStorage<0x40, 0x3c, 0x84>;


// TEMPLATE: GAME 0x0051d120 FOLDED
// ?FUN_0051d120@SBResourceArrayLifecycle44@@QAEXXZ
void SBResourceArrayLifecycle44::FUN_0051d120()
{
    typedef std::vector<unsigned long> Values;
    Values *values = (Values *)this;
    values->erase(values->begin(), values->end());
    values->~Values();
}
#include "SBResourceTextArrayLifetime.h"

// FUNCTION: GAME 0x005fe790
SBResourceUnk005fe790::~SBResourceUnk005fe790()
{
}

// FUNCTION: GAME 0x005fe880
SBResourceUnk005fe880::~SBResourceUnk005fe880()
{
}

void EmitResourceWideArrayDestruction(SBResourceArrayLifecycle74 *values)
{
    delete[] values;
}

// FUNCTION: GAME 0x005fed80
SBResourceUnk005fed80::~SBResourceUnk005fed80()
{
}

// FUNCTION: GAME 0x005fee70
SBResourceUnk005fee70::~SBResourceUnk005fee70()
{
}

void EmitResourceNarrowArrayDestruction(SBResourceArrayLifecycle84 *values)
{
    delete[] values;
}

bool SBResourceManager::FUN_005fdcc0(int, unsigned long) { return false; }
bool SBResourceManager::FUN_005fe000(int, unsigned long) { return false; }
bool SBResourceManager::FUN_005fe380(int, unsigned long) { return false; }
bool SBResourceManager::FUN_005fe970(int, unsigned long) { return false; }
bool SBResourceManager::FUN_005fef60(int, unsigned long) { return false; }



#include <vector>

// TEMPLATE: GAME 0x005b1ba0
// ?clear@?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@QAEXXZ
template class std::vector<std::string>;

// TEMPLATE: GAME 0x00606070
// ?resize@?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@QAEXIABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z

// TEMPLATE: GAME 0x0045a490 FOLDED
// ?size@?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@QBEIXZ

// TEMPLATE: GAME 0x0056dac0 FOLDED
// ?_Destroy@?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@IAEXPAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@0@Z

void ForceResourceNarrowResize(std::vector<std::string> &values, unsigned int count, const std::string &value)
{
    void (std::vector<std::string>::*resize)(unsigned int, const std::string &) = &std::vector<std::string>::resize;
    (values.*resize)(count, value);
}

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
