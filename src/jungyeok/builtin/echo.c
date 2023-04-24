/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:34:07 by jungyeok          #+#    #+#             */
/*   Updated: 2023/04/24 15:52:08 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	_echo(t_command *cmd, int fd)
{
	int	i;
	int	flag;

	if (ft_strncmp(cmd->program[0], "echo\0", 5))
		return (1);
	flag = 1;
	if (ft_strncmp(cmd->program[1], "-n\0", 3))
		flag = 0;
	i = flag + 1;
	ft_putstr_fd(cmd->program[i], fd);
	if (!flag)
		ft_putchar('\n', fd);
	return (0);
}
