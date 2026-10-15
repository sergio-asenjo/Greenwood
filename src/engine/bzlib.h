#ifndef GREENWOOD_BZLIB_H
#define GREENWOOD_BZLIB_H

#include <stdio.h>

#define BZ_RUN               0
#define BZ_FLUSH             1
#define BZ_FINISH            2

#define BZ_OK                0
#define BZ_RUN_OK            1
#define BZ_FLUSH_OK          2
#define BZ_FINISH_OK         3
#define BZ_STREAM_END        4
#define BZ_SEQUENCE_ERROR    (-1)
#define BZ_PARAM_ERROR       (-2)
#define BZ_MEM_ERROR         (-3)
#define BZ_DATA_ERROR        (-4)
#define BZ_DATA_ERROR_MAGIC  (-5)
#define BZ_IO_ERROR          (-6)
#define BZ_UNEXPECTED_EOF    (-7)
#define BZ_OUTBUFF_FULL      (-8)
#define BZ_CONFIG_ERROR      (-9)

typedef struct
{
    char *next_in;
    unsigned int avail_in;
    unsigned int total_in_lo32;
    unsigned int total_in_hi32;

    char *next_out;
    unsigned int avail_out;
    unsigned int total_out_lo32;
    unsigned int total_out_hi32;

    void *state;

    void *(*bzalloc)(void *, int, int);
    void (*bzfree)(void *, void *);
    void *opaque;
} bz_stream;

#define BZ_API(func) __stdcall func
#define BZ_MAX_UNUSED 5000

typedef void BZFILE;

extern "C" {

int BZ_API(BZ2_bzCompressInit)(bz_stream *strm, int blockSize100k, int verbosity, int workFactor);
int BZ_API(BZ2_bzCompress)(bz_stream *strm, int action);
int BZ_API(BZ2_bzCompressEnd)(bz_stream *strm);
int BZ_API(BZ2_bzDecompressInit)(bz_stream *strm, int verbosity, int small);
int BZ_API(BZ2_bzDecompress)(bz_stream *strm);
int BZ_API(BZ2_bzDecompressEnd)(bz_stream *strm);

BZFILE *BZ_API(BZ2_bzWriteOpen)(int *bzerror, FILE *f, int blockSize100k, int verbosity, int workFactor);
void BZ_API(BZ2_bzWrite)(int *bzerror, BZFILE *b, void *buf, int len);
void BZ_API(BZ2_bzWriteClose)(int *bzerror, BZFILE *b, int abandon,
                              unsigned int *nbytes_in, unsigned int *nbytes_out);
void BZ_API(BZ2_bzWriteClose64)(int *bzerror, BZFILE *b, int abandon,
                                unsigned int *nbytes_in_lo32, unsigned int *nbytes_in_hi32,
                                unsigned int *nbytes_out_lo32, unsigned int *nbytes_out_hi32);
BZFILE *BZ_API(BZ2_bzReadOpen)(int *bzerror, FILE *f, int verbosity, int small, void *unused, int nUnused);
void BZ_API(BZ2_bzReadClose)(int *bzerror, BZFILE *b);

int BZ_API(BZ2_bzBuffToBuffCompress)(char *dest, unsigned int *destLen, char *source, unsigned int sourceLen,
                                     int blockSize100k, int verbosity, int workFactor);
int BZ_API(BZ2_bzBuffToBuffDecompress)(char *dest, unsigned int *destLen, char *source, unsigned int sourceLen,
                                       int small, int verbosity);

const char *BZ_API(BZ2_bzlibVersion)(void);

BZFILE *BZ_API(BZ2_bzopen)(const char *path, const char *mode);
int BZ_API(BZ2_bzwrite)(BZFILE *b, void *buf, int len);
void BZ_API(BZ2_bzclose)(BZFILE *b);

}

#endif
