#include <stdio.h>
#include <stdbool.h>

#define SIZE 140

char map[SIZE][SIZE];
bool explored[SIZE][SIZE] = {};

typedef struct Details {
    int area, perimeter;
} Details;

bool debug = false;

int count_sides(char c, int row, int col) {
    bool top_left     = row-1 <  0    || col-1 <  0    || map[row-1][col-1] != c;
    bool top_right    = row-1 <  0    || col+1 >= SIZE || map[row-1][col+1] != c;
    bool bottom_left  = row+1 >= SIZE || col-1 <  0    || map[row+1][col-1] != c;
    bool bottom_right = row+1 >= SIZE || col+1 >= SIZE || map[row+1][col+1] != c;
    if (!(top_left || top_right || bottom_left || bottom_right)) return 0;

    if (debug) {
        printf("[%c,%c,%c]\n", row-1 < 0 || col-1 < 0 ? ' ' : map[row-1][col-1], row-1 < 0 ? ' ' : map[row-1][col], row-1 < 0 || col+1 >= SIZE ? ' ' : map[row-1][col+1]);
        printf("[%c,%c,%c]\n", col-1 < 0 ? ' ' : map[row  ][col-1], map[row  ][col], col+1 >= SIZE ? ' ' : map[row  ][col+1]);
        printf("[%c,%c,%c]\n", row+1 >= SIZE || col-1 < 0 ? ' ' : map[row+1][col-1], row+1 >= SIZE ? ' ' : map[row+1][col], row+1 >= SIZE || col+1 >= SIZE ? ' ' : map[row+1][col+1]);
    }

    int count = 0;

    bool top_ex  = row-1 < 0  || map[row-1][col] != c;
    bool left_ex = col-1 < 0  || map[row][col-1] != c;
    bool top_in  = row-1 >= 0 && map[row-1][col] == c;
    bool left_in = col-1 >= 0 && map[row][col-1] == c;
    if (top_ex && left_ex || top_in && left_in && top_left) count++;

    bool right_ex = col+1 >= SIZE || map[row][col+1] != c;
    bool right_in = col+1 <  SIZE && map[row][col+1] == c;
    if (top_ex && right_ex || top_in && right_in && top_right) count++;

    bool bottom_ex = row+1 >= SIZE || map[row+1][col] != c;
    bool bottom_in = row+1 <  SIZE && map[row+1][col] == c;
    if (bottom_ex && left_ex || bottom_in && left_in && bottom_left) count++;

    if (bottom_ex && right_ex || bottom_in && right_in && bottom_right) count++;

    if (debug) printf("count: %i\n\n", count);

    return count;
}

Details calculate_price(char c, int row, int col) {
    if (row < 0 || col < 0 || row >= SIZE || col >= SIZE || map[row][col] != c || explored[row][col]) return (Details){};

    explored[row][col] = true;

    // if (row == 111 && col == 112) collect = true;

    Details left  = calculate_price(c, row, col-1);
    Details right = calculate_price(c, row, col+1);
    Details up    = calculate_price(c, row-1, col);
    Details down  = calculate_price(c, row+1, col);

    int perimeter = count_sides(c, row, col);

    return (Details) {
        .area = 1 + left.area + right.area + up.area + down.area,
        .perimeter = perimeter + left.perimeter + right.perimeter + up.perimeter + down.perimeter,
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
            // if (ret.area == 97 && ret.perimeter == 47) {
            //     printf("%i, %i\n", i, j);
            //     return 0;
            // }
            // if (ret.area == 205 && ret.perimeter == 87) {
            //     printf("%i, %i\n", i, j);
            //     return 0;
            // }
        }
    }
    printf("price: %i\n", price);
}
