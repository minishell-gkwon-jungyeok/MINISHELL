/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 22:00:36 by edwin             #+#    #+#             */
/*   Updated: 2023/05/04 16:24:16 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_line_quote(char *line)
{
	int	at;
	int	quotes;

	at = 0;
	quotes = 0;
	while (line[at])
	{
		quotes = parse_set_quotes(line[at], quotes);
		at++;
	}
	if (quotes != 0) // 닫히지 않은 따옴표 예외처리
	{
		printf("test exit: quotes error\n");
		exit(1);
	}
	return (0);
}

int	is_ended_quote(char **nodes)
{
	int	i;
	int	j;
	char quote;

	i = 0;
	while (!strcmp(nodes[i], ""))
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
		i++;
	}
	return (1);
}

char	*ft_strjoin_char(char const *s1, char s2)
{
	char	*ret;
	size_t	s1_len;

	if (!s1 && !s2)
		return (0);
	else if (!s1)
		return (ft_strdup(&s2));
	else if (!s2)
		return (ft_strdup((char *)s1));
	s1_len = ft_strlen((char *)s1);
	ret = (char *)malloc(sizeof(char) * (s1_len + 2));
	if (!ret)
		return (0);
	ft_strlcpy(ret, s1, s1_len + 1);
	ft_strlcpy(ret + s1_len, &s2, 2);
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

void parse(char *line)
{
	char	*str = NULL;
	int		quotes = 0;
	int		index = 0;
//	int		space = 1;
//	int		pipe = 0;
	int		i  =0 ;
	char	*tmp = NULL;

	while (*line)
	{
		quotes = parse_set_quotes(*line, quotes); // line 이 \' 혹은 \" 일때 예외 처리를 위해 구분
		if ((quotes == 2 || quotes == 0) && *line == '$')
		{
			while (line[i + 1] != '$' || line[i + 1] || line[i + 1] != ' ')
				i++;
			ft_strlcpy(tmp, &line[1], i + 1);
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
		line++;
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

int	doller_parse_with_del_quot(t_command *cmd, t_sys_info *info)
{
	int i;
	int j;
	//int quote;

	i = -1;
	while (++i < info->cmd_cnt)
	{
		j = -1;
		while (cmd[i].program[++j])
			parse(cmd[i].program[j]);
		j = -1;
		while (++j < 4)
			if (cmd[i].info[j])
				parse(cmd[i].info[j]);
	}
	return (1);
}
