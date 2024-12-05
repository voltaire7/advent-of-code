#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define RULE_COUNT 1176
#define UPDATE_ROW_COUNT 190
#define UPDATE_COL_COUNT 23

char rules[RULE_COUNT][2];
char updates[UPDATE_ROW_COUNT][UPDATE_COL_COUNT] = {};

char *read_entire_file(char* filename) {
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

char *collect_rules(char *content) {
    int i = 0;
    for (; i < RULE_COUNT; i++) {
        rules[i][0] = atoi(content + i * 6);
        rules[i][1] = atoi(content + i * 6 + 3);
    }
    return content + i * 6 + 1;
}

void collect_updates(char *content) {
    int len = strlen(content);
    for (int i = 0, j = 0, k = 0; i < len; i += 3, k++) {
        if (content[i-1] == '\n') {
            j++;
            k = 0;
        }
        updates[j][k] = atoi(content + i);
    }
}

bool is_valid(char left, char right) {
    for (int i = 0; i < RULE_COUNT; i++) {
        if (left == rules[i][1] && right == rules[i][0]) return false;
    }
    return true;
}

int main() {
    char *content = read_entire_file("2024/inputs/day-5");
    content = collect_rules(content);
    collect_updates(content);

    int sum = 0;
    int count = 0;
    for (int i = 0; i < UPDATE_ROW_COUNT; i++) {
        bool valid = true;
        for (int j = 0; j < UPDATE_COL_COUNT; j++) {
            for (int k = j + 1; k < UPDATE_COL_COUNT; k++) {
                if (!is_valid(updates[i][j], updates[i][k])) {
                    char temp = updates[i][j];
                    updates[i][j] = updates[i][k];
                    updates[i][k] = temp;
                    valid = false;
                }
            }
        }
        if (valid) continue;

        count++;
        int j = 0;
        while (j < UPDATE_COL_COUNT && updates[i][j] != 0) j++;
        sum += updates[i][j/2];
    }
    printf("sum: %i\n", sum);
    printf("count: %i\n", count);
}
