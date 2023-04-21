/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edwin <edwin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:00:27 by gkwon             #+#    #+#             */
/*   Updated: 2023/04/21 17:08:57 by edwin            ###   ########.fr       */
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
	}
	return (cnt);
}

int	init_cmd(char *node, t_command *cmd)
{
	const static char	*string_table[] = {"<", ">", "<<", ">>"};
	int					i;
	int					at;
	int					end;
	int					len;

	i = -1;
	cmd->info = malloc(sizeof(char *) * 4);
	while (string_table[++i])
	{
		len = 0;
		at = ft_strnstr(node, string_table[i], ft_strlen(node));
		end = at;
		if (at)
		{
			if (i < 2)
				end++;
			else
				end += 2;
			while (node[end] != ' ')
				end++;
			while (node[end + len] != ' ' && !node[end + len])
				len++;
			cmd->info[i] = malloc(len + 1);
			cmd->info[i][len] = 0;
			ft_memmove(cmd->info[i], node[end], len);
			ft_strlcpy(node[at], node[end + len - 1], ft_strlen(&node[end + len
					- 1]));
			node[at + len] = 0;
		}
	}
	cmd->program = node;
}

int	tokenize(char *line)
{
	char		**nodes;
	t_token		*token;
	t_command	**cmd;
	int			i;

	i = -1;
	cmd = malloc(sizeof(t_command) * pipe_cnt(line) + 1);
	cmd[pipe_cnt(line)] = NULL;
	nodes = ft_split(line, '|');
	// handle quotes
	while (cmd[++i])
		init_cmd(nodes[i], cmd[i]);
	// check is built-in or not
	while (*nodes)
	{
		printf("%s\n", *nodes);
		nodes++;
	}
	return (0);
}

void	ft_free_command(t_command **command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (command[i]->input)
			free(command[i]->input);
		if (command[i]->output)
			free(command[i]->output);
		if (command[i]->delimiter)
			free(command[i]->delimiter);
		if (command[i]->output_append)
			free(command[i]->output_append);
		free(command[i]);
		i++;
	}
	free(command);
}

int	display(char **envp)
{
	t_command	*command;
	char		*line;

	//	int			number_of_pipe;
	while (1)
	{
		line = readline("bash-3.2$ ");
		tokenize(line /*, &number_of_pipe*/);
		//command = ft_calloc(number_of_pipe + 2, sizeof(t_command));
		//ft_memset(&command, 0, sizeof(command));
		printf("\n");
		//add_history();
		//excute();
		_jungyeok(&command, envp);
		//ft_free_command(&command);
	}
}

int	main(int ac, char **av, char **envp)
{
	if (ac != 1)
		return (1);
	//execve("/bin/bash", NULL, envp);
	display(envp);
	(void)av;
	return (0);
}
