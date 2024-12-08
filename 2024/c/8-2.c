#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 50

char map[SIZE][SIZE] = {};
bool bools[SIZE][SIZE] = {};

void find(int *y, int *x) {
    char c = map[*y][*x];
    for (int i = *y; i < SIZE; i++) {
        for (int j = i > *y ? 0 : *x + 1; j < SIZE; j++) {
            // printf("debug 3: %c, %i, %i\n", c, i, j);
            if (map[i][j] == c) {
                *y = i, *x = j;
                return;
            }
        }
    }
    *y = -1, *x = -1;
}

int main() {
    FILE *file = fopen("2024/inputs/day-8", "r");
    for (int i = 0; i < SIZE; i++) fscanf(file, "%s ", map[i]);

    for (int y1 = 0; y1 < SIZE; y1++) {
        for (int x1 = 0; x1 < SIZE; x1++) {
            if (map[y1][x1] == '.') continue;
            bools[y1][x1] = true;
            char c = map[y1][x1];
            int y2 = y1, x2 = x1;
            for (;;) {
                find(&y2, &x2);
                // printf("debug 1: %c, %i, %i\n", map[y1][x1], y1, x1);
                // printf("debug 2: %c, %i, %i\n\n", map[y2][x2], y2, x2);
                if (y2 < 0 || x2 < 0) break;

                int disty = y2 - y1, distx = x2 - x1;
                for (int i = 0; y1-disty*i >= 0 && y1-disty*i < SIZE && x1-distx*i >= 0 && x1-distx*i < SIZE; i++) {
                    bools[y1-disty*i][x1-distx*i] = true;
                }
                for (int i = 0; y2+disty*i >= 0 && y2+disty*i < SIZE && x2+distx*i >= 0 && x2+distx*i < SIZE; i++) {
                    bools[y2+disty*i][x2+distx*i] = true;
                }
            }
        }
    }

    int count = 0;
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            count += bools[y][x];
        }
    }
    printf("count: %i\n", count);

    return 0;
    for (int i = 0; i < SIZE; i++) {
        printf("%.*s\n", SIZE, map[i]);
    }
}