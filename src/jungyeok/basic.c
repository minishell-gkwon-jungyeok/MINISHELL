/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 05:51:55 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/10 16:41:57 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	bool_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 && s2)
	{
		while (s1[i])
		{
			if (s1[i] != s2[i])
				return (true);
			i++;
		}
	}
	else if (!s2 && s1)
		return (true);
	else if (!s1 && s2)
		return (true);
	else
		return (false);
	return (true);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (*s1 == 2)
		return (0);
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

char	ft_abs(int a)
{
	if (a < 0)
		a *= -1;
	return ((char)a + '0');
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		s;
	int		l;
	int		nn;

	s = (n > 0) - (n < 0);
	l = (!s);
	nn = n;
	while (nn)
	{
		l++;
		nn /= 10;
	}
	ret = ft_calloc(1, (s < 0) + l + 1);
	if (s < 0)
		ret[0] = '-';
	else if (!s)
		ret[0] = '0';
	while (n)
	{
		ret[(s < 0) + --l] = ft_abs(n % 10);
		n /= 10;
	}
	return (ret);
}
