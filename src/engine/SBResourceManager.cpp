#include "SBResourceManager.h"
#include "RHUIRendererPortrait.h"

struct SBResourceUnkIterator
{
    SBResourceUnk00605440Node *m_node;
    SBResourceUnkIterator(SBResourceUnk00605440Node *node) : m_node(node) {}
};

inline SBResourceUnkIterator SBResourceFind(SBResourceUnk00605440 &tree, const unsigned long &key)
{
    SBResourceUnkIterator found(tree.FUN_00605440(key));
    SBResourceUnk00605440Node *head = tree.m_head;
    return (found.m_node != head && key >= found.m_node->m_key
        ? found : SBResourceUnkIterator(head));
}

// FUNCTION: GAME 0x006002d0
unsigned short SBResourceManager::FUN_006002d0(unsigned long id)
{
    SBResourceUnk00605440 &tree = m_64;
    SBResourceUnk00605440Node *found = SBResourceFind(tree, id).m_node;
    if (found == m_64.m_head) {
        if (!FUN_00600db0(id)) {
            SBAssert(0,
                // STRING: GAME 0x006bb368
                "P:\\Robin Hood\\SBLibNG\\SBResourceManager.cpp", 0x525,
                // STRING: GAME 0x006bb508
                "Unable to recover a resource");
            return 0;
        }
        found = SBResourceFind(tree, id).m_node;
    }
    return found->m_18;
}

// FUNCTION: GAME 0x00600390
unsigned short SBResourceManager::FUN_00600390(unsigned long id)
{
    SBResourceUnk00605440 &tree = m_64;
    SBResourceUnk00605440Node *found = SBResourceFind(tree, id).m_node;
    if (found == m_64.m_head) {
        if (!FUN_00600db0(id)) {
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBResourceManager.cpp", 0x544,
                "Unable to recover a resource");
            return 0;
        }
        found = SBResourceFind(tree, id).m_node;
    }
    return found->m_1a;
}

template<class T> struct SBResourceUnkArrayIterator
{
    SBResourceManager::Node<T> *m_node;
    SBResourceUnkArrayIterator(SBResourceManager::Node<T> *node) : m_node(node) {}
};

inline SBResourceUnkArrayIterator<unsigned long> SBResourceFind(
    SBResourceManager::Tree44 &tree, const unsigned long &key)
{
    SBResourceUnkArrayIterator<unsigned long> found(tree.FUN_00605220(key));
    SBResourceManager::Node<unsigned long> *head = tree.m_head;
    return (found.m_node != head && key >= found.m_node->m_key
        ? found : SBResourceUnkArrayIterator<unsigned long>(head));
}

inline SBResourceUnkArrayIterator<SBResourceManager::Element> SBResourceFind(
    SBResourceManager::Tree84 &tree, const unsigned long &key)
{
    SBResourceUnkArrayIterator<SBResourceManager::Element> found(tree.FUN_00605660(key));
    SBResourceManager::Node<SBResourceManager::Element> *head = tree.m_head;
    return (found.m_node != head && key >= found.m_node->m_key
        ? found : SBResourceUnkArrayIterator<SBResourceManager::Element>(head));
}

// FUNCTION: GAME 0x00600550
unsigned int SBResourceManager::FUN_00600550(unsigned long id)
{
    Tree44 &tree = m_44;
    Node<unsigned long> *found = SBResourceFind(tree, id).m_node;
    if (found == m_44.m_head) {
        if (!FUN_00600db0(id)) {
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBResourceManager.cpp", 0x586,
                "Unable to recover a resource");
            return 0;
        }
        found = SBResourceFind(tree, id).m_node;
    }
    if (found->m_first == 0)
        return 0;
    return found->m_last - found->m_first;
}

// FUNCTION: GAME 0x00600620
unsigned int SBResourceManager::FUN_00600620(unsigned long id)
{
    Tree84 &tree = m_84;
    Node<Element> *found = SBResourceFind(tree, id).m_node;
    if (found == m_84.m_head) {
        if (!FUN_00600db0(id)) {
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBResourceManager.cpp", 0x5c6,
                "Unable to recover a resource");
            return 0;
        }
        found = SBResourceFind(tree, id).m_node;
    }
    if (found->m_first == 0)
        return 0;
    return found->m_last - found->m_first;
}

inline SBResourceManager::Tree44::Iterator SBResourceFindWrapped(
    SBResourceManager::Tree44 &tree, const unsigned long &key)
{
    SBResourceManager::Tree44::Iterator found = tree.FUN_00602580(key);
    SBResourceManager::Node<unsigned long> *head = tree.m_head;
    return (found.m_node != head && key >= found.m_node->m_key
        ? found : SBResourceManager::Tree44::Iterator(head));
}

bool RHUnk00600820::ResolveSurface(void *surface, unsigned int indexValue, float *output)
{
    unsigned long &id = *(unsigned long *)&surface;
    int index = indexValue;
    unsigned long &value = *(unsigned long *)output;
    SBResourceManager &view = *(SBResourceManager *)this;
    SBResourceManager::Tree44 &tree = view.m_44;
    SBResourceManager::Node<unsigned long> *found = SBResourceFindWrapped(tree, id).m_node;
    if (found == view.m_44.m_head) {
        if (!view.FUN_00600db0(id)) {
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBResourceManager.cpp", 0x61b,
                "Unable to recover a resource");
            return false;
        }
        found = SBResourceFind(tree, id).m_node;
    }
    int count = found->m_first == 0 ? 0 : found->m_last - found->m_first;
    if (count > index && index >= 0) {
        value = found->m_first[index];
        return true;
    }
    value = 0;
    return false;
}

