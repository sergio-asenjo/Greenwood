#include "bzlib_private.h"

extern "C" {

// FUNCTION: GAME 0x0062d000
static void makeMaps_d(DState *s)
{
    Int32 i;
    s->nInUse = 0;
    for (i = 0; i < 256; i++)
        if (s->inUse[i]) {
            s->seqToUnseq[s->nInUse] = i;
            s->nInUse++;
        }
}

// STUB: GAME 0x0062ab00
Int32 BZ2_decompress(DState *s)
{
    makeMaps_d(s);
    return BZ_OK;
}

}
