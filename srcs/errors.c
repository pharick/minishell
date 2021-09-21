/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbelva <cbelva@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 13:19:43 by cbelva            #+#    #+#             */
/*   Updated: 2021/04/11 16:03:53 by cbelva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(void)
{
	char	*str;

	if (!errno)
		return (0);
	g_environ.status = 1;
	str = strerror(errno);
	ft_putendl_fd(str, 2);
	return (1);
}

void	print_parser_error(char token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putchar_fd(token, 2);
	ft_putendl_fd("'", 2);
	g_environ.status = 258;
}

void	print_export_error(char *token, char *command)
{
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": not a valid identifier: `", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("'", 2);
}

void	print_command_error(char *command)
{
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putendl_fd(command, 2);
}

void	print_redirect_error(char *path, int status)
{
	if (status == -1)
	{
		ft_putstr_fd("minishell: no such file or directory: ", 2);
		ft_putendl_fd(path, 2);
	}
}
