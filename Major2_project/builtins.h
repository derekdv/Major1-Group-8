#ifndef BUILTINS_H
#define BUILTINS_H

int is_builtin(const char *cmd);
void run_builtin(char **args);

#endif