#include <stdio.h>

int main() {
    FILE *file = fopen("2024/inputs/day-13", "r");

    long tokens = 0;

    while (!feof(file)) {
        long ax, ay, bx, by, px, py;
        fscanf(file, "Button A: X+%li, Y+%li ", &ax, &ay);
        fscanf(file, "Button B: X+%li, Y+%li ", &bx, &by);
        fscanf(file, "Prize: X=%li, Y=%li ", &px, &py);

        px += 10000000000000;
        py += 10000000000000;

        long  numeratorX = px*by - py*bx;
        long denomiatorX = ax*by - ay*bx;

        long  numeratorY = px*ay - py*ax;
        long denomiatorY = ay*bx - ax*by;

        if (numeratorX % denomiatorX == 0 && numeratorY % denomiatorY == 0) {
            long a = numeratorX / denomiatorX;
            long b = numeratorY / denomiatorY;
            tokens += 3*a + b;
            // printf("%li\n", 3*a + b);
        }
    }

    printf("%li\n", tokens);
}
