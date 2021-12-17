#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
    char *filename = "./data.txt";
    int result = 0;
    FILE *fp;
    int minx, miny, maxx, maxy, high = 0, tmp;
    int x, y, currx, curry, vx, vy, startx, starty;
    if ((fp = fopen(filename, "r")) == NULL) {
        printf("error opening file %s\n", filename);
        return 1;
    }
    fscanf(fp, "target area: x=%d..%d, y=%d..%d", &minx, &maxx, &miny, &maxy);
    for (x = 0; x < 1000; x++) {
        for (y = -1000; y < 1000; y++) {
            startx = x;
            starty = y;
            vx = x;
            vy = y;
            currx = curry = tmp = 0;
            while ((currx <= maxx) && (curry > miny)) {
                currx += vx;
                curry += vy;
                if (vx)
                    if (abs(vx) == vx) { vx--; }
                    else { vx++; }
                vy--;
                if (!vy)
                    tmp = curry;
                if ((currx >= minx) && (curry <= maxy) && (currx <= maxx) && (curry >= miny)) {
                    result++;
                    if (tmp > high) {
                        printf("x:y  %d:%d high %d new %d   start x:y %d:%d\n", x, y, high, tmp, startx, starty);
                        high = tmp;
                    }
                    break;
                }
            }
        }
    }
    printf("part1 %d \npart2 %d\n", high, result);
    return 0;
}