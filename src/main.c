/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edwin <edwin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:00:27 by gkwon             #+#    #+#             */
/*   Updated: 2023/04/20 03:49:14 by edwin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strlen(char *str)
{
	int i;

	i = 0;
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

int	main(int ac, char **envp)
{
	if (ac != 1)
		return (1);
	//execve("/bin/bash", NULL, envp);
	display(envp);
	return (0);
}
