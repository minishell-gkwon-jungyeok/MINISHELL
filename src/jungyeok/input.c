/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 04:57:47 by jungyeok          #+#    #+#             */
/*   Updated: 2023/04/29 19:59:58 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	_heredoc(char *s, t_mini *c)
{
	char	*line;

	c->fd_in = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (c->fd_in < 0)
		return (1);
	dup2(c->fd_in, 0);
	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(s, line))
			break ;
		write(c->fd_in, line, ft_strlen(line));
		write(c->fd_in, "\n", 1);
		free(line);
	}
	return (0);
}

int	_input(char *s, t_mini *c)
{
	char	*se;

	c->fd_in = open(s, O_RDONLY);
	if (c->fd_in < 0)
	{
		write(2, "bash: ", 6);
		write(2, s, ft_strlen(s));
		write(2, ": ", 2);
		se = strerror(2);
		write(2, se, ft_strlen(se));
		write(2, "\n", 1);
		return (1);
	}
	dup2(c->fd_in, 0);
	return (0);
}

int	open_fd(t_command *command, t_mini *c)
{
	if (command[c->index].delimiter)
	{
		if (_heredoc(command[c->index].delimiter, c))
			return (1);
	}
	else if (command[c->index].input)
	{
		if (_input(command[c->index].input, c))
			return (1);
	}
	else if (c->index == 0)
		return (0);
	else
		dup2(c->pipe[2 * c->index], 0);
	if (command[c->index].output)
	{
		if (_output(command[c->index].output, c))
			return (1);
	}
	else if (command[c->index].output_append)
	{
		if (_output_append(command[c->index].output_append, c))
			return (1);
	}
	else if (c->index == c->ncmd - 1)
		return (0);
	else
		dup2(c->pipe[2 * c->index + 1], 1);
	return (0);
}
