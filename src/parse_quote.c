/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 22:00:36 by edwin             #+#    #+#             */
/*   Updated: 2023/05/09 16:30:16 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_ended_quote(char **nodes, int i, int j)
{
	char	quote;

	if (*nodes == 0)
		return (1);
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
			j++;
		}
	}
	return (1);
}

void	parse_set_double_quotes(char *line, int quotes, int *result)
{
	if (quotes == 2)
	{
		*result = 0;
		*line = 7;
	}
	else if (quotes == 1)
		*result = 1;
	else
	{
		*result = 2;
		*line = 7;
	}
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
		parse_set_double_quotes(line, quotes, &result);
	return (result);
}

void	replace_env(char **line, char **env, int i)
{
	char		*target_env;
	char		*target_val;
	int			len;

	len = 0;
	while ((*line)[i + len + 1] && ((*line)[i + len + 1] != '$'
			|| (*line)[i + len + 1] != ' '))
		len++;
	target_env = ft_substr((*line), i + 1, len);
	if (get_env_val(&target_env, env, &target_val))
		(*line) = replace_middle((*line), i, len +1, target_val);
	else
		ft_err("no env exsist");
}

void	parse(char **line, char **env)
{
	char	**spl;
	int		quotes;
	int		len;
	int		i;

	dprintf(2, "line = %s\n", *line);
	len = 0;
	quotes = 0;
	if (*line)
	{
		i = -1;
		while ((*line)[++i])
		{
			quotes = parse_set_quotes(&(*line)[i], quotes);
			if ((quotes == 2 || quotes == 0) && (*line)[i] == '$')
				replace_env(line, env, i);
			else if (((*line)[i] == ';' || (*line)[i] == '\\') && quotes == 0)
				ft_err("not allowed character used");
		}
		spl = std_split(*line, 32);
		*line = ft_strdup(spl[0]);
		for (int j=0; spl[j]; j++)
			free(spl[j]);
		free(spl);
	}
}

/*
 * 	함수 5개 제한 때문에
 *	src/parse_quote_util.c로 옮겼어요
int	doller_parse_with_del_quot(t_command *cmd, t_sys_info *info, char **env)
{
	int	i;
	int	j;

	i = -1;
	while (++i < info->cmd_cnt)
	{
		j = -1;
		while (cmd[i].cmd[++j])
			parse(&cmd[i].cmd[j], env);
		j = -1;
		while (++j < 4)
			if (cmd[i].info[j])
				parse(&cmd[i].info[j], env);
	}
	return (1);
}
*/
