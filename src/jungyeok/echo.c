/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 22:29:59 by jungyeok          #+#    #+#             */
/*   Updated: 2023/04/21 22:51:13 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(t_command **command, t_mini *c, int fd)
{
	int	i;
	int	flag;

	flag = (!(ft_strncmp(command[c->index]->program[1], "-n\0", 3)));
	i = (flag) * 2 + (!flag);
	write(fd, s, ft_strlen(s));
	if (flag)
		write(2, "\n", 1);
}
