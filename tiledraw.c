#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

const char *CMYK = "cmyk";
const char *FILL[] = {"cyan", "magenta", "yellow", "black"};
const char *STROKE[] = {"black", "black", "black", "gray"};

void draw(char sides[4], FILE *out)
{
    fprintf(out, "<svg width='100' height='100'>\n");
    fprintf(out, "<g transform='translate(50,50)'>\n");
    fprintf(out, "<rect x='-50' y='-50' width='100' height='100' "
            "fill='#bbf'/>\n");
    for (int i = 0; i < 4; i++) {
        double x = cos(i * 3.141592653589793 / 2) * 50;
        double y = sin(i * 3.141592653589793 / 2) * 50;
        int c = strchr(CMYK, tolower(sides[i])) - CMYK;
        const char *fill = FILL[c];
        const char *stroke = STROKE[c];
        if (isupper(sides[i])) {
            fprintf(out, "<circle cx='0' cy='0' r='20' fill='%s' "
                    "stroke='%s' transform='translate(%.0f,%.0f)'/>\n",
                    fill, stroke, x, y);
        } else {
            fprintf(out, "<rect x='-20' y='-20' width='40' height='40' "
                    "fill='%s' stroke='%s' "
                    "transform='translate(%.0f,%.0f)'/>\n",
                    fill, stroke, x, y);
        }
    }
    fprintf(out, "</g>\n</svg>\n");
}

int main()
{
    int n;
    scanf("%d\n", &n);
    for (int i = 0; i < n * n; i++) {
        char line[6];
        fgets(line, sizeof(line), stdin);
        char filename[32];
        snprintf(filename, sizeof(filename), "tile-%c.svg", 'A' + i);
        FILE *out = fopen(filename, "w");
        draw(line, out);
        fclose(out);
    }
    return 0;
}
