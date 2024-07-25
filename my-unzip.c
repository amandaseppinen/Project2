#include <stdio.h>
#include <stdlib.h>

void decompress(FILE *input) {
    while (1) {
        int count;
        if (fread(&count, sizeof(int), 1, input) != 1) {
            break;
        }
        int c = fgetc(input);
        if (c == EOF) {
            break;
        }
        for (int i = 0; i < count; i++) {
            fputc(c, stdout);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("my-unzip: file1 [file2 ...]\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            printf("my-unzip: cannot open file\n");
            return 1;
        }

        decompress(file);
        fclose(file);
    }

    return 0;
}
