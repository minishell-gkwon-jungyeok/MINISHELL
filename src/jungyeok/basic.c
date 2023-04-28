/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 05:51:55 by jungyeok          #+#    #+#             */
/*   Updated: 2023/04/29 04:44:59 by jungyeok         ###   ########.fr       */
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
