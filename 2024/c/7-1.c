#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define EQUATION_COUNT 850
#define u64 unsigned long

u64 targets[EQUATION_COUNT];
u64 items[EQUATION_COUNT][20] = {};

u64 add(u64 x, u64 y) { return x + y; }
u64 mul(u64 x, u64 y) { return x * y; }

char *read_entire_file(char* filename) {
    FILE *file = fopen(filename, "r");
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
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

bool find(u64 target, u64 *arr, u64 sum) {
    if (*arr == 0) return target == sum;
    else return find(target, arr + 1, *arr + sum) || find(target, arr + 1, *arr * sum);
}

int main() {
    char *content = read_entire_file("2024/inputs/day-7");
    parse(&content);

    u64 sum = 0;
    for (u64 i = 0; i < EQUATION_COUNT; i++) {
        if (find(targets[i], items[i] + 1, items[i][0])) sum += targets[i];
    }
    printf("sum: %li\n", sum);
}
