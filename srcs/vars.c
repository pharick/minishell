/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbelva <cbelva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 14:28:04 by cbelva            #+#    #+#             */
/*   Updated: 2021/04/09 13:47:21 by cbelva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_var(char *key, char *value)
{
	t_env	*var;

	var = (t_env *)malloc(sizeof(t_env));
	var->key = ft_strdup(key);
	var->value = ft_strdup(value);
	ft_lst_remove_if(&g_environ.env_lst, var->key, &unset_cmp,
		(void (*)(void *))(&free_env));
	ft_lstadd_front(&g_environ.env_lst, ft_lstnew(var));
}

char	*get_var(char *key)
{
	t_list	*node;
	char	*node_key;

	node = g_environ.env_lst;
	while (node)
	{
		node_key = ((t_env *)(node->content))->key;
		if (!ft_strcmp(node_key, key))
			return (((t_env *)(node->content))->value);
		node = node->next;
	}
	return (NULL);
}

char	*find_path(char **pathes, char *command)
{
	char	*res_path;
	char	*tmp;
	int		fd;
	int		i;

	i = 0;
	while (pathes[i])
	{
		tmp = ft_strjoin(pathes[i], "/");
		res_path = ft_strjoin(tmp, command);
		free(tmp);
		fd = open(res_path, O_RDONLY);
		if (fd > 0)
		{
			close(fd);
			errno = 0;
			return (res_path);
		}
		free(res_path);
		i++;
	}
	return (NULL);
}

char	*path_prefix(char *command)
{
	char	*path;
	char	**pathes;
	char	*res_path;

	path = get_var("PATH");
	if (!path)
		return (ft_strdup(command));
	pathes = ft_split(path, ':');
	res_path = find_path(pathes, command);
	if (res_path)
	{
		ft_free_tokens(pathes);
		return (res_path);
	}
	ft_free_tokens(pathes);
	errno = 0;
	return (NULL);
}

void	set_shlvl(void)
{
	int		shlvl;
	char	*new_shlvl;

	shlvl = ft_atoi(get_var("SHLVL"));
	new_shlvl = ft_itoa(shlvl + 1);
	set_var("SHLVL", new_shlvl);
	free(new_shlvl);
}
