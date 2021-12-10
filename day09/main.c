#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h> /* mmap() is defined in this header */
#include <fcntl.h>
#include <stdio.h>

void err_quit(char *msg) {
    printf(msg);
    return;
}

int get(char *src, int width, int height, int i, int j) {
    if (i < 0 || i >= width) {
        return 99;
    }
    if (j < 0 || j >= height) {
        return 99;
    }
    if (src[j * (width + 1) + i] == 0) {
        return 99;
    }
    return src[j * (width + 1) + i] - 47;
}

int get2(char *src, int width, int height, int i, int j) {
    if (i < 0 || i >= width) {
        return 0;
    }
    if (j < 0 || j >= height) {
        return 0;
    }
    return src[j * (width + 1) + i];
}

int greaterSize(char *src, int width, int height, int i, int j) {
    int res = 1;
    int start = get2(src, width, height, i, j);
    if (start == 57) {
        return 0;
    }

    src[j * (width + 1) + i] = 0;


    int probe = get2(src, width, height, i - 1, j);
    if (probe > start) {
        res = res + greaterSize(src, width, height, i - 1, j);
    }
    probe = get2(src, width, height, i + 1, j);
    if (probe > start) {
        res = res + greaterSize(src, width, height, i + 1, j);
    }
    probe = get2(src, width, height, i, j - 1);
    if (probe > start) {
        res = res + greaterSize(src, width, height, i, j - 1);
    }
    probe = get2(src, width, height, i, j + 1);
    if (probe > start) {
        res = res + greaterSize(src, width, height, i, j + 1);
    }
    return res;
}

int calc(char *src, int width, int height, int i, int j) {
    int res = get(src, width, height, i, j);
    if (get(src, width, height, i - 1, j) <= res) {
        return 0;
    }
    if (get(src, width, height, i + 1, j) <= res) {
        return 0;
    }
    if (get(src, width, height, i, j - 1) <= res) {
        return 0;
    }
    if (get(src, width, height, i, j + 1) <= res) {
        return 0;
    }
    return res;
}

int main(int argc, char *argv[]) {
    int fdin;
    char *src, *fsrc;
    struct stat statbuf;
    int mode = 0x0777;
    int minTop;
    int top[3];

    /* open the input file */
    if ((fdin = open("data.txt", O_RDONLY)) < 0) {
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
    int width = 0;
    while (src[width] != 10) {
        width++;
    }
    int height = statbuf.st_size / width;
    int j, i, h, part1, res, basin;
    top[0] = 0;
    top[1] = 0;
    top[2] = 0;
    minTop = 0;

    for (j = 0; j < height; ++j) {
        for (i = 0; i < width; ++i) {
            res = calc(src, width, height, i, j);
            part1 += res;
            if (res > 0) {
                basin = greaterSize(src, width, height, i, j);
                if (basin > minTop) {
                    for (h = 0; h < 3; ++h) {
                        if (minTop == top[h]) {
                            top[h] = basin;
                            break;
                        }
                    }
                    minTop = 20000;
                    for (h = 0; h < 3; ++h) {
                        if (minTop > top[h]) {
                            minTop = top[h];
                        }
                    }
                }
            }
        }
    }
    int part2 = 1;
    for (h = 0; h < 3; ++h) {
        part2 *= top[h];
    }
    printf("> part1 %d  part2 %d<", part1, part2);
}