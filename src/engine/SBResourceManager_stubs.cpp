#include "SBNullstr.h"
#include "SBResourceManager.h"

void FUN_0064158f(void *) {}

SBResourceManager::ResourceNode *&SBResourceManager::Tree54::FUN_00601650(ResourceNode *&result, const unsigned long &key)
{
    ResourceNode *node = FUN_00605330(key);
    result = node != m_head && key >= node->m_key ? node : m_head;
    return result;
}

SBResourceManager::Tree44::Iterator &SBResourceManager::Tree44::FUN_006013a0(Iterator &result, const unsigned long &key)
{
    Node<unsigned long> *node = FUN_00605220(key);
    result.m_node = node != m_head && key >= node->m_key ? node : m_head;
    return result;
}

SBResourceUnkKeyNode *&SBResourceManager::Tree74::FUN_00601bd0(SBResourceUnkKeyNode *&result, const unsigned long &key)
{
    SBResourceUnkKeyNode *node = FUN_00605550(key);
    result = node != m_head && key >= node->m_key ? node : m_head;
    return result;
}

SBResourceUnkKeyNode *&SBResourceManager::Tree74::FUN_006042a0(SBResourceUnkKeyNode *&result, const unsigned long &key)
{
    result = FUN_00605550(key);
    return result;
}

SBResourceManager::Node<unsigned long> *SBResourceManager::Tree44::FUN_00605770(const unsigned long &) { return 0; }
SBResourceManager::Tree44::Iterator &SBResourceManager::Tree44::FUN_00601210(Iterator &result, Node<unsigned long> *, Node<unsigned long> *) { return result; }
void SBResourceManager::FUN_006001d0(Tree44::Iterator &) {}

class SBResourceUnkAdvance
{
public:
    SBResourceManager::Tree44::Iterator m_value;
    void FUN_006057c0();
};

void SBResourceUnkAdvance::FUN_006057c0() {}

SBResourceManager::Node<SBResourceManager::Element> *&SBResourceManager::Tree84::FUN_00604d30(Node<Element> *&result, const unsigned long &key)
{
    result = FUN_00605660(key);
    return result;
}

SBResourceManager::Tree44::Iterator &SBResourceManager::Tree44::FUN_00602580(Iterator &result, const unsigned long &key)
{
    result.m_node = FUN_00605220(key);
    return result;
}

SBResourceManager::Node<unsigned long> *SBResourceManager::Tree44::FUN_00605220(const unsigned long &)
{
    return 0;
}

SBResourceUnk00605440Node *SBResourceUnk00605440::FUN_00605440(const unsigned long &)
{
    return 0;
}

SBResourceManager::Node<SBResourceManager::Element> *SBResourceManager::Tree84::FUN_00605660(const unsigned long &)
{
    return 0;
}

SBResourceManager::ResourceNode *SBResourceManager::Tree54::FUN_00605330(const unsigned long &)
{
    return 0;
}

bool SBResourceManager::FUN_005fd8e0(int, unsigned long) { return false; }
bool SBResourceManager::FUN_005fdcc0(int, unsigned long) { return false; }
bool SBResourceManager::FUN_005fe000(int, unsigned long) { return false; }
bool SBResourceManager::FUN_005fe380(int, unsigned long) { return false; }
bool SBResourceManager::FUN_005fe970(int, unsigned long) { return false; }
bool SBResourceManager::FUN_005fef60(int, unsigned long) { return false; }
bool SBResourceManager::FUN_005ff3a0(int, unsigned long) { return false; }
bool SBResourceManager::FUN_005ff730(int, unsigned long) { return false; }
bool SBResourceManager::FUN_005ffac0(int, unsigned long) { return false; }
bool SBResourceManager::FUN_005ffe50(int, unsigned long) { return false; }

SBResourceUnkKeyNode *SBResourceManager::Tree34::FUN_005093e0(const unsigned long &)
{
    return 0;
}

SBResourceUnkKeyNode *SBResourceManager::Tree74::FUN_00605550(const unsigned long &)
{
    return 0;
}

// FUNCTION: GAME 0x00617690
SBResourceUnkKeyIterator SBResourceUnkTreeEnd::FUN_00617690()
{
    return SBResourceUnkKeyIterator(m_head);
}

#include <vector>

void ForceWideRangeInsert(std::vector<std::wstring> &values, std::wstring *position,
                          const std::wstring *first, const std::wstring *last)
{
    typedef void (std::vector<std::wstring>::*Insert)(std::wstring *, const std::wstring *, const std::wstring *);
    Insert insert = &std::vector<std::wstring>::insert;
    (values.*insert)(position, first, last);
}

// TEMPLATE: GAME 0x00607660
// ?insert@?$vector@V?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@V?$allocator@V?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@@2@@std@@QAEXPAV?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@2@PBV32@1@Z
