/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbelva <cbelva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 10:48:57 by cbelva            #+#    #+#             */
/*   Updated: 2021/04/07 14:04:46 by cbelva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_callback(int signal_number)
{
	(void)signal_number;
	ft_putstr("\nminishell$ ");
	g_environ.status = 255;
}

static void	sigquit_callback(int signal_number)
{
	(void)signal_number;
}

void	set_signals(void)
{
	signal(SIGINT, &sigint_callback);
	signal(SIGQUIT, &sigquit_callback);
	signal(SIGTERM, SIG_IGN);
}

void	reset_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	print_termsig(int status)
{
	if (status == COMMAND_TERMINATED)
		ft_putendl("");
	else if (status == COMMAND_QUIT)
		ft_putendl("Quit: 3");
}
