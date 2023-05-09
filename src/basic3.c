/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:35:57 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/09 17:55:55 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_realloc_c(char *s, int c)
{
	int		i[4];
	char	*ret;

	i[LEN] = ft_strlen(s);
	i[IN] = 0;
	i[NC] = 0;
	while (s[i[IN]])
	{
		if (s[i[IN]] == (char) c)
			i[NC]++;
		i[IN]++;
	}
	ret = ft_calloc(1, i[LEN] - i[NC] + 1);
	i[IN] = 0;
	i[JN] = 0;
	while (s[i[IN]])
	{
		if (s[i[IN]] !=c)
		{
			ret[i[JN]] = s[i[IN]];
			i[JN]++;
		}
		i[IN]++;
	}
	return (ret);
}
