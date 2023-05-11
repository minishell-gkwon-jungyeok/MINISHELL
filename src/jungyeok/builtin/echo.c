/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:34:07 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/11 16:51:12 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	_env_echo(char *s, char **env, int *j)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(s, env[i], ft_strlen(s)))
		{
			*j = i;
			return (true);
		}
		i++;
	}
	return (false);
}

void	_env_write(int len, char *env)
{
	int	i;

	i = 0;
	while (env[len + i])
	{
		write(1, env + len + i, 1);
		i++;
	}
}

int	_echo(t_command *cmd, t_mini *c)
{
	int	i;
	int	flag;

	(void) c;
	if (ft_strcmp(cmd->cmd[0], "echo"))
		return (1);
	flag = 0;
	if (cmd->cmd[1] && ft_strncmp(cmd->cmd[1], "-n", 3))
		flag = 1;
	i = flag + 1;
	while (cmd->cmd[i])
	{
		write(1, cmd->cmd[i], ft_strlen(cmd->cmd[i]));
		if (cmd->cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	return (0);
}
