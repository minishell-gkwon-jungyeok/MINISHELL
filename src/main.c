/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edwin <edwin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:00:27 by gkwon             #+#    #+#             */
/*   Updated: 2023/04/21 00:29:09 by edwin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

int	validate_type(char *node, t_token *token)
{
	if (node[0] == '-')
		token->type = OPTION;
	if (node[0] == '|')
		token->type = PIPE;
	if (node[0] == '\'')
		token->type = OPTION;
}

t_token	creat_token_list(char **nodes)
{
	int	i;
	t_token *tmp;

	i = 0;
	while (nodes[i])
	{
		tmp = malloc(sizeof(t_token));
		validate_type(nodes[i], tmp);
	}
}

int pipe_cnt(char *line)
{
	int cnt;

	cnt = 0;
	while (*line)
	{
		if (*line == '|')
			cnt++;
	}
	return (cnt);
}

int check_cmd(char *line, t_command **cmd)
{
	
}

int	tokenize(char *line)
{
	char	**nodes;
	t_token	*token;
	t_command *cmd;

	cmd = malloc(sizeof(t_command) * pipe_cnt(line) + 1);
	//nodes = ft_split(line, ' ');
	check_cmd();
	token = creat_token_list(nodes);
	while (*nodes)
	{
		printf("%s\n", *nodes);
		nodes++;
	}
	return (0);
}

int	display(char **envp)
{
	char	*line;

	(void)envp;
	while (1)
	{
		line = readline("bash-3.2$ ");
		tokenize(line);
		printf("\n");
		//add_history();
		//excute();
	}
}

int	main(int ac, char **av, char **envp)
{
	t_command	*command;

	if (ac != 1)
		return (1);
	//execve("/bin/bash", NULL, envp);
	display(envp);
	_jungyeok(&command, envp);
	return (0);
}
