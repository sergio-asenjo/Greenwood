#include "RHFontManager.h"

RHFontManager::Fonts::~Fonts() {}
std::string RHFontManager::Get(FILE *, char) { return std::string(); }
void RHFontManager::TrimString(std::string &) {}
RHFontInsertResult::RHFontInsertResult(const RHFontIterator &iterator, const bool &inserted)
    : first(iterator), second(inserted) {}
RHFontInsertResult RHFontMap::FUN_00502c20(const std::pair<const std::string, void *> &)
{
    RHFontIterator iterator;
    iterator.m_node = 0;
    bool inserted = false;
    return RHFontInsertResult(iterator, inserted);
}

// LIBRARY: GAME 0x006435d7
extern "C" int fgetc(FILE *) { return 0; }
