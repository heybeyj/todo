#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TODO "/.todo"
#define READ_BLOCK 1024

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

    int opt, print, del;
    del = print = 0;
    while ((opt = getopt(argc, argv, "ld")) != -1) {
        switch (opt) {
            case 'l':
                print = 1;
                break;
            case 'd':
                del = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-l -d]\n", argv[0]);
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
    if (del) {
        fclose(todo);
        todo = fopen(filename, "w");
        printf("[+] Cleared todo list\n");
    }
    fclose(todo);
    exit(EXIT_SUCCESS);
}
