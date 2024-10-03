#include <stdio.h>
#include <string.h>

#define BUFSIZE 1000000

char  input[BUFSIZE] = "1321131112";
char output[BUFSIZE];

char* itoa(int val, int base) {
    static char buf[32] = {0};
    int i = 30;
    for (; val && i; --i, val /= base) buf[i] = "0123456789abcdef"[val % base];
    return &buf[i + 1];
}

int main() {
    char c[] = "0";
    for (int i = 0; i < 40; i++) {
        for (int j = 0; input[j]; j++) {
            int n = 1; c[0] = input[j];
            while (input[++j] == c[0]) n++; --j;
            strcat(output, itoa(n, 10));
            strcat(output, c);
        }
        strcpy(input, output);
        strcpy(output, "");
    }
    printf("%s, %lu\n", input, strlen(input));
}
