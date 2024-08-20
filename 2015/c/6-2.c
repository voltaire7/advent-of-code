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

char grid[1000][1000] = {0};

enum {
    TOGGLE   = 7,
    TURN_ON  = 8,
    TURN_OFF = 9,
};

int main() {
    char* content = read_entire_file("inputs/day-6");

    while (*content) {
        int type;

        if (content[1] == 'o')
            type = TOGGLE;
        else if (content[6] == 'n')
            type = TURN_ON;
        else if (content[6] == 'f')
            type = TURN_OFF;

        int x1 = strtol(content + type, &content, 10);
        int y1 = strtol(content + 1, &content, 10);
        int x2 = strtol(content + 9, &content, 10);
        int y2 = strtol(content + 1, &content, 10);
        content++;

        for (int x = x1; x <= x2; x++)
            for (int y = y1; y <= y2; y++) switch (type) {
                    case TOGGLE:
                        grid[x][y] += 2;
                        break;
                    case TURN_ON:
                        grid[x][y]++;
                        break;
                    case TURN_OFF:
                        if (grid[x][y] != 0) grid[x][y]--;
                        break;
                };
    }

    int count = 0;
    for (int x = 0; x < 1000; x++)
        for (int y = 0; y < 1000; y++) count += grid[x][y];
    printf("%i\n", count);
}
