#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 1000

int lists[2][INPUT_SIZE];

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

void parse_content(char *content) {
    for (int i = 0; i < INPUT_SIZE; i++) {
        lists[0][i] = strtol(content, &content, 10);
        lists[1][i] = strtol(content, &content, 10);
    }
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    char *content = read_entire_file("inputs/day-1");
    parse_content(content);

    qsort(lists[0], INPUT_SIZE, sizeof(int), compare);
    qsort(lists[1], INPUT_SIZE, sizeof(int), compare);

    int distance = 0;
    for (int i = 0; i < INPUT_SIZE; i++) {
        distance += abs(lists[1][i] - lists[0][i]);
    }
    printf("%i\n", distance);

    return 0;
    // debug
    for (int i = 0; i < INPUT_SIZE; i++) {
        printf("%i, %i\n", lists[0][i], lists[1][i]);
    }
}
