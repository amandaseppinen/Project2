#include <stdio.h>
#include <stdlib.h>

void compress(FILE *input) {
    int count = 0;
    char current_char = EOF;
    while (1) {
        int c = fgetc(input);
        if (c == EOF) {
            if (count > 0) {
                fwrite(&count, sizeof(int), 1, stdout);
                fputc(current_char, stdout);
            }
            break;
        }

        if (c == current_char) {
            count++;
        } else {
            if (count > 0) {
                fwrite(&count, sizeof(int), 1, stdout);
                fputc(current_char, stdout);
            }
            current_char = c;
            count = 1;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("my-zip: file1 [file2 ...]\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            printf("my-zip: cannot open file\n");
            return 1;
        }

        compress(file);
        fclose(file);
    }

    return 0;
}
