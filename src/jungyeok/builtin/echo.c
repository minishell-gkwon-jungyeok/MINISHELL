/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:34:07 by jungyeok          #+#    #+#             */
/*   Updated: 2023/04/27 17:38:17 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	_echo(t_command *cmd)
{
	int	i;
	int	flag;

	if (ft_strncmp(cmd->program[0], "echo\0", 5))
		return (1);
	flag = 1;
	if (ft_strncmp(cmd->program[1], "-n\0", 3))
		flag = 0;
	i = flag + 1;
	write(1, cmd->program[i], ft_strlen(cmd->program[i]));
	if (!flag)
		write(1, "\n", 1);
	return (0);
}
