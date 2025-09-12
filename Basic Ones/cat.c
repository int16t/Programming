#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    int c;

    if (argc == 1) {
        while ((c = getchar()) != EOF) {
            putchar(c);
        }
    } else {
        for (int i = 1; i < argc; i++) {
            fp = fopen(argv[i], "r");
            if (fp == NULL) {
                perror(argv[i]);
                continue;
            }
            while ((c = fgetc(fp)) != EOF) {
                putchar(c);
            }

            fclose(fp);
        }
    }

    return 0;
}
