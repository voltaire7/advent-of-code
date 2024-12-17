#include <stdint.h>
#include <stdio.h>

#define PROGRAM 2412751344550330

typedef enum Instruction {
    ADV, BXL, BST, JNZ, BXC, OUT, BDV, CDV
} Instruction;

typedef enum Register {
    A, B, C
} Register;

uint64_t program[100], registers[3];

uint64_t run(int size, uint64_t a) {
    long r[3] = { a, r[B], r[C] };

    uint64_t result = 0;
    for (int pointer = 0; pointer < size; pointer += 2) {
        uint64_t operand = program[pointer+1];
        uint64_t combo = operand <= 3 ? operand : r[operand-4];

        switch (program[pointer]) {
            case ADV:
                r[A] = r[A] / (1 << combo);
                break;
            case BXL:
                r[B] = r[B] ^ operand;
                break;
            case BST:
                r[B] = combo % 8;
                break;
            case JNZ:
                if (r[A]) pointer = operand - 2;
                break;
            case BXC:
                r[B] = r[B] ^ r[C];
                break;
            case OUT:
                result = result * 10 + (combo % 8);
                break;
            case BDV:
                r[B] = r[A] / (1 << combo);
                break;
            case CDV:
                r[C] = r[A] / (1 << combo);
                break;
        }
    }
    return result;
}

uint64_t search(int size, uint64_t a, uint64_t b) {
    uint64_t mid = (a + b) / 2;
    uint64_t result = run(size, mid);
    printf("mid: %llu, result: %llu\n", mid, result);
    if (result == PROGRAM) {
        return result;
    } else if (result < PROGRAM) {
        return search(size, mid, b);
    } else {
        return search(size, a, mid);
    }
}

int main() {
    FILE *file = fopen("2024/inputs/day-17", "r");

    fscanf(file, "Register A: %llu ", &registers[A]);
    fscanf(file, "Register B: %llu ", &registers[B]);
    fscanf(file, "Register C: %llu ", &registers[C]);

    fscanf(file, "Program: %llu,", program);
    int size = 0;
    for (; !feof(file); size++) {
        fscanf(file, "%llu,", program + size + 1);
    }

    printf("part 1: %llu\n", run(size, registers[A]));
    uint64_t result = search(size, 0, 1000000000000000);
    printf("part 2: %llu\n", result);
}
