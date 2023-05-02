/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 05:51:55 by jungyeok          #+#    #+#             */
/*   Updated: 2023/04/30 17:45:38 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 && s2)
	{
		while (s1[i])
		{
			if (s1[i] != s2[i])
				return ((unsigned char )s1[i] - (unsigned char)s2[i]);
			i++;
		}
	}
	else if (!s2 && s1)
		return ((unsigned char )s1[i]);
	else if (!s1 && s2)
		return ((unsigned char )s2[i]);
	else
		return (0);
	return ((unsigned char )s1[i] - (unsigned char)s2[i]);
}

char	*strjoin_jungyeok(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		j;

	ret = ft_calloc(1, ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	while (s1 && s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		ret[i + j] = s2[j];
		j++;
	}
	return (ret);
}