// FUNCTION: GAME 0x00600920
bool SBResourceManager::FUN_00600920(unsigned long id, unsigned long index, unsigned long &value)
{
    Tree44 &tree = m_44;
    Node<unsigned long> *found = SBResourceFind(tree, id).m_node;
    if (found == m_44.m_head) {
        if (!FUN_00600db0(id)) {
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBResourceManager.cpp", 0x646,
                "Unable to recover a resource");
            return false;
        }
        found = SBResourceFind(tree, id).m_node;
    }
    value = found->m_first[index];
    return true;
}

struct SBResourceUnkRecoveryIterator
{
    SBResourceManager::ResourceNode *m_node;
    SBResourceUnkRecoveryIterator(SBResourceManager::ResourceNode *node) : m_node(node) {}
};

inline SBResourceUnkRecoveryIterator SBResourceFind(
    SBResourceManager::Tree54 &tree, const unsigned long &key)
{
    SBResourceUnkRecoveryIterator found(tree.FUN_00605330(key));
    SBResourceManager::ResourceNode *head = tree.m_head;
    return (found.m_node != head && key >= found.m_node->m_key
        ? found : SBResourceUnkRecoveryIterator(head));
}

// deferred: unannotated pending reccmp #534
bool SBResourceManager::FUN_00600db0(unsigned long id)
{
    Tree54 &tree = m_54;
    ResourceNode *found = SBResourceFind(tree, id).m_node;
    if (found == m_54.m_head) {
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBResourceManager.cpp", 0x6b2,
            // STRING: GAME 0x006bb394
            "Asking to recover a resource with unknow id");
        return false;
    }
    switch (found->m_type) {
    case 0x20434950: return FUN_005fdcc0(0, id);
    case 0x204f4452: return FUN_005ffac0(0, id);
    case 0x20525543: return FUN_005fef60(0, id);
    case 0x43434950: return FUN_005fe000(0, id);
    case 0x44494c53: return FUN_005ff3a0(0, id);
    case 0x4654504e: return FUN_005fd8e0(0, id);
    case 0x4c474f54: return FUN_005ffe50(0, id);
    case 0x4e545442: return FUN_005ff730(0, id);
    case 0x54584554: return FUN_005fe380(0, id);
    }
    return false;
}

inline SBResourceUnkKeyIterator SBResourceFindExternalEnd(
    SBResourceManager::Tree44 &tree, const unsigned long &key)
{
    SBResourceUnkKeyIterator found((SBResourceUnkKeyNode *)tree.FUN_00605220(key));
    SBResourceUnkTreeEnd &view = (SBResourceUnkTreeEnd &)tree;
    return (found.m_node != view.FUN_00617690().m_node && key >= found.m_node->m_key
        ? found : view.FUN_00617690());
}

inline SBResourceUnkKeyIterator SBResourceFindExternalEnd(
    SBResourceManager::Tree74 &tree, const unsigned long &key)
{
    SBResourceUnkKeyIterator found(tree.FUN_00605550(key));
    SBResourceUnkTreeEnd &view = (SBResourceUnkTreeEnd &)tree;
    return (found.m_node != view.FUN_00617690().m_node && key >= found.m_node->m_key
        ? found : view.FUN_00617690());
}

inline SBResourceUnkKeyIterator SBResourceFind(
    SBResourceManager::Tree34 &tree, const unsigned long &key)
{
    SBResourceUnkKeyIterator found(tree.FUN_005093e0(key));
    SBResourceUnkKeyNode *head = tree.m_head;
    return (found.m_node != head && key >= found.m_node->m_key
        ? found : SBResourceUnkKeyIterator(head));
}

// FUNCTION: GAME 0x00600f10
int SBResourceManager::FUN_00600f10(unsigned long id)
{
    Node<unsigned long> *head = m_44.m_head;
    if (SBResourceFindExternalEnd(m_44, id).m_node == (SBResourceUnkKeyNode *)head) {
        SBResourceUnkKeyNode *otherHead = m_34.m_head;
        if (SBResourceFind(m_34, id).m_node == otherHead)
            return 0;
    }
    return 1;
}

// Parked 0x00600fc0: shared bool return width; unannotated to preserve callers.
bool RHMapResources::FUN_00600fc0(unsigned resource)
{
    const unsigned long &id = *(const unsigned long *)&resource;
    SBResourceManager &view = *(SBResourceManager *)this;
    SBResourceUnkKeyNode *head = view.m_74.m_head;
    if (SBResourceFindExternalEnd(view.m_74, id).m_node == head) {
        SBResourceUnkKeyNode *otherHead = view.m_34.m_head;
        if (SBResourceFind(view.m_34, id).m_node == otherHead)
            return false;
    }
    return true;
}

void EmitSBResourceManager(SBResourceManager *resource)
{
    resource->FUN_006002d0(0);
    resource->FUN_00600390(0);
    resource->FUN_00600550(0);
    resource->FUN_00600620(0);
    unsigned long value;
    ((RHUnk00600820 *)resource)->ResolveSurface(0, 0, (float *)&value);
    resource->FUN_00600920(0, 0, value);
    resource->FUN_00600f10(0);
    ((RHMapResources *)resource)->FUN_00600fc0(0);
}
