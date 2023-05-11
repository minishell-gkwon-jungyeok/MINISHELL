/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:56:33 by edwin             #+#    #+#             */
/*   Updated: 2023/05/11 16:36:00 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cut_and_paste(char **node, int i, int at, t_command *cmd)
{
	int		len;
	char	*ret;
	int		end;

	end = at + (1 + (i / 2));
	len = 0;
	while ((*node)[end] == ' ')
		end++;
	while ((*node)[end + len] != ' ' && (*node)[end + len] != 0 && (*node)[end
		+ len] != '<' && (*node)[end + len] != '>')
		len++;
	if (cmd->info[i][0])
	{
		ret = ft_calloc(len + 2, 1);
		ret[0] = ' ';
		ft_memmove(ret + 1, (*node) + end, len);
		cmd->info[i] = ft_strjoin(cmd->info[i], ret);
	}
	else
	{
		cmd->info[i] = ft_calloc(len + 1, 1);
		ft_memmove(cmd->info[i], (*node) + end, len);
	}
	while (end - at + len)
		(*node)[end + len-- - 1] = ' ';
}

void	init_cmd(char *node, t_command *cmd)
{
	static char	*string_table[] = {"<", ">", "<<", ">>"};
	int			i;
	int			at;

	cmd->info = ft_calloc(sizeof(char *), 5);
	i = -1;
	while (++i < 4)
		cmd->info[i] = ft_calloc(sizeof(char *), 1);
	i = 0;
	while (i < 4)
	{
		at = ft_strnstr(node, string_table[i], ft_strlen(node));
		if (at != -1
			&& node[at + ft_strlen(string_table[i])] != string_table[i][0]
			&& (node[at - 1] != 34 && node[at - 1] != 39)
			&& (node[at + 1] != 34 && node[at + 1] != 39))
			cut_and_paste(&node, i, at, cmd);
		else if (!cmd->info[i++][0])
			cmd->info[i - 1] = NULL;
	}
	cmd->cmd = ft_split(node, ' ');
	free(node);
}

void	builtin_check(t_command *cmd, int cmd_cnt)
{
	int			i;
	int			j;
	static char	*st[] = {
		"cd", "echo", "env", "exit", "export", "pwd", "unset"};

	i = 0;
	while (i < cmd_cnt)
	{
		if (!(cmd + i)->cmd || (cmd + i)->cmd[0] == 0)
		{
			i++;
			continue ;
		}
		j = -1;
		while (++j < 7)
			if (ft_strnstr((cmd + i)->cmd[0], st[j], ft_strlen((cmd
							+ i)->cmd[0])) > -1)
				if (ft_strlen((cmd + i)->cmd[0]) == ft_strlen(st[j]))
					(cmd + i)->built_in = true;
		i++;
	}
}
