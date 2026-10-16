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
    SBGeoPoint2D(const SBGeoPoint2D &);
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

struct SBResourceMouseValue
{
    SBGeoPoint2D m_point;
    unsigned short m_flags;
    unsigned short m_frameLength;
};

typedef std::pair<const unsigned long, SBResourceMouseValue> SBResourceMousePair;
void SBResourceConstructMouse(SBResourceMousePair *, const SBResourceMousePair &);

struct RHUnk00571160Position;
class RHScriptPositionList
{
public:
    static void Unk00588190(RHUnk00571160Position *, const RHUnk00571160Position *);
};

void SBResourceConstructArray44(unsigned long *, const unsigned long &);
void SBResourceConstructArray74(unsigned long *, const unsigned long &);
void SBResourceConstructArray84(unsigned long *, const unsigned long &);

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

struct SBResourceTreeLinks;

class SBResourceTreeIterator54
{
public:
    SBResourceTreeLinks *m_node;
    void FUN_00605870();
};

class SBResourceTreeIterator64
{
public:
    SBResourceTreeLinks *m_node;
    void FUN_00605920();
};

class SBResourceUnkAdvance
{
public:
    SBResourceTreeLinks *m_node;
    void FUN_006057c0();
};

class SBResourceTreeIterator74
{
public:
    SBResourceTreeLinks *m_node;
    void FUN_00605a20();
};

