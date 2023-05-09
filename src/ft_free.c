/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edwin <edwin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:58:35 by edwin             #+#    #+#             */
/*   Updated: 2023/05/09 15:44:09 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	_ft_free_command(t_command **cmd, t_sys_info *info, int i)
{
	while (++i < info->cmd_cnt)
	{
		if ((*cmd)[i].input)
			free((*cmd)[i].input);
		if ((*cmd)[i].output)
			free((*cmd)[i].output);
		if ((*cmd)[i].delimiter)
			free((*cmd)[i].delimiter);
		if ((*cmd)[i].output_append)
			free((*cmd)[i].output_append);
	}
}

void	ft_free_command(t_command **cmd, t_sys_info *info)
{
	int			i;
	int			j;

	i = 0;
	while (i < info->cmd_cnt)
	{
		j = 0;
		while ((*cmd + i)->cmd[j])
			if ((*cmd + i)->cmd[j])
				free((*cmd + i)->cmd[j++]);
		free((*cmd + i)->cmd);
		j = -1;
		while (++j < 4)
			if ((*cmd + i)->info[j])
				free((*cmd + i)->info[j]);
		free((*cmd + i)->info);
		i++;
	}
	_ft_free_command(cmd, info, -1);
	free(*cmd);
}

void	ft_exit(int return_val)
{
	printf("exit\n");
	exit(return_val);
}
