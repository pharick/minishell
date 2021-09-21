/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbelva <cbelva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 17:05:38 by cbelva            #+#    #+#             */
/*   Updated: 2021/04/12 11:13:24 by cbelva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_keys(char *buff, char *str, size_t *i, t_list *history)
{
	if (!ft_strcmp(buff, tgetstr("kl", NULL)))
		return (tkey_left(i));
	else if (!ft_strcmp(buff, tgetstr("kr", NULL)))
		return (tkey_right(i, str));
	else if (buff[0] == 127)
		return (tkey_backspace(i, str));
	else if (!ft_strcmp(buff, tgetstr("ku", NULL)))
		return (tkey_history(history, BACKWARD, i, str));
	else if (!ft_strcmp(buff, tgetstr("kd", NULL)))
		return (tkey_history(history, FORWARD, i, str));
	else if (buff[0] == 4 || buff[0] == '\t' || buff[0] == '\b'
		|| !ft_strcmp(buff, "\E[1;2A")
		|| !ft_strcmp(buff, "\E[1;2B")
		|| !ft_strcmp(buff, "\E[1;2C")
		|| !ft_strcmp(buff, "\E[1;2D")
		|| is_russian(buff))
		return (1);
	return (0);
}

static int	if_eof(char *buff, char *str, struct termios *term)
{
	if (buff[0] == 4 && str[0] == '\0')
	{
		free(str);
		reset_terminal(term);
		return (1);
	}
	return (0);
}

static void	get_key(int *ret, char *buff)
{
	*ret = read(0, buff, 1024);
	buff[*ret] = '\0';
}

static void	get_line_init(char **str, t_list **history, size_t *i)
{
	*str = (char *)malloc(1024 * sizeof(char));
	tkey_history(*history, RESET, i, *str);
	(*str)[0] = '\0';
	*i = 0;
}

char	*get_line(t_list *history)
{
	char			buff[1024];
	char			*str;
	size_t			i;
	int				ret;
	struct termios	term;

	init_terminal(&term);
	get_line_init(&str, &history, &i);
	get_key(&ret, buff);
	while (ret >= 0 && ft_strcmp(buff, "\n"))
	{
		check_sigint(str, &i);
		if (if_eof(buff, str, &term))
			return (NULL);
		if (!check_keys(buff, str, &i, history))
		{
			line_insert(str, buff, i, ret);
			i += ret;
			ft_putstr(buff);
		}
		get_key(&ret, buff);
	}
	ft_putchar('\n');
	reset_terminal(&term);
	return (str);
}
