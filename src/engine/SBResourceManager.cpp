#include "SBNullstr.h"
#include "SBResourceManager.h"
#include "RHUIRendererPortrait.h"
#include "RHSaveGame.h"
#include <list>
#include "SBUIRenderer.h"

struct SBResourceUnkIterator
{
    SBResourceUnk00605440Node *m_node;
    SBResourceUnkIterator(SBResourceUnk00605440Node *node) : m_node(node) {}
};

class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    ~SBGeoPoint2D();
    float m_x;
    float m_y;
};

class FUN_005ff390
{
public:
    SBGeoPoint2D m_point;
    FUN_005ff390();
};

class SBResourceUnk005fdc70
{
public:
    char m_00[8];
    unsigned long *m_first;
    unsigned long *m_last;
    unsigned long *m_end;
    void FUN_005fdc70();
};

void FUN_0064158f(void *);

class RHUnkFXDraw
{
public:
    unsigned short FUN_005e56c0(unsigned long);
    unsigned short FUN_005e5750(unsigned long);
};

class RHFrameHolderRowMap
{
public:
    struct Node;
    struct Iterator
    {
        Iterator() {}
        Iterator(Node *node) : m_node(node) {}
        Node *m_node;
    };
    typedef std::pair<Iterator, bool> TreePair;
    struct Value
    {
        unsigned long first;
        unsigned long second;
        Value(const unsigned long &key, const unsigned long &value) : first(key), second(value) {}
    };
    TreePair InsertTree(const Value &);
};

class RHUnk005fd5c0
{
public:
    bool FUN_005fd5c0(const std::string &);
};

class SBResourceUnkAdvance
{
public:
    SBResourceManager::Tree44::Iterator m_value;
    void FUN_006057c0();
};

// FUNCTION: GAME 0x005fd4a0
void SBUIUnk005fd4a0::FUN_005fd4a0(long resource)
{
    if (resource == -1)
        return;
    unsigned long &id = *(unsigned long *)&resource;
    SBResourceManager &view = *(SBResourceManager *)this;
    SBResourceManager::ResourceNode *found;
    {
        SBResourceManager::ResourceNode *storage;
        found = view.m_54.FUN_00601650(storage, id);
    }
    if (found == view.m_54.m_head) {
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBResourceManager.cpp", 0x51,
            "Asking to recover a resource with unknow id");
        return;
    }
    switch (found->m_type) {
    case 0x20434950:
    case 0x43434950:
    case 0x4654504e:
    case 0x4c474f54:
    case 0x4e545442:
        {
            SBResourceManager::Tree44 &tree = view.m_44;
            SBResourceManager::Tree44::Iterator candidate(tree.FUN_00605220(id));
            SBResourceManager::Tree44::Iterator iterator = candidate.m_node != tree.m_head && id >= candidate.m_node->m_key
                ? candidate : SBResourceManager::Tree44::Iterator(tree.m_head);
            if (iterator.m_node != view.m_44.m_head) {
                view.FUN_006001d0(iterator);
                SBResourceManager::Node<unsigned long> *last = tree.FUN_00605770(id);
                SBResourceManager::Node<unsigned long> *first = tree.FUN_00605220(id);
                SBResourceManager::Tree44::Iterator current(first);
                while (current.m_node != last)
                    ((SBResourceUnkAdvance *)&current)->FUN_006057c0();
                SBResourceManager::Tree44::Iterator result;
                tree.FUN_00601210(result, first, last);
            }
        }
    }
}

// FUNCTION: GAME 0x005fd5c0
bool RHUnk005fd5c0::FUN_005fd5c0(const std::string &name)
{
    SBResourceManager &view = *(SBResourceManager *)this;
    RHUnk005f4fc0 *file = new RHUnk005f4fc0;
    if (file->FUN_005f5090(name, 1) != 0)
        return false;
    unsigned long type;
    file->Access(&type, 4);
    file->Access(&file->m_version, 4);
    unsigned long version = file->m_version;
    if (type != 0x53455253) {
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBResourceManager.cpp", 0x90,
            // STRING: GAME 0x006bb3ec
            "Tried to add a file which is not a resource to the resource manager");
        return false;
    }
    if (version != 0x100) {
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBResourceManager.cpp", 0xa0,
            // STRING: GAME 0x006bb3c0
            "Unsupported version of the resource file");
        return false;
    }
    if (view.FUN_005fd710(*file) != true)
        return false;
    ((std::list<RHUnk005f4fc0 *> *)((char *)this + 0x10))->push_front(file);
    *(char *)((char *)this + 0x20) = 1;
    return true;
}

