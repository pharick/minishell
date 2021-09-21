/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_history.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbelva <cbelva@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 12:07:08 by cbelva            #+#    #+#             */
/*   Updated: 2021/04/08 15:54:15 by cbelva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	place_line(char *str, char *line, size_t *i)
{
	size_t	len;

	len = ft_strlen(str);
	while (str[*i])
	{
		ft_putstr(tgetstr("nd", NULL));
		(*i)++;
	}
	while (len > 0)
	{
		ft_putstr(tgetstr("le", NULL));
		ft_putstr(tgetstr("dc", NULL));
		len--;
	}
	ft_strlcpy(str, line, 1024);
	*i = ft_strlen(str);
	ft_putstr(str);
}

static int	history_backward(t_list *history, char *str, size_t *i, ssize_t *n)
{
	t_list	*line;

	line = ft_lst_at(history, ++(*n));
	if (!line)
	{
		(*n)--;
		return (1);
	}
	place_line(str, line->content, i);
	return (1);
}

static int	history_forward(t_list *history, char *str, size_t *i, ssize_t *n)
{
	t_list	*line;

	if (*n == 0)
	{
		(*n)--;
		place_line(str, "", i);
		return (1);
	}
	if (*n < 0)
		return (1);
	line = ft_lst_at(history, --(*n));
	place_line(str, line->content, i);
	return (1);
}

int	tkey_history(t_list *history, int mode, size_t *i, char *str)
{
	static ssize_t	n;

	if (mode == RESET)
	{
		n = -1;
		return (1);
	}
	if (mode == BACKWARD)
		return (history_backward(history, str, i, &n));
	if (mode == FORWARD)
		return (history_forward(history, str, i, &n));
	return (1);
}
