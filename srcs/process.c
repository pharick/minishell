/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbelva <cbelva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 12:05:05 by cbelva            #+#    #+#             */
/*   Updated: 2021/04/09 13:38:30 by cbelva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*check_execute(char *line, int *start, t_list *tokens)
{
	t_command	*command;

	while (ft_isspace(line[*start]))
		(*start)++;
	if (!line[*start] || line[*start] == ';' || line[*start] == '|')
	{
		command = (t_command *)malloc(sizeof(t_command));
		if (line[*start] == '|')
			command->execute_type = PIPE;
		else
			command->execute_type = DEFAULT;
		command->tokens = tokens;
		if (line[*start] == ';' || line[*start] == '|')
			(*start)++;
		return (command);
	}
	return (NULL);
}

static int	if_execute(t_list **commands, char *line,
								int *start, t_list **tokens)
{
	t_command	*command;

	command = check_execute(line, start, *tokens);
	if (command)
	{
		if (!(command->tokens))
		{
			free_commands(commands);
			free_command(command);
			print_parser_error(line[*start - 1]);
			return (1);
		}
		ft_lstadd_back(commands, ft_lstnew(command));
		*tokens = NULL;
	}
	return (0);
}

static int	if_redirects(char *line, int *start,
									int *end, t_list **tokens)
{
	if (check_redirects(line, end))
	{
		add_token(line, *start, *end, tokens);
		*start = *end;
		return (1);
	}
	return (0);
}

t_list	*process(char *line)
{
	t_list	*tokens;
	t_list	*commands;
	int		start;
	int		end;

	commands = NULL;
	tokens = NULL;
	start = 0;
	while (line[start])
	{
		while (ft_isspace(line[start]))
			start++;
		if (!line[start])
			return (commands);
		end = start;
		if (if_redirects(line, &start, &end, &tokens))
			continue ;
		token_end(line, &end);
		add_token(line, start, end, &tokens);
		start = end;
		if (if_execute(&commands, line, &start, &tokens))
			return (NULL);
	}
	return (commands);
}
