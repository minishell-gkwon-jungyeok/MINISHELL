/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 01:49:05 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/11 16:50:42 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	isprintable(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (false);
	while (s[i])
	{
		if (32 > s[i] || s[i] > 126)
			return (false);
		i++;
	}
	return (true);
}

void	change(char **s)
{
	char	*tmp1;
	char	*tmp2;
	int		i;

	tmp1 = *s;
	tmp2 = ft_realloc_c(tmp1, 127);
	ft_memset(tmp1, 0, ft_strlen(tmp1));
	tmp1 = tmp2;
	i = 0;
	while (!isprintable(tmp1) && i < 32)
	{
		tmp2 = ft_realloc_c(tmp1, i);
		i++;
		ft_memset(tmp1, 0, ft_strlen(tmp1));
		free(tmp1);
		tmp1 = tmp2;
	}
	*s = tmp1;
}

void	is_builtin(t_command **cmd, int ncmd)
{
	int	i;

	i = -1;
	while (++i < ncmd)
	{
		if (!isprintable((*cmd)[i].cmd[0]))
			change(&(*cmd)[i].cmd[0]);
		if (ft_strncmp((*cmd)[i].cmd[0], "cd", 3)
			|| ft_strncmp((*cmd)[i].cmd[0], "echo", 5)
			|| ft_strncmp((*cmd)[i].cmd[0], "export", 7)
			|| ft_strncmp((*cmd)[i].cmd[0], "env", 4)
			|| ft_strncmp((*cmd)[i].cmd[0], "exit", 5)
			|| ft_strncmp((*cmd)[i].cmd[0], "unset", 6)
			|| ft_strncmp((*cmd)[i].cmd[0], "pwd", 4))
			(*cmd)[i].built_in = true;
	}
}
