#include <stdio.h>
#include <string.h>

#define SIZE 57
#define MAX 100

char map[SIZE][SIZE];

typedef struct Vector2 {
    int x, y;
} Vector2;

int iter(char current, Vector2 position, Vector2 found[MAX]) {
    static int count = 0;
    if (current == '0') count = 0;
    if (current == '9') {
        found[count] = position;
        count++;
        return count;
    }

    char next = current + 1;
    if (position.x-1 >= 0   && map[position.y][position.x-1] == next) iter(next, (Vector2){position.x-1, position.y}, found);
    if (position.x+1 < SIZE && map[position.y][position.x+1] == next) iter(next, (Vector2){position.x+1, position.y}, found);
    if (position.y-1 >= 0   && map[position.y-1][position.x] == next) iter(next, (Vector2){position.x, position.y-1}, found);
    if (position.y+1 < SIZE && map[position.y+1][position.x] == next) iter(next, (Vector2){position.x, position.y+1}, found);
    return count;
}

int count(int x, int y) {
    Vector2 found[MAX];
    memset(found, -1, sizeof(Vector2) * MAX);
    int count = iter('0', (Vector2){x, y}, found);
    int true_count = 0;
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (found[i].x == found[j].x && found[i].y == found[j].y) goto duplicate;
        }
        true_count++;
    duplicate:;
    }
    return true_count;
}

int main() {
    FILE *file = fopen("2024/inputs/day-10", "r");
    for (int y = 0; y < SIZE; y++) {
        fscanf(file, "%s ", map[y]);
    }

    int sum = 0;
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            if (map[y][x] == '0') sum += count(x, y);
        }
    }
    printf("sum: %i\n", sum);

    return 0;
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            printf("%c", map[y][x]);
        }
        printf("\n");
    }
}
