#include "SBNullstr.h"
#include "RHElementProjectile.h"

#define RH_PROJECTILE_ACCESS(field, width, line) \
    if (file.Access(&(field), width) < 0) \
    { \
        SBString *error = file.GetError(); \
        const char *reason = error->m_chars ? error->m_chars : ""; \
        SBAssert(0, g_projectileFile, line, "Serialize failed reason is %s", reason); \
        return false; \
    }

// GLOBAL: GAME 0x006aed38
static const char g_projectileFile[] = "P:\\Robin Hood\\RHelementprojectile.cpp";
// GLOBAL: GAME 0x006aed60
static const char g_projectileNestedFile[] = "P:\\Robin Hood\\RHelementprojectile.cpp";

// Parked: frame and cursor scheduling; unannotated to preserve matched callers.
bool RHElementProjectile::Serialize(SBFile &file)
{
    unsigned count;
    // STRING: GAME 0x006aed88
    RHSerializeName(file, "RHElementProjectile");
    RH_PROJECTILE_ACCESS(m_132, 1, 1404);
    RH_PROJECTILE_ACCESS(m_133, 1, 1405);
    RH_PROJECTILE_ACCESS(m_135, 1, 1406);
    RH_PROJECTILE_ACCESS(m_130, 2, 1407);
    RH_PROJECTILE_ACCESS(m_118, 16, 1408);
    if (!((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fbec0(file, m_120))
    {
        SBAssert(1, g_projectileNestedFile, 1409, "Serialization failed");
        return false;
    }
    RH_PROJECTILE_ACCESS(m_128, 2, 1411);
    m_100.Serialize(file);
    unsigned version = file.m_version;
    if (version >= 44)
        m_10c.Serialize(file);
    g_pEngine->FUN_004c3bd0(file, m_12c);
    if (!file.m_bLoading)
    {
        count = m_138.m_count;
        RH_PROJECTILE_ACCESS(count, 4, 1427);
        for (unsigned i = 0; i < count; ++i)
        {
            RHProjectileList &list = m_138;
            ((RHTitbitList *)&list)->At(i);
            RHUnk00613e90 *value = (RHUnk00613e90 *)list.m_cursor.node->data;
            RH_PROJECTILE_ACCESS(value->m_0c, 2, 1433);
            RH_PROJECTILE_ACCESS(value->m_0e, 1, 1434);
            RH_PROJECTILE_ACCESS(value->m_10, 4, 1435);
            value->m_00.Serialize(file);
        }
    }
    else
    {
        RH_PROJECTILE_ACCESS(count, 4, 1441);
        m_138.Resize(count);
        for (unsigned i = 0; i < count; ++i)
        {
            RHUnk00613e90 *value = new RHUnk00613e90;
            RH_PROJECTILE_ACCESS(value->m_0c, 2, 1448);
            RH_PROJECTILE_ACCESS(value->m_0e, 1, 1449);
            RH_PROJECTILE_ACCESS(value->m_10, 4, 1450);
            value->m_00.Serialize(file);
            m_138.Get(i) = value;
        }
    }
    RHElementObject::Serialize(file);
    if (file.m_version < 44)
    {
        const RHUnk005df510 *value;
        if (m_138.m_count == 0)
            value = (RHUnk005df510 *)((char *)*(void **)((char *)this + 0x50) + 0x10);
        else
            value = (RHUnk005df510 *)m_138.m_head->previous->data;
        m_10c = *value;
    }
    return true;
}

void RHElementProjectile::Emit(SBFile &file)
{
    Serialize(file);
}
