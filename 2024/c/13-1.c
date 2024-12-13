#include <stdatomic.h>
#include <stdio.h>

typedef struct Vector2 {
    int x, y;
} Vector2;

typedef struct ClawMachine {
    Vector2 A, B, Prize;
} ClawMachine;

int count_lines(FILE *file) {
    int lines = 0;
    char c;

    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') lines++;
    }
    fseek(file, 0, SEEK_SET);

    return lines;
}

void collect_input(FILE *file, ClawMachine cm[], int length) {
    for (int i = 0; i < length; i++) {
        fscanf(file, "Button A: X+%i, Y+%i ", &cm[i].A.x, &cm[i].A.y);
        fscanf(file, "Button B: X+%i, Y+%i ", &cm[i].B.x, &cm[i].B.y);
        fscanf(file, "Prize: X=%i, Y=%i ", &cm[i].Prize.x, &cm[i].Prize.y);
    }
}

int calculate_tokens(ClawMachine cm) {
    int B = 0;
    while (B * cm.B.x <= cm.Prize.x || B * cm.B.y <= cm.Prize.y) B++;

    while (B-- >= 0) {
        int A = -1, x, y;

        do {
            A++;
            x = B * cm.B.x + A * cm.A.x;
            y = B * cm.B.y + A * cm.A.y;
        } while (x < cm.Prize.x && y < cm.Prize.y);

        if (x == cm.Prize.x && y == cm.Prize.y) return 3 * A + B;
    }

    return -1;
}

int main() {
    FILE *file = fopen("2024/inputs/day-13", "r");
    int lines = count_lines(file), length = (lines+1) / 4;
    ClawMachine cm[length];
    collect_input(file, cm, length);

    int sum = 0;
    for (int i = 0; i < length; i++) {
        int tokens = calculate_tokens(cm[i]);
        if (tokens != -1) sum += tokens;
    }
    printf("sum: %i\n", sum);
}
