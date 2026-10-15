#include "bzlib_private.h"
#include <fcntl.h>
#include <io.h>

extern char g_unk0x6c0560[4];

// GLOBAL: GAME 0x006bf2c0
extern "C" FILE _iob[];

extern "C" {

// stdio stream immediates (_iob+0x20/+0x40) have no exact recomp entity.
// STUB: GAME 0x00625350
void BZ2_bz__AssertH__fail(int errcode)
{
    fprintf(stderr,
        // STRING: GAME 0x006bbaec
        "\n\nbzip2/libbzip2: internal error number %d.\nThis is a bug in bzip2/libbzip2, %s.\nPlease report it to me at: jseward@acm.org.  If this happened\nwhen you were using some program which uses libbzip2 as a\ncomponent, you should also report this bug to the author(s)\nof that program.  Please make an effort to report this bug;\ntimely and accurate bug reports eventually lead to higher\nquality software.  Thanks.  Julian Seward, 21 March 2000.\n\n",
        errcode,
        BZ2_bzlibVersion());
    exit(3);
}

// FUNCTION: GAME 0x00625550
static int bz_config_ok(void)
{
    if (sizeof(int) != 4) return 0;
    if (sizeof(short) != 2) return 0;
    if (sizeof(char) != 1) return 0;
    return 1;
}

// FUNCTION: GAME 0x00625560
static void *default_bzalloc(void *opaque, Int32 items, Int32 size)
{
    void *v = malloc(items * size);
    return v;
}

// FUNCTION: GAME 0x00625580
static void default_bzfree(void *opaque, void *addr)
{
    if (addr != NULL) free(addr);
}

// FUNCTION: GAME 0x00625590
static void prepare_new_block(EState *s)
{
    Int32 i;
    s->nblock = 0;
    s->numZ = 0;
    s->state_out_pos = 0;
    BZ_INITIALISE_CRC(s->blockCRC);
    for (i = 0; i < 256; i++) s->inUse[i] = False;
    s->blockNo++;
}

// FUNCTION: GAME 0x006255d0
static void init_RL(EState *s)
{
    s->state_in_ch = 256;
    s->state_in_len = 0;
}

// FUNCTION: GAME 0x00625770
static Bool isempty_RL(EState *s)
{
    if (s->state_in_ch < 256 && s->state_in_len > 0)
        return False;
    else
        return True;
}

// FUNCTION: GAME 0x00625380
int BZ_API(BZ2_bzCompressInit)(bz_stream *strm, int blockSize100k, int verbosity, int workFactor)
{
    Int32 n;
    EState *s;

    if (!bz_config_ok()) return BZ_CONFIG_ERROR;

    if (strm == NULL ||
        blockSize100k < 1 || blockSize100k > 9 ||
        workFactor < 0 || workFactor > 250)
        return BZ_PARAM_ERROR;

    if (workFactor == 0) workFactor = 30;
    if (strm->bzalloc == NULL) strm->bzalloc = default_bzalloc;
    if (strm->bzfree == NULL) strm->bzfree = default_bzfree;

    s = (EState *)BZALLOC(sizeof(EState));
    if (s == NULL) return BZ_MEM_ERROR;
    s->strm = strm;

    s->arr1 = NULL;
    s->arr2 = NULL;
    s->ftab = NULL;

    n = 100000 * blockSize100k;
    s->arr1 = (UInt32 *)BZALLOC(n * sizeof(UInt32));
    s->arr2 = (UInt32 *)BZALLOC((n + BZ_N_OVERSHOOT) * sizeof(UInt32));
    s->ftab = (UInt32 *)BZALLOC(65537 * sizeof(UInt32));

    if (s->arr1 == NULL || s->arr2 == NULL || s->ftab == NULL) {
        if (s->arr1 != NULL) BZFREE(s->arr1);
        if (s->arr2 != NULL) BZFREE(s->arr2);
        if (s->ftab != NULL) BZFREE(s->ftab);
        if (s != NULL) BZFREE(s);
        return BZ_MEM_ERROR;
    }

    s->blockNo = 0;
    s->state = BZ_S_INPUT;
    s->mode = BZ_M_RUNNING;
    s->combinedCRC = 0;
    s->blockSize100k = blockSize100k;
    s->nblockMAX = 100000 * blockSize100k - 19;
    s->verbosity = verbosity;
    s->workFactor = workFactor;

    s->block = (UChar *)s->arr2;
    s->mtfv = (UInt16 *)s->arr1;
    s->zbits = NULL;
    s->ptr = (UInt32 *)s->arr1;

    strm->state = s;
    strm->total_in_lo32 = 0;
    strm->total_in_hi32 = 0;
    strm->total_out_lo32 = 0;
    strm->total_out_hi32 = 0;
    init_RL(s);
    prepare_new_block(s);
    return BZ_OK;
}

// FUNCTION: GAME 0x006258d0
static void add_pair_to_block(EState *s)
{
    Int32 i;
    UChar ch = (UChar)(s->state_in_ch);
    for (i = 0; i < s->state_in_len; i++) {
        BZ_UPDATE_CRC(s->blockCRC, ch);
    }
    s->inUse[s->state_in_ch] = True;
    switch (s->state_in_len) {
    case 1:
        s->block[s->nblock] = (UChar)ch; s->nblock++;
        break;
    case 2:
        s->block[s->nblock] = (UChar)ch; s->nblock++;
        s->block[s->nblock] = (UChar)ch; s->nblock++;
        break;
    case 3:
        s->block[s->nblock] = (UChar)ch; s->nblock++;
        s->block[s->nblock] = (UChar)ch; s->nblock++;
        s->block[s->nblock] = (UChar)ch; s->nblock++;
        break;
    default:
        s->inUse[s->state_in_len - 4] = True;
        s->block[s->nblock] = (UChar)ch; s->nblock++;
        s->block[s->nblock] = (UChar)ch; s->nblock++;
        s->block[s->nblock] = (UChar)ch; s->nblock++;
        s->block[s->nblock] = (UChar)ch; s->nblock++;
        s->block[s->nblock] = ((UChar)(s->state_in_len - 4));
        s->nblock++;
        break;
    }
}

// FUNCTION: GAME 0x006258a0
static void flush_RL(EState *s)
{
    if (s->state_in_ch < 256) add_pair_to_block(s);
    init_RL(s);
}

#define ADD_CHAR_TO_BLOCK(zs, zchh0)               \
    {                                              \
        UInt32 zchh = (UInt32)(zchh0);             \
        if (zchh != zs->state_in_ch &&             \
            zs->state_in_len == 1) {               \
            UChar ch = (UChar)(zs->state_in_ch);   \
            BZ_UPDATE_CRC(zs->blockCRC, ch);       \
            zs->inUse[zs->state_in_ch] = True;     \
            zs->block[zs->nblock] = (UChar)ch;     \
            zs->nblock++;                          \
            zs->state_in_ch = zchh;                \
        }                                          \
        else if (zchh != zs->state_in_ch ||        \
                 zs->state_in_len == 255) {        \
            if (zs->state_in_ch < 256)             \
                add_pair_to_block(zs);             \
            zs->state_in_ch = zchh;                \
            zs->state_in_len = 1;                  \
        } else {                                   \
            zs->state_in_len++;                    \
        }                                          \
    }

// FUNCTION: GAME 0x006259e0
static Bool copy_input_until_stop(EState *s)
{
    Bool progress_in = False;

    if (s->mode == BZ_M_RUNNING) {
        while (True) {
            if (s->nblock >= s->nblockMAX) break;
            if (s->strm->avail_in == 0) break;
            progress_in = True;
            ADD_CHAR_TO_BLOCK(s, (UInt32)(*((UChar *)(s->strm->next_in))));
            s->strm->next_in++;
            s->strm->avail_in--;
            s->strm->total_in_lo32++;
            if (s->strm->total_in_lo32 == 0) s->strm->total_in_hi32++;
        }
    } else {
        while (True) {
            if (s->nblock >= s->nblockMAX) break;
            if (s->strm->avail_in == 0) break;
            if (s->avail_in_expect == 0) break;
            progress_in = True;
            ADD_CHAR_TO_BLOCK(s, (UInt32)(*((UChar *)(s->strm->next_in))));
            s->strm->next_in++;
            s->strm->avail_in--;
            s->strm->total_in_lo32++;
            if (s->strm->total_in_lo32 == 0) s->strm->total_in_hi32++;
            s->avail_in_expect--;
        }
    }
    return progress_in;
}

// FUNCTION: GAME 0x00625bd0
static Bool copy_output_until_stop(EState *s)
{
    Bool progress_out = False;

    while (True) {
        if (s->strm->avail_out == 0) break;
        if (s->state_out_pos >= s->numZ) break;

        progress_out = True;
        *(s->strm->next_out) = s->zbits[s->state_out_pos];
        s->state_out_pos++;
        s->strm->avail_out--;
        s->strm->next_out++;
        s->strm->total_out_lo32++;
        if (s->strm->total_out_lo32 == 0) s->strm->total_out_hi32++;
    }

    return progress_out;
}

// FUNCTION: GAME 0x00625790
static Bool handle_compress(bz_stream *strm)
{
    Bool progress_in = False;
    Bool progress_out = False;
    EState *s = (EState *)strm->state;

    while (True) {
        if (s->state == BZ_S_OUTPUT) {
            progress_out |= copy_output_until_stop(s);
            if (s->state_out_pos < s->numZ) break;
            if (s->mode == BZ_M_FINISHING &&
                s->avail_in_expect == 0 &&
                isempty_RL(s)) break;
            prepare_new_block(s);
            s->state = BZ_S_INPUT;
            if (s->mode == BZ_M_FLUSHING &&
                s->avail_in_expect == 0 &&
                isempty_RL(s)) break;
        }

        if (s->state == BZ_S_INPUT) {
            progress_in |= copy_input_until_stop(s);
            if (s->mode != BZ_M_RUNNING && s->avail_in_expect == 0) {
                flush_RL(s);
                BZ2_compressBlock(s, (Bool)(s->mode == BZ_M_FINISHING));
                s->state = BZ_S_OUTPUT;
            }
            else if (s->nblock >= s->nblockMAX) {
                BZ2_compressBlock(s, False);
                s->state = BZ_S_OUTPUT;
            }
            else if (s->strm->avail_in == 0) {
                break;
            }
        }
    }

    return progress_in || progress_out;
}

// FUNCTION: GAME 0x006255f0
int BZ_API(BZ2_bzCompress)(bz_stream *strm, int action)
{
    Bool progress;
    EState *s;
    if (strm == NULL) return BZ_PARAM_ERROR;
    s = (EState *)strm->state;
    if (s == NULL) return BZ_PARAM_ERROR;
    if (s->strm != strm) return BZ_PARAM_ERROR;

preswitch:
    switch (s->mode) {
    case BZ_M_IDLE:
        return BZ_SEQUENCE_ERROR;

    case BZ_M_RUNNING:
        if (action == BZ_RUN) {
            progress = handle_compress(strm);
            return progress ? BZ_RUN_OK : BZ_PARAM_ERROR;
        }
        else if (action == BZ_FLUSH) {
            s->avail_in_expect = strm->avail_in;
            s->mode = BZ_M_FLUSHING;
            goto preswitch;
        }
        else if (action == BZ_FINISH) {
            s->avail_in_expect = strm->avail_in;
            s->mode = BZ_M_FINISHING;
            goto preswitch;
        }
        else
            return BZ_PARAM_ERROR;

    case BZ_M_FLUSHING:
        if (action != BZ_FLUSH) return BZ_SEQUENCE_ERROR;
        if (s->avail_in_expect != s->strm->avail_in)
            return BZ_SEQUENCE_ERROR;
        progress = handle_compress(strm);
        if (s->avail_in_expect > 0 || !isempty_RL(s) ||
            s->state_out_pos < s->numZ) return BZ_FLUSH_OK;
        s->mode = BZ_M_RUNNING;
        return BZ_RUN_OK;

    case BZ_M_FINISHING:
        if (action != BZ_FINISH) return BZ_SEQUENCE_ERROR;
        if (s->avail_in_expect != s->strm->avail_in)
            return BZ_SEQUENCE_ERROR;
        progress = handle_compress(strm);
        if (!progress) return BZ_SEQUENCE_ERROR;
        if (s->avail_in_expect > 0 || !isempty_RL(s) ||
            s->state_out_pos < s->numZ) return BZ_FINISH_OK;
        s->mode = BZ_M_IDLE;
        return BZ_STREAM_END;
    }
    return BZ_OK;
}

// FUNCTION: GAME 0x00625c30
int BZ_API(BZ2_bzCompressEnd)(bz_stream *strm)
{
    EState *s;
    if (strm == NULL) return BZ_PARAM_ERROR;
    s = (EState *)strm->state;
    if (s == NULL) return BZ_PARAM_ERROR;
    if (s->strm != strm) return BZ_PARAM_ERROR;

    if (s->arr1 != NULL) BZFREE(s->arr1);
    if (s->arr2 != NULL) BZFREE(s->arr2);
    if (s->ftab != NULL) BZFREE(s->ftab);
    BZFREE(strm->state);

    strm->state = NULL;

    return BZ_OK;
}

// FUNCTION: GAME 0x00625cc0
int BZ_API(BZ2_bzDecompressInit)(bz_stream *strm, int verbosity, int small)
{
    DState *s;

    if (!bz_config_ok()) return BZ_CONFIG_ERROR;

    if (strm == NULL) return BZ_PARAM_ERROR;
    if (small != 0 && small != 1) return BZ_PARAM_ERROR;
    if (verbosity < 0 || verbosity > 4) return BZ_PARAM_ERROR;

    if (strm->bzalloc == NULL) strm->bzalloc = default_bzalloc;
    if (strm->bzfree == NULL) strm->bzfree = default_bzfree;

    s = (DState *)BZALLOC(sizeof(DState));
    if (s == NULL) return BZ_MEM_ERROR;
    s->strm = strm;
    strm->state = s;
    s->state = BZ_X_MAGIC_1;
    s->bsLive = 0;
    s->bsBuff = 0;
    s->calculatedCombinedCRC = 0;
    strm->total_in_lo32 = 0;
    strm->total_in_hi32 = 0;
    strm->total_out_lo32 = 0;
    strm->total_out_hi32 = 0;
    s->smallDecompress = (Bool)small;
    s->ll4 = NULL;
    s->ll16 = NULL;
    s->tt = NULL;
    s->currBlockNo = 0;
    s->verbosity = verbosity;

    return BZ_OK;
}

// FUNCTION: GAME 0x00625f50
static void unRLE_obuf_to_output_FAST(DState *s)
{
    UChar k1;

    if (s->blockRandomised) {
        while (True) {
            while (True) {
                if (s->strm->avail_out == 0) return;
                if (s->state_out_len == 0) break;
                *((UChar *)(s->strm->next_out)) = s->state_out_ch;
                BZ_UPDATE_CRC(s->calculatedBlockCRC, s->state_out_ch);
                s->state_out_len--;
                s->strm->next_out++;
                s->strm->avail_out--;
                s->strm->total_out_lo32++;
                if (s->strm->total_out_lo32 == 0) s->strm->total_out_hi32++;
            }

            if (s->nblock_used == s->save_nblock + 1) return;

            s->state_out_len = 1;
            s->state_out_ch = s->k0;
            BZ_GET_FAST(k1); BZ_RAND_UPD_MASK;
            k1 ^= BZ_RAND_MASK; s->nblock_used++;
            if (s->nblock_used == s->save_nblock + 1) continue;
            if (k1 != s->k0) { s->k0 = k1; continue; };

            s->state_out_len = 2;
            BZ_GET_FAST(k1); BZ_RAND_UPD_MASK;
            k1 ^= BZ_RAND_MASK; s->nblock_used++;
            if (s->nblock_used == s->save_nblock + 1) continue;
            if (k1 != s->k0) { s->k0 = k1; continue; };

            s->state_out_len = 3;
            BZ_GET_FAST(k1); BZ_RAND_UPD_MASK;
            k1 ^= BZ_RAND_MASK; s->nblock_used++;
            if (s->nblock_used == s->save_nblock + 1) continue;
            if (k1 != s->k0) { s->k0 = k1; continue; };

            BZ_GET_FAST(k1); BZ_RAND_UPD_MASK;
            k1 ^= BZ_RAND_MASK; s->nblock_used++;
            s->state_out_len = ((Int32)k1) + 4;
            BZ_GET_FAST(s->k0); BZ_RAND_UPD_MASK;
            s->k0 ^= BZ_RAND_MASK; s->nblock_used++;
        }
    } else {
        UInt32 c_calculatedBlockCRC = s->calculatedBlockCRC;
        UChar c_state_out_ch = s->state_out_ch;
        Int32 c_state_out_len = s->state_out_len;
        Int32 c_nblock_used = s->nblock_used;
        Int32 c_k0 = s->k0;
        UInt32 *c_tt = s->tt;
        UInt32 c_tPos = s->tPos;
        char *cs_next_out = s->strm->next_out;
        unsigned int cs_avail_out = s->strm->avail_out;

        UInt32 avail_out_INIT = cs_avail_out;
        Int32 s_save_nblockPP = s->save_nblock + 1;
        unsigned int total_out_lo32_old;

        while (True) {
            if (c_state_out_len > 0) {
                while (True) {
                    if (cs_avail_out == 0) goto return_notr;
                    if (c_state_out_len == 1) break;
                    *((UChar *)(cs_next_out)) = c_state_out_ch;
                    BZ_UPDATE_CRC(c_calculatedBlockCRC, c_state_out_ch);
                    c_state_out_len--;
                    cs_next_out++;
                    cs_avail_out--;
                }
            s_state_out_len_eq_one:
                {
                    if (cs_avail_out == 0) {
                        c_state_out_len = 1; goto return_notr;
                    };
                    *((UChar *)(cs_next_out)) = c_state_out_ch;
                    BZ_UPDATE_CRC(c_calculatedBlockCRC, c_state_out_ch);
                    cs_next_out++;
                    cs_avail_out--;
                }
            }
            if (c_nblock_used == s_save_nblockPP) {
                c_state_out_len = 0; goto return_notr;
            };
            c_state_out_ch = c_k0;
            BZ_GET_FAST_C(k1); c_nblock_used++;
            if (k1 != c_k0) {
                c_k0 = k1; goto s_state_out_len_eq_one;
            };
            if (c_nblock_used == s_save_nblockPP)
                goto s_state_out_len_eq_one;

            c_state_out_len = 2;
            BZ_GET_FAST_C(k1); c_nblock_used++;
            if (c_nblock_used == s_save_nblockPP) continue;
            if (k1 != c_k0) { c_k0 = k1; continue; };

            c_state_out_len = 3;
            BZ_GET_FAST_C(k1); c_nblock_used++;
            if (c_nblock_used == s_save_nblockPP) continue;
            if (k1 != c_k0) { c_k0 = k1; continue; };

            BZ_GET_FAST_C(k1); c_nblock_used++;
            c_state_out_len = ((Int32)k1) + 4;
            BZ_GET_FAST_C(c_k0); c_nblock_used++;
        }

    return_notr:
        total_out_lo32_old = s->strm->total_out_lo32;
        s->strm->total_out_lo32 += (avail_out_INIT - cs_avail_out);
        if (s->strm->total_out_lo32 < total_out_lo32_old)
            s->strm->total_out_hi32++;

        s->calculatedBlockCRC = c_calculatedBlockCRC;
        s->state_out_ch = c_state_out_ch;
        s->state_out_len = c_state_out_len;
        s->nblock_used = c_nblock_used;
        s->k0 = c_k0;
        s->tt = c_tt;
        s->tPos = c_tPos;
        s->strm->next_out = cs_next_out;
        s->strm->avail_out = cs_avail_out;
    }
}

// FUNCTION: GAME 0x00625da0
__inline__ Int32 BZ2_indexIntoF(Int32 indx, Int32 *cftab)
{
    Int32 nb, na, mid;
    nb = 0;
    na = 256;
    do {
        mid = (nb + na) >> 1;
        if (indx >= cftab[mid]) nb = mid; else na = mid;
    }
    while (na - nb != 1);
    return nb;
}

// FUNCTION: GAME 0x00626460
static void unRLE_obuf_to_output_SMALL(DState *s)
{
    UChar k1;

    if (s->blockRandomised) {
        while (True) {
            while (True) {
                if (s->strm->avail_out == 0) return;
                if (s->state_out_len == 0) break;
                *((UChar *)(s->strm->next_out)) = s->state_out_ch;
                BZ_UPDATE_CRC(s->calculatedBlockCRC, s->state_out_ch);
                s->state_out_len--;
                s->strm->next_out++;
                s->strm->avail_out--;
                s->strm->total_out_lo32++;
                if (s->strm->total_out_lo32 == 0) s->strm->total_out_hi32++;
            }

            if (s->nblock_used == s->save_nblock + 1) return;

            s->state_out_len = 1;
            s->state_out_ch = s->k0;
            BZ_GET_SMALL(k1); BZ_RAND_UPD_MASK;
            k1 ^= BZ_RAND_MASK; s->nblock_used++;
            if (s->nblock_used == s->save_nblock + 1) continue;
            if (k1 != s->k0) { s->k0 = k1; continue; };

            s->state_out_len = 2;
            BZ_GET_SMALL(k1); BZ_RAND_UPD_MASK;
            k1 ^= BZ_RAND_MASK; s->nblock_used++;
            if (s->nblock_used == s->save_nblock + 1) continue;
            if (k1 != s->k0) { s->k0 = k1; continue; };

            s->state_out_len = 3;
            BZ_GET_SMALL(k1); BZ_RAND_UPD_MASK;
            k1 ^= BZ_RAND_MASK; s->nblock_used++;
            if (s->nblock_used == s->save_nblock + 1) continue;
            if (k1 != s->k0) { s->k0 = k1; continue; };

            BZ_GET_SMALL(k1); BZ_RAND_UPD_MASK;
            k1 ^= BZ_RAND_MASK; s->nblock_used++;
            s->state_out_len = ((Int32)k1) + 4;
            BZ_GET_SMALL(s->k0); BZ_RAND_UPD_MASK;
            s->k0 ^= BZ_RAND_MASK; s->nblock_used++;
        }
    } else {
        while (True) {
            while (True) {
                if (s->strm->avail_out == 0) return;
                if (s->state_out_len == 0) break;
                *((UChar *)(s->strm->next_out)) = s->state_out_ch;
                BZ_UPDATE_CRC(s->calculatedBlockCRC, s->state_out_ch);
                s->state_out_len--;
                s->strm->next_out++;
                s->strm->avail_out--;
                s->strm->total_out_lo32++;
                if (s->strm->total_out_lo32 == 0) s->strm->total_out_hi32++;
            }

            if (s->nblock_used == s->save_nblock + 1) return;

            s->state_out_len = 1;
            s->state_out_ch = s->k0;
            BZ_GET_SMALL(k1); s->nblock_used++;
            if (s->nblock_used == s->save_nblock + 1) continue;
            if (k1 != s->k0) { s->k0 = k1; continue; };

            s->state_out_len = 2;
            BZ_GET_SMALL(k1); s->nblock_used++;
            if (s->nblock_used == s->save_nblock + 1) continue;
            if (k1 != s->k0) { s->k0 = k1; continue; };

            s->state_out_len = 3;
            BZ_GET_SMALL(k1); s->nblock_used++;
            if (s->nblock_used == s->save_nblock + 1) continue;
            if (k1 != s->k0) { s->k0 = k1; continue; };

            BZ_GET_SMALL(k1); s->nblock_used++;
            s->state_out_len = ((Int32)k1) + 4;
            BZ_GET_SMALL(s->k0); s->nblock_used++;
        }
    }
}

// stdio stream immediates (_iob+0x20/+0x40) have no exact recomp entity.
// STUB: GAME 0x00625dd0
int BZ_API(BZ2_bzDecompress)(bz_stream *strm)
{
    DState *s;
    if (strm == NULL) return BZ_PARAM_ERROR;
    s = (DState *)strm->state;
    if (s == NULL) return BZ_PARAM_ERROR;
    if (s->strm != strm) return BZ_PARAM_ERROR;

    while (True) {
        if (s->state == BZ_X_IDLE) return BZ_SEQUENCE_ERROR;
        if (s->state == BZ_X_OUTPUT) {
            if (s->smallDecompress)
                unRLE_obuf_to_output_SMALL(s); else
                unRLE_obuf_to_output_FAST(s);
            if (s->nblock_used == s->save_nblock + 1 && s->state_out_len == 0) {
                BZ_FINALISE_CRC(s->calculatedBlockCRC);
                if (s->verbosity >= 3)
                    // STRING: GAME 0x006bbcdc
                    VPrintf2(" {0x%x, 0x%x}", s->storedBlockCRC,
                             s->calculatedBlockCRC);
                if (s->verbosity >= 2)
                    // STRING: GAME 0x006bbcd8
                    VPrintf0("]");
                if (s->calculatedBlockCRC != s->storedBlockCRC)
                    return BZ_DATA_ERROR;
                s->calculatedCombinedCRC
                    = (s->calculatedCombinedCRC << 1) |
                      (s->calculatedCombinedCRC >> 31);
                s->calculatedCombinedCRC ^= s->calculatedBlockCRC;
                s->state = BZ_X_BLKHDR_1;
            } else {
                return BZ_OK;
            }
        }
        if (s->state >= BZ_X_MAGIC_1) {
            Int32 r = BZ2_decompress(s);
            if (r == BZ_STREAM_END) {
                if (s->verbosity >= 3)
                    // STRING: GAME 0x006bbca4
                    VPrintf2("\n    combined CRCs: stored = 0x%x, computed = 0x%x",
                             s->storedCombinedCRC, s->calculatedCombinedCRC);
                if (s->calculatedCombinedCRC != s->storedCombinedCRC)
                    return BZ_DATA_ERROR;
                return r;
            }
            if (s->state != BZ_X_OUTPUT) return r;
        }
    }

    AssertH(0, 6001);

    return 0;
}

// FUNCTION: GAME 0x00626b30
int BZ_API(BZ2_bzDecompressEnd)(bz_stream *strm)
{
    DState *s;
    if (strm == NULL) return BZ_PARAM_ERROR;
    s = (DState *)strm->state;
    if (s == NULL) return BZ_PARAM_ERROR;
    if (s->strm != strm) return BZ_PARAM_ERROR;

    if (s->tt != NULL) BZFREE(s->tt);
    if (s->ll16 != NULL) BZFREE(s->ll16);
    if (s->ll4 != NULL) BZFREE(s->ll4);

    BZFREE(strm->state);
    strm->state = NULL;

    return BZ_OK;
}

#define BZ_SETERR(eee)                    \
    {                                     \
        if (bzerror != NULL) *bzerror = eee; \
        if (bzf != NULL) bzf->lastErr = eee; \
    }

typedef struct
{
    FILE *handle;
    Char buf[BZ_MAX_UNUSED];
    Int32 bufN;
    Bool writing;
    bz_stream strm;
    Int32 lastErr;
    Bool initialisedOk;
} bzFile;

// FUNCTION: GAME 0x00626bc0
BZFILE *BZ_API(BZ2_bzWriteOpen)(int *bzerror, FILE *f, int blockSize100k, int verbosity, int workFactor)
{
    Int32 ret;
    bzFile *bzf = NULL;

    BZ_SETERR(BZ_OK);

    if (f == NULL ||
        (blockSize100k < 1 || blockSize100k > 9) ||
        (workFactor < 0 || workFactor > 250) ||
        (verbosity < 0 || verbosity > 4))
    { BZ_SETERR(BZ_PARAM_ERROR); return NULL; };

    if (ferror(f))
    { BZ_SETERR(BZ_IO_ERROR); return NULL; };

    bzf = (bzFile *)malloc(sizeof(bzFile));
    if (bzf == NULL)
    { BZ_SETERR(BZ_MEM_ERROR); return NULL; };

    BZ_SETERR(BZ_OK);
    bzf->initialisedOk = False;
    bzf->bufN = 0;
    bzf->handle = f;
    bzf->writing = True;
    bzf->strm.bzalloc = NULL;
    bzf->strm.bzfree = NULL;
    bzf->strm.opaque = NULL;

    if (workFactor == 0) workFactor = 30;
    ret = BZ2_bzCompressInit(&(bzf->strm), blockSize100k,
                             verbosity, workFactor);
    if (ret != BZ_OK)
    { BZ_SETERR(ret); free(bzf); return NULL; };

    bzf->strm.avail_in = 0;
    bzf->initialisedOk = True;
    return bzf;
}

// FUNCTION: GAME 0x00626d10
void BZ_API(BZ2_bzWrite)(int *bzerror, BZFILE *b, void *buf, int len)
{
    Int32 n, n2, ret;
    bzFile *bzf = (bzFile *)b;

    BZ_SETERR(BZ_OK);
    if (bzf == NULL || buf == NULL || len < 0)
    { BZ_SETERR(BZ_PARAM_ERROR); return; };
    if (!(bzf->writing))
    { BZ_SETERR(BZ_SEQUENCE_ERROR); return; };
    if (ferror(bzf->handle))
    { BZ_SETERR(BZ_IO_ERROR); return; };

    if (len == 0)
    { BZ_SETERR(BZ_OK); return; };

    bzf->strm.avail_in = len;
    bzf->strm.next_in = (char *)buf;

    while (True) {
        bzf->strm.avail_out = BZ_MAX_UNUSED;
        bzf->strm.next_out = bzf->buf;
        ret = BZ2_bzCompress(&(bzf->strm), BZ_RUN);
        if (ret != BZ_RUN_OK)
        { BZ_SETERR(ret); return; };

        if (bzf->strm.avail_out < BZ_MAX_UNUSED) {
            n = BZ_MAX_UNUSED - bzf->strm.avail_out;
            n2 = fwrite((void *)(bzf->buf), sizeof(UChar),
                        n, bzf->handle);
            if (n != n2 || ferror(bzf->handle))
            { BZ_SETERR(BZ_IO_ERROR); return; };
        }

        if (bzf->strm.avail_in == 0)
        { BZ_SETERR(BZ_OK); return; };
    }
}

// FUNCTION: GAME 0x00626e90
void BZ_API(BZ2_bzWriteClose)(int *bzerror, BZFILE *b, int abandon,
                              unsigned int *nbytes_in, unsigned int *nbytes_out)
{
    BZ2_bzWriteClose64(bzerror, b, abandon,
                       nbytes_in, NULL, nbytes_out, NULL);
}

// FUNCTION: GAME 0x00626ec0
void BZ_API(BZ2_bzWriteClose64)(int *bzerror, BZFILE *b, int abandon,
                                unsigned int *nbytes_in_lo32, unsigned int *nbytes_in_hi32,
                                unsigned int *nbytes_out_lo32, unsigned int *nbytes_out_hi32)
{
    Int32 n, n2, ret;
    bzFile *bzf = (bzFile *)b;

    if (bzf == NULL)
    { BZ_SETERR(BZ_OK); return; };
    if (!(bzf->writing))
    { BZ_SETERR(BZ_SEQUENCE_ERROR); return; };
    if (ferror(bzf->handle))
    { BZ_SETERR(BZ_IO_ERROR); return; };

    if (nbytes_in_lo32 != NULL) *nbytes_in_lo32 = 0;
    if (nbytes_in_hi32 != NULL) *nbytes_in_hi32 = 0;
    if (nbytes_out_lo32 != NULL) *nbytes_out_lo32 = 0;
    if (nbytes_out_hi32 != NULL) *nbytes_out_hi32 = 0;

    if ((!abandon) && bzf->lastErr == BZ_OK) {
        while (True) {
            bzf->strm.avail_out = BZ_MAX_UNUSED;
            bzf->strm.next_out = bzf->buf;
            ret = BZ2_bzCompress(&(bzf->strm), BZ_FINISH);
            if (ret != BZ_FINISH_OK && ret != BZ_STREAM_END)
            { BZ_SETERR(ret); return; };

            if (bzf->strm.avail_out < BZ_MAX_UNUSED) {
                n = BZ_MAX_UNUSED - bzf->strm.avail_out;
                n2 = fwrite((void *)(bzf->buf), sizeof(UChar),
                            n, bzf->handle);
                if (n != n2 || ferror(bzf->handle))
                { BZ_SETERR(BZ_IO_ERROR); return; };
            }

            if (ret == BZ_STREAM_END) break;
        }
    }

    if (!abandon && !ferror(bzf->handle)) {
        fflush(bzf->handle);
        if (ferror(bzf->handle))
        { BZ_SETERR(BZ_IO_ERROR); return; };
    }

    if (nbytes_in_lo32 != NULL)
        *nbytes_in_lo32 = bzf->strm.total_in_lo32;
    if (nbytes_in_hi32 != NULL)
        *nbytes_in_hi32 = bzf->strm.total_in_hi32;
    if (nbytes_out_lo32 != NULL)
        *nbytes_out_lo32 = bzf->strm.total_out_lo32;
    if (nbytes_out_hi32 != NULL)
        *nbytes_out_hi32 = bzf->strm.total_out_hi32;

    BZ_SETERR(BZ_OK);
    BZ2_bzCompressEnd(&(bzf->strm));
    free(bzf);
}

// FUNCTION: GAME 0x00627090
BZFILE *BZ_API(BZ2_bzReadOpen)(int *bzerror, FILE *f, int verbosity, int small, void *unused, int nUnused)
{
    bzFile *bzf = NULL;
    int ret;

    BZ_SETERR(BZ_OK);

    if (f == NULL ||
        (small != 0 && small != 1) ||
        (verbosity < 0 || verbosity > 4) ||
        (unused == NULL && nUnused != 0) ||
        (unused != NULL && (nUnused < 0 || nUnused > BZ_MAX_UNUSED)))
    { BZ_SETERR(BZ_PARAM_ERROR); return NULL; };

    if (ferror(f))
    { BZ_SETERR(BZ_IO_ERROR); return NULL; };

    bzf = (bzFile *)malloc(sizeof(bzFile));
    if (bzf == NULL)
    { BZ_SETERR(BZ_MEM_ERROR); return NULL; };

    BZ_SETERR(BZ_OK);

    bzf->initialisedOk = False;
    bzf->handle = f;
    bzf->bufN = 0;
    bzf->writing = False;
    bzf->strm.bzalloc = NULL;
    bzf->strm.bzfree = NULL;
    bzf->strm.opaque = NULL;

    while (nUnused > 0) {
        bzf->buf[bzf->bufN] = *((UChar *)(unused)); bzf->bufN++;
        unused = ((void *)(1 + ((UChar *)(unused))));
        nUnused--;
    }

    ret = BZ2_bzDecompressInit(&(bzf->strm), verbosity, small);
    if (ret != BZ_OK)
    { BZ_SETERR(ret); free(bzf); return NULL; };

    bzf->strm.avail_in = bzf->bufN;
    bzf->strm.next_in = bzf->buf;

    bzf->initialisedOk = True;
    return bzf;
}

// FUNCTION: GAME 0x00627220
void BZ_API(BZ2_bzReadClose)(int *bzerror, BZFILE *b)
{
    bzFile *bzf = (bzFile *)b;

    BZ_SETERR(BZ_OK);
    if (bzf == NULL)
    { BZ_SETERR(BZ_OK); return; };

    if (bzf->writing)
    { BZ_SETERR(BZ_SEQUENCE_ERROR); return; };

    if (bzf->initialisedOk)
        (void)BZ2_bzDecompressEnd(&(bzf->strm));
    free(bzf);
}

// FUNCTION: GAME 0x006272a0
int BZ_API(BZ2_bzBuffToBuffCompress)(char *dest, unsigned int *destLen, char *source, unsigned int sourceLen,
                                     int blockSize100k, int verbosity, int workFactor)
{
    bz_stream strm;
    int ret;

    if (dest == NULL || destLen == NULL ||
        source == NULL ||
        blockSize100k < 1 || blockSize100k > 9 ||
        verbosity < 0 || verbosity > 4 ||
        workFactor < 0 || workFactor > 250)
        return BZ_PARAM_ERROR;

    if (workFactor == 0) workFactor = 30;
    strm.bzalloc = NULL;
    strm.bzfree = NULL;
    strm.opaque = NULL;
    ret = BZ2_bzCompressInit(&strm, blockSize100k,
                             verbosity, workFactor);
    if (ret != BZ_OK) return ret;

    strm.next_in = source;
    strm.next_out = dest;
    strm.avail_in = sourceLen;
    strm.avail_out = *destLen;

    ret = BZ2_bzCompress(&strm, BZ_FINISH);
    if (ret == BZ_FINISH_OK) goto output_overflow;
    if (ret != BZ_STREAM_END) goto errhandler;

    *destLen -= strm.avail_out;
    BZ2_bzCompressEnd(&strm);
    return BZ_OK;

output_overflow:
    BZ2_bzCompressEnd(&strm);
    return BZ_OUTBUFF_FULL;

errhandler:
    BZ2_bzCompressEnd(&strm);
    return ret;
}

// FUNCTION: GAME 0x006273d0
int BZ_API(BZ2_bzBuffToBuffDecompress)(char *dest, unsigned int *destLen, char *source, unsigned int sourceLen,
                                       int small, int verbosity)
{
    bz_stream strm;
    int ret;

    if (dest == NULL || destLen == NULL ||
        source == NULL ||
        (small != 0 && small != 1) ||
        verbosity < 0 || verbosity > 4)
        return BZ_PARAM_ERROR;

    strm.bzalloc = NULL;
    strm.bzfree = NULL;
    strm.opaque = NULL;
    ret = BZ2_bzDecompressInit(&strm, verbosity, small);
    if (ret != BZ_OK) return ret;

    strm.next_in = source;
    strm.next_out = dest;
    strm.avail_in = sourceLen;
    strm.avail_out = *destLen;

    ret = BZ2_bzDecompress(&strm);
    if (ret == BZ_OK) goto output_overflow_or_eof;
    if (ret != BZ_STREAM_END) goto errhandler;

    *destLen -= strm.avail_out;
    BZ2_bzDecompressEnd(&strm);
    return BZ_OK;

output_overflow_or_eof:
    if (strm.avail_out > 0) {
        BZ2_bzDecompressEnd(&strm);
        return BZ_UNEXPECTED_EOF;
    } else {
        BZ2_bzDecompressEnd(&strm);
        return BZ_OUTBUFF_FULL;
    };

errhandler:
    BZ2_bzDecompressEnd(&strm);
    return ret;
}

// FUNCTION: GAME 0x00627500
const char *BZ_API(BZ2_bzlibVersion)(void)
{
    // STRING: GAME 0x006bbcec
    return "1.0.1, 23-June-2000";
}

// stdio stream immediates (_iob+0x20/+0x40) have no exact recomp entity.
// STUB: GAME 0x00627530
static BZFILE *bzopen_or_bzdopen(const char *path, int fd, const char *mode, int open_mode)
{
    int bzerr;
    char unused[BZ_MAX_UNUSED];
    int blockSize100k = 9;
    int writing = 0;
    char mode2[10] = {g_unk0x6c0560[0]};
    FILE *fp = NULL;
    BZFILE *bzfp = NULL;
    int verbosity = 0;
    int workFactor = 30;
    int smallMode = 0;
    int nUnused = 0;

    if (mode == NULL) return NULL;
    while (*mode) {
        switch (*mode) {
        case 'r':
            writing = 0; break;
        case 'w':
            writing = 1; break;
        case 's':
            smallMode = 1; break;
        default:
            if (isdigit((int)(*mode))) {
                blockSize100k = *mode - BZ_HDR_0;
            }
        }
        mode++;
    }
    strcat(mode2, writing ?
        // STRING: GAME 0x006bbd08
        "w" :
        // STRING: GAME 0x006bbd04
        "r");
    // STRING: GAME 0x006bbd00
    strcat(mode2, "b");

    if (open_mode == 0) {
        if (path == NULL || strcmp(path, g_unk0x6c0560) == 0) {
            fp = (writing ? stdout : stdin);
            _setmode(_fileno(fp), _O_BINARY);
        } else {
            fp = fopen(path, mode2);
        }
    } else {
        fp = _fdopen(fd, mode2);
    }
    if (fp == NULL) return NULL;

    if (writing) {
        if (blockSize100k < 1) blockSize100k = 1;
        if (blockSize100k > 9) blockSize100k = 9;
        bzfp = BZ2_bzWriteOpen(&bzerr, fp, blockSize100k,
                               verbosity, workFactor);
    } else {
        bzfp = BZ2_bzReadOpen(&bzerr, fp, verbosity, smallMode,
                              unused, nUnused);
    }
    if (bzfp == NULL) {
        if (fp != stdin && fp != stdout) fclose(fp);
        return NULL;
    }
    return bzfp;
}

// FUNCTION: GAME 0x00627510
BZFILE *BZ_API(BZ2_bzopen)(const char *path, const char *mode)
{
    return bzopen_or_bzdopen(path, -1, mode, 0);
}

// FUNCTION: GAME 0x00627740
int BZ_API(BZ2_bzwrite)(BZFILE *b, void *buf, int len)
{
    int bzerr;

    BZ2_bzWrite(&bzerr, b, buf, len);
    if (bzerr == BZ_OK) {
        return len;
    } else {
        return -1;
    }
}

// stdio stream immediates (_iob+0x20/+0x40) have no exact recomp entity.
// STUB: GAME 0x00627770
void BZ_API(BZ2_bzclose)(BZFILE *b)
{
    int bzerr;
    FILE *fp = ((bzFile *)b)->handle;

    if (b == NULL) { return; }
    if (((bzFile *)b)->writing) {
        BZ2_bzWriteClose(&bzerr, b, 0, NULL, NULL);
        if (bzerr != BZ_OK) {
            BZ2_bzWriteClose(NULL, b, 1, NULL, NULL);
        }
    } else {
        BZ2_bzReadClose(&bzerr, b);
    }
    if (fp != stdin && fp != stdout) {
        fclose(fp);
    }
}

}
