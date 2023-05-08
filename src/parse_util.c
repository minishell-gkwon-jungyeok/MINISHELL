/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:57:52 by edwin             #+#    #+#             */
/*   Updated: 2023/05/08 19:54:19 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pipe_cnt(char *line)
{
	int		cnt;
	char	quote;

	cnt = 0;
	while (*line)
	{
		while (*line == '\"' || *line == '\'')
		{
			quote = *line;
			line++;
			if (!*line)
				ft_err("not ended quotes");
			while (*line != quote)
				line++;
			line++;
		}
		if (*line == '|')
			cnt++;
		if (!*line)
			break ;
		line++;
	}
	return (cnt);
}

bool	get_env_val(char **s, char **env, char **target_val)
{
	int		i;
	int		find_idx;

	i = -1;
	while (env[++i])
	{
		if (bool_strncmp(env[i], *s, ft_strlen(*s)))
		{
			free(*s);
			find_idx = ft_getindex(env[i], (int) '=');
			find_idx++;
			*target_val = ft_strdup(&env[i][find_idx]);
			return (true);
		}
	}
	free(*s);
	return (false);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*ret;

	if (len == 0 || *s == 0 || ft_strlen(s) <= start)
		return (ft_strdup(""));
	if (ft_strlen(s) <= len + start)
		len = ft_strlen(s) - start;
	ret = (char *)malloc(len + 1);
	if (!ret)
		return (0);
	ft_memmove(ret, s + start, len);
	ret[len] = '\0';
	return (ret);
}

bool	bool_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*s1 && *s2)
	{
		if ((unsigned char)*s1 != (unsigned char)*s2)
		{
			if ((unsigned char)*s1 > (unsigned char)*s2)
				return (false);
			else if ((unsigned char)*s1 < (unsigned char)*s2)
				return (false);
		}
		s1++;
		s2++;
		n--;
		if (n == 0)
			return (true);
	}
	if ((unsigned char)*s1 > (unsigned char)*s2)
		return (false);
	else if ((unsigned char)*s1 < (unsigned char)*s2)
		return (false);
	return (true);
}

char	*replace_middle(char *s1, int start, int len, char *s2)
{
	char	*fnt;
	char	*mid;
	char	*end;
	char	*ret;

	fnt = (char *)malloc(start + 1);
	fnt[start] = 0;
	ft_memmove(fnt, s1, start);
	mid = (char *)malloc(ft_strlen(s2) + 1);
	mid[ft_strlen(s2)] = 0;
	ft_memmove(mid, s2, ft_strlen(s2));
	end = (char *)malloc(ft_strlen(s1) - (start + len) + 1);
	end[ft_strlen(s1) - (start + len)] = 0;
	ft_memmove(end, &s1[start + len], ft_strlen(s1) - (len + start));
	ret = (char *)malloc(ft_strlen(fnt) + ft_strlen(mid) + ft_strlen(end) + 1);
	ft_memmove(ret, fnt, ft_strlen(fnt));
	ft_memmove(ret + ft_strlen(fnt), mid, ft_strlen(mid));
	ft_memmove(ret + ft_strlen(fnt) + ft_strlen(mid), end, ft_strlen(end));
	ret[ft_strlen(fnt) + ft_strlen(mid) + ft_strlen(end)] = 0;
	free(fnt);
	free(mid);
	free(end);
	free(s1);
	free(s2);
	return (ret);
}
