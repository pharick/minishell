/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_edit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbelva <cbelva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 11:45:24 by cbelva            #+#    #+#             */
/*   Updated: 2021/03/17 11:45:38 by cbelva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	line_insert(char *str, char *buff, int i, int ret)
{
	int	j;

	j = ft_strlen(str);
	while (j >= i)
	{
		str[j + ret] = str[j];
		j--;
	}
	j = 0;
	while (j < ret)
	{
		str[i + j] = buff[j];
		j++;
	}
}

void	line_remove(char *str, int i)
{
	int	j;
	int	len;

	j = i;
	len = ft_strlen(str);
	while (j <= len)
	{
		str[j] = str[j + 1];
		j++;
	}
}
