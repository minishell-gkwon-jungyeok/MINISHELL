/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 04:57:47 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/10 17:41:54 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <errno.h>

int	_error_jungyeok(char *s)
{
	char	*se;

	write(2, "bash: ", 6);
	write(2, s, ft_strlen(s));
	write(2, ": ", 2);
	se = strerror(errno);
	write(2, se, ft_strlen(se));
	write(2, "\n", 1);
	return (1);
}

int	_heredoc(char *s, t_mini *c)
{
	char	*line;

	c->hered = 1;
	c->fd_in = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (c->fd_in < 0)
		return (_error_jungyeok(s));
	while (1)
	{
		line = readline("heredoc> ");
		if (!ft_strcmp(s, line) || !line)
			break ;
		write(c->fd_in, line, ft_strlen(line));
		write(c->fd_in, "\n", 1);
		ft_memset(line, 0, ft_strlen(line));
		free(line);
	}
	close(c->fd_in);
	c->fd_in = open(".heredoc", O_RDONLY);
	dup2(c->fd_in, 0);
	c->hered = 0;
	return (0);
}

int	_input(char *s, t_mini *c)
{
	c->fd_in = open(s, O_RDONLY);
	if (c->fd_in < 0)
		return (_error_jungyeok(s));
	dup2(c->fd_in, 0);
	close(c->fd_in);
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
	else if (c->index != 0)
		dup2(c->pipe[(c->index - 1) << 1], 0);
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
	else if (c->index != c->ncmd - 1)
		dup2(c->pipe[(c->index << 1) + 1], 1);
	return (0);
}

void	fclose_pipe(t_mini *c, int index, int npip)
{
	int	save[2];
	int	i;

	save[0] = -1;
	save[1] = -1;
	if (index)
		save[0] = index - 1;
	if (index != npip)
		save[1] = index;
	i = 0;
	while (i < npip)
	{
		if (i != save[0] && i != save[1])
		{
			close(c->pipe[i << 1]);
			close(c->pipe[(i << 1) + 1]);
		}
		i++;
	}
}
