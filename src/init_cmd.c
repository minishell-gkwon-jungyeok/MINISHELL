/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:56:33 by edwin             #+#    #+#             */
/*   Updated: 2023/05/03 03:06:12 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_cmd(char *node, t_command *cmd)
{
	const static char	*string_table[] = {"<", ">", "<<", ">>"};
	int					i;
	int					at;
	int					end;
	int					len;
	int					tmp;
	char				*ret;

	if (!node)
		exit(1);
	i = -1;
	cmd->info = ft_calloc(sizeof(char *), 4);
	while (++i < 4)
		cmd->info[i] = ft_calloc(sizeof(char *), 1);
	i = 0;
	while (i < 4)
	{
		len = 0;
		at = ft_strnstr(node, string_table[i], ft_strlen(node));
		end = at;
		if (at != -1 && node[at
				+ ft_strlen((char *)string_table[i])] != string_table[i][0])
		{
			if (i < 2)
				end++;
			else
				end += 2;
			while (node[end] == ' ')
				end++;
			while (node[end + len] != ' ' && node[end + len] != 0 && node[end
					+ len] != '<' && node[end + len] != '>')
				len++;
			if (cmd->info[i][0])
			{
				ret = malloc(len + 2);
				ret[len] = 0;
				ret[0] = ' ';
				ft_memmove(ret + 1, node + end, len);
				cmd->info[i] = ft_strjoin(cmd->info[i], ret);
			}
			else
			{
				cmd->info[i] = ft_calloc(len + 1, 1);
				cmd->info[i][len] = 0;
				ft_memmove(cmd->info[i], node + end, len);
			}
			tmp = ft_strlen(&node[len]);
			ft_strlcpy(node + at, node + end + len, tmp);
			node[at] = 0;
		}
		else
		{
			if (!cmd->info[i][0])
				cmd->info[i] = NULL;
			i++;
		}
	}
	cmd->program = ft_split(node, ' ');
	free(node);
}

void	builtin_check(t_command *cmd, t_sys_info *info)
{
	const static char	*string_table[] = {"cd", "echo",
		"env", "exit", "export", "pwd", "unset"};
	int					i;
	int					j;

	i = 0;
	while (i < info->cmd_cnt)
	{
		if (!(cmd + i)->program)
		{
			i++;
			continue ;
		}
		j = 0;
		while (j < 7)
		{
			if (ft_strnstr((cmd + i)->program[0], string_table[j], ft_strlen((cmd + i)
						->program[0])) > -1)
						if (ft_strlen((cmd + i)->program[0]) == ft_strlen((char *)string_table[j]))
							(cmd + i)->built_in = true;
			j++;
		}
		i++;
	}
}
