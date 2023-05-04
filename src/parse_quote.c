/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 22:00:36 by edwin             #+#    #+#             */
/*   Updated: 2023/05/05 00:10:03 by gkwon            ###   ########.fr       */
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*p;
	unsigned int	s1l;
	unsigned int	s2l;

	s1l = ft_strlen(s1);
	s2l = ft_strlen(s2);
	p = (char *)malloc(s1l + s2l + 1);
	if (!p)
		return (NULL);
	ft_memmove(p, s1, s1l);
	ft_memmove(p + s1l, s2, s2l);
	p[s1l + s2l] = 0;
	return (p);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
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

int	parse_set_quotes(char line, int quotes)
{
	int	result;

	result = quotes;
	if (line == '\'')
	{
		if (quotes == 1)
			result = 0;
		else if (quotes == 2)
			result = 2;
		else
			result = 1;
	}
	else if (line == '\"')
	{
		if (quotes == 2)
			result = 0;
		else if (quotes == 1)
			result = 1;
		else
			result = 2;
	}
	return (result);
}

void parse(char *line, char **env)
{
	char	*str = NULL;
	int		quotes = 0;
	int		index = 0;
	int		space = 1;
	int		pipe = 0;
	int		i;
	char	*find_env;
	int		len;

	i = -1;
	len = 0;
	while (line[++i])
	{
		quotes = parse_set_quotes(line[i], quotes); // line 이 \' 혹은 \" 일때 예외 처리를 위해 구분
		if (quotes == 2 && quotes == 0 && line[i] == '$')
		{
			while (line[i + 1] != '$' || line[i + 1] || line[i + 1] != ' ')
				len++;
			find_env = ft_substr(line, i + 1, len);
			if (_env_ehco(find_env, env, index))
			{
				front = ft_strdup();
				mid = ft_strjoin(&line[i], &env[index]);
				back = ft_strdup(line[i + len + 1]);
			}
			else
			{

			}
			free(find_env);
		}
		else
		{
			// 해석하지 않는 특수문자 예외처리
			if ((*line == ';' || *line == '\\') && quotes == 0)
			{
				printf("test exit: %c\n", *line);
				exit(1);
			}
		}
	}
	if (quotes != 0) // 닫히지 않은 따옴표 예외처리
	{
		printf("test exit: quotes error\n");
		exit(1);
	}
	if (str != NULL) // 마지막에 출력하지 않은 문자열이 남은 경우 처리
	{
		printf("[%d] : %s\n", index, str);
		free(str);
	}
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
			parse(cmd[i].program[j], env);
		j = -1;
		while (++j < 4)
			if (cmd[i].info[j])
				parse(cmd[i].info[j], env);
	}
	return (1);
}
