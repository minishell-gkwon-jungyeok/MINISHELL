/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basicc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 07:13:12 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/11 16:51:02 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	if (!c)
	{
		while (s[i])
			i++;
		return (s + i);
	}
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return (s + i);
		i++;
	}
	return (NULL);
}

int	ft_getindex(char *s, int c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return (i);
		i++;
	}
	return (0);
}

bool	ft_cmd(t_command *command, t_mini *c)
{
	if (ft_strncmp(command[c->index].cmd[0], "export", 7)
		|| ft_strncmp(command[c->index].cmd[0], "exit", 5)
		|| ft_strncmp(command[c->index].cmd[0], "cd", 3)
		|| ft_strncmp(command[c->index].cmd[0], "unset", 6))
		return (true);
	return (false);
}