// Parked: pair-temporary stores and assert argument register scheduling differ.
// STUB: GAME 0x005fd710
bool SBResourceManager::FUN_005fd710(SBFile &file)
{
    unsigned long count;
    unsigned long type;
    file.Access(&count, 4);
    unsigned long zero = 0;
    for (unsigned long index = 0; index < count; ++index) {
        file.Access(&type, 4);
        unsigned long &id = *(unsigned long *)((char *)this + 0xc);
        file.Access(&id, 4);
        RHFrameHolderRowMap::Value value(id, zero);
        ((RHFrameHolderRowMap *)&m_34)->InsertTree(value);
        switch (type) {
        case 0x20434950: if (!FUN_005fdcc0((int)&file, zero)) return false; break;
        case 0x204f4452: if (!FUN_005ffac0((int)&file, zero)) return false; break;
        case 0x20525543: if (!FUN_005fef60((int)&file, zero)) return false; break;
        case 0x43434950: if (!FUN_005fe000((int)&file, zero)) return false; break;
        case 0x44494c53: if (!FUN_005ff3a0((int)&file, zero)) return false; break;
        case 0x45564157: if (!FUN_005fe970((int)&file, zero)) return false; break;
        case 0x4654504e: if (!FUN_005fd8e0((int)&file, zero)) return false; break;
        case 0x4c474f54: if (!FUN_005ffe50((int)&file, zero)) return false; break;
        case 0x4e545442: if (!FUN_005ff730((int)&file, zero)) return false; break;
        case 0x54584554: if (!FUN_005fe380((int)&file, zero)) return false; break;
        default:
            char name[6];
            *(unsigned long *)name = type;
            name[5] = 0;
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBResourceManager.cpp", 0x125,
                // STRING: GAME 0x006bb430
                "Unsupported resource type in resource file (%s)", name);
            return false;
        }
    }
    return true;
}

#include <vector>

class SBResourceUnk005fed80
{
public:
    char m_00[4];
    std::vector<std::string> m_values;
    char m_14[0xc];
    std::string m_text;
    void FUN_005fed80();
};

class SBResourceUnk005fee70
{
public:
    char m_00[4];
    std::vector<std::string> m_values;
    char m_14[0xc];
    std::string m_text;
    void FUN_005fee70();
};

// Parked: the target's 0x0064158f deallocation call has no local resolvable entity in this assignment.
// STUB: GAME 0x005fdc70
void SBResourceUnk005fdc70::FUN_005fdc70()
{
    unsigned long *source = m_last;
    unsigned long *end = m_last;
    unsigned long *destination = m_first;
    for (; source != end; ++source, ++destination)
        *destination = *source;
    m_last = destination;
    FUN_0064158f(m_first);
    m_first = 0;
    m_last = 0;
    m_end = 0;
}

// Parked: target EH, iterator scheduling, and the static-CRT npos data load differ from this source shape.
// STUB: GAME 0x005fed80
void SBResourceUnk005fed80::FUN_005fed80()
{
    typedef std::string String;
    m_values.clear();
    m_text.~String();
    m_values.~vector();
}

// Parked: target EH, iterator scheduling, and the static-CRT npos data load differ from this source shape.
// STUB: GAME 0x005fee70
void SBResourceUnk005fee70::FUN_005fee70()
{
    typedef std::string String;
    m_values.clear();
    m_text.~String();
    m_values.~vector();
}

// FUNCTION: GAME 0x005ff390
FUN_005ff390::FUN_005ff390()
{
}

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

// Parked: anonymous static-destructor callback cannot be uniquely annotation-bound.
// STUB: GAME 0x00600450
const SBGeoPoint2D &SBResourceManager::FUN_00600450(unsigned long id)
{
    // GLOBAL: GAME 0x006c1848
    static SBGeoPoint2D pointDummy;
    SBResourceUnk00605440 &tree = m_64;
    SBResourceUnk00605440Node *found = SBResourceFind(tree, id).m_node;
    if (found == m_64.m_head) {
        if (!FUN_00600db0(id)) {
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBResourceManager.cpp", 0x565,
                "Unable to recover a resource");
            return pointDummy;
        }
        found = SBResourceFind(tree, id).m_node;
    }
    return *(SBGeoPoint2D *)((char *)found + 0x10);
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

