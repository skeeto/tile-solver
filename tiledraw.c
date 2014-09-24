#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

const char *CMYK = "cmyk";
const char *FILL[] = {"cyan", "magenta", "yellow", "black"};
const char *STROKE[] = {"black", "black", "black", "gray"};

void draw(char sides[4], FILE *out)
{
    fprintf(out, "<svg width='200' height='200'>\n");
    fprintf(out, "<g transform='translate(100,100) rotate(-90)'>\n");
    fprintf(out, "<rect x='-100' y='-100' width='200' height='200' "
            "fill='#bbf'/>\n");
    for (int i = 0; i < 4; i++) {
        double x = cos(i * 3.141592653589793 / 2) * 100;
        double y = sin(i * 3.141592653589793 / 2) * 100;
        int c = strchr(CMYK, tolower(sides[i])) - CMYK;
        const char *fill = FILL[c];
        const char *stroke = STROKE[c];
        if (isupper(sides[i])) {
            fprintf(out, "<circle cx='0' cy='0' r='40' fill='%s' "
                    "stroke='%s' transform='translate(%.0f,%.0f)'/>\n",
                    fill, stroke, x, y);
        } else {
            fprintf(out, "<rect x='-40' y='-40' width='80' height='80' "
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
