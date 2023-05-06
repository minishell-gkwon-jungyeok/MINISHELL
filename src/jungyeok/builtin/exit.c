/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edwin <edwin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 05:56:01 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/05 21:42:20 by edwin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

#define INDEX	0
#define SIGN	1
#define ABS		2
#define RETURNN	3

/*
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct s_command{
	char **cmd;
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
	i[RETURNN] = i[SIGN] * i[ABS];
	ret = (unsigned char)i[RETURNN];
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

void	__exit(t_command *cmd, t_mini *c)
{
	write(1, "exit\n", 5);
	if (!cmd->cmd[1])
	{
		c->dollar = 0;
		exit(0);
	}
	if (_alpha(cmd->cmd[1]))
	{
		write(2, "bash: exit: ", 12);
		write(2, cmd->cmd[1], ft_strlen(cmd->cmd[1]));
		write(2, ": numeric argument required\n", 28);
		c->dollar = 255;
		exit(255);
	}
	if (cmd->cmd[2])
	{
		c->dollar = 1;
		write(2, "bash: exit: too many arguments\n", 31);
		return ;
	}
	c->dollar = _atoi256(cmd->cmd[1]);
	exit(c->dollar);
}

/*
int	main(int ac, char **av){
	t_command c;
	memset(&c, 0, sizeof(t_command));
	
	c.cmd = calloc(8, ac + 1);
	for (int i = 0; i < ac; i++)
		c.cmd[i] = strdup(av[i]);

	__exit(&c);

	for (int i = 0; i < ac; i++)
		free(c.cmd[i]);
	free(c.cmd);
}
*/
