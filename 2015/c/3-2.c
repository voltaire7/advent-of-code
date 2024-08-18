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
    char* content = read_entire_file("inputs/day-3");

    int houses[512][512] = {0};

    int x1 = 127, y1 = 127;
    int x2 = 127, y2 = 127;
    houses[x1][y1] = 1;
    int count      = 1;
    for (; *content; content += 2) {
        switch (*content) {
            case '>':
                x1++;
                break;
            case '<':
                x1--;
                break;
            case '^':
                y1++;
                break;
            case 'v':
                y1--;
                break;
        }
        if (!houses[x1][y1]) {
            count++;
            houses[x1][y1]++;
        }
        switch (*(content + 1)) {
            case '>':
                x2++;
                break;
            case '<':
                x2--;
                break;
            case '^':
                y2++;
                break;
            case 'v':
                y2--;
                break;
        }
        if (!houses[x2][y2]) {
            count++;
            houses[x2][y2]++;
        }
    }
    printf("%i\n", count);
}
