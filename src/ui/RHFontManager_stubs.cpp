#include "SBNullstr.h"
#include "RHFontManager.h"

// FUNCTION: GAME 0x00503960
void RHFontConstructValue(std::pair<const std::string, void *> *storage, const std::pair<const std::string, void *> &value)
{
    new ((void *)storage) std::pair<const std::string, void *>(value);
}

// FUNCTION: GAME 0x005f5460
RHFontManager::Fonts::~Fonts() {}

// LIBRARY: GAME 0x006435d7
extern "C" int fgetc(FILE *) { return 0; }

// LIBRARY: GAME 0x00643540
extern "C" int ungetc(int, FILE *) { return 0; }

void *RHFontManager::GetFont(const std::string &) const { return 0; }
