/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbelva <cbelva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:54:32 by cbelva            #+#    #+#             */
/*   Updated: 2021/03/02 14:34:43 by cbelva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_tokens(t_list *tokens)
{
	t_list	*node;
	t_list	*next;

	node = tokens;
	while (node)
	{
		next = node->next;
		ft_lstdelone(node, free);
		node = next;
	}
}

void	free_command(t_command *command)
{
	free_tokens(command->tokens);
	free(command);
}

void	free_commands(t_list **commands)
{
	ft_lstclear(commands, (void (*)(void *))(&free_command));
}