// Parked: receiver/index register allocation differs despite matching frame and x87 comparisons.
// STUB: GAME 0x006006f0
bool SBUIUnk006006f0::FUN_006006f0(long resource, RHUnk005fc3b0 &output)
{
    bool valid = false;
    unsigned long &id = *(unsigned long *)&resource;
    SBResourceManager &view = *(SBResourceManager *)this;
    SBResourceManager::Tree44 &tree = view.m_44;
    SBResourceManager::Tree44::Iterator storage;
    SBResourceManager::Node<unsigned long> *found = tree.FUN_006013a0(storage, id).m_node;
    if (found == view.m_44.m_head) {
        if (!view.FUN_00600db0(id)) {
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBResourceManager.cpp", 0x5eb,
                "Unable to recover a resource");
            return false;
        }
        SBResourceManager::Tree44::Iterator recoveryStorage;
        found = tree.FUN_006013a0(recoveryStorage, id).m_node;
    }
    unsigned int count = found->m_first == 0 ? 0 : found->m_last - found->m_first;
    SBGeoPoint2D &size = *(SBGeoPoint2D *)&output;
    size.m_x = 0;
    size.m_y = 0;
    for (unsigned int index = 0; index < count; ++index) {
        unsigned long surface = found->m_first[index];
        if (surface) {
            unsigned short width = (*(RHUnkFXDraw **)((char *)this + 4))->FUN_005e56c0(surface);
            unsigned short height = (*(RHUnkFXDraw **)((char *)this + 4))->FUN_005e5750(found->m_first[index]);
            if (width > *(volatile float *)&size.m_x)
                size.m_x = width;
            if (height > *(volatile float *)&size.m_y)
                size.m_y = height;
            valid = true;
        }
    }
    return valid;
}

inline SBResourceManager::Tree44::Iterator SBResourceFindWrapped(
    SBResourceManager::Tree44 &tree, const unsigned long &key)
{
    SBResourceManager::Tree44::Iterator storage;
    SBResourceManager::Tree44::Iterator found = tree.FUN_00602580(storage, key);
    SBResourceManager::Node<unsigned long> *head = tree.m_head;
    return (found.m_node != head && key >= found.m_node->m_key
        ? found : SBResourceManager::Tree44::Iterator(head));
}

// Unannotated: counted callers use a different shared entity in an unassigned TU.
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
    unsigned long *first = *(unsigned long *volatile *)&found->m_first;
    int count = first == 0 ? 0 : found->m_last - first;
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

// Parked: wide-string assignment inlines _Tidy and character copying unlike the target.
// STUB: GAME 0x006009e0
bool RHMapResources::FUN_006009e0(unsigned resource, unsigned index, RHMapWideText &output)
{
    const unsigned long &id = *(const unsigned long *)&resource;
    SBResourceManager &view = *(SBResourceManager *)this;
    SBResourceManager::Tree74 &tree = view.m_74;
    SBResourceUnkKeyNode *storage;
    SBResourceUnkKeyNode *found = tree.FUN_00601bd0(storage, id);
    if (found == view.m_74.m_head) {
        if (!view.FUN_00600db0(id)) {
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBResourceManager.cpp", 0x668,
                "Unable to recover a resource");
            return false;
        }
        SBResourceUnkKeyNode *recoveryStorage;
        SBResourceUnkKeyIterator candidate(tree.FUN_006042a0(recoveryStorage, id));
        found = (candidate.m_node != tree.m_head && id >= candidate.m_node->m_key
            ? candidate : SBResourceUnkKeyIterator(tree.m_head)).m_node;
    }
    SBResourceManager::Node<std::wstring> *node = (SBResourceManager::Node<std::wstring> *)found;
    std::wstring *first = *(std::wstring *volatile *)&node->m_first;
    if (first == 0 || index >= (unsigned int)(node->m_last - first))
        return false;
    ((std::wstring &)output).assign(node->m_first[index]);
    return true;
}

class RHProfileText
{
public:
    bool FUN_00402280(unsigned int, bool);
    void FUN_00402260(unsigned int);
};

class RHSoundCacheString
{
public:
    void FUN_00402780();
};

