#ifndef MAIN_H
#define MAIN_H

#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

extern char **environ;

#define RESET_BUF -1
#define MAX_BUFFER_SIZE 1024
#define CUSTOM_UNSIGNED 2
#define CUSTOM_LOWERCASE 1
#define BUFFER_READ 1024
#define FILE_FOR_HIST ".simple_shell_history"
#define HIST_MAXIMUM 4096

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/**
 * struct num_str - linked list
 * @num: number
 * @str: string
 * @next: next node
 */

typedef struct num_str
{
	int num;
	char *str;
	struct num_str *next;
} list_struct;

/**
 * struct program_info - pseudo-arguements
 * @arg: a string from getline with arg
 * @argv: arr of str generated from arg
 * @path: path
 * @argc: arg count
 * @line_count: the error count
 * @err_num: error code
 * @linecount_flag: if ...
 * @fname: program filename
 * @env: linked list 
 * @environ: custom modified copy env
 * @history: history
 * @alias: alias
 * @env_changed: on if environ was changed
 * @status: the rturn status
 * @cmd_buf: adr of ptr to cmd
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: fd 
 * @histcount: history
 */

 typedef struct program_info
{
            	char *arg;
            	char **argv;
            	char *path;
            	int argc;
            	unsigned int line_count;
            	int err_num;
            	int linecount_flag;
            	char *fname;
            	list_struct *env;
            	list_struct *history;
            	list_struct *alias;
            	char **environ;
            	int env_changed;
            	int status;
            	char **cmd_buf;
            	int cmd_buf_type;
            	int readfd;
            	int histcount;
} info_struct;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - builtin string
 * @type: the builtin cmd
 * @func: function
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_struct *);
} builtin_table;

/*get_info2.c*/
void free2(char **p);
int free3(void **ptr);

/*printers.c*/
void error_puts(char *string);
int error_putchar(char charac);
/*histories.c*/
int history_print(info_struct *information);
int construct_history(info_struct *information, char *buffer, int lcount);
int history_renumber(info_struct *information);
int history_write(info_struct *information);
char *fetch_history(info_struct *information);
/*loops.c*/
int hash_batch(info_struct *information, char **agv);

/*string1.c*/
char *custom_strcat(char *dest, char *src);
int custom_strlen(char *str);
int custom_strcmp(char *str1, char *str2);
char *needle_check(const char *search_string, const char *sub_str);
/*string2.c*/
char *custom_strcpy(char *d, char *s);
int custom_putchar(char c);
void custom_puts(char *s);
char *custom_strdup(const char *s);
char **lists_str(list_struct *head);
/*string3.c*/
char *custom_strncat(char *d, char *s, int bytes);
char *custom_strchr(char *str, char c);
char *custom_strncpy(char *d, char *s, int bytes);
int check_delim(char c, char *delim);

/*error_printer.c*/
char *conv_num(long int num, int b, int f);
int error_atoi(char *str);
void error_print(info_struct *information, char *str);
int _print(int msg, int filedesc);
void hush_comments(char *buffer);
int error_putsfd(char *str, int filedesc);

/*custom_getline.c*/
ssize_t custom_getline(info_struct *information, char **ptr, size_t *size);
void signal_helper(int sig);
ssize_t buffer_inbut(info_struct *information, char **buffer, size_t *length);
ssize_t obtain_input(info_struct *information);
ssize_t buffer_reader(info_struct *information, char *buffer, size_t *size);

/*get_info*/
void info_start(info_struct *information, char **agv);
void reset_info(info_struct *information);
void free1(info_struct *information, int entire);

/*interactive_mode.c*/
int interactive_mode(info_struct *information);
int custom_atoi(char *str);
int custom_isalpha(int c);

/*custom_strtok.c*/
char **custom_strtow(char *str, char *delim);
char **custom_strtow2(char *str, char delim);

/*utils.c*/
int search_chain(info_struct *information, char *buffer, size_t *pos);
void get_chain(info_struct *information, char *buffer, size_t *pos, size_t i, size_t length);
int alias_exchange(info_struct *information);
int vars_exchange(info_struct *information);
int string_exchange(char **old, char *new);

/*env_vars.c*/
int custom_env_list(info_struct *information);
int custom_myunsetenv(info_struct *information);
int custom_mysetenv(info_struct *information);
char *get_environ(info_struct *information, const char *name);
int custom_env(info_struct *information);
int build_environ(info_struct *info);

int custom_my_env(info_struct *information);
int custom_my_setenv(info_struct *information);
int custom_my_unsetenv(info_struct *information);

/*new9_1.c*/
 int custom_setenv(info_struct *inf, char *varr, char *val);
 int custom_unsetenv(info_struct *inf, char *varr);
 char **obtain_environ(info_struct *inf);
 int custom_unsetenv(info_struct *inf, char *varr);
 int custom_setenv(info_struct *inf, char *varr, char *val);
 char *mem_init(char *st, char ba, unsigned int n);
 char *custom_start(const char *h, const char *n);
 ssize_t get_node_with_index(list_struct *head, list_struct *nd);
 list_struct *list_prefix(list_struct *head, char *pref, char c);
 size_t _prints_lists(const list_struct *n);
 char **convert_list_to_strings(list_struct *head);
 size_t l_length(const list_struct *n);
 void free_text_list(list_struct **head_pointer);
 int delete_n_by_index(list_struct **head, unsigned int index);
 size_t print_text_list(const list_struct *n);
 list_struct *append_list_node(list_struct **head, const char *str, int num);
 list_struct *add_list_node(list_struct **head, const char *str, int num);

 int unsetCommandAlias(info_struct *commandInfo, char *str);
 int setCommandAlias(info_struct *commandInfo, char *str);
 int printCommandAlias(info_struct *nd);
char *custom_find_path(info_struct *inf, char *pts, char *cmd);
char *custom_dup_chars(char *pts, int strt, int stp);
int custom_is_cmd(info_struct *inf, char *adr);
void custom_fork_cmd(info_struct *info);
void search_command(info_struct *info);
int search_builtin_cmd(info_struct *info);
/*int hash_batch(info_struct *info, char **av);*/


int custom_myhelp(info_struct *info);
int custom_mycd(info_struct *info);
int custom_my_exit(info_struct *info);

/*new2.c*/
int custom_unset_alias(info_struct *commandInfo, char *text);
int custom_myalias(info_struct *commandInfo);
int custom_print_alias(list_struct *node);
int custom_set_alias(info_struct *commandInfo, char *text);
int custom_my_history(info_struct *commandInfo);
list_struct *node_with(list_struct *nd, char *pf, char c);

void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int error_putfd(char ch, int fd);
#endif
