/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbelva <cbelva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:50:55 by cbelva            #+#    #+#             */
/*   Updated: 2021/03/08 11:14:21 by cbelva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_single_quotes(char *token, int *j, int *squote, int dquote)
{
	if (token[*j] == '\'' && !(*squote) && !dquote)
	{
		*squote = 1;
		(*j)++;
		return (1);
	}
	else if (token[*j] == '\'' && *squote && !dquote)
	{
		*squote = 0;
		(*j)++;
		return (1);
	}
	return (0);
}

static int	process_double_quotes(char *token, int *j, int squote, int *dquote)
{
	if (token[*j] == '\"' && !(*dquote) && !squote)
	{
		*dquote = 1;
		(*j)++;
		return (1);
	}
	else if (token[*j] == '\"' && *dquote && !squote)
	{
		*dquote = 0;
		(*j)++;
		return (1);
	}
	return (0);
}

static void	process_symbol(char **token, int *i, int *j, int *quotes)
{
	if ((*token)[*j] == '\\' && !(quotes[0]))
	{
		(*j)++;
		(*token)[(*i)++] = (*token)[(*j)++];
	}
	else if (process_single_quotes(*token, j, &quotes[0], quotes[1]))
		;
	else if (process_double_quotes(*token, j, quotes[0], &quotes[1]))
		;
	else if (process_variables(token, i, j, quotes[0]))
		;
	else
		(*token)[(*i)++] = (*token)[(*j)++];
}

static char	*process_token(char *token)
{
	char	*new;
	int		i;
	int		j;
	int		quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	i = 0;
	j = 0;
	while (token[j])
		process_symbol(&token, &i, &j, quotes);
	token[i] = '\0';
	new = ft_strdup(token);
	free(token);
	return (new);
}

void	process_tokens(t_list *tokens)
{
	t_list	*node;

	node = tokens;
	while (node)
	{
		node->content = process_token(node->content);
		node = node->next;
	}
}
