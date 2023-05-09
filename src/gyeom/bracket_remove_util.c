/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bracket_remove_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 00:44:28 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/10 01:48:53 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check3439(int n[2], char *s, int i)
{
	if (s[i] == 34 && n[N34] == OUQ && n[N39] == OUQ)
	{
		s[i] = 7;
		n[N34] = INQ;
	}
	else if (s[i] == 39 && n[N34] == OUQ && n[N39] == OUQ)
	{
		s[i] = 7;
		n[N39] = INQ;
	}
	else if (s[i] == 34 && n[N34] == INQ && n[N39] == OUQ)
	{
		s[i] = 7;
		n[N34] = OUQ;
	}
	else if (s[i] == 39 && n[N34] == OUQ && n[N39] == INQ)
	{
		s[i] = 7;
		n[N39] = OUQ;
	}
}

char	*ft_strdup3439(char *s, int *len)
{
	char	*tmp;
	char	*ret;
	int		i;
	int		n[2];

	n[N34] = OUQ;
	n[N39] = OUQ;
	while (s[*len])
	{
		if (n[N34] == OUQ && n[N39] == OUQ
			&& (s[*len] == 32 || s[*len] == 60 || s[*len] == 62))
			break ;
		if (s[*len] == 34 || s[*len] == 39)
			check3439(n, s, *len);
		(*len)++;
	}
	tmp = ft_calloc(1, *len + 1);
	i = -1;
	while (++i < *len)
		tmp[i] = s[i];
	ret = ft_realloc_c(tmp, 7);
	free(tmp);
	return (ret);
}
