#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define SIZE 50

char map[SIZE][SIZE];

bool move(int x, int y, int vx, int vy) {
    switch (map[y+vy][x+vx]) {
        case 'O': {
            bool result = move(x+vx, y+vy, vx, vy);
            if (!result) return false;
        }
        case '.':
            map[y+vy][x+vx] = map[y][x];
            map[y][x] = '.';
            return true;
        case '#':
            return false;
    }
    return true;
}

int main() {
    FILE *file = fopen("2024/inputs/day-15", "r");
    for (int i = 0; i < SIZE; i++) {
        fscanf(file, "%s ", map[i]);
    }

    int x, y;
    for (y = 0; y < SIZE; y++) {
        for (x = 0; x < SIZE; x++) {
            if (map[y][x] == '@') goto found;
        }
    }
found:;

    printf("initial state:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%.*s\n", SIZE, map[i]);
    }
    printf("\n");
    char c;
    while ((c = fgetc(file)) != EOF) {
        int vx = 0, vy = 0;
        switch (c) {
            case '<':
                vx = -1, vy = 0;
                break;
            case '>':
                vx = +1, vy = 0;
                break;
            case '^':
                vx = 0, vy = -1;
                break;
            case 'v':
                vx = 0, vy = +1;
                break;
        }
        if (move(x, y, vx, vy)) x += vx, y += vy;
        continue;
        printf("%i, %i\n", x, y);

        printf("move: %c\n", c);
        for (int i = 0; i < SIZE; i++) {
            printf("%.*s\n", SIZE, map[i]);
        }
        printf("\n");
    }

    long sum = 0;
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            if (map[y][x] == 'O') sum += 100 * y + x;
        }
    }
    printf("sum: %li\n", sum);
}
