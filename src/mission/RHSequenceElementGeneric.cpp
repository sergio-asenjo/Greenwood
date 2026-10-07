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

// Parked: iterator-copy scheduling and counted line-serializer operands differ.
// STUB: GAME 0x00586a30
bool RHSequenceElementGeneric::Serialize(SBFile &file, bool pointers)
{
    FUN_00584ef0(file, pointers);
    unsigned int count;
    int key;
    if (!file.m_bLoading)
    {
        count = m_64.count;
        RH_GENERIC_ACCESS(count, 4, 86);
        RHGenericIterator iterator(m_64.head->left);
        for (unsigned int index = 0; index < count; ++index, iterator.FUN_00587ed0())
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
                g_pEngine->SerializeNestedA(file, &iterator.node->value);
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
        properties.FUN_005874d0(RHGenericIterator(properties.head->left), RHGenericIterator(properties.head));
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
                g_pEngine->SerializeNestedA(file, &property.value);
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

void RHSequenceElementGeneric::Emit(SBFile &file, bool pointers)
{
    Serialize(file, pointers);
}
