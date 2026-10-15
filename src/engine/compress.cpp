#include "bzlib_private.h"

extern "C" {

// FUNCTION: GAME 0x00628820
void BZ2_bsInitWrite(EState *s)
{
    s->bsLive = 0;
    s->bsBuff = 0;
}

// FUNCTION: GAME 0x006289e0
static void bsFinishWrite(EState *s)
{
    while (s->bsLive > 0) {
        s->zbits[s->numZ] = (UChar)(s->bsBuff >> 24);
        s->numZ++;
        s->bsBuff <<= 8;
        s->bsLive -= 8;
    }
}

#define bsNEEDW(nz)                       \
    {                                     \
        while (s->bsLive >= 8) {          \
            s->zbits[s->numZ]             \
                = (UChar)(s->bsBuff >> 24); \
            s->numZ++;                    \
            s->bsBuff <<= 8;              \
            s->bsLive -= 8;               \
        }                                 \
    }

// FUNCTION: GAME 0x00628a40
static __inline__ void bsW(EState *s, Int32 n, UInt32 v)
{
    bsNEEDW(n);
    s->bsBuff |= (v << (32 - s->bsLive - n));
    s->bsLive += n;
}

// FUNCTION: GAME 0x00628ad0
static void bsPutUInt32(EState *s, UInt32 u)
{
    bsW(s, 8, (u >> 24) & 0xffL);
    bsW(s, 8, (u >> 16) & 0xffL);
    bsW(s, 8, (u >> 8) & 0xffL);
    bsW(s, 8, u & 0xffL);
}

// FUNCTION: GAME 0x00628b20
static void bsPutUChar(EState *s, UChar c)
{
    bsW(s, 8, (UInt32)c);
}

// FUNCTION: GAME 0x00628d20
static void makeMaps_e(EState *s)
{
    Int32 i;
    s->nInUse = 0;
    for (i = 0; i < 256; i++)
        if (s->inUse[i]) {
            s->unseqToSeq[i] = s->nInUse;
            s->nInUse++;
        }
}

// FUNCTION: GAME 0x00628b40
static void generateMTFValues(EState *s)
{
    UChar yy[256];
    Int32 i, j;
    Int32 zPend;
    Int32 wr;
    Int32 EOB;

    UInt32 *ptr = s->ptr;
    UChar *block = s->block;
    UInt16 *mtfv = s->mtfv;

    makeMaps_e(s);
    EOB = s->nInUse + 1;

    for (i = 0; i <= EOB; i++) s->mtfFreq[i] = 0;

    wr = 0;
    zPend = 0;
    for (i = 0; i < s->nInUse; i++) yy[i] = (UChar)i;

    for (i = 0; i < s->nblock; i++) {
        UChar ll_i;
        j = ptr[i] - 1; if (j < 0) j += s->nblock;
        ll_i = s->unseqToSeq[block[j]];

        if (yy[0] == ll_i) {
            zPend++;
        } else {
            if (zPend > 0) {
                zPend--;
                while (True) {
                    if (zPend & 1) {
                        mtfv[wr] = BZ_RUNB; wr++;
                        s->mtfFreq[BZ_RUNB]++;
                    } else {
                        mtfv[wr] = BZ_RUNA; wr++;
                        s->mtfFreq[BZ_RUNA]++;
                    }
                    if (zPend < 2) break;
                    zPend = (zPend - 2) / 2;
                };
                zPend = 0;
            }
            {
                register UChar rtmp;
                register UChar *ryy_j;
                register UChar rll_i;
                rtmp = yy[1];
                yy[1] = yy[0];
                ryy_j = &(yy[1]);
                rll_i = ll_i;
                while (rll_i != rtmp) {
                    register UChar rtmp2;
                    ryy_j++;
                    rtmp2 = rtmp;
                    rtmp = *ryy_j;
                    *ryy_j = rtmp2;
                };
                yy[0] = rtmp;
                j = ryy_j - &(yy[0]);
                mtfv[wr] = j + 1; wr++; s->mtfFreq[j + 1]++;
            }
        }
    }

    if (zPend > 0) {
        zPend--;
        while (True) {
            if (zPend & 1) {
                mtfv[wr] = BZ_RUNB; wr++;
                s->mtfFreq[BZ_RUNB]++;
            } else {
                mtfv[wr] = BZ_RUNA; wr++;
                s->mtfFreq[BZ_RUNA]++;
            }
            if (zPend < 2) break;
            zPend = (zPend - 2) / 2;
        };
        zPend = 0;
    }

    mtfv[wr] = EOB; wr++; s->mtfFreq[EOB]++;

    s->nMTF = wr;
}

// STUB: GAME 0x00628d50
static void sendMTFValues(EState *s)
{
}

// stdio stream immediates (_iob+0x20/+0x40) have no exact recomp entity.
// STUB: GAME 0x00628840
void BZ2_compressBlock(EState *s, Bool is_last_block)
{
    if (s->nblock > 0) {
        BZ_FINALISE_CRC(s->blockCRC);
        s->combinedCRC = (s->combinedCRC << 1) | (s->combinedCRC >> 31);
        s->combinedCRC ^= s->blockCRC;
        if (s->blockNo > 1) s->numZ = 0;

        if (s->verbosity >= 2)
            // STRING: GAME 0x006bbd38
            VPrintf4("    block %d: crc = 0x%8x, combined CRC = 0x%8x, size = %d\n",
                     s->blockNo, s->blockCRC, s->combinedCRC, s->nblock);

        BZ2_blockSort(s);
    }

    s->zbits = (UChar *)(&((UChar *)s->arr2)[s->nblock]);

    if (s->blockNo == 1) {
        BZ2_bsInitWrite(s);
        bsPutUChar(s, BZ_HDR_B);
        bsPutUChar(s, BZ_HDR_Z);
        bsPutUChar(s, BZ_HDR_h);
        bsPutUChar(s, (UChar)(BZ_HDR_0 + s->blockSize100k));
    }

    if (s->nblock > 0) {
        bsPutUChar(s, 0x31); bsPutUChar(s, 0x41);
        bsPutUChar(s, 0x59); bsPutUChar(s, 0x26);
        bsPutUChar(s, 0x53); bsPutUChar(s, 0x59);

        bsPutUInt32(s, s->blockCRC);

        bsW(s, 1, 0);

        bsW(s, 24, s->origPtr);
        generateMTFValues(s);
        sendMTFValues(s);
    }

    if (is_last_block) {
        bsPutUChar(s, 0x17); bsPutUChar(s, 0x72);
        bsPutUChar(s, 0x45); bsPutUChar(s, 0x38);
        bsPutUChar(s, 0x50); bsPutUChar(s, 0x90);
        bsPutUInt32(s, s->combinedCRC);
        if (s->verbosity >= 2)
            // STRING: GAME 0x006bbd14
            VPrintf1("    final combined CRC = 0x%x\n   ", s->combinedCRC);
        bsFinishWrite(s);
    }
}

}
