#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char* content = read_entire_file("inputs/day-5");
    int   len     = strlen(content);

    int nice = 0;
    for (int i = 0; i < len; i += 17) {
        int j = i;

        int repeat = 0;
        for (; j - i < 16; j++) {
            if (j - i < 14 && content[j] == content[j + 2]) repeat++;
        }

        int pair = 0;
        if (repeat)
            for (j = i; j - i < 13; j++)
                for (int k = j + 2; k - i < 15; k++)
                    if (content[j] == content[k]
                        && content[j + 1] == content[k + 1]) {
                        pair++;
                        goto end;
                    }
    end:
        if (repeat && pair) nice++;
    }
    printf("nice: %i\n", nice);
}
