/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edwin <edwin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:58:35 by edwin             #+#    #+#             */
/*   Updated: 2023/04/29 22:04:57 by edwin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_command(t_command **cmd, t_sys_info *info)
{
	int			i;
	int			j;

	i = 0;
	while (i < info->cmd_cnt)
	{
		j = 0;
		if (cmd[i]->program[j])
			while (cmd[i]->program[j])
				free(cmd[i]->program[j++]);
		free(cmd[i]->program);
		j = -1;
		while (++j < 4)
			if (cmd[i]->info[j])
				free(cmd[i]->info[j]);
		free(cmd[i]->info);
		i++;
	}
	free(cmd);
}

void	ft_exit(int return_val)
{
	printf("exit\n");
	exit(return_val);
}
