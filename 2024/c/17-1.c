#include <stdio.h>

typedef enum Instruction {
    ADV, BXL, BST, JNZ, BXC, OUT, BDV, CDV
} Instruction;

typedef enum Register {
    A, B, C
} Register;

long program[100], reg[3];

// might need to check for invalid combo
void run(int size) {
    for (int pointer = 0; pointer < size; pointer += 2) {
        long operand = program[pointer+1];
        long combo = operand <= 3 ? operand : reg[operand-4];

        switch (program[pointer]) {
            case ADV: reg[A] = reg[A] / (1 << combo);
                break;
            case BXL:
                reg[B] = reg[B] ^ operand;
                break;
            case BST:
                reg[B] = combo % 8;
                break;
            case JNZ:
                if (reg[A]) pointer = operand - 2;
                break;
            case BXC:
                reg[B] = reg[B] ^ reg[C];
                break;
            case OUT:
                printf("%li,", combo % 8);
                break;
            case BDV:
                reg[B] = reg[A] / (1 << combo);
                break;
            case CDV:
                reg[C] = reg[A] / (1 << combo);
                break;
        }
    }
}

int main() {
    FILE *file = fopen("2024/inputs/day-17", "r");

    fscanf(file, "Register A: %li ", &reg[A]);
    fscanf(file, "Register B: %li ", &reg[B]);
    fscanf(file, "Register C: %li ", &reg[C]);

    fscanf(file, "Program: %li,", program);
    int size = 0;
    for (; !feof(file); size++) {
        fscanf(file, "%li,", program + size + 1);
    }

    run(size);
    printf("\b \n");
}
