/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbelva <cbelva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 11:57:22 by cbelva            #+#    #+#             */
/*   Updated: 2021/04/12 11:13:09 by cbelva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <term.h>
# include "libft.h"

# define MAX_PATH 4096

enum			e_execute_types
{
	DEFAULT,
	PIPE
};

enum			e_statuses
{
	COMMAND_NOT_FOUND = 127,
	COMMAND_TERMINATED = 130,
	COMMAND_QUIT = 131
};

enum			e_history
{
	BACKWARD,
	FORWARD,
	RESET
};

typedef struct s_env
{
	char	*key;
	char	*value;
}				t_env;

typedef struct s_command
{
	t_list	*tokens;
	int		execute_type;
}				t_command;

typedef struct s_redirects
{
	int			read_fd;
	int			write_fd;
}				t_redirects;

typedef struct s_environ
{
	t_list	*env_lst;
	int		status;
}				t_environ;

t_environ	g_environ;

t_list	*process(char *line);
void	token_end(char *line, int *end);
void	add_token(char *line, int start, int end, t_list **tokens);
int		check_redirects(char *line, int *end);

void	process_tokens(t_list *tokens);
int		process_variables(char **token, int *i, int *j, int squote);
char	*get_prefix(char *file);
void	execute(t_list *commands);
void	execute_command(t_command *command);

void	execute_pipes(t_list **commands);

int		process_redirects(t_list *tokens, t_redirects *redirects);
void	connect_redirects(t_redirects *redirects);

t_list	*get_env_lst(char **environ);
t_env	*parse_var(char *var);
char	**env_to_array(t_list *env_lst);
void	free_env(t_env *env);
void	print_env(t_env *env, int fd);
char	*get_var(char *key);
void	set_var(char *key, char *value);
char	*path_prefix(char *command);
void	set_shlvl(void);

int		unset_cmp(t_env *data, char *data_ref);
int		env(char **argv, t_redirects *redirects);
int		pwd(char **argv, t_redirects *redirects);
int		export_builtin(char **argv, t_redirects *redirects);
int		unset(char **argv);
int		echo_builtin(char **argv, t_redirects *redirects);
int		cd(char **argv);
int		get_fd(t_redirects *redirects);
int		exit_builtin(char **argv);

int		print_error(void);
void	print_parser_error(char token);
void	print_export_error(char *token, char *command);
void	print_command_error(char *command);
void	print_redirect_error(char *path, int status);

void	free_commands(t_list **commands);
void	free_command(t_command *command);

void	set_signals(void);
void	reset_signals(void);
void	print_termsig(int status);

void	init_terminal(struct termios *term);
void	reset_terminal(struct termios *term);
int		is_russian(char *str);

char	*get_line(t_list *history);
void	line_insert(char *str, char *buff, int i, int ret);
void	line_remove(char *str, int i);
int		tkey_left(size_t *i);
int		tkey_right(size_t *i, char *str);
int		tkey_backspace(size_t *i, char *str);
int		tkey_history(t_list *history, int mode, size_t *i, char *str);
void	check_sigint(char *str, size_t *i);

#endif
