/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:10:59 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/10 23:49:19 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	odd_3439(char *s)
{
	int	i;
	int	n[2];

	n[N34] = OUQ;
	n[N39] = OUQ;
	i = -1;
	while (s[++i])
	{
		if (s[i] == 34 && n[N34] == OUQ && n[N39] == OUQ)
			n[N34] = INQ;
		else if (s[i] == 39 && n[N34] == OUQ && n[N39] == OUQ)
			n[N39] = INQ;
		else if (s[i] == 34 && n[N34] == INQ && n[N39] == OUQ)
			n[N34] = OUQ;
		else if (s[i] == 39 && n[N34] == OUQ && n[N39] == INQ)
			n[N39] = OUQ;
	}
	if (n[N34] == INQ || n[N39] == INQ)
		return (1);
	return (0);
}

int	check_3439(t_command **cmd, int ncmd)
{
	int	i;

	i = -1;
	while (++i < ncmd)
		if (odd_3439((*cmd)[i].unit))
			return (1);
	return (0);
}

int	free_units(t_command **cmd, int ncmd)
{
	int	i;

	i = -1;
	while (++i < ncmd)
		free((*cmd)[i].unit);
	free(*cmd);
	return (1);
}

int	pipe_split(char **line, t_command **cmd, t_mini *c)
{
	int		i;
	char	**tmp;

	tmp = split_gyeom(*line, 124);
	ft_memset(*line, 0, ft_strlen(*line));
	free(*line);
	i = 0;
	while (tmp[i])
		i++;
	c->ncmd = i;
	*cmd = ft_calloc(sizeof(t_command), c->ncmd + 1);
	i = -1;
	while (++i < c->ncmd)
	{
		(*cmd)[i].unit = ft_strdup(tmp[i]);
		free(tmp[i]);
	}
	free(tmp);
	if (check_3439(cmd, c->ncmd))
		return (free_units(cmd, c->ncmd));
	return (0);
}
