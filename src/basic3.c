/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:35:57 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/11 10:52:16 by jungyeok         ###   ########.fr       */
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
		if (s[i[IN]] != (char) c)
		{
			ret[i[JN]] = s[i[IN]];
			i[JN]++;
		}
		i[IN]++;
	}
	return (ret);
}

int	ft_strlen_c(char *s, int c)
{
	int	i;

	i = 0;
	if (s)
		while (s[i] && s[i] != (char) c)
			i++;
	return (i);
}

char	*ft_strdup_c(char *s, int c)
{
	int		i[2];
	char	*ret;

	if (!s)
		return (NULL);
	i[JN] = ft_strlen_c(s, c);
	ret = ft_calloc(1, i[JN] + 1);
	i[IN] = 0;
	while (s[i[IN]] && s[i[IN]] != (char) c)
	{
		ret[i[IN]] = s[i[IN]];
		i[IN]++;
	}
	return (ret);
}

void	free_split(char ***ret, int i)
{
	if (!(*ret)[i] && !(*ret)[i - 1][0])
	{
		free((*ret)[i - 1]);
		(*ret)[i - 1] = NULL;
	}
}

char	**split_jungyeok(char *s, int c)
{
	char	*cur;
	char	**ret;
	int		i[2];

	i[IN] = -1;
	i[JN] = 0;
	while (s[++i[IN]])
		if (s[i[IN]] == c)
			i[JN]++;
	ret = ft_calloc(8, i[JN] + 2);
	i[IN] = 0;
	cur = s;
	while (cur && i[IN] < i[JN] + 1)
	{
		ret[i[IN]] = ft_strdup_c(cur, c);
		i[IN]++;
		cur = ft_strchr(cur, c);
		while (cur && *cur == (char) c)
			cur++;
	}
	while (i[JN] + 1 - i[IN])
		free(ret[i[JN]-- + 1]);
	free_split(&ret, i[JN] + 1);
	return (ret);
}