class SBResourceTreeIterator84
{
public:
    SBResourceTreeLinks *m_node;
    void FUN_00605b20();
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
        found = view.m_54.FUN_00601650(id).m_node;
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

struct SBResourceWideString : std::wstring {};

class SBResourceUnk005fed80
{
public:
    char m_00[4];
    std::vector<std::string> m_values;
    char m_14[0xc];
    std::string m_text;
    ~SBResourceUnk005fed80();
};

class SBResourceUnk005fe790
{
public:
    char m_00[4];
    std::vector<SBResourceWideString> m_values;
    char m_14[0xc];
    std::wstring m_text;
    ~SBResourceUnk005fe790();
};

class SBResourceUnk005fe880
{
public:
    char m_00[4];
    std::vector<SBResourceWideString> m_values;
    char m_14[0xc];
    std::wstring m_text;
    ~SBResourceUnk005fe880();
};

class SBResourceUnk005fee70
{
public:
    char m_00[4];
    std::vector<std::string> m_values;
    char m_14[0xc];
    std::string m_text;
    ~SBResourceUnk005fee70();
};

// FUNCTION: GAME 0x005fdc70
void SBResourceUnk005fdc70::FUN_005fdc70()
{
    std::vector<unsigned long> &values = *(std::vector<unsigned long> *)((char *)this + 4);
    values.clear();
    values.~vector();
}

// Parked: vector erase invokes _Tidy instead of the target out-of-line string destructor; this/EH and iterator registers differ.
// STUB: GAME 0x005fe790
SBResourceUnk005fe790::~SBResourceUnk005fe790()
{
    m_values.clear();
}

// Parked: vector erase invokes _Tidy instead of the target out-of-line string destructor; this/EH and iterator registers differ.
// STUB: GAME 0x005fe880
SBResourceUnk005fe880::~SBResourceUnk005fe880()
{
    m_values.clear();
}

// Parked: target EH, iterator scheduling, and the static-CRT npos data load differ from this source shape.
// STUB: GAME 0x005fed80
SBResourceUnk005fed80::~SBResourceUnk005fed80()
{
    std::vector<std::string> &values = m_values;
    values.erase(values.begin(), values.end());
}

// Parked: target EH, iterator scheduling, and the static-CRT npos data load differ from this source shape.
// STUB: GAME 0x005fee70
SBResourceUnk005fee70::~SBResourceUnk005fee70()
{
    std::vector<std::string> &values = m_values;
    values.erase(values.begin(), values.end());
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

#include "RHEngineWidenedCalls.h"

// FUNCTION: GAME 0x006001d0
void SBResourceManager::FUN_006001d0(Tree44::Iterator &position)
{
    SBResourceSurfaceArray surfaces;
    SBResourceSurfaceArray &source = *(SBResourceSurfaceArray *)((char *)position.m_node + 0x10);
    if (&source != &surfaces) {
        typedef std::vector<int> Values;
        int *(Values::*erase)(int *, int *) = &Values::erase;
        (((Values *)&surfaces.m_values)->*erase)((int *)surfaces.m_values.begin(), (int *)surfaces.m_values.end());
        surfaces.Assign(source, 0);
    }
    while (surfaces.Size() > 0) {
        unsigned long surface = *surfaces.m_values.begin();
        if (surface)
            (*(RHEngineWidenedCalls **)(m_00 + 4))->FUN_005e5160(surface);
        surfaces.m_values.erase(surfaces.m_values.begin());
        surfaces.m_changed = true;
    }
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
    SBResourceManager::Node<unsigned long> *found = tree.FUN_006013a0(id).m_node;
    if (found == view.m_44.m_head) {
        if (!view.FUN_00600db0(id)) {
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBResourceManager.cpp", 0x5eb,
                "Unable to recover a resource");
            return false;
        }
        found = tree.FUN_006013a0(id).m_node;
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
    SBResourceUnkKeyNode *found = tree.FUN_00601bd0(id).m_node;
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

struct SBResourceTreeLinks
{
    SBResourceTreeLinks *m_left;
    SBResourceTreeLinks *m_parent;
    SBResourceTreeLinks *m_right;
    unsigned long m_key;
};

class RHUnk00641782
{
public:
    RHUnk00641782();
    ~RHUnk00641782();
};

class SBResourceTreePrevious44
{
public:
    SBResourceTreeLinks *m_node;
    void FUN_00605270();
};

class SBResourceTreePrevious54
{
public:
    SBResourceTreeLinks *m_node;
    void FUN_00605380();
};

class SBResourceTreePrevious64
{
public:
    SBResourceTreeLinks *m_node;
    void FUN_00605490();
};

class SBResourceTreePrevious74
{
public:
    SBResourceTreeLinks *m_node;
    void FUN_006055a0();
};

class SBResourceTreePrevious84
{
public:
    SBResourceTreeLinks *m_node;
    void FUN_006056b0();
};

// GLOBAL: GAME 0x006c1854
SBResourceTreeLinks *g_unk0x006c1854 = 0;
// GLOBAL: GAME 0x006c185c
SBResourceTreeLinks *g_unk0x006c185c = 0;
// GLOBAL: GAME 0x006c1864
SBResourceTreeLinks *g_unk0x006c1864 = 0;
// GLOBAL: GAME 0x006c186c
SBResourceTreeLinks *g_unk0x006c186c = 0;
// GLOBAL: GAME 0x006c1874
SBResourceTreeLinks *g_unk0x006c1874 = 0;

// GLOBAL: GAME 0x006c1858
unsigned int g_unk0x006c1858 = 0;
// GLOBAL: GAME 0x006c1860
unsigned int g_unk0x006c1860 = 0;
// GLOBAL: GAME 0x006c1868
unsigned int g_unk0x006c1868 = 0;
// GLOBAL: GAME 0x006c1870
unsigned int g_unk0x006c1870 = 0;
// GLOBAL: GAME 0x006c1878
unsigned int g_unk0x006c1878 = 0;

extern RHFrameHolderRowMap::Node *g_unk0x006c0b2c;

// GLOBAL: GAME 0x006c0b28
unsigned int g_unk0x006c0b28 = 0;

template<unsigned int S, unsigned int C, unsigned int I>
inline SBResourceTreeLinks *&SBResourceTreeStorage<S, C, I>::Root() { return m_head->m_parent; }

template<unsigned int S, unsigned int C, unsigned int I>
inline SBResourceTreeLinks *&SBResourceTreeStorage<S, C, I>::Leftmost() { return m_head->m_left; }

template<unsigned int S, unsigned int C, unsigned int I>
inline SBResourceTreeLinks *&SBResourceTreeStorage<S, C, I>::Rightmost() { return m_head->m_right; }

template<unsigned int S, unsigned int C, unsigned int I>
inline SBResourceTreeIterator SBResourceTreeStorage<S, C, I>::Begin()
{
    return SBResourceTreeIterator(Leftmost());
}

// Parked: explicit erase output storage does not share the subsequent lock slot.
// STUB: GAME 0x00601070
template<> void SBResourceTreeStorage<0x40, 0x3c, 0x84>::Dispose()
{
    SBResourceManager::Tree84 &tree = *(SBResourceManager::Tree84 *)this;
    {
        SBResourceTreeFindIterator<SBResourceManager::Node<SBResourceManager::Element> > result;
        typedef SBResourceTreeFindIterator<SBResourceManager::Node<SBResourceManager::Element> > Iterator;
        Iterator &(SBResourceManager::Tree84::*erase)(Iterator &, SBResourceManager::Node<SBResourceManager::Element> *, SBResourceManager::Node<SBResourceManager::Element> *) = &SBResourceManager::Tree84::FUN_00601d50;
        (tree.*erase)(result, (SBResourceManager::Node<SBResourceManager::Element> *)Leftmost(),
            (SBResourceManager::Node<SBResourceManager::Element> *)m_head);
    }
    operator delete(m_head);
    m_head = 0;
    m_size = 0;
    RHUnk00641782 lock;
    if (--g_unk0x006c1878 == 0) {
        operator delete(g_unk0x006c1874);
        g_unk0x006c1874 = 0;
    }
}

// FUNCTION: GAME 0x006010e0
template<> SBResourceTreeStorage<0x34, 0x30, 0x44>::InsertResult SBResourceTreeStorage<0x34, 0x30, 0x44>::Insert(const unsigned long &value)
{
    SBResourceTreeLinks *parent = m_head;
    SBResourceTreeLinks *node = parent->m_parent;
    bool before = true;
    {
        RHUnk00641782 lock;
        while (node != g_unk0x006c1854) {
            parent = node;
            before = value < node->m_key;
            node = before ? node->m_left : node->m_right;
        }
    }
    if (m_multi) {
        InsertResult result(InsertNode(node, parent, value), true);
        return result;
    }
    SBResourceTreeIterator position(parent);
    if (before) {
        if (position.m_node == m_head->m_left) {
            InsertResult result(InsertNode(node, parent, value), true);
            return result;
        }
        ((SBResourceTreePrevious44 *)&position)->FUN_00605270();
    }
    if (position.m_node->m_key < value) {
        InsertResult result(InsertNode(node, parent, value), true);
        return result;
    }
    InsertResult result(position, false);
    return result;
}

// FUNCTION: GAME 0x00601210
SBResourceManager::Tree44::Iterator &SBResourceManager::Tree44::FUN_00601210(Iterator &result, Node<unsigned long> *first, Node<unsigned long> *last)
{
    SBResourceTreeStorage<0x34, 0x30, 0x44> &tree = *(SBResourceTreeStorage<0x34, 0x30, 0x44> *)this;
    if (tree.m_size != 0 && first == (Node<unsigned long> *)tree.Leftmost() && last == m_head) {
        RHUnk00641782 lock;
        SBResourceTreeLinks *node = tree.Root();
        {
            RHUnk00641782 inner;
            for (SBResourceTreeLinks *next = node; next != g_unk0x006c1854; node = next) {
                tree.Destroy(next->m_right);
                next = next->m_left;
                ((SBResourceArrayLifecycle44 *)((char *)node + 0x10))->FUN_0051d120();
                operator delete(node);
            }
        }
        tree.Root() = g_unk0x006c1854;
        tree.m_size = 0;
        tree.Leftmost() = (SBResourceTreeLinks *)m_head;
        tree.Rightmost() = (SBResourceTreeLinks *)m_head;
        result.m_node = (Node<unsigned long> *)tree.Begin().m_node;
        return result;
    }
    while (first != last) {
        SBResourceTreeLinks *node = (SBResourceTreeLinks *)first;
        ((SBResourceUnkAdvance *)&first)->FUN_006057c0();
        tree.EraseNode(node);
    }
    result.m_node = first;
    return result;
}

// FUNCTION: GAME 0x00601350
unsigned int SBResourceManager::Tree44::FUN_00601350(const unsigned long &key)
{
    Node<unsigned long> *last = FUN_00605770(key);
    Node<unsigned long> *first = FUN_00605220(key);
    unsigned int count = 0;
    Iterator current(first);
    while (current.m_node != last) {
        ++count;
        ((SBResourceUnkAdvance *)&current)->FUN_006057c0();
    }
    FUN_00601210(current, first, last);
    return count;
}

// FUNCTION: GAME 0x006013a0
SBResourceManager::Tree44::Iterator SBResourceManager::Tree44::FUN_006013a0(const unsigned long &key)
{
    Iterator candidate(FUN_00605220(key));
    Node<unsigned long> *head = m_head;
    return candidate.m_node != head && key >= candidate.m_node->m_key
        ? candidate : Iterator(head);
}

// FUNCTION: GAME 0x006013f0
template<> SBResourceTreeStorage<0x20, 0x1c, 0x54>::InsertResult SBResourceTreeStorage<0x20, 0x1c, 0x54>::Insert(const unsigned long &value)
{
    SBResourceTreeLinks *parent = m_head;
    SBResourceTreeLinks *node = parent->m_parent;
    bool before = true;
    {
        RHUnk00641782 lock;
        while (node != g_unk0x006c185c) {
            parent = node;
            before = value < node->m_key;
            node = before ? node->m_left : node->m_right;
        }
    }
    if (m_multi) {
        InsertResult result(InsertNode(node, parent, value), true);
        return result;
    }
    SBResourceTreeIterator position(parent);
    if (before) {
        if (position.m_node == m_head->m_left) {
            InsertResult result(InsertNode(node, parent, value), true);
            return result;
        }
        ((SBResourceTreePrevious54 *)&position)->FUN_00605380();
    }
    if (position.m_node->m_key < value) {
        InsertResult result(InsertNode(node, parent, value), true);
        return result;
    }
    InsertResult result(position, false);
    return result;
}

// FUNCTION: GAME 0x00601520
template<> SBResourceTreeIterator SBResourceTreeStorage<0x20, 0x1c, 0x54>::EraseRange(SBResourceTreeLinks *first, SBResourceTreeLinks *last)
{
    if (m_size != 0 && first == m_head->m_left && last == m_head) {
        RHUnk00641782 lock;
        SBResourceTreeLinks *node = m_head->m_parent;
        {
            RHUnk00641782 inner;
            for (SBResourceTreeLinks *next = node; next != g_unk0x006c185c; node = next) {
                Destroy(next->m_right);
                next = next->m_left;
                operator delete(node);
            }
        }
        Root() = g_unk0x006c185c;
        m_size = 0;
        Leftmost() = m_head;
        Rightmost() = m_head;
        return Begin();
    }
    while (first != last) {
        SBResourceTreeLinks *node = first;
        ((SBResourceTreeIterator54 *)&first)->FUN_00605870();
        EraseNode(node);
    }
    return SBResourceTreeIterator(first);
}

// FUNCTION: GAME 0x00601650
SBResourceTreeFindIterator<SBResourceManager::ResourceNode> SBResourceManager::Tree54::FUN_00601650(const unsigned long &key)
{
    SBResourceTreeFindIterator<ResourceNode> candidate(FUN_00605330(key));
    ResourceNode *head = m_head;
    return candidate.m_node != head && key >= candidate.m_node->m_key
        ? candidate : SBResourceTreeFindIterator<ResourceNode>(head);
}

// FUNCTION: GAME 0x006016a0
template<> SBResourceTreeStorage<0x20, 0x1c, 0x64>::InsertResult SBResourceTreeStorage<0x20, 0x1c, 0x64>::Insert(const unsigned long &value)
{
    SBResourceTreeLinks *parent = m_head;
    SBResourceTreeLinks *node = parent->m_parent;
    bool before = true;
    {
        RHUnk00641782 lock;
        while (node != g_unk0x006c1864) {
            parent = node;
            before = value < node->m_key;
            node = before ? node->m_left : node->m_right;
        }
    }
    if (m_multi) {
        InsertResult result(InsertNode(node, parent, value), true);
        return result;
    }
    SBResourceTreeIterator position(parent);
    if (before) {
        if (position.m_node == m_head->m_left) {
            InsertResult result(InsertNode(node, parent, value), true);
            return result;
        }
        ((SBResourceTreePrevious64 *)&position)->FUN_00605490();
    }
    if (position.m_node->m_key < value) {
        InsertResult result(InsertNode(node, parent, value), true);
        return result;
    }
    InsertResult result(position, false);
    return result;
}

// FUNCTION: GAME 0x006017d0
template<> SBResourceTreeIterator SBResourceTreeStorage<0x20, 0x1c, 0x64>::EraseRange(SBResourceTreeLinks *first, SBResourceTreeLinks *last)
{
    if (m_size != 0 && first == m_head->m_left && last == m_head) {
        RHUnk00641782 lock;
        SBResourceTreeLinks *node = m_head->m_parent;
        {
            RHUnk00641782 inner;
            for (SBResourceTreeLinks *next = node; next != g_unk0x006c1864; node = next) {
                Destroy(next->m_right);
                next = next->m_left;
                ((SBGeoPoint2D *)((char *)node + 0x10))->~SBGeoPoint2D();
                operator delete(node);
            }
        }
        Root() = g_unk0x006c1864;
        m_size = 0;
        Leftmost() = m_head;
        Rightmost() = m_head;
        return Begin();
    }
    while (first != last) {
        SBResourceTreeLinks *node = first;
        ((SBResourceTreeIterator64 *)&first)->FUN_00605920();
        EraseNode(node);
    }
    return SBResourceTreeIterator(first);
}

// FUNCTION: GAME 0x00601910
template<> SBResourceTreeStorage<0x40, 0x3c, 0x74>::InsertResult SBResourceTreeStorage<0x40, 0x3c, 0x74>::Insert(const unsigned long &value)
{
    SBResourceTreeLinks *parent = m_head;
    SBResourceTreeLinks *node = parent->m_parent;
    bool before = true;
    {
        RHUnk00641782 lock;
        while (node != g_unk0x006c186c) {
            parent = node;
            before = value < node->m_key;
            node = before ? node->m_left : node->m_right;
        }
    }
    if (m_multi) {
        InsertResult result(InsertNode(node, parent, value), true);
        return result;
    }
    SBResourceTreeIterator position(parent);
    if (before) {
        if (position.m_node == m_head->m_left) {
            InsertResult result(InsertNode(node, parent, value), true);
            return result;
        }
        ((SBResourceTreePrevious74 *)&position)->FUN_006055a0();
    }
    if (position.m_node->m_key < value) {
        InsertResult result(InsertNode(node, parent, value), true);
        return result;
    }
    InsertResult result(position, false);
    return result;
}

// FUNCTION: GAME 0x00601a40
SBResourceUnkKeyIterator &SBResourceManager::Tree74::FUN_00601a40(SBResourceUnkKeyIterator &result, SBResourceUnkKeyNode *first, SBResourceUnkKeyNode *last)
{
    SBResourceTreeStorage<0x40, 0x3c, 0x74> &tree = *(SBResourceTreeStorage<0x40, 0x3c, 0x74> *)this;
    if (tree.m_size != 0 && first == (SBResourceUnkKeyNode *)tree.Leftmost() && last == m_head) {
        RHUnk00641782 lock;
        SBResourceTreeLinks *node = tree.Root();
        {
            RHUnk00641782 inner;
            for (SBResourceTreeLinks *next = node; next != g_unk0x006c186c; node = next) {
                tree.Destroy(next->m_right);
                next = next->m_left;
                ((SBResourceArrayLifecycle74 *)((char *)node + 0x10))->~SBResourceArrayLifecycle74();
                operator delete(node);
            }
        }
        tree.Root() = g_unk0x006c186c;
        tree.m_size = 0;
        tree.Leftmost() = (SBResourceTreeLinks *)m_head;
        tree.Rightmost() = (SBResourceTreeLinks *)m_head;
        result.m_node = (SBResourceUnkKeyNode *)tree.Begin().m_node;
        return result;
    }
    while (first != last) {
        SBResourceTreeLinks *node = (SBResourceTreeLinks *)first;
        ((SBResourceTreeIterator74 *)&first)->FUN_00605a20();
        tree.EraseNode(node);
    }
    result.m_node = first;
    return result;
}

// FUNCTION: GAME 0x00601b80
unsigned int SBResourceManager::Tree74::FUN_00601b80(const unsigned long &key)
{
    SBResourceUnkKeyNode *last = FUN_006059d0(key);
    SBResourceUnkKeyNode *first = FUN_00605550(key);
    unsigned int count = 0;
    SBResourceUnkKeyIterator current(first);
    while (current.m_node != last) {
        ++count;
        ((SBResourceTreeIterator74 *)&current)->FUN_00605a20();
    }
    FUN_00601a40(current, first, last);
    return count;
}

// FUNCTION: GAME 0x00601bd0
SBResourceUnkKeyIterator SBResourceManager::Tree74::FUN_00601bd0(const unsigned long &key)
{
    SBResourceUnkKeyIterator candidate(FUN_00605550(key));
    SBResourceUnkKeyNode *head = m_head;
    return candidate.m_node != head && key >= candidate.m_node->m_key
        ? candidate : SBResourceUnkKeyIterator(head);
}

// FUNCTION: GAME 0x00601c20
template<> SBResourceTreeStorage<0x40, 0x3c, 0x84>::InsertResult SBResourceTreeStorage<0x40, 0x3c, 0x84>::Insert(const unsigned long &value)
{
    SBResourceTreeLinks *parent = m_head;
    SBResourceTreeLinks *node = parent->m_parent;
    bool before = true;
    {
        RHUnk00641782 lock;
        while (node != g_unk0x006c1874) {
            parent = node;
            before = value < node->m_key;
            node = before ? node->m_left : node->m_right;
        }
    }
    if (m_multi) {
        InsertResult result(InsertNode(node, parent, value), true);
        return result;
    }
    SBResourceTreeIterator position(parent);
    if (before) {
        if (position.m_node == m_head->m_left) {
            InsertResult result(InsertNode(node, parent, value), true);
            return result;
        }
        ((SBResourceTreePrevious84 *)&position)->FUN_006056b0();
    }
    if (position.m_node->m_key < value) {
        InsertResult result(InsertNode(node, parent, value), true);
        return result;
    }
    InsertResult result(position, false);
    return result;
}

// FUNCTION: GAME 0x00601d50
SBResourceTreeFindIterator<SBResourceManager::Node<SBResourceManager::Element> > &SBResourceManager::Tree84::FUN_00601d50(SBResourceTreeFindIterator<Node<Element> > &result, Node<Element> *first, Node<Element> *last)
{
    SBResourceTreeStorage<0x40, 0x3c, 0x84> &tree = *(SBResourceTreeStorage<0x40, 0x3c, 0x84> *)this;
    if (tree.m_size != 0 && first == (Node<Element> *)tree.Leftmost() && last == m_head) {
        RHUnk00641782 lock;
        SBResourceTreeLinks *node = tree.Root();
        {
            RHUnk00641782 inner;
            for (SBResourceTreeLinks *next = node; next != g_unk0x006c1874; node = next) {
                tree.Destroy(next->m_right);
                next = next->m_left;
                ((SBResourceArrayLifecycle84 *)((char *)node + 0x10))->FUN_0057c820();
                operator delete(node);
            }
        }
        tree.Root() = g_unk0x006c1874;
        tree.m_size = 0;
        tree.Leftmost() = (SBResourceTreeLinks *)m_head;
        tree.Rightmost() = (SBResourceTreeLinks *)m_head;
        result.m_node = (Node<Element> *)tree.Begin().m_node;
        return result;
    }
    while (first != last) {
        SBResourceTreeLinks *node = (SBResourceTreeLinks *)first;
        ((SBResourceTreeIterator84 *)&first)->FUN_00605b20();
        tree.EraseNode(node);
    }
    result.m_node = first;
    return result;
}

// FUNCTION: GAME 0x00601e90
unsigned int SBResourceManager::Tree84::FUN_00601e90(const unsigned long &key)
{
    Node<Element> *last = FUN_00605ad0(key);
    Node<Element> *first = FUN_00605660(key);
    unsigned int count = 0;
    SBResourceTreeFindIterator<Node<Element> > current(first);
    while (current.m_node != last) {
        ++count;
        ((SBResourceTreeIterator84 *)&current)->FUN_00605b20();
    }
    FUN_00601d50(current, first, last);
    return count;
}

// FUNCTION: GAME 0x00601ee0
SBResourceTreeFindIterator<SBResourceManager::Node<SBResourceManager::Element> > SBResourceManager::Tree84::FUN_00601ee0(const unsigned long &key)
{
    SBResourceTreeFindIterator<Node<Element> > candidate(FUN_00605660(key));
    Node<Element> *head = m_head;
    return candidate.m_node != head && key >= candidate.m_node->m_key
        ? candidate : SBResourceTreeFindIterator<Node<Element> >(head);
}

// FUNCTION: GAME 0x00601f30
template<> void SBResourceTreeStorage<0x18, 0x14, 0x34>::Initialize()
{
    RHUnk00641782 lock;
    if (g_unk0x006c0b2c == 0) {
        SBResourceTreeLinks *node = (SBResourceTreeLinks *)operator new(0x18);
        node->m_parent = 0;
        *(int *)((char *)node + 0x14) = 1;
        g_unk0x006c0b2c = (RHFrameHolderRowMap::Node *)node;
        ((SBResourceTreeLinks *)g_unk0x006c0b2c)->m_left = 0;
        ((SBResourceTreeLinks *)g_unk0x006c0b2c)->m_right = 0;
    }
    ++g_unk0x006c0b28;
    SBResourceTreeLinks *sentinel = (SBResourceTreeLinks *)g_unk0x006c0b2c;
    SBResourceTreeLinks *head = (SBResourceTreeLinks *)operator new(0x18);
    head->m_parent = sentinel;
    *(int *)((char *)head + 0x14) = 0;
    m_head = head;
    m_size = 0;
    m_head->m_left = m_head;
    m_head->m_right = m_head;
}

// Parked: erase successor/frame scheduling and payload cleanup differ.
// STUB: GAME 0x00601fe0
// ?EraseNode@?$SBResourceTreeStorage@$0DE@$0DA@$0EE@@@QAE?AUSBResourceTreeIterator@@PAUSBResourceTreeLinks@@@Z

// FUNCTION: GAME 0x00602580
SBResourceManager::Tree44::Iterator &SBResourceManager::Tree44::FUN_00602580(Iterator &result, const unsigned long &key)
{
    result.m_node = FUN_00605220(key);
    return result;
}

// Parked: target inlines the payload lifecycle and outlines its vector helpers.
// STUB: GAME 0x006025a0
template<> void SBResourceTreeStorage<0x34, 0x30, 0x44>::Destroy(SBResourceTreeLinks *node)
{
    RHUnk00641782 lock;
    for (SBResourceTreeLinks *next = node; next != g_unk0x006c1854; node = next) {
        Destroy(next->m_right);
        next = next->m_left;
        ((SBResourceArrayLifecycle44 *)((char *)node + 0x10))->FUN_0051d120();
        operator delete(node);
    }
}

// FUNCTION: GAME 0x006026b0
template<> void SBResourceTreeStorage<0x34, 0x30, 0x44>::Initialize()
{
    RHUnk00641782 lock;
    if (g_unk0x006c1854 == 0) {
        SBResourceTreeLinks *node = (SBResourceTreeLinks *)operator new(0x34);
        node->m_parent = 0;
        *(int *)((char *)node + 0x30) = 1;
        g_unk0x006c1854 = node;
        g_unk0x006c1854->m_left = 0;
        g_unk0x006c1854->m_right = 0;
    }
    ++g_unk0x006c1858;
    SBResourceTreeLinks *sentinel = g_unk0x006c1854;
    SBResourceTreeLinks *head = (SBResourceTreeLinks *)operator new(0x34);
    head->m_parent = sentinel;
    *(int *)((char *)head + 0x30) = 0;
    m_head = head;
    m_size = 0;
    m_head->m_left = m_head;
    m_head->m_right = m_head;
}

// TEMPLATE: GAME 0x00602760
// ?InsertNode@?$SBResourceTreeStorage@$0DE@$0DA@$0EE@@@QAE?AUSBResourceTreeIterator@@PAUSBResourceTreeLinks@@0ABK@Z

// Parked: erase successor/color scheduling and carried registers differ.
// STUB: GAME 0x00602a60
// ?EraseNode@?$SBResourceTreeStorage@$0CA@$0BM@$0FE@@@QAE?AUSBResourceTreeIterator@@PAUSBResourceTreeLinks@@@Z

// FUNCTION: GAME 0x00602f80
template<> void SBResourceTreeStorage<0x20, 0x1c, 0x54>::Destroy(SBResourceTreeLinks *node)
{
    RHUnk00641782 lock;
    for (SBResourceTreeLinks *next = node; next != g_unk0x006c185c; node = next) {
        Destroy(next->m_right);
        next = next->m_left;
        operator delete(node);
    }
}

// FUNCTION: GAME 0x00603010
template<> void SBResourceTreeStorage<0x20, 0x1c, 0x54>::Initialize()
{
    RHUnk00641782 lock;
    if (g_unk0x006c185c == 0) {
        SBResourceTreeLinks *node = (SBResourceTreeLinks *)operator new(0x20);
        node->m_parent = 0;
        *(int *)((char *)node + 0x1c) = 1;
        g_unk0x006c185c = node;
        g_unk0x006c185c->m_left = 0;
        g_unk0x006c185c->m_right = 0;
    }
    ++g_unk0x006c1860;
    SBResourceTreeLinks *sentinel = g_unk0x006c185c;
    SBResourceTreeLinks *head = (SBResourceTreeLinks *)operator new(0x20);
    head->m_parent = sentinel;
    *(int *)((char *)head + 0x1c) = 0;
    m_head = head;
    m_size = 0;
    m_head->m_left = m_head;
    m_head->m_right = m_head;
}

// TEMPLATE: GAME 0x006030c0
// ?InsertNode@?$SBResourceTreeStorage@$0CA@$0BM@$0FE@@@QAE?AUSBResourceTreeIterator@@PAUSBResourceTreeLinks@@0ABK@Z

// Parked: color-swap and rotation register scheduling differ.
// STUB: GAME 0x006033c0
// ?EraseNode@?$SBResourceTreeStorage@$0CA@$0BM@$0GE@@@QAE?AUSBResourceTreeIterator@@PAUSBResourceTreeLinks@@@Z

// FUNCTION: GAME 0x006038c0
template<> void SBResourceTreeStorage<0x20, 0x1c, 0x64>::Destroy(SBResourceTreeLinks *node)
{
    RHUnk00641782 lock;
    for (SBResourceTreeLinks *next = node; next != g_unk0x006c1864; node = next) {
        Destroy(next->m_right);
        next = next->m_left;
        ((SBGeoPoint2D *)((char *)node + 0x10))->~SBGeoPoint2D();
        operator delete(node);
    }
}

// FUNCTION: GAME 0x00603950
template<> void SBResourceTreeStorage<0x20, 0x1c, 0x64>::Initialize()
{
    RHUnk00641782 lock;
    if (g_unk0x006c1864 == 0) {
        SBResourceTreeLinks *node = (SBResourceTreeLinks *)operator new(0x20);
        node->m_parent = 0;
        *(int *)((char *)node + 0x1c) = 1;
        g_unk0x006c1864 = node;
        g_unk0x006c1864->m_left = 0;
        g_unk0x006c1864->m_right = 0;
    }
    ++g_unk0x006c1868;
    SBResourceTreeLinks *sentinel = g_unk0x006c1864;
    SBResourceTreeLinks *head = (SBResourceTreeLinks *)operator new(0x20);
    head->m_parent = sentinel;
    *(int *)((char *)head + 0x1c) = 0;
    m_head = head;
    m_size = 0;
    m_head->m_left = m_head;
    m_head->m_right = m_head;
}

// TEMPLATE: GAME 0x00603a00
// ?InsertNode@?$SBResourceTreeStorage@$0CA@$0BM@$0GE@@@QAE?AUSBResourceTreeIterator@@PAUSBResourceTreeLinks@@0ABK@Z

// Parked: erase frame scheduling and wide payload cleanup differ.
// STUB: GAME 0x00603d00
// ?EraseNode@?$SBResourceTreeStorage@$0EA@$0DM@$0HE@@@QAE?AUSBResourceTreeIterator@@PAUSBResourceTreeLinks@@@Z

// FUNCTION: GAME 0x006042a0
SBResourceUnkKeyNode *&SBResourceManager::Tree74::FUN_006042a0(SBResourceUnkKeyNode *&result, const unsigned long &key)
{
    result = FUN_00605550(key);
    return result;
}

// Parked: target inlines payload cleanup with out-of-line vector copy/destruction helpers.
// STUB: GAME 0x006042c0
template<> void SBResourceTreeStorage<0x40, 0x3c, 0x74>::Destroy(SBResourceTreeLinks *node)
{
    RHUnk00641782 lock;
    for (SBResourceTreeLinks *next = node; next != g_unk0x006c186c; node = next) {
        Destroy(next->m_right);
        next = next->m_left;
        ((SBResourceArrayLifecycle74 *)((char *)node + 0x10))->~SBResourceArrayLifecycle74();
        operator delete(node);
    }
}

// FUNCTION: GAME 0x006043e0
template<> void SBResourceTreeStorage<0x40, 0x3c, 0x74>::Initialize()
{
    RHUnk00641782 lock;
    if (g_unk0x006c186c == 0) {
        SBResourceTreeLinks *node = (SBResourceTreeLinks *)operator new(0x40);
        node->m_parent = 0;
        *(int *)((char *)node + 0x3c) = 1;
        g_unk0x006c186c = node;
        g_unk0x006c186c->m_left = 0;
        g_unk0x006c186c->m_right = 0;
    }
    ++g_unk0x006c1870;
    SBResourceTreeLinks *sentinel = g_unk0x006c186c;
    SBResourceTreeLinks *head = (SBResourceTreeLinks *)operator new(0x40);
    head->m_parent = sentinel;
    *(int *)((char *)head + 0x3c) = 0;
    m_head = head;
    m_size = 0;
    m_head->m_left = m_head;
    m_head->m_right = m_head;
}

// TEMPLATE: GAME 0x00604490
// ?InsertNode@?$SBResourceTreeStorage@$0EA@$0DM@$0HE@@@QAE?AUSBResourceTreeIterator@@PAUSBResourceTreeLinks@@0ABK@Z

// Parked: erase frame scheduling and narrow payload cleanup differ.
// STUB: GAME 0x00604790
// ?EraseNode@?$SBResourceTreeStorage@$0EA@$0DM@$0IE@@@QAE?AUSBResourceTreeIterator@@PAUSBResourceTreeLinks@@@Z

// FUNCTION: GAME 0x00604d30
SBResourceManager::Node<SBResourceManager::Element> *&SBResourceManager::Tree84::FUN_00604d30(Node<Element> *&result, const unsigned long &key)
{
    result = FUN_00605660(key);
    return result;
}

// Parked: target inlines the narrow payload lifecycle and outlines its vector helpers.
// STUB: GAME 0x00604d50
template<> void SBResourceTreeStorage<0x40, 0x3c, 0x84>::Destroy(SBResourceTreeLinks *node)
{
    RHUnk00641782 lock;
    for (SBResourceTreeLinks *next = node; next != g_unk0x006c1874; node = next) {
        Destroy(next->m_right);
        next = next->m_left;
        ((SBResourceArrayLifecycle84 *)((char *)node + 0x10))->FUN_0057c820();
        operator delete(node);
    }
}

// FUNCTION: GAME 0x00604e70
template<> void SBResourceTreeStorage<0x40, 0x3c, 0x84>::Initialize()
{
    RHUnk00641782 lock;
    if (g_unk0x006c1874 == 0) {
        SBResourceTreeLinks *node = (SBResourceTreeLinks *)operator new(0x40);
        node->m_parent = 0;
        *(int *)((char *)node + 0x3c) = 1;
        g_unk0x006c1874 = node;
        g_unk0x006c1874->m_left = 0;
        g_unk0x006c1874->m_right = 0;
    }
    ++g_unk0x006c1878;
    SBResourceTreeLinks *sentinel = g_unk0x006c1874;
    SBResourceTreeLinks *head = (SBResourceTreeLinks *)operator new(0x40);
    head->m_parent = sentinel;
    *(int *)((char *)head + 0x3c) = 0;
    m_head = head;
    m_size = 0;
    m_head->m_left = m_head;
    m_head->m_right = m_head;
}

// TEMPLATE: GAME 0x00604f20
// ?InsertNode@?$SBResourceTreeStorage@$0EA@$0DM@$0IE@@@QAE?AUSBResourceTreeIterator@@PAUSBResourceTreeLinks@@0ABK@Z

static inline SBResourceTreeLinks *&SBResourceLeft(SBResourceTreeLinks *node)
{
    return node->m_left;
}

static inline SBResourceTreeLinks *&SBResourceRight(SBResourceTreeLinks *node)
{
    return node->m_right;
}

static inline SBResourceTreeLinks *SBResourceMax44(SBResourceTreeLinks *node)
{
    RHUnk00641782 lock;
    while (node->m_right != g_unk0x006c1854)
        node = node->m_right;
    return node;
}

static inline SBResourceTreeLinks *SBResourceMax54(SBResourceTreeLinks *node)
{
    RHUnk00641782 lock;
    while (node->m_right != g_unk0x006c185c)
        node = node->m_right;
    return node;
}

static inline SBResourceTreeLinks *SBResourceMax64(SBResourceTreeLinks *node)
{
    RHUnk00641782 lock;
    while (node->m_right != g_unk0x006c1864)
        node = node->m_right;
    return node;
}

static inline SBResourceTreeLinks *SBResourceMax74(SBResourceTreeLinks *node)
{
    RHUnk00641782 lock;
    while (node->m_right != g_unk0x006c186c)
        node = node->m_right;
    return node;
}

static inline SBResourceTreeLinks *SBResourceMax84(SBResourceTreeLinks *node)
{
    RHUnk00641782 lock;
    while (node->m_right != g_unk0x006c1874)
        node = node->m_right;
    return node;
}

template<class T> __forceinline T *SBResourceLowerBound(T *const &head, SBResourceTreeLinks *const &nil, const unsigned long &key)
{
    SBResourceTreeLinks *node = ((SBResourceTreeLinks *)head)->m_parent;
    SBResourceTreeLinks *found = (SBResourceTreeLinks *)head;
    while (node != nil) {
        if (node->m_key < key)
            node = node->m_right;
        else {
            found = node;
            node = node->m_left;
        }
    }
    return (T *)found;
}

template<unsigned int I> struct SBResourceTreeTraits;

template<> struct SBResourceTreeTraits<0x44>
{
    static SBResourceTreeLinks *Nil() { return g_unk0x006c1854; }
    static void Construct(unsigned long *output, const unsigned long &value) { SBResourceConstructArray44(output, value); }
    static void Advance(SBResourceTreeLinks *&node) { ((SBResourceUnkAdvance *)&node)->FUN_006057c0(); }
    static void DestroyValue(SBResourceTreeLinks *node) { ((SBResourceArrayLifecycle44 *)((char *)node + 0x10))->FUN_0051d120(); }
};

template<> struct SBResourceTreeTraits<0x54>
{
    static SBResourceTreeLinks *Nil() { return g_unk0x006c185c; }
    static void Advance(SBResourceTreeLinks *&node) { ((SBResourceTreeIterator54 *)&node)->FUN_00605870(); }
    static void DestroyValue(SBResourceTreeLinks *) {}
    static void Construct(unsigned long *output, const unsigned long &value) {
        RHScriptPositionList::Unk00588190((RHUnk00571160Position *)output, (const RHUnk00571160Position *)&value);
    }
};

template<> struct SBResourceTreeTraits<0x64>
{
    static SBResourceTreeLinks *Nil() { return g_unk0x006c1864; }
    static void Advance(SBResourceTreeLinks *&node) { ((SBResourceTreeIterator64 *)&node)->FUN_00605920(); }
    static void DestroyValue(SBResourceTreeLinks *node) { ((SBGeoPoint2D *)((char *)node + 0x10))->~SBGeoPoint2D(); }
    static void Construct(unsigned long *output, const unsigned long &value) {
        SBResourceConstructMouse((SBResourceMousePair *)output, (const SBResourceMousePair &)value);
    }
};

template<> struct SBResourceTreeTraits<0x74>
{
    static SBResourceTreeLinks *Nil() { return g_unk0x006c186c; }
    static void Construct(unsigned long *output, const unsigned long &value) { SBResourceConstructArray74(output, value); }
    static void Advance(SBResourceTreeLinks *&node) { ((SBResourceTreeIterator74 *)&node)->FUN_00605a20(); }
    static void DestroyValue(SBResourceTreeLinks *node) { ((SBResourceArrayLifecycle74 *)((char *)node + 0x10))->~SBResourceArrayLifecycle74(); }
};

template<> struct SBResourceTreeTraits<0x84>
{
    static SBResourceTreeLinks *Nil() { return g_unk0x006c1874; }
    static void Construct(unsigned long *output, const unsigned long &value) { SBResourceConstructArray84(output, value); }
    static void Advance(SBResourceTreeLinks *&node) { ((SBResourceTreeIterator84 *)&node)->FUN_00605b20(); }
    static void DestroyValue(SBResourceTreeLinks *node) { ((SBResourceArrayLifecycle84 *)((char *)node + 0x10))->FUN_0057c820(); }
};

template<unsigned int S, unsigned int C, unsigned int I>
inline int &SBResourceTreeStorage<S, C, I>::Color(SBResourceTreeLinks *node)
{
    return *(int *)((char *)node + C);
}

template<unsigned int S, unsigned int C, unsigned int I>
inline void SBResourceTreeStorage<S, C, I>::Lrotate(SBResourceTreeLinks *x)
{
    RHUnk00641782 lock;
    SBResourceTreeLinks *y = x->m_right;
    x->m_right = y->m_left;
    if (y->m_left != SBResourceTreeTraits<I>::Nil())
        y->m_left->m_parent = x;
    y->m_parent = x->m_parent;
    if (x == Root())
        Root() = y;
    else if (x == x->m_parent->m_left)
        x->m_parent->m_left = y;
    else
        x->m_parent->m_right = y;
    y->m_left = x;
    x->m_parent = y;
}

template<unsigned int S, unsigned int C, unsigned int I>
inline void SBResourceTreeStorage<S, C, I>::Rrotate(SBResourceTreeLinks *x)
{
    RHUnk00641782 lock;
    SBResourceTreeLinks *y = x->m_left;
    x->m_left = y->m_right;
    if (y->m_right != SBResourceTreeTraits<I>::Nil())
        y->m_right->m_parent = x;
    y->m_parent = x->m_parent;
    if (x == Root())
        Root() = y;
    else if (x == x->m_parent->m_right)
        x->m_parent->m_right = y;
    else
        x->m_parent->m_left = y;
    y->m_right = x;
    x->m_parent = y;
}

template<unsigned int S, unsigned int C, unsigned int I>
SBResourceTreeIterator SBResourceTreeStorage<S, C, I>::InsertNode(SBResourceTreeLinks *x, SBResourceTreeLinks *y, const unsigned long &value)
{
    RHUnk00641782 lock;
    SBResourceTreeLinks *z = (SBResourceTreeLinks *)operator new(S);
    z->m_parent = y;
    Color(z) = 0;
    z->m_left = SBResourceTreeTraits<I>::Nil();
    z->m_right = SBResourceTreeTraits<I>::Nil();
    SBResourceTreeTraits<I>::Construct(&z->m_key, value);
    ++m_size;
    if (y == m_head || x != SBResourceTreeTraits<I>::Nil() || value < y->m_key) {
        y->m_left = z;
        if (y == m_head) {
            Root() = z;
            Rightmost() = z;
        } else if (y == Leftmost())
            Leftmost() = z;
    } else {
        y->m_right = z;
        if (y == Rightmost())
            Rightmost() = z;
    }
    for (x = z; x != Root() && Color(x->m_parent) == 0; ) {
        if (x->m_parent == SBResourceLeft(x->m_parent->m_parent)) {
            y = x->m_parent->m_parent->m_right;
            if (Color(y) == 0) {
                Color(x->m_parent) = 1;
                Color(y) = 1;
                Color(x->m_parent->m_parent) = 0;
                x = x->m_parent->m_parent;
            } else {
                if (x == x->m_parent->m_right) {
                    x = x->m_parent;
                    Lrotate(x);
                }
                Color(x->m_parent) = 1;
                Color(x->m_parent->m_parent) = 0;
                Rrotate(x->m_parent->m_parent);
            }
        } else {
            y = SBResourceLeft(x->m_parent->m_parent);
            if (Color(y) == 0) {
                Color(x->m_parent) = 1;
                Color(y) = 1;
                Color(x->m_parent->m_parent) = 0;
                x = x->m_parent->m_parent;
            } else {
                if (x == x->m_parent->m_left) {
                    x = x->m_parent;
                    Rrotate(x);
                }
                Color(x->m_parent) = 1;
                Color(x->m_parent->m_parent) = 0;
                Lrotate(x->m_parent->m_parent);
            }
        }
    }
    Color(Root()) = 1;
    return SBResourceTreeIterator(z);
}

template<unsigned int S, unsigned int C, unsigned int I>
inline SBResourceTreeLinks *SBResourceTreeStorage<S, C, I>::Minimum(SBResourceTreeLinks *node)
{
    RHUnk00641782 lock;
    while (node->m_left != SBResourceTreeTraits<I>::Nil())
        node = node->m_left;
    return node;
}

template<unsigned int S, unsigned int C, unsigned int I>
inline SBResourceTreeLinks *SBResourceTreeStorage<S, C, I>::Maximum(SBResourceTreeLinks *node)
{
    RHUnk00641782 lock;
    while (node->m_right != SBResourceTreeTraits<I>::Nil())
        node = node->m_right;
    return node;
}

template<unsigned int S, unsigned int C, unsigned int I>
SBResourceTreeIterator SBResourceTreeStorage<S, C, I>::EraseNode(SBResourceTreeLinks *node)
{
    SBResourceTreeLinks *z = node;
    SBResourceTreeTraits<I>::Advance(node);
    SBResourceTreeLinks *y = z;
    RHUnk00641782 lock;
    SBResourceTreeLinks *x;
    if (SBResourceLeft(y) == SBResourceTreeTraits<I>::Nil())
        x = SBResourceRight(y);
    else if (SBResourceRight(y) == SBResourceTreeTraits<I>::Nil())
        x = SBResourceLeft(y);
    else {
        y = Minimum(SBResourceRight(y));
        x = y->m_right;
    }
    if (y != z) {
        z->m_left->m_parent = y;
        y->m_left = z->m_left;
        if (y == z->m_right)
            x->m_parent = y;
        else {
            x->m_parent = y->m_parent;
            y->m_parent->m_left = x;
            y->m_right = z->m_right;
            z->m_right->m_parent = y;
        }
        if (Root() == z)
            Root() = y;
        else if (z->m_parent->m_left == z)
            z->m_parent->m_left = y;
        else
            z->m_parent->m_right = y;
        y->m_parent = z->m_parent;
        std::swap(Color(z), Color(y));
        y = z;
    } else {
        x->m_parent = y->m_parent;
        if (Root() == z)
            Root() = x;
        else if (z->m_parent->m_left == z)
            z->m_parent->m_left = x;
        else
            z->m_parent->m_right = x;
        if (Leftmost() == z) {
            if (z->m_right == SBResourceTreeTraits<I>::Nil())
                Leftmost() = z->m_parent;
            else
                Leftmost() = Minimum(x);
        }
        if (Rightmost() == z) {
            if (z->m_left == SBResourceTreeTraits<I>::Nil())
                Rightmost() = z->m_parent;
            else
                Rightmost() = Maximum(x);
        }
    }
    if (Color(y) == 1) {
        while (x != Root() && Color(x) == 1) {
            if (x == x->m_parent->m_left) {
                SBResourceTreeLinks *w = x->m_parent->m_right;
                if (Color(w) == 0) {
                    Color(w) = 1;
                    Color(x->m_parent) = 0;
                    Lrotate(x->m_parent);
                    w = x->m_parent->m_right;
                }
                if (Color(w->m_left) == 1 && Color(w->m_right) == 1) {
                    Color(w) = 0;
                    x = x->m_parent;
                } else {
                    if (Color(w->m_right) == 1) {
                        Color(w->m_left) = 1;
                        Color(w) = 0;
                        Rrotate(w);
                        w = x->m_parent->m_right;
                    }
                    Color(w) = Color(x->m_parent);
                    Color(x->m_parent) = 1;
                    Color(w->m_right) = 1;
                    Lrotate(x->m_parent);
                    break;
                }
            } else {
                SBResourceTreeLinks *w = x->m_parent->m_left;
                if (Color(w) == 0) {
                    Color(w) = 1;
                    Color(x->m_parent) = 0;
                    Rrotate(x->m_parent);
                    w = x->m_parent->m_left;
                }
                if (Color(w->m_right) == 1 && Color(w->m_left) == 1) {
                    Color(w) = 0;
                    x = x->m_parent;
                } else {
                    if (Color(w->m_left) == 1) {
                        Color(w->m_right) = 1;
                        Color(w) = 0;
                        Lrotate(w);
                        w = x->m_parent->m_left;
                    }
                    Color(w) = Color(x->m_parent);
                    Color(x->m_parent) = 1;
                    Color(w->m_left) = 1;
                    Rrotate(x->m_parent);
                    break;
                }
            }
        }
        Color(x) = 1;
    }
    SBResourceTreeTraits<I>::DestroyValue(y);
    operator delete(y);
    --m_size;
    return SBResourceTreeIterator(node);
}

// FUNCTION: GAME 0x00605220
SBResourceManager::Node<unsigned long> *SBResourceManager::Tree44::FUN_00605220(const unsigned long &key)
{
    RHUnk00641782 lock;
    return SBResourceLowerBound(m_head, g_unk0x006c1854, key);
}

// FUNCTION: GAME 0x00605270
void SBResourceTreePrevious44::FUN_00605270()
{
    RHUnk00641782 lock;
    if (*(int *)((char *)m_node + 0x30) == 0 && m_node->m_parent->m_parent == m_node)
        m_node = m_node->m_right;
    else if (SBResourceLeft(m_node) != g_unk0x006c1854) {
        m_node = SBResourceMax44(SBResourceLeft(m_node));
    } else {
        SBResourceTreeLinks *parent;
        while (m_node == (parent = m_node->m_parent)->m_left)
            m_node = parent;
        m_node = parent;
    }
}

// FUNCTION: GAME 0x00605330
SBResourceManager::ResourceNode *SBResourceManager::Tree54::FUN_00605330(const unsigned long &key)
{
    RHUnk00641782 lock;
    return SBResourceLowerBound(m_head, g_unk0x006c185c, key);
}

// FUNCTION: GAME 0x00605380
void SBResourceTreePrevious54::FUN_00605380()
{
    RHUnk00641782 lock;
    if (*(int *)((char *)m_node + 0x1c) == 0 && m_node->m_parent->m_parent == m_node)
        m_node = m_node->m_right;
    else if (SBResourceLeft(m_node) != g_unk0x006c185c) {
        m_node = SBResourceMax54(SBResourceLeft(m_node));
    } else {
        SBResourceTreeLinks *parent;
        while (m_node == (parent = m_node->m_parent)->m_left)
            m_node = parent;
        m_node = parent;
    }
}

// FUNCTION: GAME 0x00605440
SBResourceUnk00605440Node *SBResourceUnk00605440::FUN_00605440(const unsigned long &key)
{
    RHUnk00641782 lock;
    return SBResourceLowerBound(m_head, g_unk0x006c1864, key);
}

// FUNCTION: GAME 0x00605490
void SBResourceTreePrevious64::FUN_00605490()
{
    RHUnk00641782 lock;
    if (*(int *)((char *)m_node + 0x1c) == 0 && m_node->m_parent->m_parent == m_node)
        m_node = m_node->m_right;
    else if (SBResourceLeft(m_node) != g_unk0x006c1864) {
        m_node = SBResourceMax64(SBResourceLeft(m_node));
    } else {
        SBResourceTreeLinks *parent;
        while (m_node == (parent = m_node->m_parent)->m_left)
            m_node = parent;
        m_node = parent;
    }
}

// FUNCTION: GAME 0x00605550
SBResourceUnkKeyNode *SBResourceManager::Tree74::FUN_00605550(const unsigned long &key)
{
    RHUnk00641782 lock;
    return SBResourceLowerBound(m_head, g_unk0x006c186c, key);
}

// FUNCTION: GAME 0x006055a0
void SBResourceTreePrevious74::FUN_006055a0()
{
    RHUnk00641782 lock;
    if (*(int *)((char *)m_node + 0x3c) == 0 && m_node->m_parent->m_parent == m_node)
        m_node = m_node->m_right;
    else if (SBResourceLeft(m_node) != g_unk0x006c186c) {
        m_node = SBResourceMax74(SBResourceLeft(m_node));
    } else {
        SBResourceTreeLinks *parent;
        while (m_node == (parent = m_node->m_parent)->m_left)
            m_node = parent;
        m_node = parent;
    }
}

// FUNCTION: GAME 0x00605660
SBResourceManager::Node<SBResourceManager::Element> *SBResourceManager::Tree84::FUN_00605660(const unsigned long &key)
{
    RHUnk00641782 lock;
    return SBResourceLowerBound(m_head, g_unk0x006c1874, key);
}

// FUNCTION: GAME 0x006056b0
void SBResourceTreePrevious84::FUN_006056b0()
{
    RHUnk00641782 lock;
    if (*(int *)((char *)m_node + 0x3c) == 0 && m_node->m_parent->m_parent == m_node)
        m_node = m_node->m_right;
    else if (SBResourceLeft(m_node) != g_unk0x006c1874) {
        m_node = SBResourceMax84(SBResourceLeft(m_node));
    } else {
        SBResourceTreeLinks *parent;
        while (m_node == (parent = m_node->m_parent)->m_left)
            m_node = parent;
        m_node = parent;
    }
}

template<class T> __forceinline T *SBResourceUpperBound(T *const &head, SBResourceTreeLinks *const &nil, const unsigned long &key)
{
    SBResourceTreeLinks *node = ((SBResourceTreeLinks *)head)->m_parent;
    SBResourceTreeLinks *found = (SBResourceTreeLinks *)head;
    while (node != nil) {
        if (key < node->m_key) {
            found = node;
            node = node->m_left;
        } else
            node = node->m_right;
    }
    return (T *)found;
}

// FUNCTION: GAME 0x00605770
SBResourceManager::Node<unsigned long> *SBResourceManager::Tree44::FUN_00605770(const unsigned long &key)
{
    RHUnk00641782 lock;
    return SBResourceUpperBound(m_head, g_unk0x006c1854, key);
}

// FUNCTION: GAME 0x006057c0
void SBResourceUnkAdvance::FUN_006057c0()
{
    RHUnk00641782 lock;
    if (m_node->m_right != g_unk0x006c1854) {
        SBResourceTreeLinks *first = m_node->m_right;
        {
            RHUnk00641782 inner;
            while (first->m_left != g_unk0x006c1854)
                first = first->m_left;
        }
        m_node = first;
    } else {
        SBResourceTreeLinks *parent;
        while (m_node == (parent = m_node->m_parent)->m_right)
            m_node = parent;
        if (m_node->m_right != parent)
            m_node = parent;
    }
}

// FUNCTION: GAME 0x00605870
void SBResourceTreeIterator54::FUN_00605870()
{
    RHUnk00641782 lock;
    if (m_node->m_right != g_unk0x006c185c) {
        SBResourceTreeLinks *first = m_node->m_right;
        {
            RHUnk00641782 inner;
            while (first->m_left != g_unk0x006c185c)
                first = first->m_left;
        }
        m_node = first;
    } else {
        SBResourceTreeLinks *parent;
        while (m_node == (parent = m_node->m_parent)->m_right)
            m_node = parent;
        if (m_node->m_right != parent)
            m_node = parent;
    }
}

// FUNCTION: GAME 0x00605920
void SBResourceTreeIterator64::FUN_00605920()
{
    RHUnk00641782 lock;
    if (m_node->m_right != g_unk0x006c1864) {
        SBResourceTreeLinks *first = m_node->m_right;
        {
            RHUnk00641782 inner;
            while (first->m_left != g_unk0x006c1864)
                first = first->m_left;
        }
        m_node = first;
    } else {
        SBResourceTreeLinks *parent;
        while (m_node == (parent = m_node->m_parent)->m_right)
            m_node = parent;
        if (m_node->m_right != parent)
            m_node = parent;
    }
}

// FUNCTION: GAME 0x006059d0
SBResourceUnkKeyNode *SBResourceManager::Tree74::FUN_006059d0(const unsigned long &key)
{
    RHUnk00641782 lock;
    return SBResourceUpperBound(m_head, g_unk0x006c186c, key);
}

// FUNCTION: GAME 0x00605a20
void SBResourceTreeIterator74::FUN_00605a20()
{
    RHUnk00641782 lock;
    if (m_node->m_right != g_unk0x006c186c) {
        SBResourceTreeLinks *first = m_node->m_right;
        {
            RHUnk00641782 inner;
            while (first->m_left != g_unk0x006c186c)
                first = first->m_left;
        }
        m_node = first;
    } else {
        SBResourceTreeLinks *parent;
        while (m_node == (parent = m_node->m_parent)->m_right)
            m_node = parent;
        if (m_node->m_right != parent)
            m_node = parent;
    }
}

// FUNCTION: GAME 0x00605ad0
SBResourceManager::Node<SBResourceManager::Element> *SBResourceManager::Tree84::FUN_00605ad0(const unsigned long &key)
{
    RHUnk00641782 lock;
    return SBResourceUpperBound(m_head, g_unk0x006c1874, key);
}

// FUNCTION: GAME 0x00605b20
void SBResourceTreeIterator84::FUN_00605b20()
{
    RHUnk00641782 lock;
    if (m_node->m_right != g_unk0x006c1874) {
        SBResourceTreeLinks *first = m_node->m_right;
        {
            RHUnk00641782 inner;
            while (first->m_left != g_unk0x006c1874)
                first = first->m_left;
        }
        m_node = first;
    } else {
        SBResourceTreeLinks *parent;
        while (m_node == (parent = m_node->m_parent)->m_right)
            m_node = parent;
        if (m_node->m_right != parent)
            m_node = parent;
    }
}

#include <new>

// FUNCTION: GAME 0x00605bd0
SBResourceArrayLifecycle74::~SBResourceArrayLifecycle74()
{
    m_values.clear();
}

// Parked: target expands SBArray insertion with separately owned size/copy/destroy helpers.
// STUB: GAME 0x00605ce0
void SBResourceConstructArray44(unsigned long *output, const unsigned long &value)
{
    typedef std::pair<const unsigned long, SBResourceSurfaceArray> Value;
    new (output) Value((const Value &)value);
}

// FUNCTION: GAME 0x00605df0
void SBResourceConstructMouse(SBResourceMousePair *output, const SBResourceMousePair &value)
{
    new (output) SBResourceMousePair(value);
}

template<> SBResourceTextArray<wchar_t>::SBResourceTextArray(const SBResourceTextArray &other)
{
    const Text *first = other.m_values.begin();
    const Text *last = other.m_values.end();
    m_values.clear();
    void (Values::*insert)(Text *, const Text *, const Text *) = &Values::insert;
    (m_values.*insert)(m_values.begin(), first, last);
    m_changed = true;
}

template<> SBResourceTextArray<char>::SBResourceTextArray(const SBResourceTextArray &other)
{
    const Text *first = other.m_values.begin();
    const Text *last = other.m_values.end();
    m_values.clear();
    void (Values::*insert)(Text *, const Text *, const Text *) = &Values::insert;
    (m_values.*insert)(m_values.begin(), first, last);
    m_changed = true;
}

// Parked: member allocator stores, scalar-destruction calls and EH layout differ.
// STUB: GAME 0x00605e60
void SBResourceConstructArray74(unsigned long *output, const unsigned long &value)
{
    typedef std::pair<const unsigned long, SBResourceTextArray<wchar_t> > Value;
    new (output) Value((const Value &)value);
}

// Parked: member construction/EH and scalar destruction differ; narrow npos folds.
// STUB: GAME 0x00605f50
void SBResourceConstructArray84(unsigned long *output, const unsigned long &value)
{
    typedef std::pair<const unsigned long, SBResourceTextArray<char> > Value;
    new (output) Value((const Value &)value);
}

// FUNCTION: GAME 0x006068e0
void SBResourceDestroyWideString(std::wstring *value)
{
    value->~basic_string();
}

class SBResourceWideValues
{
public:
    std::vector<std::wstring> m_values;
    void FUN_00606960();
};

// FUNCTION: GAME 0x00606960
void SBResourceWideValues::FUN_00606960()
{
    m_values.erase(m_values.begin(), m_values.end());
}

class RHScriptFXArray
{
public:
    void **Unk004fe420(void **, void **, void **);
    void Unk005008e0(void **, void **);
};

class RHUnk00597a70;
void FUN_0059fb00(RHUnk00597a70 **, RHUnk00597a70 *const &);
void **FUN_004598e0(void **, void **, void **);

struct SBResourceArrayStorage
{
    char m_allocator[4];
    unsigned long *m_first;
    unsigned long *m_last;
    unsigned long *m_end;
    unsigned long *begin() { return m_first; }
    unsigned long *end() { return m_last; }
    unsigned int Size()
    {
        unsigned int (std::vector<unsigned long>::*size)() const = &std::vector<unsigned long>::size;
        return (((std::vector<unsigned long> *)this)->*size)();
    }
    static unsigned long *Copy(unsigned long *first, unsigned long *last, unsigned long *output)
    {
        while (first != last) {
            *output = *first;
            ++output;
            ++first;
        }
        return output;
    }
};

// Parked: source-bound registers, insertion temporaries and allocation scheduling differ.
// STUB: GAME 0x006069e0
void SBResourceSurfaceArray::FUN_006069e0(const SBResourceSurfaceArray &other)
{
    const unsigned long *sourceFirst = other.m_values.begin();
    const unsigned long *sourceLast = other.m_values.end();
    SBResourceArrayStorage &values = *(SBResourceArrayStorage *)&m_values;
    values.m_last = SBResourceArrayStorage::Copy(values.end(), values.end(), values.begin());
    unsigned int count = sourceLast - sourceFirst;
    unsigned long *position = values.begin();
    RHScriptFXArray *array = (RHScriptFXArray *)&values;
    if ((unsigned int)(values.m_end - values.m_last) < count) {
        unsigned int size = values.m_first == 0 ? 0 : values.m_last - values.m_first;
        unsigned int grow = count < size ? size : count;
        int capacity = (values.m_first == 0 ? 0 : values.m_last - values.m_first) + grow;
        unsigned long *storage = std::_Allocate(capacity, (unsigned long *)0);
        unsigned long *output = storage;
        for (unsigned long *first = values.begin(); first != position; ++output, ++first)
            FUN_0059fb00((RHUnk00597a70 **)output, *(RHUnk00597a70 *const *)first);
        for (const unsigned long *source = sourceFirst; source != sourceLast; ++output, ++source)
            FUN_0059fb00((RHUnk00597a70 **)output, *(RHUnk00597a70 *const *)source);
        array->Unk004fe420((void **)position, (void **)values.end(), (void **)output);
        array->Unk005008e0((void **)values.begin(), (void **)values.end());
        operator delete(values.m_first);
        values.m_end = storage + capacity;
        values.m_last = storage + values.Size() + count;
        values.m_first = storage;
    } else if ((unsigned int)(values.m_last - position) < count) {
        array->Unk004fe420((void **)position, (void **)values.end(), (void **)(position + count));
        array->Unk004fe420((void **)(sourceFirst + (values.m_last - position)), (void **)sourceLast, (void **)values.end());
        FUN_004598e0((void **)sourceFirst, (void **)(sourceFirst + (values.m_last - position)), (void **)position);
        values.m_last += count;
    } else if (count > 0) {
        array->Unk004fe420((void **)(values.end() - count), (void **)values.end(), (void **)values.end());
        unsigned long *first = values.end() - count;
        unsigned long *output = values.end();
        while (first != position)
            *--output = *--first;
        FUN_004598e0((void **)sourceFirst, (void **)sourceLast, (void **)position);
        values.m_last += count;
    }
    m_changed = true;
}

void EmitSBResourceSurfaceCopy(SBResourceSurfaceArray *values, const SBResourceSurfaceArray &other)
{
    values->FUN_006069e0(other);
}

void EmitSBResourceManager(SBResourceManager *resource)
{
    ((SBResourceUnk005fe790 *)resource)->~SBResourceUnk005fe790();
    ((SBResourceUnk005fe880 *)resource)->~SBResourceUnk005fe880();
    SBResourceManager::Tree44::Iterator position;
    resource->FUN_006001d0(position);
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
    resource->m_74.FUN_006059d0(value);
    resource->m_84.FUN_00605ad0(value);
    ((SBResourceTreeIterator54 *)&position)->FUN_00605870();
    ((SBResourceTreeIterator64 *)&position)->FUN_00605920();
    ((SBResourceTreeIterator74 *)&position)->FUN_00605a20();
    ((SBResourceTreeIterator84 *)&position)->FUN_00605b20();
    ((SBResourceTreePrevious44 *)&position)->FUN_00605270();
    ((SBResourceTreePrevious54 *)&position)->FUN_00605380();
    ((SBResourceTreePrevious64 *)&position)->FUN_00605490();
    ((SBResourceTreePrevious74 *)&position)->FUN_006055a0();
    ((SBResourceTreePrevious84 *)&position)->FUN_006056b0();
    resource->m_84.FUN_00601ee0(value);
    ((SBResourceTreeStorage<0x34, 0x30, 0x44> *)resource)->Initialize();
    ((SBResourceTreeStorage<0x20, 0x1c, 0x54> *)resource)->Initialize();
    ((SBResourceTreeStorage<0x20, 0x1c, 0x64> *)resource)->Initialize();
    ((SBResourceTreeStorage<0x40, 0x3c, 0x74> *)resource)->Initialize();
    ((SBResourceTreeStorage<0x40, 0x3c, 0x84> *)resource)->Initialize();
    ((SBResourceTreeStorage<0x20, 0x1c, 0x54> *)resource)->Destroy(*(SBResourceTreeLinks **)&position);
    ((SBResourceTreeStorage<0x20, 0x1c, 0x64> *)resource)->Destroy(*(SBResourceTreeLinks **)&position);
    SBResourceConstructMouse((SBResourceMousePair *)resource, *(SBResourceMousePair *)resource);
    SBResourceDestroyWideString((std::wstring *)resource);
    ((SBResourceWideValues *)resource)->FUN_00606960();
    resource->m_44.FUN_00601350(value);
    resource->m_74.FUN_00601b80(value);
    resource->m_84.FUN_00601e90(value);
    ((SBResourceTreeStorage<0x34, 0x30, 0x44> *)resource)->Insert(value);
    ((SBResourceTreeStorage<0x20, 0x1c, 0x54> *)resource)->Insert(value);
    ((SBResourceTreeStorage<0x20, 0x1c, 0x64> *)resource)->Insert(value);
    ((SBResourceTreeStorage<0x40, 0x3c, 0x74> *)resource)->Insert(value);
    ((SBResourceTreeStorage<0x40, 0x3c, 0x84> *)resource)->Insert(value);
    ((SBResourceTreeStorage<0x20, 0x1c, 0x54> *)resource)->EraseRange(0, 0);
    ((SBResourceTreeStorage<0x20, 0x1c, 0x64> *)resource)->EraseRange(0, 0);
    ((SBResourceTreeStorage<0x40, 0x3c, 0x84> *)resource)->Dispose();
    ((SBResourceTreeStorage<0x18, 0x14, 0x34> *)resource)->Initialize();
}
