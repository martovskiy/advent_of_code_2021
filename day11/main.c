#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h> /* mmap() is defined in this header */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const int WIDTH = 10;
const int HEIGHT = 10;
const int ITERATION = 1000;
const int LAST_BYTE = (WIDTH + 1) * HEIGHT - 1;

void addOne(char *src) {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            src[i * (WIDTH + 1) + j]++;
        }
    }
}

void dotFire(char *src, int i, int j) {
    src[i * (WIDTH + 1) + j] = 48;
    for (int k = -1; k <= 1; ++k) {
        for (int l = -1; l <= 1; ++l) {
            int pos = (i + k) * (WIDTH + 1) + j + l;
            if (pos < 0 || pos >= LAST_BYTE) {
                continue;
            }
            int value = src[pos];
            if (value <= 48 || value == 10) {
                continue;
            }
            src[pos]++;
        }
    }
}

int fire(char *src) {
    int resp = 0;
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (src[i * (WIDTH + 1) + j] > 57) {
                resp++;
                dotFire(src, i, j);
            };
        }
    }
    if (resp == 0) {
        return 0;
    }
    return resp + fire(src);
}

void myPrint(char *src, int t) {
    static char count = 0;
    sleep(0.3);
    printf("\033[%d;%dH", (1), (1));
    printf("\n%d  ----%d\n", count++, t);
    printf("%s", src);
    return;
}

int main(int argc, char *argv[]) {
    int fdin;
    char *src, *fsrc;
    struct stat statbuf;

    /* open the input file */
    if ((fdin = open("../testccbhebge.txt", O_RDONLY)) < 0) {
        printf("can't open %s for reading", argv[1]);
        return 0;
    }
    /* find size of input file */
    if (fstat(fdin, &statbuf) < 0) {
        printf("fstat error");
        return 0;
    }
    src = malloc(statbuf.st_size);
    /* mmap the input file */
    if ((fsrc = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0))
        == (caddr_t) -1) {
        printf("mmap error for input");
        return 0;
    }
    memmove(src, fsrc, statbuf.st_size);
    int part1 = 0;
    myPrint(src, 0);
    for (int h = 0; h < ITERATION; ++h) {
        addOne(src);
        int t = fire(src);
        part1 += t;
        myPrint(src, t);
        if (t == 100) {
            printf("part2: %d", h + 1);
            exit(0);
        }
        if (h == 100) {
            printf("part1: %d", part1);
        }
    }
}
