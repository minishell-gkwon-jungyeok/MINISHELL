/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 05:23:43 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/03 13:58:02 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <errno.h>

int	_output(char *s, t_mini *c)
{
	char	*se;

	c->fd_out = open(s, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (c->fd_out < 0)
	{
		write(2, "bash: ", 6);
		write(2, s, ft_strlen(s));
		write(2, ": ", 2);
		se = strerror(errno);
		write(2, se, ft_strlen(se));
		write(2, "\n", 1);
		return (1);
	}
	dup2(c->fd_out, 1);
	close(c->fd_out);
	return (0);
}

int	_output_append(char *s, t_mini *c)
{
	char	*se;

	c->fd_out = open(s, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (c->fd_out < 0)
	{
		write(2, "bash: ", 6);
		write(2, s, ft_strlen(s));
		write(2, ": ", 2);
		se = strerror(errno);
		write(2, se, ft_strlen(se));
		write(2, "\n", 1);
		return (1);
	}
	dup2(c->fd_out, 1);
	close(c->fd_out);
	return (0);
}

void	close_fd(t_command *command, t_mini *c)
{
	int	i;

	i = -1;
	while (++i < c->ncmd)
	{
		if (command[i].delimiter)
			close(c->fd_in);
		else if (command[i].input)
			close(c->fd_in);
		if (command[i].output)
			close(c->fd_out);
		else if (command[i].output_append)
			close(c->fd_out);
	}
}
