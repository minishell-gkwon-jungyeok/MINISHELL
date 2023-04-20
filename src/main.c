/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:00:27 by gkwon             #+#    #+#             */
/*   Updated: 2023/04/21 01:12:05 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	validate_type(char *node, t_token *token)
{
	if (node[0] == '-')
		token->type = OPTION;
	if (node[0] == '|')
		token->type = PIPE;
	if (node[0] == '\'')
		token->type = OPTION;
	/* non-void function does not return a value */
	return (1);
}

t_token	*creat_token_list(char **nodes)
{
	int		i;
	t_token	*tmp;

	i = 0;
	while (nodes[i])
	{
		tmp = malloc(sizeof(t_token));
		validate_type(nodes[i], tmp);
	}
	/* non-void function does not return a value */
	return (tmp);
}

int	tokenize(char *line)
{
	char	**nodes;
	t_token	*token;

	nodes = ft_split(line, ' ');
	token = creat_token_list(nodes);
	while (*nodes)
	{
		printf("%s\n", *nodes);
		nodes++;
	}
	return (0);
}

int	display(t_command **command, char **envp)
{
	char	*line;

	command = NULL;
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
	display(&command, envp);
	_jungyeok(&command, envp);
	(void)av;
	return (0);
}
