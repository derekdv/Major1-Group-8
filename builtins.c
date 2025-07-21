#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "builtins.h"

int is_builtin(const char *cmd) {
    return strcmp(cmd, "cd") == 0 || strcmp(cmd, "exit") == 0;
}

void run_builtin(char **args) {
    if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "cd: missing argument\n");
        } else {
            if (chdir(args[1]) != 0) {
                perror("cd");
            }
        }
    } else if (strcmp(args[0], "exit") == 0) {
        exit(0);
    } else {
        fprintf(stderr, "Unknown builtin command: %s\n", args[0]);
    }
}
