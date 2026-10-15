#include "MD5.h"
#include <stdio.h>
#include "SB.h"

typedef char MD5SizeCheck[sizeof(MD5) == 0x6c ? 1 : -1];

extern char g_unk0x6c0560[4];

// GLOBAL: GAME 0x006bb5ac
unsigned char g_md5Padding[64] = {0x80};

// FUNCTION: GAME 0x0060e4c0
MD5::MD5()
{
    init();
}

// FUNCTION: GAME 0x0060e4d0
void MD5::update(unsigned char *input, unsigned int length)
{
    if (!finalized)
    {
        unsigned int index = (count[0] >> 3) & 0x3f;
        if ((count[0] += length << 3) < (length << 3))
            ++count[1];
        count[1] += length >> 29;
        unsigned int partLength = 64 - index;
        unsigned int i;
        if (length >= partLength)
        {
            memcpy(&buffer[index], input, partLength);
            transform(buffer);
            for (i = partLength; i + 63 < length; i += 64)
                transform(&input[i]);
            index = 0;
        }
        else
            i = 0;
        memcpy(&buffer[index], &input[i], length - i);
    }
}

// FUNCTION: GAME 0x0060e590
void MD5::finalize()
{
    unsigned char bits[8];
    encode(bits, count, 8);
    unsigned int index = (count[0] >> 3) & 0x3f;
    unsigned int padLength = index < 56 ? 56 - index : 120 - index;
    update(g_md5Padding, padLength);
    update(bits, 8);
    encode(digest, state, 16);
    memset(buffer, 0, 1);
    finalized = true;
}

// FUNCTION: GAME 0x0060e610
char *MD5::hex_digest()
{
    char *result = (char *)::operator new(33);
    if (!finalized)
        return g_unk0x6c0560;
    for (int i = 0; i < 16; ++i)
    {
        // STRING: GAME 0x006bb5ec
        sprintf(result + i * 2, "%02x", digest[i]);
    }
    result[32] = 0;
    return result;
}

// FUNCTION: GAME 0x0060e660
void MD5::init()
{
    finalized = false;
    count[0] = 0;
    count[1] = 0;
    state[0] = 0x67452301;
    state[1] = 0xefcdab89;
    state[2] = 0x98badcfe;
    state[3] = 0x10325476;
}

#define MD5_ROTATE(x, s) (((x) << (s)) | ((x) >> (32 - (s))))
#define MD5_FF(a, b, c, d, x, s, ac) { (a) += (((b) & (c)) | (~(b) & (d))) + (x) + (unsigned int)(ac); (a) = MD5_ROTATE(a, s); (a) += (b); }
#define MD5_GG(a, b, c, d, x, s, ac) { (a) += (((b) & (d)) | ((c) & ~(d))) + (x) + (unsigned int)(ac); (a) = MD5_ROTATE(a, s); (a) += (b); }
#define MD5_HH(a, b, c, d, x, s, ac) { (a) += ((b) ^ (c) ^ (d)) + (x) + (unsigned int)(ac); (a) = MD5_ROTATE(a, s); (a) += (b); }
#define MD5_II(a, b, c, d, x, s, ac) { (a) += ((c) ^ ((b) | ~(d))) + (x) + (unsigned int)(ac); (a) = MD5_ROTATE(a, s); (a) += (b); }

