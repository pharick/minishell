/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbelva <cbelva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 13:06:47 by cbelva            #+#    #+#             */
/*   Updated: 2021/04/09 13:30:17 by cbelva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

static int	execute_binary(char *file, char **argv, t_redirects *redirects)
{
	char	**environ;
	int		status;
	char	*pref_file;
	int		pid;

	pref_file = get_prefix(file);
	if (!pref_file)
		return (COMMAND_NOT_FOUND);
	environ = env_to_array(g_environ.env_lst);
	pid = fork();
	if (pid == 0)
	{
		connect_redirects(redirects);
		execve(pref_file, argv, environ);
		exit(1);
	}
	else
	{
		reset_signals();
		waitpid(pid, &status, 0);
		set_signals();
		ft_free_tokens(environ);
		free(pref_file);
	}
	return (get_status(status));
}

static int	choose_execute(char *command, char **argv, t_redirects *redirects)
{
	if (!ft_strcmp(command, "env"))
		return (env(argv, redirects));
	if (!ft_strcmp(command, "export"))
		return (export_builtin(argv, redirects));
	if (!ft_strcmp(command, "unset"))
		return (unset(argv));
	if (!ft_strcmp(command, "pwd"))
		return (pwd(argv, redirects));
	if (!ft_strcmp(command, "echo"))
		return (echo_builtin(argv, redirects));
	if (!ft_strcmp(command, "cd"))
		return (cd(argv));
	if (!ft_strcmp(command, "exit"))
		return (exit_builtin(argv));
	else
		return (execute_binary(command, argv, redirects));
}

void	execute_command(t_command *command)
{
	char			*com;
	char			**argv;
	t_redirects		redirects;

	if (!(command->tokens))
		return ;
	process_tokens(command->tokens);
	if (process_redirects(command->tokens, &redirects))
		return ;
	com = (command->tokens)->content;
	argv = (char **)ft_lst_to_array(command->tokens);
	set_var("_", ft_lstlast(command->tokens)->content);
	errno = 0;
	g_environ.status = choose_execute(com, argv, &redirects);
	if (g_environ.status == COMMAND_NOT_FOUND)
		print_command_error(com);
	print_error();
	print_termsig(g_environ.status);
	free(argv);
}

void	execute(t_list *commands)
{
	t_list		*node;
	t_command	*command;

	node = commands;
	while (node)
	{
		command = node->content;
		if (command->execute_type == PIPE)
			execute_pipes(&node);
		if (!node)
			break ;
		command = node->content;
		execute_command(command);
		node = node->next;
	}
}
