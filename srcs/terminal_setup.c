/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbelva <cbelva@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:19:25 by cbelva            #+#    #+#             */
/*   Updated: 2021/04/11 14:57:50 by cbelva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_terminal(struct termios *term)
{
	struct termios	new_term;

	tcgetattr(0, term);
	new_term = *term;
	new_term.c_lflag &= ~(ECHO);
	new_term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &new_term);
	tgetent(NULL, getenv("TERM"));
	ft_putstr(tgetstr("ks", NULL));
	ft_putstr(tgetstr("im", NULL));
}

void	reset_terminal(struct termios *term)
{
	tcsetattr(0, TCSANOW, term);
	ft_putstr(tgetstr("ke", NULL));
	ft_putstr(tgetstr("ei", NULL));
}
