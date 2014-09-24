#include <stdio.h>
#include <string.h>

#define MAX_SIZE 4

enum side {
    NORTH, EAST, SOUTH, WEST
};

struct tile {
    int sides[4];
    int orient, mark;
};

const char SIDE_NAMES[] = "CcMmYyKk";

struct solution {
    struct tile tiles[MAX_SIZE * MAX_SIZE];
    int solution[MAX_SIZE * MAX_SIZE];
    int size;
};

int tile_get(struct tile *tile, enum side side)
{
    return tile->sides[(side + tile->orient) % 4];
}

int solution_check(struct solution *s, int pos)
{
    int x = pos % s->size;
    int y = pos / s->size;
    struct tile *tile = &s->tiles[s->solution[pos]];
    if (x - 1 >= 0) {
        struct tile *west = &s->tiles[s->solution[y * s->size + (x - 1)]];
        if (tile_get(west, EAST) / 2 != tile_get(tile, WEST) / 2 ||
            tile_get(west, EAST)     == tile_get(tile, WEST))
            return 0;
    }
    if (y - 1 >= 0) {
        struct tile *north = &s->tiles[s->solution[(y - 1) * s->size + x]];
        if (tile_get(north, SOUTH) / 2 != tile_get(tile, NORTH) / 2 ||
            tile_get(north, SOUTH)     == tile_get(tile, NORTH))
            return 0;
    }
    return 1;
}

void solution_print(struct solution *s)
{
    printf("+---------+\n");
    for (int y = 0; y < s->size; y++) {
        for (int i = 0; i < 3; i++) {
            printf("|");
            for (int x = 0; x < s->size; x++) {
                int c = y * s->size + x;
                if (s->solution[c] < 0) {
                    printf("   ");
                } else {
                    struct tile *tile = &s->tiles[s->solution[c]];
                    switch (i) {
                    case 0:
                        printf(" %c ", SIDE_NAMES[tile_get(tile, NORTH)]);
                        break;
                    case 1:
                        printf("%c%x%c", SIDE_NAMES[tile_get(tile, WEST)],
                               s->solution[c],
                               SIDE_NAMES[tile_get(tile, EAST)]);
                        break;
                    case 2:
                        printf(" %c ", SIDE_NAMES[tile_get(tile, SOUTH)]);
                        break;
                    }
                }
            }
            printf("|\n");
        }
    }
    printf("+---------+\n");
}

void solution_init(struct solution *s, FILE *in)
{
    fscanf(in, "%d\n", &s->size);
    for (int i = 0; i < s->size * s->size; i++) {
        struct tile *tile = &s->tiles[i];
        char line[6];
        fgets(line, sizeof(line), in);
        for (int side = 0; side < 4; side++)
            tile->sides[side] = strchr(SIDE_NAMES, line[side]) - SIDE_NAMES;
        tile->orient = 0;
        tile->mark = 0;
        s->solution[i] = -1;
    }
}

void solution_solve(struct solution *s, int n)
{
    int ntiles = s->size * s->size;
    if (n == ntiles) {
        solution_print(s);
    } else {
        for (int t = 0; t < ntiles; t++) {
            if (!s->tiles[t].mark) {
                struct tile *tile = &s->tiles[t];
                tile->mark = 1;
                s->solution[n] = t;
                for (tile->orient = 0; tile->orient < 4; tile->orient++)
                    if (solution_check(s, n))
                        solution_solve(s, n + 1);
                s->solution[n] = -1;
                tile->mark = 0;
            }
        }
    }
}

int main()
{
    struct solution solution;
    solution_init(&solution, stdin);
    solution_solve(&solution, 0);
    return 0;
}
