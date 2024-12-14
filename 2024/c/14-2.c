#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define HEIGHT 103
#define WIDTH  101

int mod(int a, int b) {
    int result = a % b;
    if (result < 0) result += b;
    return result;
}

int main() {
    FILE *file = fopen("2024/inputs/day-14", "r");

    for (int s = 0;; s++) {
        int q[4] = {};

        char map[HEIGHT][WIDTH] = {};
        memset(map, '.', HEIGHT*WIDTH);

        bool skip = false;
        while (!feof(file)) {
            int px, py, vx, vy;
            fscanf(file, "p=%i,%i v=%i,%i ", &px, &py, &vx, &vy);
            px = mod(px + vx * s, WIDTH), py = mod(py + vy * s, HEIGHT);
            if (map[py][px] == '#') {
                skip = true;
                break;
            }
            map[py][px] = '#';
        }
        fseek(file, 0, SEEK_SET);
        if (skip) continue;
        printf("\nsecond: %i\n", s);
        for (int i = 0; i < HEIGHT; i++) {
            printf("%.*s\n", WIDTH, map[i]);
        }
        break;
    }
}
