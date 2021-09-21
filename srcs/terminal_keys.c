/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbelva <cbelva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 12:36:50 by cbelva            #+#    #+#             */
/*   Updated: 2021/04/12 11:14:13 by cbelva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tkey_left(size_t *i)
{
	if (*i > 0)
	{
		(*i)--;
		ft_putstr(tgetstr("le", NULL));
	}
	return (1);
}

int	tkey_right(size_t *i, char *str)
{
	if (*i < ft_strlen(str))
	{
		(*i)++;
		ft_putstr(tgetstr("nd", NULL));
	}
	return (1);
}

int	tkey_backspace(size_t *i, char *str)
{
	if (*i > 0)
	{
		line_remove(str, --(*i));
		ft_putstr(tgetstr("le", NULL));
		ft_putstr(tgetstr("dc", NULL));
	}
	return (1);
}

void	check_sigint(char *str, size_t *i)
{
	if (g_environ.status == 255)
	{
		str[0] = '\0';
		*i = 0;
		g_environ.status = 1;
	}
}

int	is_russian(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isprint(str[i]))
			return (1);
		i++;
	}
	return (0);
}
