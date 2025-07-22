#ifndef BUILTINS_H
#define BUILTINS_H

int is_builtin(const char *cmd);
void run_builtin(char **args);

// PATH functions
void init_path();
void cleanup_path();
char **get_path_list();
int is_path_cmd(const char *cmd);
void run_path(char **args);

// HISTORY functions
void add_to_history(const char *cmd);
void show_history();
void clear_history();
void execute_history(int index, char *line_buffer);
int is_history_cmd(const char *cmd);
void run_history(char **args, char *line_buffer);

#endif
