#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "builtins.h"

#define MAX_LINE 1024
#define MAX_ARGS 64

void parse_input(char *line, char **args) {
    int i = 0;
    args[i] = strtok(line, " \t\n");
    while (args[i] != NULL && i < MAX_ARGS - 1) {
        args[++i] = strtok(NULL, " \t\n");
    }
    args[i] = NULL;
}

int main() {
    char line[MAX_LINE];
    char *args[MAX_ARGS];

    init_path();

    while (1) {
        printf("newshell> ");
        if (fgets(line, sizeof(line), stdin) == NULL) {
            perror("fgets");
            continue;
        }

        add_to_history(line);

        parse_input(line, args);
        if (args[0] == NULL) continue;

        if (strcmp(args[0], "myhistory") == 0 && args[1] && strcmp(args[1], "-e") == 0) {
            run_history(args, line);
            parse_input(line, args);
        }

        if (is_builtin(args[0])) {
            run_builtin(args);
            continue;
        }

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
        } else if (pid == 0) {
            execvp(args[0], args);
            perror("execvp");
            exit(EXIT_FAILURE);
        } else {
            wait(NULL);
        }
    }

    cleanup_path();
    return 0;
}
