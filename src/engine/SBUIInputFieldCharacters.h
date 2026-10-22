#ifndef SB_UI_INPUT_FIELD_CHARACTERS_H
#define SB_UI_INPUT_FIELD_CHARACTERS_H

#include <list>

struct SBUIInputFieldCharacter
{
    unsigned short character;
    unsigned int width;
};

typedef std::list<SBUIInputFieldCharacter> SBUIInputFieldCharacters;

#endif
