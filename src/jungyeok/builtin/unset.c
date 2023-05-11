/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:54:34 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/11 16:51:27 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
#include <stdlib.h>
#include <stdio.h>
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

void *ft_calloc(int i, int j){
	int n = i * j;
	if (!n)
		n = 1;
	char *d = malloc(n);
	for (int ii = 0; ii<n; ii++)
		d[ii] = '\0';
	return ((void *)d);
}

char *ft_strdup(char *s){
	char *d = ft_calloc(1, ft_strlen(s) + 1);
	for(int i=0;s[i];i++)
		d[i] = s[i];
	return (d);
}

void	ft_memset(void *s, int i, int size){
	char *d = s;
	for (int j = 0; j < size; j++)
		d[j] = (unsigned char)i;
}

int ft_strncmp(char *s1, char *s2, int n)
{
    int i;

    i = 0;
    while (i < n && (s1[i] || s2[i]))
    {   
        if (s1[i] != s2[i])
            return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
        i++;
    }   
    return (0);
}
*/

bool	_is_s(char *envi, char *cmdj)
{
	int	len;

	len = ft_strlen(cmdj);
	if (ft_strncmp(envi, cmdj, len) && envi[len] == '=')
		return (true);
	else
		return (false);
}

void	_kill_envi(char ***env, int i)
{
	int		j;
	char	*tmp;

	j = i;
	while ((*env)[j])
	{
		if ((*env)[j + 1])
		{
			tmp = (*env)[j];
			(*env)[j] = ft_strdup((*env)[j + 1]);
			ft_memset(tmp, 0, ft_strlen(tmp));
			free(tmp);
		}
		j++;
	}
	ft_memset((*env)[j - 1], 0, ft_strlen((*env)[j - 1]));
	free((*env)[j - 1]);
	(*env)[j - 1] = NULL;
}

int	_unset(t_command *cmd, char ***env)
{
	int	i;
	int	j;

	i = 0;
	while ((*env)[i])
	{
		j = 1;
		while (cmd->cmd[j])
		{
			if (_is_s((*env)[i], cmd->cmd[j]))
				_kill_envi(env, i);
			j++;
		}
		i++;
	}
	return (0);
}

/*
int	main(int size, char **av, char **env){
	if (size == 1)
		return (1);

	t_command c;
	ft_memset(&c, 0, sizeof(t_command));
	
	c.cmd = ft_calloc(8, size + 1);
	for (int i = 0; i < size; i++)
		c.cmd[i] = ft_strdup(av[i]);
	
	for (int i = 0; c.cmd[i]; i++)
		printf("c.cmd[%d] = %s\n", i, c.cmd[i]);

	size = 0;
	while (env[size])
		size++;
	
	char **d = ft_calloc(8, (size + 1));
	for (int i = 0; env[i]; i++)
		d[i] = ft_strdup(env[i]);

	printf("\n<<<< BEFORE >>>>\n\n");
	for (int i = 0; d[i]; i++)
		printf("%s\n", d[i]);

	_unset(&c, &d);

	printf("\n<<<< AFTER >>>>\n\n");
	for (int i = 0; d[i]; i++)
		printf("%s\n", d[i]);

	for(int i = 0; d[i]; i++)
		free(d[i]);
	free(d);
}
*/
