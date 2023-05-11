/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edwin <edwin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 02:16:53 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/11 11:34:15 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct s_command{
	char **cmd;
}t_command;

void	*ft_calloc(int i, int j){
	return (calloc(i, j));
}

char	*ft_strdup(char *s){
	return (strdup(s));
}

int	ft_strcmp(char *s1, char *s2){
	return (strcmp(s1, s2));
}

int	ft_strlen(char *s){
	return (strlen(s));
}
*/

void	ft_strswap(char **s1, char **s2)
{
	char	*tmp;

	tmp = NULL;
	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

char	**_tmp(char ***env)
{
	int		i;
	int		j;
	char	**ret;

	i = 0;
	while ((*env)[i])
		i++;
	ret = ft_calloc(8, i + 1);
	i = -1;
	while ((*env)[++i])
		ret[i] = ft_strdup((*env)[i]);
	i = -1;
	while (ret[++i])
	{
		j = i;
		while (ret[++j])
			if (ft_strcmp(ret[i], ret[j]) > 0)
				ft_strswap(ret + i, ret + j);
	}
	return (ret);
}

int	_sorted_env(char ***env)
{
	int		i;
	char	**tmp;

	tmp = _tmp(env);
	i = -1;
	while (tmp[++i])
	{
		write(1, "declare -x ", 11);
		_write(tmp[i]);
	}
	i = -1;
	while (tmp[++i])
		free(tmp[i]);
	free(tmp);
	return (0);
}

void	_env_change(char *s, char ***env, int size)
{
	char	**tmp;
	char	**ret;
	int		i;

	tmp = *env;
	if (!check_env(s, env))
		return ;
	while (tmp[size])
		size++;
	ret = ft_calloc(8, size + 2);
	i = 0;
	while (tmp[i])
	{
		ret[i] = ft_strdup(tmp[i]);
		ft_memset(tmp[i], 0, ft_strlen(tmp[i]));
		free(tmp[i]);
		i++;
	}
	free(tmp[i]);
	free(tmp);
	ret[i] = ft_strdup(s);
	*env = ret;
}

int	_export(t_command *cmd, char ***env)
{
	int	i;

	if (!cmd->cmd[1])
		return (_sorted_env(env));
	i = 0;
	while (cmd->cmd[++i])
	{
		if ('0' <= cmd->cmd[i][0] && cmd->cmd[i][0] <= '9')
		{
			write(2, "bash: export: `", 15);
			write(2, cmd->cmd[i], ft_strlen(cmd->cmd[i]));
			write(2, "': not a valid identifier\n", 26);
			continue ;
		}
		_env_change(cmd->cmd[i], env, 0);
	}
	return (0);
}

/*
int main(int ac, char **av, char **env){
	int size;
	for (size = 0; env[size]; size++);

	char **d = calloc(8, size + 1);
	for (int i = 0; i < size; i ++)
		d[i] = strdup(env[i]);

	printf("\n\n    BEFORE    \n\n\n");
	for (int i = 0; i < size; i ++)
		printf("i = %d %s\n", i, d[i]);

	t_command c;
	memset(&c, 0, sizeof(t_command));
	c.cmd = calloc(8, ac + 1);
	for (int i = 0; i < ac; i++)
		c.cmd[i] = av[i];

	_export(&c, &d);

	printf("\n\n    AFTER    \n\n\n");
	for (int i = 0; d[i]; i++)
		printf("i = %d %s\n", i, d[i]);

	for (int i = 0; d[i] ; i++)
		free(d[i]);
	free(d);
}
*/
