/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:30:09 by jungyeok          #+#    #+#             */
/*   Updated: 2023/04/27 17:39:52 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct s_command{
	char **program;
}t_command;

char	*ft_strdup(char *s){
	int	size = strlen(s);
	char *ret = calloc(1, size + 1);
	for(int i=0;i<size;i++)
		ret[i] = s[i];
	return (ret);
}
*/

int	_cd(t_command *cmd)
{
	int	flag;
	int	ret;

	flag = 0;
	if (!cmd->program[1])
	{
		flag = 1;
		cmd->program[1] = ft_strdup("/Users/jungyeok");
	}
	ret = chdir(cmd->program[1]);
	if (ret)
	{
		write(1, "bash: cd: ", 10);
		write(1, cmd->program[1], ft_strlen(cmd->program[1]));
		write(1, ": No such file or directory\n", 28);
		return (1);
	}
	if (flag)
		free(cmd->program[1]);
	return (0);
}

/*
int main(int ac, char **av){
	char *pwd = getcwd(0, 0);
	printf("%s\n", pwd);
	free(pwd);

	t_command c;
	memset(&c, 0, sizeof(t_command));

	c.program = calloc(8, (ac + 1));
	for (int i = 0; i < ac; i++)
		c.program[i] = strdup(av[i]);

	_cd(&c);

	pwd = getcwd(0, 0);
	printf("%s\n", pwd);
	free(pwd);

	for (int i = 0; i < ac; i++)
		free(c.program[i]);
	free(c.program);
}
*/
