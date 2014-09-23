#include <stdio.h>
#include <string.h>

enum part {
    R0, R1, Y0, Y1, G0, G1, B0, B1
};

enum side {
    NORTH, EAST, SOUTH, WEST
};

struct card {
    const enum part parts[4];
    int id, orient, mark;
};

const char *PARTS[] = {
    "R", "r", "Y", "y", "G", "g", "B", "b"
};

const struct card CARDS[9] = {
    {{R0, Y0, G0, B1}, 0},
    {{R0, G1, B0, G1}, 1},
    {{R1, B0, Y1, G0}, 2},
    {{R1, Y0, B1, Y0}, 3},
    {{R0, G0, B1, Y1}, 4},
    {{R1, B1, Y1, G0}, 5},
    {{R0, Y0, G0, B0}, 6},
    {{R0, G0, B0, Y1}, 7},
    {{R0, B1, G1, Y0}, 8}
};

enum part get(struct card *card, enum side side)
{
    return card->parts[(side + card->orient) % 4];
}

int check(struct card *s[9], int i)
{
    int ix = i % 3, iy = i / 3;
    int west = iy * 3 + (ix - 1);
    int north = (iy - 1) * 3 + ix;
    if (west >= 0)
        if (get(s[west], EAST) / 2 != get(s[i], WEST) / 2 ||
            get(s[west], EAST)     == get(s[i], WEST))
            return 0;
    if (north >= 0)
        if (get(s[north], SOUTH) / 2 != get(s[i], NORTH) / 2 ||
            get(s[north], SOUTH)     == get(s[i], NORTH))
            return 0;
    return 1;
}

void print_solution(struct card *s[9])
{
    for (int y = 0; y < 3; y++) {
        for (int i = 0; i < 3; i++) {
            for (int x = 0; x < 3; x++) {
                int c = y * 3 + x;
                switch (i) {
                case 0:
                    if (s[c])
                        printf(" %s ", PARTS[get(s[c], NORTH)]);
                    else
                        printf(" - ");
                    break;
                case 1:
                    if (s[c])
                        printf("%s%d%s", PARTS[get(s[c], WEST)],
                               s[c]->id,
                               PARTS[get(s[c], EAST)]);
                    else
                        printf("- -");
                    break;
                case 2:
                    if (s[c])
                        printf(" %s ", PARTS[get(s[c], SOUTH)]);
                    else
                        printf(" - ");
                    break;
                }
            }
            printf("\n");
        }
    }
    printf("\n");
}

void solve(struct card cards[9], struct card *solution[9], int n)
{
    if (n == 9) {
        print_solution(solution);
        return;
    }
    if (n >= 6) {
        print_solution(solution);
    }
    for (int c = 0; c < 9; c++) {
        if (!cards[c].mark) {
            cards[c].mark = 1;
            struct card *card = solution[n] = &cards[c];
            for (card->orient = 0; card->orient < 4; card->orient++)
                if (check(solution, n))
                    solve(cards, solution, n + 1);
            solution[n] = NULL;
            cards[c].mark = 0;
        }
    }
}

int main()
{
    struct card cards[9], *solution[9] = {0};
    memcpy(cards, CARDS, sizeof(cards));
    solve(cards, solution, 0);
    return 0;
}
