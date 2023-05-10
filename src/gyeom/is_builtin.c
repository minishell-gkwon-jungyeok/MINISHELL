/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 01:49:05 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/10 01:55:19 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	is_builtin(t_command **cmd, int ncmd)
{
	int	i;

	i = -1;
	while (++i < ncmd)
	{
		if (!ft_strncmp((*cmd)[i].cmd[0], "cd", 3)
			|| !ft_strncmp((*cmd)[i].cmd[0], "echo", 5)
			|| !ft_strncmp((*cmd)[i].cmd[0], "export", 7)
			|| !ft_strncmp((*cmd)[i].cmd[0], "env", 4)
			|| !ft_strncmp((*cmd)[i].cmd[0], "exit", 5)
			|| !ft_strncmp((*cmd)[i].cmd[0], "unset", 6)
			|| !ft_strncmp((*cmd)[i].cmd[0], "pwd", 4))
			(*cmd)[i].built_in = true;
	}
}
