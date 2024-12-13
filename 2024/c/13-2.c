#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct Vector2 {
    uint64_t x, y;
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
        fscanf(file, "Button A: X+%llu, Y+%llu ", &cm[i].A.x, &cm[i].A.y);
        fscanf(file, "Button B: X+%llu, Y+%llu ", &cm[i].B.x, &cm[i].B.y);
        fscanf(file, "Prize: X=%llu, Y=%llu ", &cm[i].Prize.x, &cm[i].Prize.y);
        // cm[i].Prize.x += 10000000000000, cm[i].Prize.y += 10000000000000;
    }
}

uint64_t calculate_tokens(ClawMachine cm) {
    uint64_t B = MIN(cm.Prize.x/cm.B.x + 1, cm.Prize.y/cm.B.y + 1);

    while (B-- != -1) {
        uint64_t diffx = (cm.Prize.x - B * cm.B.x);
        uint64_t diffy = (cm.Prize.y - B * cm.B.y);

        bool ifx = diffx % cm.A.x == 0;
        bool ify = diffy % cm.A.y == 0;

        if (ifx && ify) {
            uint64_t A = diffx / cm.A.x;
            if (A == diffy / cm.A.y) {
                return 3 * A + B;
            }
        }
    }

    return 0;
}

int main() {
    FILE *file = fopen("2024/inputs/day-13", "r");
    int lines = count_lines(file), length = (lines+1) / 4;
    ClawMachine cm[length];
    collect_input(file, cm, length);

    uint64_t sum = 0;
    for (int i = 0; i < length; i++) {
        uint64_t tokens = calculate_tokens(cm[i]);
        if (tokens) sum += tokens;
    }
    printf("sum: %llu\n", sum);

    return 0;
    for (int i = 0; i < length; i++) {
        printf("Button A: X+%llu, Y+%llu\n", cm[i].A.x, cm[i].A.y);
        printf("Button B: X+%llu, Y+%llu\n", cm[i].B.x, cm[i].B.y);
        printf("Prize: X=%llu, Y=%llu\n\n", cm[i].Prize.x, cm[i].Prize.y);
    }
}
