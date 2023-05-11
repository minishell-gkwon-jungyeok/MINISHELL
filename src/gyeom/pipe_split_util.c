/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 21:35:35 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/11 15:37:19 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	_3439(char c, int n[2])
{
	if (c == 34 && n[N34] == OUQ && n[N39] == OUQ)
		n[N34] = INQ;
	else if (c == 39 && n[N34] == OUQ && n[N39] == OUQ)
		n[N39] = INQ;
	else if (c == 34 && n[N34] == INQ && n[N39] == OUQ)
		n[N34] = OUQ;
	else if (c == 39 && n[N34] == OUQ && n[N39] == INQ)
		n[N39] = OUQ;
}

int	len_gyeom(char *s, int c)
{
	int	i;
	int	len;
	int	n[2];

	len = 0;
	n[N34] = OUQ;
	n[N39] = OUQ;
	i = 0;
	if (s)
	{
		while (s[i])
		{
			if (n[N34] == OUQ && n[N39] == OUQ && s[i] == c)
				len++;
			_3439(s[i], n);
			i++;
		}
	}
	return (len);
}

char	*strchr3439(char *s, int c)
{
	int	i;
	int	n[2];

	i = -1;
	n[N34] = OUQ;
	n[N39] = OUQ;
	while (s[++i])
	{
		if (n[N34] == OUQ && n[N39] == OUQ && s[i] == c)
			return (s + i);
		_3439(s[i], n);
	}
	return (NULL);
}

char	*strdup3439(char *s, int c)
{
	char	*ret;
	int		i;
	int		j;
	int		n[2];

	i = -1;
	n[N34] = OUQ;
	n[N39] = OUQ;
	while (s[++i])
	{
		if (n[N34] == OUQ && n[N39] == OUQ && s[i] == c)
			break ;
		_3439(s[i], n);
	}
	ret = ft_calloc(1, i + 1);
	j = -1;
	while (++j < i)
	{
		ret[j] = s[j];
	}
	return (ret);
}

char	**split_gyeom(char *s, int c)
{
	char	**ret;
	char	*cur;
	int		len;
	int		i;

	len = len_gyeom(s, c);
	ret = ft_calloc(8, len + 2);
	i = 0;
	cur = s;
	while (cur && i < len + 1)
	{
		ret[i] = strdup3439(cur, c);
		i++;
		cur = strchr3439(cur, c);
		while (cur && *cur == c)
			cur++;
	}
	while (len + 1 - i)
		free(ret[len-- + 1]);
	if (!ret[len + 1] && !ret[len][0])
	{
		free(ret[len]);
		ret[len] = NULL;
	}
	return (ret);
}
