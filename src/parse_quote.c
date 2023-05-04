/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 22:00:36 by edwin             #+#    #+#             */
/*   Updated: 2023/05/05 02:55:55 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_ended_quote(char **nodes, int i, int j)
{
	char	quote;

	i = -1;
	while (!strcmp(nodes[++i], ""))
	{
		j = 0;
		while (nodes[i][j])
		{
			if (nodes[i][j] == '\"' || nodes[i][j] == '\'')
			{
				while (nodes[i][j] == '\"' || nodes[i][j] == '\'')
				{
					quote = nodes[i][j++];
					if (!nodes[i][j])
						return (0);
					while (nodes[i][j++] != quote)
						if (!nodes[i][j])
							return (0);
				}
			}
			else
				j++;
		}
	}
	return (1);
}

//char	*ft_strjoin(char const *s1, char const *s2)
//{
//	char			*p;
//	unsigned int	s1l;
//	unsigned int	s2l;

//	s1l = ft_strlen(s1);
//	s2l = ft_strlen(s2);
//	p = (char *)malloc(s1l + s2l + 1);
//	if (!p)
//		return (NULL);
//	ft_memmove(p, s1, s1l);
//	ft_memmove(p + s1l, s2, s2l);
//	p[s1l + s2l] = 0;
//	return (p);
//}

char	*replace_middle(char *s1, int start, int len, char *s2)
{
	char			*fnt;
	char			*mid;
	char			*end;
	char			*ret;

	fnt = (char *)malloc(start + 1);
	fnt[start] = 0;
	ft_memmove(fnt, s1, start);
	mid = (char *)malloc(len + 1);
	mid[len] = 0;
	ft_memmove(mid, s2, len);
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

bool	get_env_val(char **s, char **env)
{
	int		i;
	char	*tmp;

	i = -1;
	while (env[++i])
	{
		if (bool_strncmp(env[i], *s, ft_strlen(*s)))
		{
			tmp = *s;
			free(tmp);
			tmp = ft_strchr(env[i], (int) '=');
			tmp++;
			*s = ft_strdup(tmp);
			return (true);
		}
	}
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

int	parse_set_quotes(char *line, int quotes)
{
	int	result;

	result = quotes;
	if (*line == '\'')
	{
		if (quotes == 1)
		{
			result = 0;
			*line = 7;
		}
		else if (quotes == 2)
			result = 2;
		else
		{
			result = 1;
			*line = 7;
		}
	}
	else if (*line == '\"')
	{
		if (quotes == 2)
		{
			result = 0;
			*line = 7;
		}
		else if (quotes == 1)
			result = 1;
		else
		{
			result = 2;
			*line = 7;
		}
	}
	return (result);
}

void parse(char **line, char **env)
{
	int		quotes = 0;
	int		i;
	char	*target_env;
	int		len;

	i = -1;
	while ((*line)[++i])
	{
		len = 0;
		quotes = parse_set_quotes(&(*line)[i], quotes);
		if ((quotes == 2 || quotes == 0) && (*line)[i] == '$')
		{
			while ((*line)[i + len + 1] && ((*line)[i + len + 1] != '$' || (*line)[i + len + 1] != ' '))
				len++;
			target_env = ft_substr((*line), i + 1, len - 1);
			if (get_env_val(&target_env, env))
				(*line) = replace_middle((*line), i, len + 1, target_env);
			else
			{
				printf("no env exsist\n");
				exit(1);
			}
		}
		else
		{
			if (((*line)[i] == ';' || (*line)[i] == '\\') && quotes == 0)
			{
				printf("not allowed character used\n");
				exit(1);
			}
		}
	}
	*line = *std_split(*line, 7);
}

int	doller_parse_with_del_quot(t_command *cmd, t_sys_info *info, char **env)
{
	int i;
	int j;
	//int quote;

	i = -1;
	while (++i < info->cmd_cnt)
	{
		j = -1;
		while (cmd[i].program[++j])
			parse(&cmd[i].program[j], env);
		j = -1;
		while (++j < 4)
			if (cmd[i].info[j])
				parse(&cmd[i].info[j], env);
	}
	return (1);
}
