#ifndef RHELEMENTSCROLLSTATICSTORAGE_H
#define RHELEMENTSCROLLSTATICSTORAGE_H

#include <vector>

class RHElementScroll;

class RHElementScrollStaticStorage
{
public:
    static std::vector<RHElementScroll *> aAllScrolls;
};

#define g_unk0x6c09dc (*(RHElementScroll ***)((char *)&RHElementScrollStaticStorage::aAllScrolls + 4))
#define g_unk0x006c09e0 (*(RHElementScroll ***)((char *)&RHElementScrollStaticStorage::aAllScrolls + 8))

#endif
