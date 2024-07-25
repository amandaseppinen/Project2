#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("my-grep: searchterm [file ...]\n");
        return 1;
    }

    char *search_term = argv[1];

    for (int i = 2; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            printf("my-grep: cannot open file\n");
            return 1;
        }

        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            if (strstr(buffer, search_term) != NULL) {
                printf("%s", buffer);
            }
        }

        fclose(file);
    }

    if (argc == 2) { // No files specified
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (strstr(buffer, search_term) != NULL) {
                printf("%s", buffer);
            }
        }
    }

    return 0;
}
