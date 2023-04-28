/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 04:47:57 by jungyeok          #+#    #+#             */
/*   Updated: 2023/04/29 04:48:32 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	_err_hd(char *s)
{
	unlink(".heredoc");
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	return (1);
}

int	_heredoc(char *s, t_mini *c)
{
	int		fd;
	char	*line;

	fd = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (1);
	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(s, line))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	c->fd_out = open(".heredoc", O_RDONLY);
	if (c->fd_out < 0)
		return (_err_hd("heredoc error"));
	return (0);
}
