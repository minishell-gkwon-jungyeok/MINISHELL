/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:00:27 by gkwon             #+#    #+#             */
/*   Updated: 2023/04/26 06:33:48 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pipe_cnt(char *line)
{
	int	cnt;

	cnt = 0;
	while (*line)
	{
		if (*line == '|')
			cnt++;
		line++;
	}
	return (cnt);
}

void	init_cmd(char *node, t_command *cmd)
{
	const static char	*string_table[] = {"<", ">", "<<", ">>"};
	int					i;
	int					at;
	int					end;
	int					len;
	int					tmp;
	//char				*node;
	char				*ret;

	//node = ft_strdup(nod);
	i = -1;
	cmd->info = (char **)ft_calloc(sizeof(char *), 4);
	while (++i < 4)
		cmd->info[i] = (char *)ft_calloc(sizeof(char), 1);
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
			node[at + tmp] = 0;
		}
		else
			i++;
	}
	cmd->program = ft_split(node, ' ');
	//free(node);
}

void	builtin_check(t_command **cmd, t_sys_info *info)
{
	const static char	*string_table[] = {"cd", "echo",
		"env", "exit", "export", "pwd", "unset"};
	int					i;
	int					j;

	i = 0;
	while (i < info->cmd_cnt)
	{
		j = 0;
		while (j < 7)
		{
			if (ft_strnstr(cmd[i]->program[0], string_table[j], ft_strlen(cmd[i]
						->program[0])) > -1)
						if (ft_strlen(cmd[i]->program[0]) == ft_strlen((char *)string_table[j]))
							(*cmd)[i].built_in = true;
			j++;
		}
		i++;
	}
}

int	tokenize(char *line, t_command **cmd, t_sys_info *info)
{
	char	**nodes;
	int		i;
	int		j;

	i = -1;
	nodes = ft_split(line, '|');
	if (!nodes[0])
	{
		free(nodes);
		return (0);
	}
	while (++i < info->cmd_cnt)
		init_cmd(nodes[i], cmd[i]);
	builtin_check(cmd, info);
	i = -1;
	while (++i < info->cmd_cnt)
	{
		j = -1;
		while ((*cmd)[i].program[++j])
			printf("program is : %s\n", (*cmd)[i].program[j]);
		printf("is builtin : %d\n", (*cmd)[i].built_in);
		if ((*cmd)[i].info[0])
			printf("input is : %s\n", (*cmd)[i].info[0]);
		if ((*cmd)[i].info[1])
			printf("output is : %s\n", (*cmd)[i].info[1]);
		if ((*cmd)[i].info[2])
			printf("del is : %s\n", (*cmd)[i].info[2]);
		if ((*cmd)[i].info[3])
			printf("output_append is : %s\n", (*cmd)[i].info[3]);
	}
	free(nodes);
	// check is built-in or not
	return (0);
}

void	ft_free_command(t_command **tmp, t_sys_info *info)
{
	int			i;
	int			j;
	t_command	*cmd;

	cmd = *tmp;
	i = 0;
	while (i < info->cmd_cnt)
	{
		j = 0;
		if (cmd[i].program[j])
			while (cmd[i].program[j])
			{
				free(cmd[i].program[j]);
				cmd[i].program[j++] = 0;
			}
		free(cmd[i].program);
		cmd[i].program = 0;
		j = 0;
		while (j < 4)
		{
			if (cmd[i].info[j])
			{
				free(cmd[i].info[j]);
				cmd[i].info[j] = 0;
			}
			j++;
		}
		free(cmd[i].info);
		cmd[i].info = 0;
		i++;
	}
	free(cmd);
	cmd = 0;
}

int	display(t_sys_info *info, char ***envp)
{
	t_command	**cmd;
	char		*line;
	int			i;

	envp = NULL;
	while (1)
	{
		line = readline("bash-3.3$ ");
		if (ft_strncmp(line, "\0", 1))
		{
			info->cmd_cnt = pipe_cnt(line) + 1;
			cmd = ft_calloc(sizeof(t_command *), info->cmd_cnt);
			i = 0;
			while (i < info->cmd_cnt)
				cmd[i++] = ft_calloc(sizeof(t_command), 1);
			tokenize(line, cmd, info);
			add_history(line);
			//_jungyeok(&command, envp);
			ft_free_command(cmd, info);
			free(cmd);
		}
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_sys_info	info;

	if (ac != 1)
		return (1);
	//execve("/bin/bash", NULL, envp);
	display(&info, &envp);
	(void)av;
	return (0);
}
