#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define EQUATION_COUNT 850
#define u64 unsigned long

u64 targets[EQUATION_COUNT];
u64 items[EQUATION_COUNT][20] = {};

char *read_entire_file(char* filename) {
    FILE *file = fopen(filename, "r");
    fseek(file, 0, SEEK_END);
    u64 fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *str = malloc(fsize + 1);
    fread(str, fsize, 1, file);
    fclose(file);

    str[fsize] = 0;
    return str;
}

void parse(char **content) {
    for (int i = 0; i < EQUATION_COUNT; i++) {
        targets[i] = strtoul(*content, content, 10);
        ++*content;
        for (int j = 0; **content && **content != '\n'; j++) {
            items[i][j] = strtoul(*content, content, 10);
        }
    }
}

u64 count_digits(u64 n) {
    int i = 0;
    for (; n; n /= 10, i++);
    return i;
}

u64 concat(u64 x, u64 y) {
    for (int i = 0; i < count_digits(y); i++) x *= 10;
    return x + y;
}

bool find(u64 target, u64 *arr, u64 sum) {
    if (*arr == 0) return target == sum;
    else return find(target, arr + 1, *arr + sum) ||
                find(target, arr + 1, *arr * sum) ||
                find(target, arr + 1, concat(sum, *arr));
}

int main() {
    char *content = read_entire_file("2024/inputs/day-7");
    parse(&content);

    u64 sum = 0;
    for (u64 i = 0; i < EQUATION_COUNT; i++) {
        if (find(targets[i], items[i] + 1, items[i][0])) sum += targets[i];
    }
    printf("sum: %lu\n", sum);
}
