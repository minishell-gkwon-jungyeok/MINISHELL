/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _32split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 01:31:54 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/11 15:36:41 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	really(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	if (s)
	{
		while (s[i])
		{
			if (s[i] != 32)
				return (0);
			i++;
		}
	}
	return (1);
}

void	_32check(t_command *cmd)
{
	char	*tmp;
	int		i;
	int		flag;

	flag = 0;
	if (!cmd->cmd[0] || cmd->cmd[0][0] == '\0' || cmd->cmd[0][0] == 32)
		flag = really(cmd->cmd[0]);
	if (flag == 1)
	{
		tmp = cmd->cmd[0];
		i = 0;
		while (cmd->cmd[i])
		{
			cmd->cmd[i] = cmd->cmd[i + 1];
			i++;
		}
		ft_memset(tmp, 0, ft_strlen(tmp));
		free(tmp);
	}
}

void	_32split(t_command **cmd, int ncmd)
{
	int	i;

	i = -1;
	while (++i < ncmd)
		(*cmd)[i].cmd = split_gyeom((*cmd)[i].unit, 32);
	i = -1;
	while (++i < ncmd)
		_32check((*cmd) + i);
}
