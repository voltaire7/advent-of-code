#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 130

char map[SIZE][SIZE];

typedef struct Vector2 {
    int x;
    int y;
} Vector2;

typedef enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT,
} Direction;

char *read_entire_file(char* filename) {
    FILE *file = fopen(filename, "r");
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *str = malloc(fsize + 1);
    fread(str, fsize, 1, file);
    fclose(file);

    str[fsize] = 0;
    return str;
}

void to_map(char *content) {
    for (int i = 0; content[i]; i++) {
        map[i / (SIZE+1)][i % (SIZE+1)] = content[i];
    }
}

Vector2 get_position() {
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            if (map[y][x] == '^') return (Vector2){ x, y };
        }
    }
    fprintf(stderr, "Big error.\n");
    exit(1);
}

bool is_loop(Vector2 position) {
    unsigned long count = 0;
    Direction direction = UP;

    do {
        count++;

        Vector2 old = position;
        switch (direction) {
            case UP:
                position.y--;
                break;
            case RIGHT:
                position.x++;
                break;
            case DOWN:
                position.y++;
                break;
            case LEFT:
                position.x--;
                break;
        }

        if (map[position.y][position.x] == '#' || map[position.y][position.x] == 'O') {
            direction += direction == LEFT ? -LEFT : 1;
            position = old;
        }

        if (count > SIZE * SIZE) return true;
    } while (position.x >= 0 && position.x < SIZE && position.y >= 0 && position.y < SIZE);

    return false;
}

// 1911, not 1915
int main() {
    char *content = read_entire_file("2024/inputs/day-6");
    to_map(content);
    Vector2 position = get_position();

    int count = 0;
    for (int y = 0; y <= SIZE; y++) {
        for (int x = 0; x <= SIZE; x++) {
            if (map[y][x] == '.') map[y][x] = 'O';
            count += is_loop(position);
            if (map[y][x] == 'O') map[y][x] = '.';
        }
    }
    printf("loops: %i\n", count);
}
