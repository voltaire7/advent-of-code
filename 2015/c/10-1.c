#include <stdio.h>
#include <string.h>
#include <time.h>

#define BUFSIZE 10000000

char  input[BUFSIZE] = "1321131112";
char output[BUFSIZE];

char* itoa(int val, int base) {
    static char buf[32] = {0};
    int i = 30;
    for (; val && i; --i, val /= base) buf[i] = "0123456789abcdef"[val % base];
    return &buf[i + 1];
}

int main() {
    for (int i = 0; i < 40; i++) {
        for (int j = 0, offset = 0; input[j]; j++) {
            int n = 1;
            char c = input[j];
            while (input[++j] == c) n++; --j;
            offset += sprintf(output + offset, "%i%c", n, c);
        }
        strcpy(input, output);
        strcpy(output, "");
    }
    printf("%lu\n", strlen(input));
}
