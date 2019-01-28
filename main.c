#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TODO "/.todo"
#define READ_BLOCK 1024

void help(const char *prog_name);

int main(int argc, char **argv)
{
    const char *homedir = getenv("HOME");
    const int filename_len = strlen(homedir) + strlen(TODO);
    char filename[filename_len + 1];
    sprintf(filename, "%s%s", homedir, TODO);
    FILE *todo = fopen(filename, "a+");

    if (argc < 2) {
        char c;
        while (1) {
            c = getchar();
            if (c == '\n') {
                fclose(todo);
                exit(EXIT_SUCCESS);
            } else {
                fputc(c, todo);
            }
            while ((c = getchar()) != '\n') {
                fputc(c, todo);
            }
            fputc('\n', todo);
        }
    }

    int opt, print;
    while ((opt = getopt(argc, argv, "hl")) != -1) {
        switch (opt) {
            case 'h':
                help(argv[0]);
                exit(EXIT_SUCCESS);
            case 'l':
                print = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-l]\n", argv[0]);
                fclose(todo);
                exit(EXIT_FAILURE);
        }
    }

    if (print) {
        int bytes_read = 1;
        char contents[READ_BLOCK];
        while (bytes_read) {
            bytes_read = fread(contents, 1, READ_BLOCK, todo);
            if (feof(todo)) {
                contents[bytes_read] = '\0';
            }
            printf("%s", contents);
        }
    }
    fclose(todo);
    exit(EXIT_SUCCESS);
}

void help(const char *prog_name)
{
    const char *message =
        "A todo list command line application\n"
        "\n"
        "Usage: %s [OPTIONS]\n"
        "With no options, it will read from stdin until a blank line is "
        "provided and append\nthe input to the todo list (~/.todo). Each line "
        "is a single item on the list.\n"
        "\n"
        "OPTIONS:\n"
        "  -h\n      show this message and exit\n"
        "  -l\n      print the current todo list\n";
    printf(message, prog_name);
}
