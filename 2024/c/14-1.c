#include <stdio.h>

#define HEIGHT 103
#define WIDTH  101

int mod(int a, int b) {
    int result = a % b;
    if (result < 0) result += b;
    return result;
}

int main() {
    FILE *file = fopen("2024/inputs/day-14", "r");

    int q[4] = {};
    while (!feof(file)) {
        int px, py, vx, vy;
        fscanf(file, "p=%i,%i v=%i,%i ", &px, &py, &vx, &vy);
        px = mod(px + vx * 100, WIDTH), py = mod(py + vy * 100, HEIGHT);
        if (px < (WIDTH-1) / 2) {
            if (py < (HEIGHT-1) / 2) {
                q[0]++;
            } else if (py > (HEIGHT-1) / 2) {
                q[3]++;
            }
        } else if (px > (WIDTH-1) / 2) {
            if (py < (HEIGHT-1) / 2) {
                q[1]++;
            } else if (py > (HEIGHT-1) / 2) {
                q[2]++;
            }
        }
    }
    printf("safety_factor: %i\n", q[0]*q[1]*q[2]*q[3]);
}
