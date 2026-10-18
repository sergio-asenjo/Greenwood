#include "SBNullstr.h"
#include "RHSequenceElementGeneric.h"

// STRING: GAME 0x006b7550
#define RH_GENERIC_FILE "P:\\Robin Hood\\RHSequenceElementGeneric.cpp"

#define RH_GENERIC_ACCESS(value, size, line) \
    if (file.Access(&(value), size) < 0) \
    { \
        SBString *error = file.GetError(); \
        SBAssert(0, RH_GENERIC_FILE, line, "Serialize failed reason is %s", error->m_chars ? error->m_chars : ""); \
        return false; \
    }

class RHUnk00641782
{
public:
    RHUnk00641782();
    ~RHUnk00641782();
};

// GLOBAL: GAME 0x006c1034
RHGenericNode *g_unk0x006c1034;

inline RHGenericNode *RHGenericMap::Minimum(RHGenericNode *node)
{
    RHUnk00641782 lock;
    while (Left(node) != g_unk0x006c1034)
        node = Left(node);
    return node;
}

inline RHGenericNode *RHGenericMap::Maximum(RHGenericNode *node)
{
    RHUnk00641782 lock;
    while (Right(node) != g_unk0x006c1034)
        node = Right(node);
    return node;
}

struct RHUnk00571160Position;

class RHScriptPositionList
{
public:
    static void Unk00588190(RHUnk00571160Position *destination, const RHUnk00571160Position *source);
};

inline RHGenericMap &RHGenericMap::Assign(const RHGenericMap &other)
{
    if (this != &other)
    {
        Clear();
        ((char *)this)[1] = ((const char *)&other)[1];
        RHUnk00641782 lock;
        RHGenericNode *root;
        {
            RHGenericNode *node = other.head->parent;
            RHGenericNode *parent = head;
            RHUnk00641782 inner;
            root = node;
            while (node != g_unk0x006c1034)
            {
                RHGenericNode *copy = FUN_005880b0(parent, node->color);
                if (root == node)
                    root = copy;
                copy->right = FUN_00587f80(node->right, copy);
                RHScriptPositionList::Unk00588190((RHUnk00571160Position *)&copy->key, (const RHUnk00571160Position *)&node->key);
                parent->left = copy;
                node = node->left;
                parent = copy;
            }
            parent->left = g_unk0x006c1034;
        }
        Root() = root;
        unsigned int size = other.count;
        count = size;
        if (Root() != g_unk0x006c1034)
        {
            Leftmost() = Minimum(Root());
            Rightmost() = Maximum(Root());
        }
        else
        {
            head->left = head;
            head->right = head;
        }
    }
    return *this;
}

// GLOBAL: GAME 0x006c1030
unsigned int g_unk0x006c1030;

class RHUnk00584d60
{
public:
    RHUnk00584d60();
    RHUnk00584d60(unsigned short level, int command, void *actor);
    ~RHUnk00584d60();
    char m_00[4];
    unsigned char m_04;
    char m_05[0x5f];
};

inline void RHGenericMap::Initialize()
{
    char compare;
    char allocator;
    m_00[0] = allocator;
    m_00[1] = compare;
    multi = false;
    RHUnk00641782 lock;
    if (g_unk0x006c1034 == 0)
    {
        g_unk0x006c1034 = Buynode(0, 1);
        Left(g_unk0x006c1034) = 0, Right(g_unk0x006c1034) = 0;
    }
    ++g_unk0x006c1030;
    head = Buynode(g_unk0x006c1034, 0), count = 0;
    Leftmost() = head, Rightmost() = head;
}

class RHUnk5865a0 : public RHUnk00584d60
{
public:
    RHUnk5865a0();
    RHGenericMap m_64;
};

// FUNCTION: GAME 0x005865a0
RHUnk5865a0::RHUnk5865a0()
{
    m_64.Initialize();
    *(unsigned *)this = 0x679d5c;
    m_04 = 2;
}

class RHUnk005866a0 : public RHUnk00584d60
{
public:
    RHUnk005866a0(unsigned short level, int command, void *actor);
    ~RHUnk005866a0();
    void *FUN_00586680(unsigned int flags);
    RHGenericMap m_64;
};

