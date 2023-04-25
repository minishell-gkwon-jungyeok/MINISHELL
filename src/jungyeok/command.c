/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 21:13:15 by jungyeok          #+#    #+#             */
/*   Updated: 2023/04/25 12:36:26 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	command_access(char **path, t_command *cmd, t_mini *c)
{
	char	*d;
	char	*ret;

	while (*path)
	{
		d = ft_strjoin(*path, "/");
		ret = ft_strjoin(d, cmd->program[0]);
		free(d);
		if (!access(ret, 0))
		{
			c->cmd = ret;
			return (0);
		}
		free(ret);
		path++;
		
	}
	return (1);
}
