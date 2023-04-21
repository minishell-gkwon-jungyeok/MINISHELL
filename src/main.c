/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:00:27 by gkwon             #+#    #+#             */
/*   Updated: 2023/04/21 02:12:17 by jungyeok         ###   ########.fr       */
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
		tokenize(line/*, &number_of_pipe*/);
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
