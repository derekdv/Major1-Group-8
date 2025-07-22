#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "builtins.h"

#define MAX_PATHS 64
#define MAX_HISTORY 20

// PATH storage
static char *path_list[MAX_PATHS];
static int path_count = 0;

// HISTORY storage
static char *history[MAX_HISTORY];
static int history_count = 0;
static int history_index = 0;

void init_path() {
    char *env_path = getenv("PATH");
    if (!env_path) return;

    char *copy = strdup(env_path);
    char *token = strtok(copy, ":");
    while (token && path_count < MAX_PATHS) {
        path_list[path_count++] = strdup(token);
        token = strtok(NULL, ":");
    }
    free(copy);
}

void cleanup_path() {
    for (int i = 0; i < path_count; ++i) {
        free(path_list[i]);
    }
    path_count = 0;
}

char **get_path_list() {
    return path_list;
}

int is_path_cmd(const char *cmd) {
    return strcmp(cmd, "path") == 0;
}

void run_path(char **args) {
    if (!args[1]) {
        for (int i = 0; i < path_count; ++i) {
            printf("%s", path_list[i]);
            if (i != path_count - 1) printf(":");
        }
        printf("\n");
    } else if (strcmp(args[1], "+") == 0 && args[2]) {
        if (path_count < MAX_PATHS) {
            path_list[path_count++] = strdup(args[2]);
        }
    } else if (strcmp(args[1], "-") == 0 && args[2]) {
        for (int i = 0; i < path_count; ++i) {
            if (strcmp(path_list[i], args[2]) == 0) {
                free(path_list[i]);
                for (int j = i; j < path_count - 1; ++j) {
                    path_list[j] = path_list[j + 1];
                }
                path_count--;
                break;
            }
        }
    } else {
        fprintf(stderr, "Invalid path command\n");
    }
}

void add_to_history(const char *cmd) {
    if (strlen(cmd) == 0 || strcmp(cmd, "\n") == 0) return;

    if (history[history_index]) {
        free(history[history_index]);
    }
    history[history_index] = strdup(cmd);
    history_index = (history_index + 1) % MAX_HISTORY;
    if (history_count < MAX_HISTORY) history_count++;
}

void show_history() {
    int idx = history_index - history_count;
    if (idx < 0) idx += MAX_HISTORY;
    for (int i = 0; i < history_count; i++) {
        int real_idx = (idx + i) % MAX_HISTORY;
        printf("%d %s", i + 1, history[real_idx]);
    }
}

void clear_history() {
    for (int i = 0; i < MAX_HISTORY; i++) {
        if (history[i]) {
            free(history[i]);
            history[i] = NULL;
        }
    }
    history_count = 0;
    history_index = 0;
}

void execute_history(int index, char *line_buffer) {
    if (index < 1 || index > history_count) {
        fprintf(stderr, "myhistory: invalid index\n");
        return;
    }

    int real_idx = (history_index - history_count + index - 1 + MAX_HISTORY) % MAX_HISTORY;
    strcpy(line_buffer, history[real_idx]);
}

int is_history_cmd(const char *cmd) {
    return strcmp(cmd, "myhistory") == 0;
}

void run_history(char **args, char *line_buffer) {
    if (!args[1]) {
        show_history();
    } else if (strcmp(args[1], "-c") == 0) {
        clear_history();
    } else if (strcmp(args[1], "-e") == 0 && args[2]) {
        int index = atoi(args[2]);
        execute_history(index, line_buffer);
    } else {
        fprintf(stderr, "Invalid myhistory command\n");
    }
}

int is_builtin(const char *cmd) {
    return strcmp(cmd, "cd") == 0 || strcmp(cmd, "exit") == 0 || is_path_cmd(cmd) || is_history_cmd(cmd);
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
        cleanup_path();
        exit(0);
    } else if (strcmp(args[0], "path") == 0) {
        run_path(args);
    } else if (strcmp(args[0], "myhistory") == 0) {
        run_history(args, NULL);
    } else {
        fprintf(stderr, "Unknown builtin command: %s\n", args[0]);
    }
}
