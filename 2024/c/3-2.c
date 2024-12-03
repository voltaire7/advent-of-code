#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Pair {
    int left;
    int right;
} Pair;

char* read_entire_file(char* filename) {
    FILE* file = fopen(filename, "r");
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* str = malloc(fsize + 1);
    fread(str, fsize, 1, file);
    fclose(file);

    str[fsize] = 0;
    return str;
}

Pair get_pair(char **content) {
    int left, right;
    static bool should_do = true;

    for (; *(*content + 4); ++*content) {
        if (strncmp("do()", *content, 4) == 0) should_do = true;
        else if (strncmp("don't()", *content, 7) == 0) should_do = false;
        if (!should_do) continue;

        if (strncmp("mul(", *content, 4) != 0) continue;
        *content += 4;

        left = atoi(*content);
        for (; isdigit(**content); ++*content);

        if (**content != ',') continue;

        right = atoi(++*content);
        for (; isdigit(**content); ++*content);

        if (**content != ')') continue;
        else return (Pair){left, right};
    }

    return (Pair){};
}

int main() {
    char *content = read_entire_file("inputs/day-3");
    int sum = 0;
    for (;;) {
        Pair pair = get_pair(&content);
        if (pair.left != 0 && pair.right != 0) sum += pair.left * pair.right;
        else break;
    }
    printf("sum: %i\n", sum);
}
