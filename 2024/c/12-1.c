#include <stdio.h>
#include <stdbool.h>

#define SIZE 140

char map[SIZE][SIZE];
bool explored[SIZE][SIZE] = {};

typedef struct Details {
    int area, perimeter;
} Details;

Details calculate_price(char c, int row, int col) {
    if (row < 0 || col < 0 || row > SIZE || col > SIZE || map[row][col] != c) return (Details){ .perimeter = 1 };
    if (explored[row][col]) return (Details){};

    explored[row][col] = true;

    Details left  = calculate_price(c, row, col-1);
    Details right = calculate_price(c, row, col+1);
    Details up    = calculate_price(c, row-1, col);
    Details down  = calculate_price(c, row+1, col);

    return (Details) {
        .area = 1 + left.area + right.area + up.area + down.area,
        .perimeter = left.perimeter + right.perimeter + up.perimeter + down.perimeter,
    };
}

int main() {
    FILE *file = fopen("2024/inputs/day-12", "r");
    for (int i = 0; i < SIZE; i++) fscanf(file, "%s ", map[i]);

    int price = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (explored[i][j]) continue;
            Details ret = calculate_price(map[i][j], i, j);
            price += ret.area * ret.perimeter;
            printf("A region of %c plants with price %i * %i = %i\n", map[i][j], ret.area, ret.perimeter, ret.area*ret.perimeter);
        }
    }
    printf("price: %i\n", price);
}
