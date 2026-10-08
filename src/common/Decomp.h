#ifndef DECOMP_H
#define DECOMP_H

#define DECOMP_JOIN_INNER(A, B) A##B
#define DECOMP_JOIN(A, B) DECOMP_JOIN_INNER(A, B)
#define DECOMP_STATIC_ASSERT(V) namespace { typedef int DECOMP_JOIN(decomp_assert_, __LINE__)[(V) ? 1 : -1]; }
#define DECOMP_SIZE_ASSERT(T, S) DECOMP_STATIC_ASSERT(sizeof(T) == S)

typedef unsigned char undefined;
typedef unsigned short undefined2;
typedef unsigned int undefined4;

#endif
