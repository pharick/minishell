/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbelva <cbelva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 17:16:47 by cbelva            #+#    #+#             */
/*   Updated: 2021/04/09 13:46:29 by cbelva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_value(char *key)
{
	char	*value;

	if (!ft_strcmp(key, "?"))
		return (ft_itoa(g_environ.status));
	value = get_var(key);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

static int	insert_variable(char **token, int i, int end, char *key)
{
	char	*tmp;
	char	*tmp2;
	char	*value;
	int		value_len;

	value = get_value(key);
	tmp = *token;
	*token = ft_substr(tmp, 0, i);
	tmp2 = *token;
	*token = ft_strjoin(*token, value);
	free(tmp2);
	tmp2 = *token;
	*token = ft_strjoin(*token, &tmp[end]);
	free(tmp2);
	free(tmp);
	value_len = ft_strlen(value);
	free(value);
	return (value_len);
}

int	process_variables(char **token, int *i, int *j, int squote)
{
	int		start;
	int		end;
	char	*key;
	int		value_len;

	if (squote || (*token)[*j] != '$')
		return (0);
	start = (*j) + 1;
	end = start + 1;
	while (ft_isalnum((*token)[end]) || (*token)[end] == '_')
		end++;
	key = ft_substr(*token, start, end - start);
	if (ft_strcmp(key, ""))
	{
		value_len = insert_variable(token, *i, end, key);
		*i += value_len;
		*j = *i;
	}
	else
	{
		(*i)++;
		(*j)++;
	}
	free(key);
	return (1);
}

char	*get_prefix(char *file)
{
	char	*pref_file;

	if (!ft_strchr(file, '/'))
	{
		pref_file = path_prefix(file);
		if (!pref_file)
			return (NULL);
		return (pref_file);
	}
	open(file, O_RDONLY);
	return (ft_strdup(file));
}
