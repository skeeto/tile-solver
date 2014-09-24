#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

void shuffle(char *a, size_t size)
{
    for (size_t i = size - 1; i > 0; i--) {
        int n = rand() % size;
        char tmp = a[i];
        a[i] = a[n];
        a[n] = tmp;
    }
}

int main(int argc, char **argv)
{
    int n = argc < 2 ? 3 : atoi(argv[1]);
    srand(argc < 3 ? time(NULL) : atoi(argv[2]));
    char sides[n * n * 4];
    char *colors = "cmyk";
    for (int color = 0; color < 4; color++) {
        int split = (rand() % ((n * n) / 2)) + (n * n) / 3;
        for (int i = 0; i < n * n; i++) {
            char c = i < split ? colors[color] : toupper(colors[color]);
            sides[n * n * color + i] = c;
        }
    }
    shuffle(sides, sizeof(sides));
    printf("%d\n", n);
    for (int row = 0; row < n * n; row++) {
        fwrite(sides + (row * 4), 4, 1, stdout);
        putchar('\n');
    }
}
