/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbelva <cbelva@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 10:09:28 by etully            #+#    #+#             */
/*   Updated: 2021/04/09 19:54:50 by cbelva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(char **argv, t_redirects *redirects)
{
	char	path[MAX_PATH];
	int		fd;

	(void)argv;
	fd = get_fd(redirects);
	getcwd(path, MAX_PATH);
	ft_putendl_fd(path, fd);
	return (0);
}

int	echo_builtin(char **argv, t_redirects *redirects)
{
	int	nline;
	int	i;
	int	fd;

	fd = get_fd(redirects);
	if (!argv[1])
	{
		ft_putendl_fd("", fd);
		return (0);
	}
	nline = !argv[1] || ft_strcmp(argv[1], "-n");
	if (!argv[1] || ft_strcmp(argv[1], "-n"))
		i = 1;
	else
		i = 2;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], fd);
		if (argv[i + 1] && argv[i][0] != '\0')
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (nline)
		ft_putendl_fd("", fd);
	return (0);
}

static char	*cd_get_path(char *path)
{
	char	*res_path;
	char	*home;
	char	*oldpwd;

	if (!path || path[0] == '~')
		home = get_var("HOME");
	if (!path)
		res_path = ft_strdup(home);
	else if (path[0] == '-' && path[1] == '\0')
	{
		oldpwd = get_var("OLDPWD");
		if (!oldpwd)
		{
			ft_putendl_fd("OLDPWD not set", 2);
			return (NULL);
		}
		res_path = ft_strdup(oldpwd);
		ft_putendl(res_path);
	}
	else if (path[0] == '~')
		res_path = ft_strjoin(home, &path[1]);
	else
		res_path = ft_strdup(path);
	return (res_path);
}

int	cd(char **argv)
{
	char	*path;
	int		res;
	char	*old_path;

	path = cd_get_path(argv[1]);
	if (!path)
		return (1);
	res = chdir(path);
	old_path = ft_strdup(get_var("PWD"));
	set_var("OLDPWD", path);
	if (old_path)
		set_var("OLDPWD", old_path);
	free(path);
	free(old_path);
	path = (char *)malloc(MAX_PATH);
	getcwd(path, MAX_PATH);
	set_var("PWD", path);
	free(path);
	return (res);
}

int	exit_builtin(char **argv)
{
	g_environ.status = 0;
	if (argv[1])
		g_environ.status = ft_atoi(argv[1]);
	close(0);
	return (g_environ.status);
}
