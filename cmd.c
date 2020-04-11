#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    bool isCaseInsensitive = false;
    int opt;
    enum { CHARACTER_MODE, WORD_MODE, LINE_MODE } mode = CHARACTER_MODE;

    while ((opt = getopt(argc, argv, "ilw")) != -1) {
        switch (opt) {
        case 'i': isCaseInsensitive = true; break;
        case 'l': mode = LINE_MODE;
                    printf("l yooooho"); break;
        case 'w': mode = WORD_MODE; break;
        default:
            fprintf(stderr, "Usage: %s [-ilw] [file...]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

}