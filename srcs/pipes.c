/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbelva <cbelva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:16:12 by cbelva            #+#    #+#             */
/*   Updated: 2021/04/09 13:37:08 by cbelva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*get_pipes_commands(t_list **commands)
{
	t_list		*pipes_commands;
	t_command	*command;

	pipes_commands = NULL;
	command = (*commands)->content;
	while (command->execute_type == PIPE)
	{
		ft_lstadd_back(&pipes_commands, ft_lstnew(command));
		*commands = (*commands)->next;
		if (!(*commands))
		{
			ft_lstadd_back(&pipes_commands, ft_lstnew(NULL));
			return (pipes_commands);
		}
		command = (*commands)->content;
	}
	ft_lstadd_back(&pipes_commands, ft_lstnew(command));
	*commands = (*commands)->next;
	return (pipes_commands);
}

static void	execute_pipe_command(t_command *command)
{
	int	pid;
	int	fd[2];

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		execute_command(command);
		close(fd[1]);
		exit(g_environ.status);
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[1]);
		close(fd[0]);
	}
}

static void	execute_last_command(t_command *command)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		execute_command(command);
		exit(g_environ.status);
	}
	else
	{
		waitpid(pid, &status, 0);
		g_environ.status = WEXITSTATUS(status);
	}
}

void	execute_pipes(t_list **commands)
{
	t_list	*pipes_commands;
	t_list	*node;
	int		status;
	int		fd0;

	fd0 = dup(0);
	pipes_commands = get_pipes_commands(commands);
	node = pipes_commands;
	while (node->next)
	{
		execute_pipe_command(node->content);
		node = node->next;
	}
	if (node->content)
		execute_last_command(node->content);
	dup2(fd0, 0);
	while (wait(&status) > 0)
		;
	ft_lstclear(&pipes_commands, NULL);
}
