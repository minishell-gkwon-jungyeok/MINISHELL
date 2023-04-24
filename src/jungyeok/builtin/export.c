/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 02:16:53 by jungyeok          #+#    #+#             */
/*   Updated: 2023/04/25 05:55:48 by jungyeok         ###   ########.fr       */
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
	char **program;
}t_command;

void	ft_putstr_fd(char *s, int fd){
	write(fd, s, strlen(s));
}

void	ft_putchar_fd(char c, int fd){
	write(fd, &c, 1);
}

void	*ft_calloc(int i, int j){
	return (calloc(i, j));
}

char	*ft_strdup(char *s){
	return (strdup(s));
}

int	ft_strcmp(char *s1, char *s2){
	return (strcmp(s1, s2));
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

int	_sorted_env(char ***env, int fd)
{
	int		i;
	int		j;
	char	**tmp;

	tmp = _tmp(env);
	i = -1;
	while (tmp[++i])
	{
		ft_putstr_fd("declare -x ", fd);
		j = 0;
		while (tmp[i][j] != '=')
			ft_putchar_fd(tmp[i][j++], fd);
		ft_putchar_fd(tmp[i][j++], fd);
		ft_putchar_fd('\"', fd);
		while (tmp[i][j])
			ft_putchar_fd(tmp[i][j++], fd);
		ft_putstr_fd("\"\n", fd);
	}
	i = -1;
	while (tmp[++i])
		free(tmp[i]);
	free(tmp);
	return (0);
}

void	_env_change(char *s, char ***env, int size)
{
	char	**ret;
	int		i;

	ret = ft_calloc(8, size + 2);
	i = -1;
	while ((*env)[++i])
	{
		ret[i] = ft_strdup((*env)[i]);
		free((*env)[i]);
	}
	ret[i] = ft_strdup(s);
	*env = ret;
}

int	_export(t_command *cmd, char ***env, int fd)
{
	int	i;
	int	j;
	int	size;

	if (!cmd->program[1])
		return (_sorted_env(env, fd));
	size = 0;
	while ((*env)[size])
		size++;
	i = 0;
	while (cmd->program[++i])
	{
		if ('0' <= cmd->program[i][0] && cmd->program[i][0] <= '9')
		{
			ft_putstr_fd("bash: export: `", fd);
			ft_putstr_fd(cmd->program[i], fd);
			ft_putstr_fd("': not a valid identifier\n", fd);
			continue ;
		}
		j = -1;
		while (cmd->program[i][++j])
			if (cmd->program[i][j] == '=')
				_env_change(cmd->program[i], env, size);
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
	c.program = calloc(8, ac + 1);
	for (int i = 0; i < ac; i++)
		c.program[i] = av[i];

	_export(&c, &d, 1);

	printf("\n\n    AFTER    \n\n\n");
	for (int i = 0; d[i]; i++)
		printf("i = %d %s\n", i, d[i]);

	for (int i = 0; d[i] ; i++)
		free(d[i]);
	free(d);
}
*/
