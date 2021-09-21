/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbelva <cbelva@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 15:18:29 by cbelva            #+#    #+#             */
/*   Updated: 2021/04/12 10:18:33 by cbelva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(char **argv, t_redirects *redirects)
{
	t_list	*node;
	int		fd;

	(void)argv;
	fd = get_fd(redirects);
	node = g_environ.env_lst;
	while (node)
	{
		print_env(node->content, fd);
		node = node->next;
	}
	return (0);
}

int	unset_cmp(t_env *data, char *data_ref)
{
	return (ft_strcmp(data->key, data_ref));
}

static int	check_var_name(char *name)
{
	int	i;

	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	export_builtin(char **argv, t_redirects *redirects)
{
	t_env	*var;
	int		i;

	if (!(argv[1]))
		return (env(argv, redirects));
	i = 1;
	while (argv[i])
	{
		var = parse_var(argv[i++]);
		if (!var || !check_var_name(var->key))
		{
			print_export_error(argv[i - 1], "export");
			if (var)
				free_env(var);
			continue ;
		}
		ft_lst_remove_if(&g_environ.env_lst, var->key, &unset_cmp,
			(void (*)(void *))(&free_env));
		ft_lstadd_front(&g_environ.env_lst, ft_lstnew(var));
	}
	if (var)
		set_var("_", var->key);
	else
		set_var("_", argv[i - 1]);
	return (0);
}

int	unset(char **argv)
{
	if (!(argv[1]))
	{
		ft_putendl_fd("unset: not enough arguments", 2);
		return (1);
	}
	if (!check_var_name(argv[1]))
	{
		print_export_error(argv[1], "unset");
		return (1);
	}
	ft_lst_remove_if(&g_environ.env_lst, argv[1],
		&unset_cmp, (void (*)(void *))(&free_env));
	return (0);
}
