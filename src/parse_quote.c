/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 22:00:36 by edwin             #+#    #+#             */
/*   Updated: 2023/05/05 05:23:52 by gkwon            ###   ########.fr       */
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

void	parse(char **line, char **env)
{
	static int	quotes = 0;
	int			i;
	char		*target_env;
	int			len;

	i = -1;
	while ((*line)[++i])
	{
		len = 0;
		quotes = parse_set_quotes(&(*line)[i], quotes);
		if ((quotes == 2 || quotes == 0) && (*line)[i] == '$')
		{
			while ((*line)[i + len + 1] && ((*line)[i + len + 1] != '$'
					|| (*line)[i + len + 1] != ' '))
				len++;
			target_env = ft_substr((*line), i + 1, len - 1);
			if (get_env_val(&target_env, env))
				(*line) = replace_middle((*line), i, len + 1, target_env);
			else
				ft_err("no env exsist");
		}
		else if (((*line)[i] == ';' || (*line)[i] == '\\') && quotes == 0)
			ft_err("not allowed character used");
	}
	*line = *std_split(*line, 7);
}

int	doller_parse_with_del_quot(t_command *cmd, t_sys_info *info, char **env)
{
	int	i;
	int	j;

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
