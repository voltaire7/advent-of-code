#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 37

int count(char *s) {
    int count = 1;
    while (*s++) {
        if (*s == ' ') count++;
    }
    return count;
}

uint64_t *to_arr(char *s, int count) {
    uint64_t *arr = malloc(sizeof(uint64_t) * count);
    for (int i = 0; *s; i++) {
        arr[i] = strtoul(s, &s, 10);
    }
    return arr;
}

uint64_t count_digits(uint64_t n) {
    int i = 0;
    for (; n; n /= 10, i++);
    return i;
}

void blink(uint64_t **arr, int *count) {
    int new_count = 0;
    for (int i = 0; i < *count; i++) {
        if ((*arr)[i] && count_digits((*arr)[i]) % 2 == 0) new_count += 2;
        else new_count++;
    }

    uint64_t *new_arr = malloc(sizeof(uint64_t) * new_count);
    for (int i = 0, j = 0; i < *count; i++, j++) {
        int digits = count_digits((*arr)[i]);
        if ((*arr)[i] == 0) new_arr[j] = 1;
        else if (digits % 2 == 0) {
            int pow = 1;
            for (int k = 0; k < digits/2; k++) pow *= 10;

            new_arr[j++] = (*arr)[i] / pow;
            new_arr[j  ] = (*arr)[i] % pow;
        } else new_arr[j] = (*arr)[i] * 2024;
    }

    free(*arr);
    *arr = new_arr;
    *count = new_count;
}

int main() {
    FILE *file = fopen("2024/inputs/day-11", "r");
    char content[SIZE];
    fread(content, sizeof(char), SIZE, file);
    content[SIZE-1] = 0;
    int c = count(content);
    uint64_t *arr = to_arr(content, c);
    for (int i = 0; i < 25; i++) {
        blink(&arr, &c);
    }

    printf("stone count: %i\n", c);
}
