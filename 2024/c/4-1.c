#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 141

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
    char *content = read_entire_file("2024/inputs/day-4");
    char chars[SIZE][SIZE];

    for (int row = 1; row <= SIZE; row++) {
        for (int column = 1; column <= SIZE; column++) {
            chars[row-1][column-1] = content[(row-1) * SIZE + (column-1)];
        }
    }

    int count = 0;
    for (int row = 0; row < SIZE-1; row++) {
        for (int col = 0; col < SIZE-1; col++) {
            for (int horizontal = -1; horizontal <= 1; horizontal++) {
                for (int vertical = -1; vertical <= 1; vertical++) {
                    if (row + horizontal*3 < 0 || row + horizontal*3 > SIZE-1 || col + vertical*3 < 0 || col + vertical*3 > SIZE-1) continue;
                    bool condition =
                        chars[row + horizontal*0][col + vertical*0] == 'X' &&
                        chars[row + horizontal*1][col + vertical*1] == 'M' &&
                        chars[row + horizontal*2][col + vertical*2] == 'A' &&
                        chars[row + horizontal*3][col + vertical*3] == 'S';
                    if (condition) count++;
                }
            }
        }
    }
    printf("count: %i\n", count);

    return 0;
    // debug
    for (int row = 1; row < SIZE; row++) {
        for (int column = 1; column < SIZE; column++) {
            printf("%c", chars[row-1][column-1]);
        }
        printf("\n");
    }
}