class SBResourceString
{
public:
    char m_allocator;
    char *_Ptr;
    unsigned int _Len;
    unsigned int _Res;
    unsigned int size() const { return _Len; }
    unsigned int capacity() const { return _Res; }
    const char *c_str() const { return _Ptr == 0 ? "" : _Ptr; }
    __forceinline void Release()
    {
        if (_Ptr != 0) {
            unsigned char references = (unsigned char)_Ptr[-1];
            if (references != 0 && references != 255)
                --_Ptr[-1];
            else
                operator delete(_Ptr - 1);
        }
        _Ptr = 0;
        _Len = 0;
        _Res = 0;
    }
    __forceinline SBResourceString &Erase(unsigned int position, unsigned int count)
    {
        if (_Len < position)
            std::_Xran();
        ((RHSoundCacheString *)this)->FUN_00402780();
        unsigned int available = _Len - position;
        if (available < count)
            count = available;
        if (count > 0) {
            memmove(_Ptr + position, _Ptr + position + count, available - count);
            unsigned int length = _Len - count;
            if (((RHProfileText *)this)->FUN_00402280(length, false))
                ((RHProfileText *)this)->FUN_00402260(length);
        }
        return *this;
    }
    __forceinline SBResourceString &Assign(const SBResourceString &value, unsigned int position, unsigned int count)
    {
        if (value.size() < position)
            std::_Xran();
        unsigned int length = value.size() - position;
        if (count < length)
            length = count;
        if (this == &value) {
            Erase(position + length, std::string::npos);
            typedef std::string &(std::string::*EraseMember)(unsigned int, unsigned int);
            EraseMember erase = &std::string::erase;
            (((std::string *)this)->*erase)(0, position);
        } else if (length > 0 && length == value.size() && (unsigned char)value.c_str()[-1] < 254) {
            Release();
            _Ptr = (char *)value.c_str();
            _Len = value.size();
            _Res = value.capacity();
            ++_Ptr[-1];
        } else if (((RHProfileText *)this)->FUN_00402280(length, true)) {
            memcpy(_Ptr, value.c_str() + position, length);
            ((RHProfileText *)this)->FUN_00402260(length);
        }
        return *this;
    }
};

// FUNCTION: GAME 0x00600bb0
bool RHMapResources::FUN_00600bb0(unsigned long id, unsigned int index, std::string &output)
{
    SBResourceManager &view = *(SBResourceManager *)this;
    SBResourceManager::Tree84 &tree = view.m_84;
    SBResourceManager::Node<SBResourceManager::Element> *storage;
    SBResourceUnkArrayIterator<SBResourceManager::Element> candidate(tree.FUN_00604d30(storage, id));
    SBResourceManager::Node<SBResourceManager::Element> *found = (candidate.m_node != tree.m_head && id >= candidate.m_node->m_key
        ? candidate : SBResourceUnkArrayIterator<SBResourceManager::Element>(tree.m_head)).m_node;
    if (found == view.m_84.m_head) {
        if (!view.FUN_00600db0(id)) {
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBResourceManager.cpp", 0x692,
                "Unable to recover a resource");
            return false;
        }
        found = SBResourceFind(tree, id).m_node;
    }
    ((SBResourceString &)output).Assign(((SBResourceString *)found->m_first)[index], 0, std::string::npos);
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

// FUNCTION: GAME 0x00600db0
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

// FUNCTION: GAME 0x00600fc0
bool RHMapResources::FUN_00600fc0(unsigned resource)
{
    const unsigned long &id = *(const unsigned long *)&resource;
    SBResourceManager &view = *(SBResourceManager *)this;
    SBResourceUnkKeyNode *head = view.m_74.m_head;
    SBResourceUnkKeyNode *otherHead;
    return SBResourceFindExternalEnd(view.m_74, id).m_node != head
        || (otherHead = view.m_34.m_head, SBResourceFind(view.m_34, id).m_node != otherHead);
}

void EmitSBResourceManager(SBResourceManager *resource)
{
    ((RHUnk005fd5c0 *)resource)->FUN_005fd5c0(std::string());
    resource->FUN_005fd710(*(SBFile *)0);
    resource->FUN_006002d0(0);
    resource->FUN_00600390(0);
    resource->FUN_00600450(0);
    resource->FUN_00600550(0);
    resource->FUN_00600620(0);
    unsigned long value;
    ((RHUnk00600820 *)resource)->ResolveSurface(0, 0, (float *)&value);
    resource->FUN_00600920(0, 0, value);
    resource->FUN_00600f10(0);
    ((RHMapResources *)resource)->FUN_00600fc0(0);
}
