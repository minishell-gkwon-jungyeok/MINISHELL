/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jungyeok.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 22:57:18 by jungyeok          #+#    #+#             */
/*   Updated: 2023/04/21 02:34:48 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*_pat(char **env)
{
	while (ft_strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

void	_(t_command **command, int ncmd, t_mini *c)
{
	int	i;
	int	pipe[2];

	i = -1;
	while (++i < ncmd)
	{/*
		if (command[i]->input)
			
		else if (command[i]->delimiter)
			
		if (command[i]->output)
			
		else if (command[i]->output_append)
			
		_command(command[i]->command);
	*/}
	waitpid(-1, NULL, 0);
}

void	_jungyeok(t_command **command, char **envp)
{
	char	*pat;
	t_mini	c;

	ft_memset(&c, 0, sizeof(t_mini));
	while (command[c.ncmd])
	{
		if (!command[c.ncmd]->program[0])
		{
			write(2,"bash: syntax error near unexpected token `|'", 44);
			return ;
		}
	}
	pat = _pat(envp);
	ft_memset(&c, 0, sizeof(t_mini));
	c.path = ft_split(pat, ':');
	_(command, c.ncmd, &c);
	c.ncmd = -1;
	while (c.path[++c.ncmd])
		free(c.path[c.ncmd]);
	free(c.path);
}
