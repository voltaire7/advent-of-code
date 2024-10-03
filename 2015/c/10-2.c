#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* look_and_say(char* seed, int depth) {
    for (int i = 0; i < depth; i++) {
        int len = strlen(seed), offset = 0, count = 1;
        char* temp = (char*) malloc(len * 2);

        for (int j = 1; j <= len; j++) {
            if (seed[j] != seed[j - 1]) {
                offset += sprintf(temp + offset, "%d%c", count, seed[j - 1]);
                count = 1;
            } else count++;
        }

        free(seed);
        seed = strdup(temp);
        free(temp);
    }
    return seed;
}

int main() {
    int N = 50;
    char* initial = strdup("1321131112");

    char* result = look_and_say(initial, N);
    printf("Length of term after %d iterations: %lu\n", N, strlen(result));
}
