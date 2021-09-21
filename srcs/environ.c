/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbelva <cbelva@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 13:09:59 by cbelva            #+#    #+#             */
/*   Updated: 2021/04/08 13:29:27 by cbelva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*parse_var(char *var)
{
	t_env	*env;
	int		start;
	int		end;

	env = (t_env *)malloc(sizeof(t_env));
	start = 0;
	end = start;
	while (var[end] && var[end] != '=')
		end++;
	if (!var[end])
	{
		free(env);
		return (NULL);
	}
	env->key = ft_substr(var, start, end - start);
	env->value = ft_strdup(&var[++end]);
	return (env);
}

t_list	*get_env_lst(char **environ)
{
	t_list	*env_lst;
	t_env	*env;
	int		i;

	i = 0;
	env_lst = NULL;
	while (environ[i])
	{
		env = parse_var(environ[i]);
		ft_lstadd_front(&env_lst, ft_lstnew(env));
		i++;
	}
	return (env_lst);
}

char	**env_to_array(t_list *env_lst)
{
	char	**array;
	t_list	*node;
	int		len;
	char	*tmp;
	int		i;

	len = ft_lstsize(env_lst);
	array = (char **)malloc((len + 1) * sizeof(char *));
	node = env_lst;
	i = 0;
	while (node)
	{
		array[i] = ft_strdup(((t_env *)(node->content))->key);
		tmp = array[i];
		array[i] = ft_strjoin(array[i], "=");
		free(tmp);
		tmp = array[i];
		array[i] = ft_strjoin(array[i], ((t_env *)(node->content))->value);
		free(tmp);
		node = node->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

void	free_env(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

void	print_env(t_env *env, int fd)
{
	ft_putstr_fd(env->key, fd);
	ft_putstr_fd("=", fd);
	ft_putendl_fd(env->value, fd);
}
