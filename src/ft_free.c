/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:58:35 by edwin             #+#    #+#             */
/*   Updated: 2023/05/10 23:29:33 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	_ft_free_command(t_command **cmd, t_mini *c, int i)
{
	while (++i < c->cmd_cnt)
	{
		if ((*cmd)[i].input)
		{
			ft_memset((*cmd)[i].input, 0, ft_strlen((*cmd)[i].input));
			free((*cmd)[i].input);
		}
		if ((*cmd)[i].output)
		{
			ft_memset((*cmd)[i].output, 0, ft_strlen((*cmd)[i].output));
			free((*cmd)[i].output);
		}
		if ((*cmd)[i].delimiter)
		{
			ft_memset((*cmd)[i].delimiter, 0, ft_strlen((*cmd)[i].delimiter));
			free((*cmd)[i].delimiter);
		}
		if ((*cmd)[i].output_append)
		{
			ft_memset((*cmd)[i].output_append, 0,
				ft_strlen((*cmd)[i].output_append));
			free((*cmd)[i].output_append);
		}
	}
}

void	ft_free_command(t_command **cmd, t_mini *c)
{
	int			i;
	int			j;

	i = -1;
	while (++i < c->cmd_cnt)
	{
		j = -1;
		while ((*cmd)[i].cmd[++j])
		{
			ft_memset((*cmd)[i].cmd[j], 0, ft_strlen((*cmd)[i].cmd[j]));
			free((*cmd)[i].cmd[j]);
		}
		free((*cmd)[i].cmd);
	}
	_ft_free_command(cmd, c, -1);
	free(*cmd);
}

void	ft_exit(int return_val)
{
	printf("exit\n");
	exit(return_val);
}
