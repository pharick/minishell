/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbelva <cbelva@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 13:02:57 by cbelva            #+#    #+#             */
/*   Updated: 2021/04/12 10:05:09 by cbelva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_line(char *line)
{
	t_list	*commands;

	commands = process(line);
	if (commands)
		execute(commands);
	free_commands(&commands);
}

static void	exec_one_line(int argc, char **argv)
{
	if (argc == 3 && !ft_strcmp(argv[1], "-c"))
	{
		process_line(argv[2]);
		exit(g_environ.status);
	}
}

static void	add_history(char *line, t_list **history)
{
	if (line[0] != '\0')
		ft_lstadd_front(history, ft_lstnew(line));
	else
		free(line);
}

int	main(int argc, char **argv)
{
	char		*line;
	t_list		*history;
	extern char	**environ;

	history = NULL;
	g_environ.env_lst = get_env_lst(environ);
	set_shlvl();
	exec_one_line(argc, argv);
	set_signals();
	ft_putstr("minishell$ ");
	line = get_line(history);
	while (read(0, NULL, 0) >= 0 && errno != EIO && line)
	{
		add_history(line, &history);
		process_line(line);
		if (read(0, NULL, 0) >= 0)
		{
			ft_putstr("minishell$ ");
			line = get_line(history);
		}
	}
	ft_lstclear(&g_environ.env_lst, (void (*)(void *))(&free_env));
	ft_putendl("exit");
	return (g_environ.status);
}
