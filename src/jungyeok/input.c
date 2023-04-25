/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:26:48 by jungyeok          #+#    #+#             */
/*   Updated: 2023/04/25 12:35:40 by jungyeok         ###   ########.fr       */
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

	fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (1);
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(s, line, ft_strlen(s) + 1))
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
