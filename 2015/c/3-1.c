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

    int x = 127, y = 127;
    houses[x][y] = 1;
    int count    = 1;
    for (; *content; content++) {
        switch (*content) {
            case '>':
                x++;
                break;
            case '<':
                x--;
                break;
            case '^':
                y++;
                break;
            case 'v':
                y--;
                break;
        }
        if (!houses[x][y]) {
            count++;
            houses[x][y]++;
        }
    }
    printf("%i\n", count);
}
