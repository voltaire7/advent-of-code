#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 50

char map  [SIZE][SIZE] = {};
bool bools[SIZE][SIZE] = {};

bool find(int *y, int *x) {
    char c = map[*y][*x];
    for (int i = *y; i < SIZE; i++) {
        for (int j = i > *y ? 0 : *x + 1; j < SIZE; j++) {
            if (map[i][j] == c) {
                *y = i, *x = j;
                return true;
            }
        }
    }
    return false;
}

int main() {
    FILE *file = fopen("2024/inputs/day-8", "r");
    for (int i = 0; i < SIZE; i++) fscanf(file, "%s ", map[i]);

    for (int y1 = 0; y1 < SIZE; y1++) {
        for (int x1 = 0; x1 < SIZE; x1++) {
            if (map[y1][x1] == '.') continue;
            char c = map[y1][x1];
            int y2 = y1, x2 = x1;
            while (find(&y2, &x2)) {
                int disty = y2 - y1, distx = x2 - x1;
                if (y1-disty >= 0 && y1-disty < SIZE && x1-distx >= 0 && x1-distx < SIZE) bools[y1-disty][x1-distx] = true;
                if (y2+disty >= 0 && y2+disty < SIZE && x2+distx >= 0 && x2+distx < SIZE) bools[y2+disty][x2+distx] = true;
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
}