// FUNCTION: GAME 0x0060e690
void MD5::transform(unsigned char *block)
{
    unsigned int a = state[0], b = state[1], c = state[2], d = state[3], x[16];
    decode(x, block, 64);
    MD5_FF(a, b, c, d, x[0], 7, 0xd76aa478);
    MD5_FF(d, a, b, c, x[1], 12, 0xe8c7b756);
    MD5_FF(c, d, a, b, x[2], 17, 0x242070db);
    MD5_FF(b, c, d, a, x[3], 22, 0xc1bdceee);
    MD5_FF(a, b, c, d, x[4], 7, 0xf57c0faf);
    MD5_FF(d, a, b, c, x[5], 12, 0x4787c62a);
    MD5_FF(c, d, a, b, x[6], 17, 0xa8304613);
    MD5_FF(b, c, d, a, x[7], 22, 0xfd469501);
    MD5_FF(a, b, c, d, x[8], 7, 0x698098d8);
    MD5_FF(d, a, b, c, x[9], 12, 0x8b44f7af);
    MD5_FF(c, d, a, b, x[10], 17, 0xffff5bb1);
    MD5_FF(b, c, d, a, x[11], 22, 0x895cd7be);
    MD5_FF(a, b, c, d, x[12], 7, 0x6b901122);
    MD5_FF(d, a, b, c, x[13], 12, 0xfd987193);
    MD5_FF(c, d, a, b, x[14], 17, 0xa679438e);
    MD5_FF(b, c, d, a, x[15], 22, 0x49b40821);
    MD5_GG(a, b, c, d, x[1], 5, 0xf61e2562);
    MD5_GG(d, a, b, c, x[6], 9, 0xc040b340);
    MD5_GG(c, d, a, b, x[11], 14, 0x265e5a51);
    MD5_GG(b, c, d, a, x[0], 20, 0xe9b6c7aa);
    MD5_GG(a, b, c, d, x[5], 5, 0xd62f105d);
    MD5_GG(d, a, b, c, x[10], 9, 0x02441453);
    MD5_GG(c, d, a, b, x[15], 14, 0xd8a1e681);
    MD5_GG(b, c, d, a, x[4], 20, 0xe7d3fbc8);
    MD5_GG(a, b, c, d, x[9], 5, 0x21e1cde6);
    MD5_GG(d, a, b, c, x[14], 9, 0xc33707d6);
    MD5_GG(c, d, a, b, x[3], 14, 0xf4d50d87);
    MD5_GG(b, c, d, a, x[8], 20, 0x455a14ed);
    MD5_GG(a, b, c, d, x[13], 5, 0xa9e3e905);
    MD5_GG(d, a, b, c, x[2], 9, 0xfcefa3f8);
    MD5_GG(c, d, a, b, x[7], 14, 0x676f02d9);
    MD5_GG(b, c, d, a, x[12], 20, 0x8d2a4c8a);
    MD5_HH(a, b, c, d, x[5], 4, 0xfffa3942);
    MD5_HH(d, a, b, c, x[8], 11, 0x8771f681);
    MD5_HH(c, d, a, b, x[11], 16, 0x6d9d6122);
    MD5_HH(b, c, d, a, x[14], 23, 0xfde5380c);
    MD5_HH(a, b, c, d, x[1], 4, 0xa4beea44);
    MD5_HH(d, a, b, c, x[4], 11, 0x4bdecfa9);
    MD5_HH(c, d, a, b, x[7], 16, 0xf6bb4b60);
    MD5_HH(b, c, d, a, x[10], 23, 0xbebfbc70);
    MD5_HH(a, b, c, d, x[13], 4, 0x289b7ec6);
    MD5_HH(d, a, b, c, x[0], 11, 0xeaa127fa);
    MD5_HH(c, d, a, b, x[3], 16, 0xd4ef3085);
    MD5_HH(b, c, d, a, x[6], 23, 0x04881d05);
    MD5_HH(a, b, c, d, x[9], 4, 0xd9d4d039);
    MD5_HH(d, a, b, c, x[12], 11, 0xe6db99e5);
    MD5_HH(c, d, a, b, x[15], 16, 0x1fa27cf8);
    MD5_HH(b, c, d, a, x[2], 23, 0xc4ac5665);
    MD5_II(a, b, c, d, x[0], 6, 0xf4292244);
    MD5_II(d, a, b, c, x[7], 10, 0x432aff97);
    MD5_II(c, d, a, b, x[14], 15, 0xab9423a7);
    MD5_II(b, c, d, a, x[5], 21, 0xfc93a039);
    MD5_II(a, b, c, d, x[12], 6, 0x655b59c3);
    MD5_II(d, a, b, c, x[3], 10, 0x8f0ccc92);
    MD5_II(c, d, a, b, x[10], 15, 0xffeff47d);
    MD5_II(b, c, d, a, x[1], 21, 0x85845dd1);
    MD5_II(a, b, c, d, x[8], 6, 0x6fa87e4f);
    II(d, a, b, c, x[15], 10, 0xfe2ce6e0);
    II(c, d, a, b, x[6], 15, 0xa3014314);
    II(b, c, d, a, x[13], 21, 0x4e0811a1);
    II(a, b, c, d, x[4], 6, 0xf7537e82);
    II(d, a, b, c, x[11], 10, 0xbd3af235);
    II(c, d, a, b, x[2], 15, 0x2ad7d2bb);
    II(b, c, d, a, x[9], 21, 0xeb86d391);
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    memset((unsigned char *)x, 0, sizeof(x));
}

// FUNCTION: GAME 0x0060f040
void MD5::encode(unsigned char *output, unsigned int *input, unsigned int length)
{
    for (unsigned int i = 0, j = 0; j < length; ++i, j += 4)
    {
        output[j] = (unsigned char)(input[i] & 0xff);
        output[j + 1] = (unsigned char)((input[i] >> 8) & 0xff);
        output[j + 2] = (unsigned char)((input[i] >> 16) & 0xff);
        output[j + 3] = (unsigned char)((input[i] >> 24) & 0xff);
    }
}

// FUNCTION: GAME 0x0060f090
void MD5::decode(unsigned int *output, unsigned char *input, unsigned int length)
{
    for (unsigned int i = 0, j = 0; j < length; ++i, j += 4)
        output[i] = (unsigned int)input[j] | ((unsigned int)input[j + 1] << 8) |
                    ((unsigned int)input[j + 2] << 16) | ((unsigned int)input[j + 3] << 24);
}

// FUNCTION: GAME 0x0060f0e0
void MD5::memcpy(unsigned char *output, unsigned char *input, unsigned int length)
{
    for (unsigned int i = 0; i < length; ++i)
        output[i] = input[i];
}

// FUNCTION: GAME 0x0060f100
void MD5::memset(unsigned char *output, unsigned char value, unsigned int length)
{
    for (unsigned int i = 0; i < length; ++i)
        output[i] = value;
}

// FUNCTION: GAME 0x0060f130
void MD5::II(unsigned int &a, unsigned int b, unsigned int c, unsigned int d,
             unsigned int x, unsigned int s, unsigned int ac)
{
    unsigned int value = a + (c ^ (b | ~d));
    value += x;
    value += ac;
    a = ((value << s) | (value >> (32 - s))) + b;
}

// FUNCTION: GAME 0x0060f180
bool MD5::operator==(MD5 &other)
{
    for (int i = 0; i < 16; ++i)
        if (digest[i] != other.digest[i])
            return false;
    return true;
}

// FUNCTION: GAME 0x0060f1c0
bool MD5::operator!=(MD5 &other)
{
    return !operator==(other);
}

// FUNCTION: GAME 0x0060f1e0
void MD5::Serialize(SBFile &file)
{
    for (int i = 0; i < 16; ++i)
        file.Access(&digest[i], 1);
}

void MD5::Emit(unsigned char *input, unsigned int length, MD5 &other)
{
    init();
    update(input, length);
    finalize();
    hex_digest();
    operator==(other);
}
