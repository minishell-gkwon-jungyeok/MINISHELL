/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 05:23:43 by jungyeok          #+#    #+#             */
/*   Updated: 2023/04/29 17:27:23 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	_output(char *s, t_mini *c)
{
	c->fd_out = open(s, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (c->fd_out < 0)
	{
		write(2, "bash: ", 6);
		write(2, s, ft_strlen(s));
		write(2, ": Permission denied\n", 20);
		return (1);
	}
	return (0);
}

int	_output_append(char *s, t_mini *c)
{
	c->fd_out = open(s, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (c->fd_out < 0)
	{
		write(2, "bash: ", 6);
		write(2, s, ft_strlen(s));
		write(2, ": Permission denied\n", 20);
		return (1);
	}
	return (0);
}

void	close_fd(t_command *command, t_mini *c)
{
	if (command[c->index].delimiter)
		close(c->fd_in);
	else if (command[c->index].input)
		close(c->fd_in);
	if (command[c->index].output)
		close(c->fd_out);
	else if (command[c->index].output_append)
		close(c->fd_out);
}
