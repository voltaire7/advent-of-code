#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

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

int main() {
    char* content = read_entire_file("inputs/day-8");

    int count_literal = 0;
    for (int i = 0; content[i]; i++)
        if (content[i] != '\n') count_literal++;
    int count_memory = 0;
    for (int i = 1; content[i]; i++) {
        switch (content[i]) {
            case '\\':
                count_memory++;
                if (content[++i] == 'x') i += 2;
                break;
            case '"':
            case '\n':
                break;
            default:
                count_memory++;
                break;
        }
    }

    printf("answer: %i\n", count_literal - count_memory);
}
