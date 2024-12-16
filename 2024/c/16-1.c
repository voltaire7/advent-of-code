#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 141
#define MAX_NODES (SIZE * SIZE)
#define TURN_COST 1000

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point pos;
    float g, h, f;
    Point parent;
    int in_open, in_closed;
    int dir; // Direction: 0=none, 1=up, 2=right, 3=down, 4=left
} Node;

char grid[SIZE][SIZE];
Node nodes[SIZE][SIZE];

float heuristic(Point a, Point b) {
    return abs(a.x - b.x) + abs(a.y - b.y); // Manhattan distance
}

void init_grid() {
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            nodes[y][x] = (Node){
                .pos = {x, y},
                .g = INFINITY,
                .h = 0,
                .f = INFINITY,
                .parent = {-1, -1},
                .in_open = 0,
                .in_closed = 0,
                .dir = 0,
            };
        }
    }
}

Node *find_lowest_f(Node *open_list[], int open_count) {
    Node *lowest = open_list[0];
    for (int i = 1; i < open_count; i++) {
        if (open_list[i]->f < lowest->f)
            lowest = open_list[i];
    }
    return lowest;
}

int is_valid(int x, int y) {
    return x >= 0 && y >= 0 && x < SIZE && y < SIZE;
}

void add_to_open(Node *node, Node *open_list[], int *open_count) {
    node->in_open = 1;
    open_list[(*open_count)++] = node;
}

void remove_from_open(Node *node, Node *open_list[], int *open_count) {
    node->in_open = 0;
    for (int i = 0; i < *open_count; i++) {
        if (open_list[i] == node) {
            open_list[i] = open_list[--(*open_count)];
            return;
        }
    }
}

void reconstruct_path(Node *node) {
    printf("Path: ");
    while (node->parent.x != -1) {
        printf("(%d, %d) <- ", node->pos.x, node->pos.y);
        node = &nodes[node->parent.y][node->parent.x];
    }
    printf("\n");
}

int get_direction(Point from, Point to) {
    if (to.y < from.y) return 1; // Up
    if (to.x > from.x) return 2; // Right
    if (to.y > from.y) return 3; // Down
    if (to.x < from.x) return 4; // Left
    return 0; // None
}

void a_star(Point start, Point goal) {
    init_grid();

    Node *open_list[MAX_NODES];
    int open_count = 0;

    Node *start_node = &nodes[start.y][start.x];
    start_node->g = 0;
    start_node->h = heuristic(start, goal);
    start_node->f = start_node->g + start_node->h;
    start_node->dir = 2;
    add_to_open(start_node, open_list, &open_count);

    while (open_count > 0) {
        Node *current = find_lowest_f(open_list, open_count);

        if (current->pos.x == goal.x && current->pos.y == goal.y) {
            reconstruct_path(current);
            printf("Total Score: %.0f\n", current->g); // Print the score (g contains total cost).
            return;
        }

        remove_from_open(current, open_list, &open_count);
        current->in_closed = 1;

        int neighbors[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for (int i = 0; i < 4; i++) {
            int nx = current->pos.x + neighbors[i][0];
            int ny = current->pos.y + neighbors[i][1];

            if (!is_valid(nx, ny) || grid[ny][nx] == '#')
                continue;

            Node *neighbor = &nodes[ny][nx];
            if (neighbor->in_closed)
                continue;

            int new_dir = get_direction(current->pos, neighbor->pos);
            float turn_cost = (current->dir && current->dir != new_dir) ? TURN_COST : 0;

            float tentative_g = current->g + 1 + turn_cost; // 1 for step, TURN_COST for turns
            if (!neighbor->in_open || tentative_g < neighbor->g) {
                neighbor->parent = current->pos;
                neighbor->g = tentative_g;
                neighbor->h = heuristic(neighbor->pos, goal);
                neighbor->f = neighbor->g + neighbor->h;
                neighbor->dir = new_dir;

                if (!neighbor->in_open) {
                    add_to_open(neighbor, open_list, &open_count);
                }
            }
        }
    }

    printf("No path found!\n");
}

int main() {
    FILE *file = fopen("2024/inputs/day-16", "r");
    for (int i = 0; i < SIZE; i++) {
        fscanf(file, "%s ", grid[i]);
    }

    Point start, goal;
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            if (grid[y][x] == 'S') start = (Point){ x, y };
            else if (grid[y][x] == 'E') goal = (Point){ x, y };
        }
    }
    a_star(start, goal);
}
