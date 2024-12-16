#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 141

char map[SIZE][SIZE];
bool explored[SIZE][SIZE] = {};

typedef enum Direction {
    EAST,
    SOUTH,
    WEST,
    NORTH,
} Direction;

void *arrdup(void *arr, int size, int length) {
    void *new_arr = malloc(size * length);
    if (!new_arr) {
        printf("Failed to duplicate the array.\n");
        exit(1);
    }
    memcpy(new_arr, arr, size * length);
    return new_arr;
}

bool *dup(bool *explored) {
    return arrdup(explored, sizeof(bool), SIZE*SIZE);
}

unsigned find(int x, int y, Direction d, int turn_count, bool *explored) {
    if (map[y][x] == '#' || explored[SIZE * y + x]) {
        free(explored);
        return -1;
    } else if (map[y][x] == 'E') {
        free(explored);
        return turn_count * 1000;
    }
    explored[SIZE * y + x] = true;

    // printf("debug: %i, %i, %i, %c\n", x, y, explored[SIZE * y + x], map[y][x]);
    // for (int i = 0; i < SIZE; i++) {
    //     for (int j = 0; j < SIZE; j++) {
    //         printf("%i", explored[SIZE * i + j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");

    unsigned right = find(x+1, y, EAST,  (d == EAST  ? 0 : 1) + turn_count, dup(explored));
    unsigned down  = find(x, y+1, SOUTH, (d == SOUTH ? 0 : 1) + turn_count, dup(explored));
    unsigned left  = find(x-1, y, WEST,  (d == WEST  ? 0 : 1) + turn_count, dup(explored));
    unsigned up    = find(x, y-1, NORTH, (d == NORTH ? 0 : 1) + turn_count, dup(explored));
    
    unsigned s1 = right < down ? right : down;
    unsigned s2 = left < up ? left : up;
    unsigned smallest = s1 < s2 ? s1 : s2;

    free(explored);
    if (smallest != -1) return 1 + smallest;
    else return -1;
}

int main() {
    FILE *file = fopen("2024/inputs/day-16", "r");
    for (int i = 0; i < SIZE; i++) {
        fscanf(file, "%s ", map[i]);
    }

    int y, x;
    for (y = 0; y < SIZE; y++) {
        for (x = 0; x < SIZE; x++) {
            if (map[y][x] == 'S') goto found;
        }
    }
found:;

    printf("smallest score: %u\n", find(x, y, EAST, 0, dup((bool *) explored)));

    return 0;
    for (int i = 0; i < SIZE; i++) {
        printf("%.*s\n", SIZE, map[i]);
    }
}
