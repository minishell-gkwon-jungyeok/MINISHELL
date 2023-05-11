/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_change.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:36:30 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/11 16:50:35 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remake_unit(char **s, int cur, char *env, int len)
{
	char	*ret;
	int		i;
	int		j;
	int		k;
	int		env_len;

	env_len = ft_strlen(env);
	ret = ft_calloc(1, ft_strlen(*s) - (len + 1) + env_len + 1);
	i = -1;
	while (++i < cur)
		ret[i] = (*s)[i];
	j = -1;
	while (++j < env_len)
		ret[i + j] = env[j];
	k = 0;
	while ((*s)[i + len + 1 + k])
	{
		ret[i + j + k] = (*s)[i + len + 1 + k];
		k++;
	}
	ft_memset(*s, 0, ft_strlen(*s));
	free(*s);
	return (ret);
}

bool	if_in39(char *s, int cur)
{
	int	ii;
	int	i[2];

	ii = 0;
	i[N34] = OUQ;
	i[N39] = OUQ;
	while (ii < cur)
	{
		if (s[ii] == 34 && i[N34] == OUQ && i[N39] == OUQ)
			i[N34] = INQ;
		else if (s[ii] == 39 && i[N34] == OUQ && i[N39] == OUQ)
			i[N39] = INQ;
		else if (s[ii] == 34 && i[N34] == INQ && i[N39] == OUQ)
			i[N34] = OUQ;
		else if (s[ii] == 39 && i[N34] == OUQ && i[N39] == INQ)
			i[N39] = OUQ;
		ii++;
	}
	if (i[N39] == INQ)
		return (true);
	return (false);
}

bool	if_in34(char *s, int cur)
{
	int	ii;
	int	i[2];

	ii = 0;
	i[N34] = OUQ;
	i[N39] = OUQ;
	while (ii < cur)
	{
		if (s[ii] == 34 && i[N34] == OUQ && i[N39] == OUQ)
			i[N34] = INQ;
		else if (s[ii] == 39 && i[N34] == OUQ && i[N39] == OUQ)
			i[N39] = INQ;
		else if (s[ii] == 34 && i[N34] == INQ && i[N39] == OUQ)
			i[N34] = OUQ;
		else if (s[ii] == 39 && i[N34] == OUQ && i[N39] == INQ)
			i[N39] = OUQ;
		ii++;
	}
	if (i[N34] == INQ)
		return (true);
	return (false);
}

void	isenv(char **s, char **env)
{
	char	*tmp;
	int		i[3];

	if (!(*s))
		return ;
	tmp = ft_strchr(*s, 36);
	while (tmp)
	{
		tmp++;
		i[CURRENT] = tmp - *s;
		if (if_in39(*s, i[CURRENT]))
			continue ;
		i[JNDEX] = 0;
		while (env[i[JNDEX]])
		{
			i[LENGTH] = ft_strlen_c(env[i[JNDEX]], 61);
			if (ft_strncmp(tmp, env[i[JNDEX]], i[LENGTH])
				&& (if_in34(*s, i[CURRENT]) || tmp[i[LENGTH]] == 32
					|| (!if_in34(*s, i[CURRENT]) && !if_in39(*s, i[CURRENT]))))
				*s = remake_unit(s, tmp - 1 - *s,
						ft_strchr(env[i[JNDEX]], 61) + 1, i[LENGTH]);
			i[JNDEX]++;
		}
		tmp = ft_strchr(*s + i[CURRENT], 36);
	}
}

void	env_change(t_command **cmd, char **env, int ncmd)
{
	int		i;

	i = -1;
	while (++i < ncmd)
		isenv(&(*cmd)[i].unit, env);
}
