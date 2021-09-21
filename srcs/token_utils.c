/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbelva <cbelva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:51:05 by cbelva            #+#    #+#             */
/*   Updated: 2021/04/09 13:41:32 by cbelva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_quotes(char *line, int *end)
{
	char	quote;
	int		escape;

	escape = 0;
	quote = line[*end];
	(*end)++;
	while (line[*end])
	{
		if (line[*end] == quote && !escape)
			break ;
		escape = line[*end] == '\\' && quote == '\"';
		(*end)++;
	}
}

void	token_end(char *line, int *end)
{
	while (line[*end] && !ft_isspace(line[*end])
		&& line[*end] != ';' && line[*end] != '|'
		&& line[*end] != '>' && line[*end] != '<')
	{
		if (line[*end] == '\\')
			(*end)++;
		if (line[*end] == '\'' || line[*end] == '\"')
			process_quotes(line, end);
		(*end)++;
	}
}

void	add_token(char *line, int start, int end, t_list **tokens)
{
	char	*token;

	if (end - start <= 0)
		return ;
	token = ft_substr(line, start, end - start);
	ft_lstadd_back(tokens, ft_lstnew(token));
}

int	check_redirects(char *line, int *end)
{
	int	res;

	res = line[*end] == '>' || line[*end] == '<';
	while (line[*end] == '>')
		(*end)++;
	while (line[*end] == '<')
		(*end)++;
	return (res);
}

int	get_fd(t_redirects *redirects)
{
	if (redirects->write_fd)
		return (redirects->write_fd);
	return (1);
}
