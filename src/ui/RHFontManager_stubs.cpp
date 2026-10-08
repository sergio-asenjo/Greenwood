#include "RHFontManager.h"

RHFontManager::Fonts::~Fonts() {}
// Parked: tree insertion uses CRT critical-section imports.
// STUB: GAME 0x00502c20
RHFontInsertResult RHFontMap::FUN_00502c20(const std::pair<const std::string, void *> &)
{
    RHFontIterator iterator;
    iterator.m_node = 0;
    bool inserted = false;
    return RHFontInsertResult(iterator, inserted);
}

// LIBRARY: GAME 0x006435d7
extern "C" int fgetc(FILE *) { return 0; }

// LIBRARY: GAME 0x00643540
extern "C" int ungetc(int, FILE *) { return 0; }
