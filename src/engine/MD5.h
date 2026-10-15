#ifndef GREENWOOD_MD5_H
#define GREENWOOD_MD5_H

class SBFile;

class MD5
{
public:
    MD5();
    enum Uninitialized { UninitializedStorage };
    explicit MD5(Uninitialized) {}
    void update(unsigned char *input, unsigned int length);
    void finalize();
    char *hex_digest();
    void init();
    void transform(unsigned char *block);
    static void encode(unsigned char *output, unsigned int *input, unsigned int length);
    static void decode(unsigned int *output, unsigned char *input, unsigned int length);
    static void memcpy(unsigned char *output, unsigned char *input, unsigned int length);
    static void memset(unsigned char *output, unsigned char value, unsigned int length);
    static void II(unsigned int &a, unsigned int b, unsigned int c, unsigned int d,
                   unsigned int x, unsigned int s, unsigned int ac);
    bool operator==(MD5 &other);
    bool operator!=(MD5 &other);
    void Serialize(SBFile &file);
    void Emit(unsigned char *input, unsigned int length, MD5 &other);

    unsigned int state[4];
    unsigned int count[2];
    unsigned char buffer[64];
    unsigned char digest[16];
    bool finalized;
};

#endif
