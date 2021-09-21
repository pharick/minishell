/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbelva <cbelva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 12:02:00 by cbelva            #+#    #+#             */
/*   Updated: 2021/04/09 13:40:23 by cbelva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_fd(int *fd)
{
	if (!(*fd))
		return ;
	close(*fd);
	*fd = 0;
}

static int	open_file(t_redirects *redirects, char *token, char *path)
{
	if (!ft_strcmp(token, "<"))
	{
		close_fd(&(redirects->read_fd));
		return (redirects->read_fd = open(path, O_RDONLY));
	}
	if (!ft_strcmp(token, ">"))
	{
		close_fd(&(redirects->write_fd));
		return (redirects->write_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC,
				S_IREAD | S_IWRITE));
	}
	if (!ft_strcmp(token, ">>"))
	{
		close_fd(&(redirects->write_fd));
		return (redirects->write_fd = open(path, O_WRONLY | O_APPEND | O_CREAT,
				S_IREAD | S_IWRITE));
	}
	return (-1);
}

static int	process_redirect(t_redirects *redirects, t_list *token,
								t_list **next)
{
	int	status;

	status = open_file(redirects, token->content, (*next)->content);
	if (status < 0)
	{
		print_redirect_error((*next)->content, status);
		return (1);
	}
	*next = (*next)->next;
	ft_lstdelone(token->next, free);
	return (0);
}

int	process_redirects(t_list *tokens, t_redirects *redirects)
{
	t_list	*token;
	t_list	*prev;
	t_list	*next;

	prev = tokens;
	token = tokens->next;
	redirects->read_fd = 0;
	redirects->write_fd = 0;
	while (token)
	{
		if (ft_strcmp(token->content, "<") && ft_strcmp(token->content, ">")
			&& ft_strcmp(token->content, ">>"))
		{
			prev = token;
			token = token->next;
			continue ;
		}
		next = token->next;
		if (next && (process_redirect(redirects, token, &next)))
			return (1);
		ft_lstdelone(token, free);
		prev->next = next;
		token = next;
	}
	return (0);
}

void	connect_redirects(t_redirects *redirects)
{
	if (redirects->read_fd)
		dup2(redirects->read_fd, 0);
	if (redirects->write_fd)
		dup2(redirects->write_fd, 1);
}
