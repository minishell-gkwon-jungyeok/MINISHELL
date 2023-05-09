/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _3439to7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 01:16:02 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/10 01:26:57 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	to7(char *s)
{
	int	i;
	int	n[2];

	n[N34] = OUQ;
	n[N39] = OUQ;
	i = 0;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
			check3439(n, s, i);
		i++;
	}
}

void	_3439to7(t_command **cmd, int ncmd)
{
	int		i;
	char	*tmp;

	i = -1;
	while (++i < ncmd)
	{
		tmp = (*cmd)[i].unit;
		to7(tmp);
		(*cmd)[i].unit = ft_realloc_c(tmp, 7);
		ft_memset(tmp, 0, ft_strlen(tmp));
		free(tmp);
	}
}
