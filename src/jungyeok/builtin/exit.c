/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 05:56:01 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/01 10:15:51 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

#define INDEX	0
#define SIGN	1
#define ABS		2
#define RETURN	3

/*
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct s_command{
	char **program;
}t_command;

int	ft_strlen(char *s){
	int	i = 0;
	if (s)
		while (s[i])
			i++;
	return (i);
}
*/

int	_atoi256(char *s)
{
	int				i[4];
	unsigned char	ret;

	i[INDEX] = 0;
	i[SIGN] = 1;
	if (s[i[INDEX]] == '-' || s[i[INDEX]] == '+')
	{
		if (s[i[INDEX]] == '-')
			i[SIGN] *= -1;
		i[INDEX]++;
	}
	i[ABS] = 0;
	while (s[i[INDEX]])
	{
		i[ABS] = i[ABS] * 10 + s[i[INDEX]] - '0';
		i[INDEX]++;
	}
	i[RETURN] = i[SIGN] * i[ABS];
	ret = (unsigned char)i[RETURN];
	return ((int)ret);
}

bool	_alpha(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (true);
		i++;
	}
	return (false);
}

void	__exit(t_command *cmd)
{
	write(1, "exit\n", 5);
	if (!cmd->program[1])
		exit(0);
	if (_alpha(cmd->program[1]))
	{
		write(1, "bash: exit: ", 12);
		write(1, cmd->program[1], ft_strlen(cmd->program[1]));
		write(1, ": numeric argument required\n", 28);
		exit(255);
	}
	if (cmd->program[2])
	{
		write(1, "bash: exit: too many arguments\n", 31);
		return ;
	}
	exit(_atoi256(cmd->program[1]));
}

/*
int	main(int ac, char **av){
	t_command c;
	memset(&c, 0, sizeof(t_command));
	
	c.program = calloc(8, ac + 1);
	for (int i = 0; i < ac; i++)
		c.program[i] = strdup(av[i]);

	__exit(&c);

	for (int i = 0; i < ac; i++)
		free(c.program[i]);
	free(c.program);
}
*/
