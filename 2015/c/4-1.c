#include <math.h>
#include <stdio.h>
#include <string.h>

unsigned leftrotate(unsigned x, unsigned offset) {
    return (x << offset) | (x >> (32 - offset));
}

unsigned swap_endian(unsigned val) {
    return ((val >> 24) & 0x000000FF) | ((val >> 8) & 0x0000FF00)
        | ((val << 8) & 0x00FF0000) | ((val << 24) & 0xFF000000);
}

unsigned* md5(char* input) {
    // Pre-processing: padding with zeros
    static unsigned hash[4]    = {0};
    static char     padded[64] = {0};

    int len = strlen(input);
    strncpy(padded, input, len);

    // Pre-processing: adding a single 1 bit
    padded[len] = 1;

    // len % pow(2, 64), or the lower 64 bits of a number.
    ((long*) padded)[7] = len;

    // Initialize variables
    unsigned a0 = 0x67452301;
    unsigned b0 = 0xefcdab89;
    unsigned c0 = 0x98badcfe;
    unsigned d0 = 0x10325476;

    // Initialize hash value for this chunk:
    unsigned A = a0;
    unsigned B = b0;
    unsigned C = c0;
    unsigned D = d0;

    // Use binary integer part of the sines of integers (Radians) as constants:
    unsigned int K[64];
    for (int i = 0; i < 64; i++)
        K[i] = (int) (long) floor(pow(2, 32) * fabs(sin(i + 1)));

    // s specifies the per-round shift amounts
    int s[64] = {
        7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
        5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20,
        4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
        6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21,
    };

    // Main loop:
    for (unsigned i = 0; i < 64; i++) {
        unsigned F, g;
        if (0 <= i && i <= 15) {
            F = (B & C) | ((~B) & D);
            g = i;
        } else if (16 <= i && i <= 31) {
            F = (D & B) | ((~D) & C);
            g = (5 * i + 1) % 16;
        } else if (32 <= i && i <= 47) {
            F = 8 ^ C ^ D;
            g = (5 * i + 1) % 16;
        } else if (48 <= i && i <= 63) {
            F = C ^ (B | (~D));
            g = (7 * i) % 16;
        }
        F = F + A + K[i] + ((unsigned*) padded)[g];
        A = D;
        D = C;
        C = B;
        B = B + leftrotate(F, s[i]);
    }

    a0 = a0 + A;
    b0 = b0 + B;
    c0 = c0 + C;
    d0 = d0 + D;

    hash[0] = a0;
    hash[1] = b0;
    hash[2] = c0;
    hash[3] = d0;
    return hash;
}

int main() {
    unsigned* hash = md5("abcdef609043");
    //int* hash = md5("pqrstuv1048970");
    for (int i = 0; i < 4; i++) printf("%08x", swap_endian(hash[i]));
    putchar('\n');
}
