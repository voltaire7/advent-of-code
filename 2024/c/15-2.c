#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define SIZE 50

char map[SIZE][SIZE*2];

bool check(int x, int y, int vx, int vy) {
    switch (map[y+vy][x+vx]) {
        case '[': return check(x+vx, y+vy, vx, vy) && (vx+1 == 0 ? true : check(x+vx+1, y+vy, vx, vy));
        case ']': return (vx-1 == 0 ? true : check(x+vx-1, y+vy, vx, vy)) && check(x+vx, y+vy, vx, vy);
        case '.': return true;
        case '#': return false;
    }
    return false;
}

void move(int x, int y, int vx, int vy) {
    switch (map[y+vy][x+vx]) {
        case '[':
            move(x+vx, y+vy, vx, vy);
            if (!vx) move(x+vx+1, y+vy, vx, vy);
            map[y+vy][x+vx] = map[y][x];
            map[y][x] = '.';
            break;
        case ']':
            move(x+vx, y+vy, vx, vy);
            if (!vx)  move(x+vx-1, y+vy, vx, vy);
            map[y+vy][x+vx] = map[y][x];
            map[y][x] = '.';
            break;
        case '.':
            map[y+vy][x+vx] = map[y][x];
            map[y][x] = '.';
            break;
    }
}

int main() {
    FILE *file = fopen("2024/inputs/day-15", "r");

    int y, x;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE*2; j += 2) {
            char c = fgetc(file);
            switch (c) {
                case 'O':
                    map[i][j  ] = '[';
                    map[i][j+1] = ']';
                    break;
                case '@':
                    map[i][j  ] = '@';
                    map[i][j+1] = '.';
                    y = i, x = j;
                    break;
                case '#':
                    map[i][j] = map[i][j+1] = '#';
                    break;
                case '.':
                    map[i][j] = map[i][j+1] = '.';
                    break;
                case '\n':
                    j -= 2;
                    break;
            }
        }
    }
found:;

    printf("initial state:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%.*s\n", SIZE*2, map[i]);
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
        if (check(x, y, vx, vy)) {
            move(x, y, vx, vy);
            x += vx, y += vy;
        }
        continue;

        printf("move: %c\n", c);
        for (int i = 0; i < SIZE; i++) {
            printf("%.*s\n", SIZE*2, map[i]);
        }
        printf("\n");
    }

    long sum = 0;
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE*2; x++) {
            if (map[y][x] == '[') sum += 100 * y + x;
        }
    }
    printf("sum: %li\n", sum);
}
