#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_size_t.h>

#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

// Constants are the integer part of the sines of integers (in radians) * 2^32.
uint32_t K[64] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a,
    0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340,
    0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8,
    0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa,
    0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92,
    0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
};

// Per-round shift amounts
uint32_t s[64] = {
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
    5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20,
    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21,
};

void md5(const uint8_t* initial_msg, size_t initial_len, uint8_t* digest) {
    // Initialize variables:
    uint32_t a0 = 0x67452301; // A
    uint32_t b0 = 0xefcdab89; // B
    uint32_t c0 = 0x98badcfe; // C
    uint32_t d0 = 0x10325476; // D

    // Pre-processing: padding the message
    size_t new_len = initial_len + 1;
    while (new_len % 64 != 56) {
        new_len++;
    }

    uint8_t* msg = malloc(new_len + 8);
    memcpy(msg, initial_msg, initial_len);
    msg[initial_len] = 0x80; // Append "1" bit to the message
    memset(msg + initial_len + 1, 0, new_len - initial_len - 1);

    // Append the original length in bits at the end of the buffer.
    uint64_t bits_len = 8 * initial_len; // Note: original length in *bits*
    memcpy(msg + new_len, &bits_len, 8); // Append the length as a 64-bit number

    // Process the message in successive 512-bit chunks:
    for (size_t offset = 0; offset < new_len; offset += 64) {
        // Break chunk into sixteen 32-bit words M[j]
        uint32_t* M = (uint32_t*) (msg + offset);

        // Initialize hash value for this chunk:
        uint32_t A = a0;
        uint32_t B = b0;
        uint32_t C = c0;
        uint32_t D = d0;

        // Main loop:
        for (uint32_t i = 0; i < 64; i++) {
            uint32_t F, g;

            if (i < 16) {
                F = (B & C) | ((~B) & D);
                g = i;
            } else if (i < 32) {
                F = (D & B) | ((~D) & C);
                g = (5 * i + 1) % 16;
            } else if (i < 48) {
                F = B ^ C ^ D;
                g = (3 * i + 5) % 16;
            } else {
                F = C ^ (B | (~D));
                g = (7 * i) % 16;
            }

            F = F + A + K[i] + M[g];
            A = D;
            D = C;
            C = B;
            B = B + LEFTROTATE(F, s[i]);
        }

        // Add this chunk's hash to result so far:
        a0 += A;
        b0 += B;
        c0 += C;
        d0 += D;
    }

    // Output the final hash value in little-endian
    memcpy(digest, &a0, 4);
    memcpy(digest + 4, &b0, 4);
    memcpy(digest + 8, &c0, 4);
    memcpy(digest + 12, &d0, 4);

    // Cleanup
    free(msg);
}

int main() {
    char msg[100] = "iwrupvqb";

    size_t   len = strlen(msg);
    uint8_t  result[16];
    uint64_t number = 0;
    do {
        number++;
        sprintf(msg + len, "%llu", number);
        size_t new_len = strlen(msg);
        md5((const uint8_t*) msg, new_len, result);
    } while (result[0] != 0 || result[1] != 0 || result[2] != 0);

    printf("MD5 digest: ");
    for (int i = 0; i < 16; i++) printf("%02x", result[i]);
    printf("\n");
    printf("Number: %llu\n", number);
}