// FUNCTION: GAME 0x00586680
void *RHUnk005866a0::FUN_00586680(unsigned int flags)
{
    this->~RHUnk005866a0();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005866a0
RHUnk005866a0::RHUnk005866a0(unsigned short level, int command, void *actor)
    : RHUnk00584d60(level, command, actor)
{
    m_64.Initialize();
    *(unsigned *)this = 0x679d5c;
    m_04 = 2;
}

// Parked: head load is hoisted above the literal vptr store; target loads it after.
// STUB: GAME 0x00586790
RHUnk005866a0::~RHUnk005866a0()
{
    *(unsigned *)this = 0x679d5c;
    m_64.FUN_005874d0(RHGenericIterator(m_64.head->left), RHGenericIterator(m_64.head));
    RHGenericMap &map = m_64;
    map.Freenode(map.head);
    map.head = 0, map.count = 0;
    {
        RHUnk00641782 lock;
        if (--g_unk0x006c1030 == 0)
        {
            map.Freenode(g_unk0x006c1034);
            g_unk0x006c1034 = 0;
        }
    }
}

#include "RHSequenceElementCalls.h"

// FUNCTION: GAME 0x00586840
RHSequenceElementGeneric *RHSequenceElementGeneric::FUN_00586840()
{
    RHSequenceElementGeneric *copy = (RHSequenceElementGeneric *)new RHUnk005866a0(
        *(unsigned short *)((char *)this + 0x14), *(int *)((char *)this + 0x10), *(void **)((char *)this + 0x48));
    ((RHSequenceElementCalls *)copy)->FUN_00585df0((RHSequenceElementCalls *)this);
    const RHGenericMap &source = m_64;
    RHGenericMap &properties = copy->m_64;
    properties.Assign(source);
    return copy;
}

// FUNCTION: GAME 0x00586a30
bool RHSequenceElementGeneric::Serialize(SBFile &file, bool pointers)
{
    FUN_00584ef0(file, pointers);
    unsigned int count;
    int key;
    RHGenericIterator iterator;
    if (!file.m_bLoading)
    {
        count = m_64.count;
        RH_GENERIC_ACCESS(count, 4, 86);
        iterator = RHGenericIterator(m_64.head->left);
        for (unsigned int index = 0; index < count; iterator.FUN_00587ed0(), ++index)
        {
            key = iterator.node->key;
            RH_GENERIC_ACCESS(key, 4, 92);
            switch (key)
            {
            case 6:
            case 28:
            case 33:
            case 40:
            case 41:
            case 42:
                g_pEngine->SerializeElementPointer(file, *(RHElement **)(&iterator.node->value));
                break;
            case 23:
            case 24:
                ((RHFastFindGrid *)g_unk0x6c0a9c)->SerializeLinePointer(file, (void *&)iterator.node->value.m_0);
                break;
            case 36:
                ((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fc030(file, (void *&)iterator.node->value.m_0);
                break;
            case 35:
                ((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fc030(file, (void *&)iterator.node->value.m_0);
                break;
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
            case 19:
            case 20:
            case 21:
            case 22:
            case 25:
            case 26:
            case 27:
            case 29:
            case 30:
            case 31:
            case 32:
            case 34:
            case 37:
            case 38:
            case 39:
                RH_GENERIC_ACCESS(iterator.node->value, 12, 153);
                break;
            default:
                break;
            }
        }
    }
    else
    {
        RHGenericValue vector;
        RHGenericPair property;
        property.key = 0;
        property.value = vector;
        RH_GENERIC_ACCESS(count, 4, 169);
        RHGenericMap &properties = m_64;
        properties.Clear();
        for (unsigned int index = 0; index < count; ++index)
        {
            RH_GENERIC_ACCESS(key, 4, 174);
            property.key = key;
            switch (key)
            {
            case 6:
            case 28:
            case 33:
            case 40:
            case 41:
            case 42:
                g_pEngine->SerializeElementPointer(file, *(RHElement **)(&property.value));
                break;
            case 23:
            case 24:
                ((RHFastFindGrid *)g_unk0x6c0a9c)->SerializeLinePointer(file, (void *&)property.value.m_0);
                break;
            case 36:
                ((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fc030(file, (void *&)property.value.m_0);
                break;
            case 35:
                ((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fc030(file, (void *&)property.value.m_0);
                break;
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
            case 19:
            case 20:
            case 21:
            case 22:
            case 25:
            case 26:
            case 27:
            case 29:
            case 30:
            case 31:
            case 32:
            case 34:
            case 37:
            case 38:
            case 39:
                RH_GENERIC_ACCESS(vector, 12, 237);
                property.value = vector;
                break;
            default:
                break;
            }
            RHGenericPair pair(property);
            properties.FUN_005873a0(pair);
        }
    }
    return true;
}

// FUNCTION: GAME 0x00586e50
void RHSequenceElementGeneric::FUN_00586e50(int key, unsigned char value)
{
    RHGenericValue vector;
    vector.m_0 = value;
    RHGenericPair property;
    property.key = key;
    property.value = vector;
    m_64.FUN_005873a0(property);
}

struct RHHumanMapNode
{
    RHHumanMapNode *m_left;
    RHHumanMapNode *m_parent;
    RHHumanMapNode *m_right;
    int m_key;
    unsigned int m_value;
};

struct RHHumanMapIterator
{
    RHHumanMapNode *m_node;
    RHHumanMapIterator(RHHumanMapNode *node) : m_node(node) {}
    RHHumanMapNode &operator*() const { return *m_node; }
    RHHumanMapNode *operator->() const { return &**this; }
    bool operator==(const RHHumanMapIterator &other) const { return m_node == other.m_node; }
    bool operator!=(const RHHumanMapIterator &other) const { return !(*this == other); }
};

class RHHumanMap
{
public:
    RHHumanMapNode *FUN_00588060(const int &key);
    RHHumanMapIterator end() const { return RHHumanMapIterator(m_head); }
    RHHumanMapIterator find(const int &key)
    {
        RHHumanMapIterator position = FUN_00588060(key);
        return position == end() || key < position->m_key ? end() : position;
    }
    char m_00[4];
    RHHumanMapNode *m_head;
    unsigned int m_08;
    unsigned int m_0c;
};

// FUNCTION: GAME 0x00586f10
void RHSequenceElementGeneric::FUN_00586f10(int key, unsigned long value)
{
    ((RHHumanMap *)&m_64)->find(key)->m_value = value;
}

// Parked: vector-copy scheduling and receiver adjustment differ.
// STUB: GAME 0x00587060
void RHSequenceElementGeneric::FUN_00587060(int key, const RHGenericValue &value)
{
    volatile RHGenericValue vector = value;
    RHGenericPair property;
    property.key = key;
    property.value.m_0 = vector.m_0;
    property.value.m_4 = vector.m_4;
    property.value.m_8 = vector.m_8;
    m_64.FUN_005873a0(property);
}

// FUNCTION: GAME 0x00587110
float RHSequenceElementGeneric::FUN_00587110(int key)
{
    return *(float *)&((RHHumanMap *)&m_64)->find(key)->m_value;
}

void RHSequenceElementGeneric::Emit(SBFile &file, bool pointers)
{
    FUN_00586840();
    Serialize(file, pointers);
}

class RHUnk00613e90
{
public:
    RHUnk00613e90();
    RHUnk00613e90(float x, float y, float z);
    float m_x;
    float m_y;
    float m_z;
};

// Parked: iterator temporary slots and returned-node copy differ.
// STUB: GAME 0x00587290
RHUnk00613e90 RHSequenceElementGeneric::FUN_00587290(int key)
{
    RHUnk00613e90 point;
    RHGenericConstIterator position = m_64.Find(key);
    if (position.node != m_64.head)
    {
        float x = *(float *)&position.node->value.m_0;
        float y = *(float *)&position.node->value.m_4;
        float z = *(float *)&position.node->value.m_8;
        RHUnk00613e90 value(x, y, z);
        point = value;
    }
    return point;
}

void RHSequenceElementGeneric::EmitProperties(int key, const RHGenericValue &value)
{
    FUN_00586e50(key, (unsigned char)value.m_0);
    FUN_00586f10(key, value.m_0);
    FUN_00587060(key, value);
    FUN_00587110(key);
    FUN_00587290(key);
}

inline void RHGenericMap::RotateLeft(RHGenericNode *node)
{
    RHUnk00641782 lock;
    RHGenericNode *right = node->right;
    node->right = right->left;
    if (right->left != g_unk0x006c1034)
        right->left->parent = node;
    right->parent = node->parent;
    if (node == head->parent)
        head->parent = right;
    else if (node == node->parent->left)
        node->parent->left = right;
    else
        node->parent->right = right;
    right->left = node;
    node->parent = right;
}

inline void RHGenericMap::RotateRight(RHGenericNode *node)
{
    RHUnk00641782 lock;
    RHGenericNode *left = node->left;
    node->left = left->right;
    if (left->right != g_unk0x006c1034)
        left->right->parent = node;
    left->parent = node->parent;
    if (node == head->parent)
        head->parent = left;
    else if (node == node->parent->right)
        node->parent->right = left;
    else
        node->parent->left = left;
    left->right = node;
    node->parent = left;
}

// FUNCTION: GAME 0x005874d0
RHGenericIterator RHGenericMap::FUN_005874d0(RHGenericIterator first, RHGenericIterator last)
{
    if (count == 0 || first != begin() || last != end())
    {
        while (first.node != last.node)
            FUN_00587600(first++);
        return first;
    }
    RHUnk00641782 lock;
    {
        RHGenericNode *node = head->parent;
        RHUnk00641782 inner;
        RHGenericNode *next = node;
        while (next != g_unk0x006c1034)
        {
            FUN_00587b40(next->right);
            next = next->left;
            ::operator delete(node);
            node = next;
        }
    }
    head->parent = g_unk0x006c1034;
    count = 0;
    head->left = head;
    head->right = head;
    return begin();
}

// FUNCTION: GAME 0x00587600
RHGenericIterator RHGenericMap::FUN_00587600(RHGenericIterator position)
{
    RHGenericNode *removed = (position++).Node();
    RHGenericNode *erased = removed;
    RHUnk00641782 lock;
    RHGenericNode *replacement;
    if (Left(removed) == g_unk0x006c1034)
        replacement = Right(removed);
    else if (Right(removed) == g_unk0x006c1034)
        replacement = Left(removed);
    else
    {
        removed = Minimum(Right(removed));
        replacement = Right(removed);
    }
    if (removed != erased)
    {
        Parent(Left(erased)) = removed;
        Left(removed) = Left(erased);
        if (removed == Right(erased))
            Parent(replacement) = removed;
        else
        {
            Parent(replacement) = Parent(removed);
            Left(Parent(removed)) = replacement;
            Right(removed) = Right(erased);
            Parent(Right(erased)) = removed;
        }
        if (Root() == erased)
            Root() = removed;
        else if (Left(Parent(erased)) == erased)
            Left(Parent(erased)) = removed;
        else
            Right(Parent(erased)) = removed;
        Parent(removed) = Parent(erased);
        std::swap(Color(removed), Color(erased));
        removed = erased;
    }
    else
    {
        Parent(replacement) = Parent(removed);
        if (Root() == erased)
            Root() = replacement;
        else if (Left(Parent(erased)) == erased)
            Left(Parent(erased)) = replacement;
        else
            Right(Parent(erased)) = replacement;
        if (Leftmost() == erased)
        {
            if (Right(erased) == g_unk0x006c1034)
                Leftmost() = Parent(erased);
            else
                Leftmost() = Minimum(replacement);
        }
        if (Rightmost() == erased)
        {
            if (Left(erased) == g_unk0x006c1034)
                Rightmost() = Parent(erased);
            else
                Rightmost() = Maximum(replacement);
        }
    }
    if (Color(removed) == 1)
    {
        while (replacement != Root() && Color(replacement) == 1)
        {
            if (replacement == Left(Parent(replacement)))
            {
                RHGenericNode *sibling = Right(Parent(replacement));
                if (Color(sibling) == 0)
                {
                    Color(sibling) = 1;
                    Color(Parent(replacement)) = 0;
                    RotateLeft(Parent(replacement));
                    sibling = Right(Parent(replacement));
                }
                if (Color(Left(sibling)) == 1 && Color(Right(sibling)) == 1)
                {
                    Color(sibling) = 0;
                    replacement = Parent(replacement);
                }
                else
                {
                    if (Color(Right(sibling)) == 1)
                    {
                        Color(Left(sibling)) = 1;
                        Color(sibling) = 0;
                        RotateRight(sibling);
                        sibling = Right(Parent(replacement));
                    }
                    Color(sibling) = Color(Parent(replacement));
                    Color(Parent(replacement)) = 1;
                    Color(Right(sibling)) = 1;
                    RotateLeft(Parent(replacement));
                    break;
                }
            }
            else
            {
                RHGenericNode *sibling = Left(Parent(replacement));
                if (Color(sibling) == 0)
                {
                    Color(sibling) = 1;
                    Color(Parent(replacement)) = 0;
                    RotateRight(Parent(replacement));
                    sibling = Left(Parent(replacement));
                }
                if (Color(Right(sibling)) == 1 && Color(Left(sibling)) == 1)
                {
                    Color(sibling) = 0;
                    replacement = Parent(replacement);
                }
                else
                {
                    if (Color(Left(sibling)) == 1)
                    {
                        Color(Right(sibling)) = 1;
                        Color(sibling) = 0;
                        RotateLeft(sibling);
                        sibling = Left(Parent(replacement));
                    }
                    Color(sibling) = Color(Parent(replacement));
                    Color(Parent(replacement)) = 1;
                    Color(Left(sibling)) = 1;
                    RotateRight(Parent(replacement));
                    break;
                }
            }
        }
        Color(replacement) = 1;
    }
    ::operator delete(removed);
    --count;
    return position;
}

// FUNCTION: GAME 0x00587b20
RHGenericIterator RHGenericMap::FUN_00587b20(const int &key)
{
    return RHGenericIterator((RHGenericNode *)((RHHumanMap *)this)->FUN_00588060(key));
}

// FUNCTION: GAME 0x00587b40
void RHGenericMap::FUN_00587b40(RHGenericNode *node)
{
    RHUnk00641782 lock;
    RHGenericNode *next = node;
    while (next != g_unk0x006c1034)
    {
        FUN_00587b40(next->right);
        next = next->left;
        ::operator delete(node);
        node = next;
    }
}

// FUNCTION: GAME 0x00587bd0
RHGenericIterator RHGenericMap::FUN_00587bd0(RHGenericNode *position, RHGenericNode *parent, const RHGenericPair &value)
{
    RHUnk00641782 lock;
    RHGenericNode *inserted = (RHGenericNode *)::operator new(sizeof(RHGenericNode));
    inserted->parent = parent;
    inserted->color = 0;
    inserted->left = g_unk0x006c1034;
    inserted->right = g_unk0x006c1034;
    RHScriptPositionList::Unk00588190((RHUnk00571160Position *)&inserted->key, (const RHUnk00571160Position *)&value);
    ++count;
    if (parent == head || position != g_unk0x006c1034 || value.key < parent->key)
    {
        parent->left = inserted;
        if (parent == head)
        {
            head->parent = inserted;
            head->right = inserted;
        }
        else if (parent == head->left)
            head->left = inserted;
    }
    else
    {
        parent->right = inserted;
        if (parent == head->right)
            head->right = inserted;
    }
    for (position = inserted; position != head->parent && position->parent->color == 0;)
    {
        if (Parent(position) == Left(Parent(Parent(position))))
        {
            parent = position->parent->parent->right;
            if (parent->color == 0)
            {
                position->parent->color = 1;
                parent->color = 1;
                position->parent->parent->color = 0;
                position = position->parent->parent;
            }
            else
            {
                if (position == position->parent->right)
                {
                    position = position->parent;
                    RotateLeft(position);
                }
                position->parent->color = 1;
                position->parent->parent->color = 0;
                RotateRight(position->parent->parent);
            }
        }
        else
        {
            parent = Left(Parent(Parent(position)));
            if (parent->color == 0)
            {
                position->parent->color = 1;
                parent->color = 1;
                position->parent->parent->color = 0;
                position = position->parent->parent;
            }
            else
            {
                if (position == position->parent->left)
                {
                    position = position->parent;
                    RotateRight(position);
                }
                position->parent->color = 1;
                position->parent->parent->color = 0;
                RotateLeft(position->parent->parent);
            }
        }
    }
    head->parent->color = 1;
    return RHGenericIterator(inserted);
}

// FUNCTION: GAME 0x00587ed0
void RHGenericIterator::FUN_00587ed0()
{
    RHUnk00641782 lock;
    if (node->right != g_unk0x006c1034)
    {
        RHGenericNode *next = node->right;
        {
            RHUnk00641782 inner;
            while (next->left != g_unk0x006c1034)
                next = next->left;
        }
        node = next;
    }
    else
    {
        RHGenericNode *parent;
        while (node == (parent = node->parent)->right)
            node = parent;
        if (node->right != parent)
            node = parent;
    }
}

// FUNCTION: GAME 0x00587f80
RHGenericNode *RHGenericMap::FUN_00587f80(RHGenericNode *node, RHGenericNode *parent)
{
    RHUnk00641782 lock;
    RHGenericNode *result = node;
    while (node != g_unk0x006c1034)
    {
        int color = node->color;
        RHGenericNode *copy = (RHGenericNode *)::operator new(sizeof(RHGenericNode));
        copy->parent = parent;
        copy->color = color;
        if (result == node)
            result = copy;
        copy->right = FUN_00587f80(node->right, copy);
        std::_Construct((RHGenericPair *)&copy->key, *(const RHGenericPair *)&node->key);
        parent->left = copy;
        node = node->left;
        parent = copy;
    }
    parent->left = g_unk0x006c1034;
    return result;
}

// FUNCTION: GAME 0x005880b0
RHGenericNode *RHGenericMap::FUN_005880b0(RHGenericNode *parent, int color)
{
    RHGenericNode *node = (RHGenericNode *)::operator new(sizeof(RHGenericNode));
    node->parent = parent;
    node->color = color;
    return node;
}

struct RHGenericTreeAccess
{
    static RHGenericNode *&Left(RHGenericNode *node) { return node->left; }
    static RHGenericNode *&Right(RHGenericNode *node) { return node->right; }
    static RHGenericNode *&Parent(RHGenericNode *node) { return node->parent; }
    static int &Color(RHGenericNode *node) { return node->color; }
    static RHGenericNode *Max(RHGenericNode *node)
    {
        RHUnk00641782 inner;
        while (Right(node) != g_unk0x006c1034)
            node = Right(node);
        return node;
    }
};

// FUNCTION: GAME 0x005880d0
void RHGenericIterator::FUN_005880d0()
{
    RHUnk00641782 lock;
    if (RHGenericTreeAccess::Color(node) == 0 && RHGenericTreeAccess::Parent(RHGenericTreeAccess::Parent(node)) == node)
        node = RHGenericTreeAccess::Right(node);
    else if (RHGenericTreeAccess::Left(node) != g_unk0x006c1034)
        node = RHGenericTreeAccess::Max(RHGenericTreeAccess::Left(node));
    else
    {
        RHGenericNode *parent;
        while (node == RHGenericTreeAccess::Left(parent = RHGenericTreeAccess::Parent(node)))
            node = parent;
        node = parent;
    }
}

void RHGenericMap::EmitTree(RHGenericNode *node)
{
    FUN_00587b20(node->key);
    FUN_00587bd0(node, node, *(RHGenericPair *)&node->key);
    FUN_00587b40(node);
    FUN_00587f80(node, node);
    FUN_005880b0(node, 0);
}

void RHGenericIterator::EmitTree()
{
    FUN_005880d0();
}
