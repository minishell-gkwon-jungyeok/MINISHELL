/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edwin <edwin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:30:09 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/05 21:42:20 by edwin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct s_command{
	char **cmd;
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
	if (!cmd->cmd[1])
	{
		flag = 1;
		cmd->cmd[1] = ft_strdup("/Users/jungyeok");
	}
	ret = chdir(cmd->cmd[1]);
	if (ret)
	{
		write(1, "bash: cd: ", 10);
		write(1, cmd->cmd[1], ft_strlen(cmd->cmd[1]));
		write(1, ": No such file or directory\n", 28);
		return (1);
	}
	if (flag)
		free(cmd->cmd[1]);
	return (0);
}

/*
int main(int ac, char **av){
	char *pwd = getcwd(0, 0);
	printf("%s\n", pwd);
	free(pwd);

	t_command c;
	memset(&c, 0, sizeof(t_command));

	c.cmd = calloc(8, (ac + 1));
	for (int i = 0; i < ac; i++)
		c.cmd[i] = strdup(av[i]);

	_cd(&c);

	pwd = getcwd(0, 0);
	printf("%s\n", pwd);
	free(pwd);

	for (int i = 0; i < ac; i++)
		free(c.cmd[i]);
	free(c.cmd);
}
*/
