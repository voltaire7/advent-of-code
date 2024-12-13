#include <stdio.h>
#include <stdbool.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

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
    int B = MIN(cm.Prize.x/cm.B.x + 1, cm.Prize.y/cm.B.y + 1);

    while (B-- != -1) {
        int diffx = (cm.Prize.x - B * cm.B.x);
        int diffy = (cm.Prize.y - B * cm.B.y);

        bool ifx = diffx % cm.A.x == 0;
        bool ify = diffy % cm.A.y == 0;

        if (ifx && ify) {
            int A = diffx / cm.A.x;
            if (A == diffy / cm.A.y) return 3 * A + B;
        }
    }

    return 0;
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
